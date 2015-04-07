#include "main.h"

/*
#define SOLENOID_LEFT 2
#define SOLENOID_RIGHT 1
*/
/*
PINS

clearPin  - Shift-register clear (SRCLR) IC pin 8
		HIGH - Storage register data transfered to output buffer
		LOW  - Input shift register is cleared
SS  - register clock (RCK)  IC pin 12
		RISING EDGE - Data transfers through the storage resister
SCK  - Shift-register clock (SRCK) IC pin 13
		RISING EDGE - Data transfers through the shift register
MOSI   - Serial data in (SER IN) IC pin 3
enablePin - Output enable (G) IC pin 9
		HIGH - All data in output buffers is held low and drain outputs are off
		LOW  - Data from storage register is transparent to output buffer

*/

void setDataSPI(int preConNum, int mode);

void setup(){
	pinMode(SS, OUTPUT);
	pinMode(SCLK, OUTPUT);
    pinMode(MOSI, OUTPUT);

    SPCR &= ~(1<<DORD); // Set MSB first
    SPCR |= 1<<MSTR; // Set Master Mode
    SPCR |= 1<<SPE; // Enable SPI
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

void setDataSPI(int preConNum, int mode){
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