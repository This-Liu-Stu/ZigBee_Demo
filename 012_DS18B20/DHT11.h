#ifndef __DHT11_H
#define __DHT11_H

#include "ioCC2530.h"
#include "Delay.h"

#define DATA_PIN P0_7 //DHT11Òý½Å

extern char DHT11_DATA[4];
extern char Temp_temp[];
extern char Humi_temp[];

void DHT_CMD();
void DHT11_Read();
void Get_DHT();

#endif

