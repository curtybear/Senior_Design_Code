#include "main.h"

void setDEMUXChannel(int preConNum, int mode);

int readPin = A0;

int controlPin1 = 2,
	controlPin2 = 3,
	controlPin3 = 4,
	controlPin4 = 5;

double current = 0.200;

void setup(){
	
	/*
	Serial.begin(9600);

	while(!Serial){
		;
	}
	*/

	pinMode(controlPin1, OUTPUT);
	pinMode(controlPin2, OUTPUT);
	pinMode(controlPin3, OUTPUT);
	pinMode(controlPin4, OUTPUT);

}

void loop(){
	int i = 0, tempVolt1 = 0, tempVolt2 = 0;
	double resistance = 0;

	for(i = 0; i<20; i++){
		setDEMUXChannel(1, 0);
		tempVolt1 = analogRead(readPin);
		setDEMUXChannel(1, 1);
		tempVolt2 = analogRead(readPin);
		resistance = (tempVolt1-tempVolt2)*5/1024/current;
		Serial.Print(resistance);
	}
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

void setDEMUXChannel(int preConNum, int mode){
	int channel = 2*preConNum-2+mode;
	
	digitalWrite(controlPin1, (channel & 0b0001));
	digitalWrite(controlPin2, (channel & 0b0010)>>1);
	digitalWrite(controlPin3, (channel & 0b0100)>>2);
	digitalWrite(controlPin4, (channel & 0b1000)>>3);
}