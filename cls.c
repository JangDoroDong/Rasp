#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

int main()
{
	printf("\033[2J"); //clear screen
	while(1)
	{
	wiringPiI2CWrite(dh, 00); // chanel 00 select (Light)
	int x = (wiringPiI2CRead(dh) * 80) / 255; // 0~ 255
    delay(100);
    
    wiringPiI2CWrite(dh, 01); // chanel select (Temp)
	int y = (wiringPiI2CRead(dh) * 24) / 255;
    delay(100);
 
	printf("/033[%d;%dH(%d,%d)", y, x, x, y);
	}	
	return 0;	
}


