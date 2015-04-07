#include "main.h"

/*
PINS

clearPin  - Shift-register clear (SRCLR) IC pin 8
		HIGH - Storage register data transfered to output buffer
		LOW  - Input shift register is cleared
latchPin  - register clock (RCK)  IC pin 12
		RISING EDGE - Data transfers through the storage resister
clockPin  - Shift-register clock (SRCK) IC pin 13
		RISING EDGE - Data transfers through the shift register
dataPin   - Serial data in (SER IN) IC pin 3
enablePin - Output enable (G) IC pin 9
		HIGH - All data in output buffers is held low and drain outputs are off
		LOW  - Data from storage register is transparent to output buffer

*/

void runHeaterPWM(int maxVolt, int timeStepMicros);

void setup(){
	
	/*
	Serial.begin(9600);

	while(!Serial){
		;
	}
	*/

	pinMode(SS, OUTPUT);
	pinMode(SCLK, OUTPUT);
    pinMode(MOSI, OUTPUT);

  	runHeaterPWM(24, 1000);
}

void loop(){
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

void runHeaterPWM(int maxVolt, int timeStepMicros){
	int currentTime = 0, 
		prevTime = 0;

	double currentVolt = 0;

	TCCR2A = (1<<COM2B1) | (1<<WGM21) | (1<<WGM20);
	TCCR2B = (1<<CS22);

	prevTime = micros();
	currentTime = micros();
	while(currentVolt < maxVolt){
		while(currentTime < (prevTime+timeStepMicros){

			OCR2B++;
			currentVolt = OCR2B/256.0*24;

			currentTime = micros();

		}
		prevTime = currentTime;
	}

	TCCR2A = (0<<COM2B1);
}