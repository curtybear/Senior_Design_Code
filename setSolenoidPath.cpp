#include "main.h"

#define SOLENOID_LEFT 2
#define SOLENOID_RIGHT 1

void setSolenoidPath(int preConNum);

int latchPin = 2,
	clockPin = 3,
	dataPin = 4;

void setup(){
	
	/*
	Serial.begin(9600);

	while(!Serial){
		;
	}
	*/

	pinMode(latchPin, OUTPUT);
  	pinMode(clockPin, OUTPUT);
  	pinMode(dataPin, OUTPUT);
}

void loop(){
	int i = 1;
	for(i = 1; i < 7; i++){
		setSolenoidPath(i);
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

void setSolenoidPath(int preConNum){
	digitalWrite(latchPin, LOW);
	digitalWrite(clockPin, LOW);

	int word = 0;

	int sol_1, sol_2, sol_3, sol_4, sol_5;

	switch(preConNum){
		case 1:
			sol_1 = SOLENOID_LEFT;
			sol_2 = SOLENOID_LEFT;
			sol_4 = SOLENOID_LEFT;
			break;
		case 2:
			sol_1 = SOLENOID_LEFT;
			sol_2 = SOLENOID_LEFT;
			sol_4 = SOLENOID_RIGHT;
			break;
		case 3:
			sol_1 = SOLENOID_LEFT;
			sol_2 = SOLENOID_RIGHT;
			sol_5 = SOLENOID_LEFT;
			break;
		case 4:
			sol_1 = SOLENOID_LEFT;
			sol_2 = SOLENOID_RIGHT;
			sol_5 = SOLENOID_RIGHT;
			break;
		case 5:
			sol_1 = SOLENOID_RIGHT;
			sol_3 = SOLENOID_LEFT;
			break;
		case 6:
			sol_1 = SOLENOID_RIGHT;
			sol_3 = SOLENOID_RIGHT;
			break;
		default:
			// printf("not a valid preconcentrator number\n");
	}

	word = sol_1|(sol_2<<2)|(sol_3<<4)|(sol_4<<6)|(sol_5<<2);

    shiftOut(dataPin, clockPin, MSBFIRST, (word>>8);  
    shiftOut(dataPin, clockPin, MSBFIRST, word);  

    digitalWrite(latchPin, HIGH);
}