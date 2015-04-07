#include "main.h"

void runPump(int timeSec);

int pumpPin = 2;

void setup(){
	
	/*
	Serial.begin(9600);

	while(!Serial){
		;
	}
	*/

	pinMode(pumpPin, OUTPUT);
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