
#include <stdio.h>
#include "thermocouple_sensor.h"

char str[20];
double voltage, temperature;
ThermocoupleType TC;

void main(void)
{
	// Set thermocouple type to Type K
	TC = TC_TYPE_K;    
	
	// Calculate temperature from voltage (17.85 mV)
	temperature = TC_CalculateTemperature(TC, 17.85); 
	
	sprintf(str, "Temperature is %f", temperature);
	puts(str);
	
	// Calculate voltage from temperature (-156 °C)
	voltage = TC_CalculateVoltage(TC, -156);
	
	sprintf(str, "Voltage is %f", voltage);
	puts(str);	
}
