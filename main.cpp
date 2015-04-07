#include "main.h"

void setup(){
	
	Serial.begin(9600);

	while(!Serial){
		;
	}
}

void loop(){
	serialHandler();
}
	
int main(void)
{

	init();
	
	#if defined(USBCON)
	USBDevice.attach();
	#endif
	
	setup();
	while(1) {
		loop();
	}
	return 0;
}

void sample(int preConNum, int timeSec){
	setShiftRegisters(preConNum, SAMPLING);
	runPump(timeSec);
}

void evac(int preConNum, int timeLengthmSec, int timeStepmSec, double[] timeData, double[] tempData){
	int currentTime = 0, prevTime = 0;

	setShiftRegisters(preConNum, EVAC);
	turnOnHeaterPWM();

	currentTime = millis();
	prevTime = millis();

	for(i = 0; i<256; i++){
		setHeaterPWM(i);
		while(currentTime < prevTime+timeStepmSec){
			currentTime = millis();
		}
		timeData[i] = currentTime;
		tempData[i] = tempRead(preConNum);
		prevTime = millis();
	}
}

void turnOnHeaterPWM(void){
	TCCR1A = (1<<WGM10) | (1<<WGM11);
	TCCR1B = (1<<CS10) | (1<<WGM12) | (1<<WGM13);

	TCCR1A = (1<<COM1B0);
}

void setHeaterPWM(int value){
	OCR1B = value;
}

void turnOffHeaterPWM(void){
	TCCR1A = (0<<COM1B0);
}

double readTemp(int preConNum){
	int tempVolt1, tempVolt2;
	double resistance;

	setDEMUXChannel(preConNum, 0);
	tempVolt1 = analogRead(readPin);
	setDEMUXChannel(preConNum, 1);
	tempVolt2 = analogRead(readPin);
	resistance = (tempVolt1-tempVolt2)*5/1024/current;
	
	return resistance;
}

void runPump(int timeSec){
	double currentTime = 0, prevTime = 0;

	pinMode(pumpPin, HIGH);

	currentTime = millis();
	prevTime = millis();
	while(currentTime < (prevTime+timeSec*1000){
		currentTime = millis();
	}
	pinMode(pumpPin, LOW);
}

void setDEMUXChannel(int preConNum, int mode){
	int channel = 2*preConNum-2+mode;
	
	digitalWrite(controlPin1, (channel & 0b0001));
	digitalWrite(controlPin2, (channel & 0b0010)>>1);
	digitalWrite(controlPin3, (channel & 0b0100)>>2);
	digitalWrite(controlPin4, (channel & 0b1000)>>3);
}

void setShiftRegisters(int preConNum, int mode){
	uint16_t word = 0;

	if (mode==SAMPLING){}
		word = (!((preConNum-1>>2)&1)<<9)|(((preConNum-1>>2)&1)<<8)|(!((preConNum-1>>1)&1)<<7)|(((preConNum-1>>1)&1)<<6)|(21<<(preConNum%2));
	}

	else if (mode==EVAC){
		word = (1<<(preConNum+9));
	}

	digitalWrite(SS, LOW);

	SPDR = (uint8_t)(word>>8);
	loop_until_bit_is_set(SPSR, SPIF);
	SPDR = (uint8_t)(word);
	loop_until_bit_is_set(SPSR, SPIF);

	digitalWrite(SS, HIGH);
}

uint8_t * processSerialCommand (uint8_t *buffer){
    static uint8_t str[256];
    
    for (i=0;i<256;i++){
        str[i]=0;
    }
    
    switch (buffer[0]){
	/*
        case CMD_SETBAUDRATE:
            temp_32 = (uint32_t)((((uint32_t)buffer[2])<<24)|(((uint32_t)buffer[3])<<16)|(((uint32_t)buffer[4])<<8)|(((uint32_t)buffer[5])&0xff));
            if(setBaudRate(temp_32) == 1){str[0] = FN_FAILURE;}
            else{str[0] = FN_SUCCESS;}
            strIndex++;
            break;
			*/
	}
    str[strIndex] = 255;
    return str;
}    

void serialHandler()
{
  int byte;
  static uint8_t buf[256], *resp; 
  while(Serial.available() > 0) {
	byte = Serial.read();
    // DEBUG
	//Serial.write(byte);;
    if ((buf[1] == serialBufferIndex) && ((uint8_t)byte == 255)){
      serialBufferIndex = 0;
        for(i = 0; i<256; i++){
                buf[i] = 0;
            }
      return;
    }
    buf[serialBufferIndex] = (uint8_t)byte;
    serialBufferIndex++;
    if(serialBufferIndex > 1) {
        if(buf[1] == serialBufferIndex) {
            resp = processSerialCommand(buf);
            for(i = 0; i<=(int)sizeof(resp)+1; i++){
                Serial.write(resp[i]);
                resp[i] = 0;
            }
        }
	}
  }
}