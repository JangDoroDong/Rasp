#include <stdio.h>
#include <wiringPi.h>

#define wPi_22 22

int main(int n, char * s[])
{
	int period;
	
	if(n<2)
	{
		printf("usage : pwm1 [duty_rate(%%)]\n\n");
		return 1;
	}
	
	if(n == 3)
	{
		sscanf(s[2], "%d", &period);
	}
	else
	{
		period = 10;
	}
	
	int dr, drl, drh; // duty rate
	sscanf(s[1], "%d", &dr);
	drh = (dr * period) / 100;
	drl = period - drh;
	
	wiringPiSetup(); // wPi Pin number
	
	pinMode(wPi_22, OUTPUT);
	
	for(int i=0; i<500; i++)
	{
		digitalWrite(wPi_22, 1);
		delay(drh);
		digitalWrite(wPi_22, 0);
		delay(drl);
	}
	return 0;
}
