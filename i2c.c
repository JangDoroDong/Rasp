#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

int main()
{
	int dh = wiringPiI2CSetup(0x48); // Device Reset
	
	int v1, v2, v3;
	float f1, f2, f3;
	
	while(1)
	{
	wiringPiI2CWrite(dh, 0); // chanel 00 select (Light)
	v1 = wiringPiI2CRead(dh); 
	f1 = (float)((v1/255.0)*5.0);
    delay(100);
    
    	wiringPiI2CWrite(dh, 1); // chanel select (Temp)
	v2 = wiringPiI2CRead(dh); 
	f2 = (float)((v2/255.0)*5.0);
    delay(100);
    
    	wiringPiI2CWrite(dh, 3); // chanel select (VR)
	v3 = wiringPiI2CRead(dh); 
	f3 = (float)((v3/255.0)*5.0);
	printf("ADC input level = %d %d %d(%4.1fV %4.1f  %4.1f)\n", v1, v2, v3, f1, f2, f3);
    delay(500);
	}
}
