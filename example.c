#include <stdio.h>

#include "thermocouple_sensor.h"

char str[20];

double voltage, temperature;
ThermocoupleType TC;

void main(void)
{
	TC = TC_TYPE_K;
	
	temperature = TC_CalculateTemperature(TC, 17.85); 
	
	sprintf(str, "Temperature is %f", temperature);
	puts(str);
	
	voltage = TC_CalculateVoltage(TC, -156);
	
	sprintf(str, "Voltage is %f", voltage);
	puts(str);	
}
