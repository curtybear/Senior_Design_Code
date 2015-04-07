#ifndef _MAIN_H_
#define _MAIN_H_

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include <Arduino.h>
#include <pins_arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

enum msg_commands {
    CMD_SETBAUDRATE,
};


#define FN_SUCCESS 6
#define FN_FAILURE 9
#define FN_OTHER 2

#define SERIAL_BUFFER_SIZE 256 

#define SAMPLING 0
#define EVAC 1

#define SS 10
#define MOSI 11
#define MISO 12
#define SCK 13

int readPin = A0;

int pumpPin = 12;

int controlPin1 = 2,
	controlPin2 = 3,
	controlPin3 = 4,
	controlPin4 = 5;

int i = 0;

volatile int serialBufferIndex = 0;

double current = 0.200;

void sample(int preConNum, int timeSec);
void evac(int preConNum, int timeLengthmSec, int timeIntervalmSec, double* timeData, double* tempData);

void turnOnHeaterPWM(void);
void setHeaterPWM(int value);
void turnOffHeaterPWM(void);
void setDEMUXChannel(int preConNum, int mode);
void setShiftRegisters(int preConNum, int mode);
void runPump(int timeSec);
void readTemp(int preConNum, int timeLengthmSec, int timeIntervalmSec, double* timeData, double* tempData);

uint8_t *processSerialCommand(uint8_t *buffer);
void serialHandler(void);

#ifdef __cplusplus
}
#endif

#endif
