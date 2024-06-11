#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define RED 	8
#define GREEN 	9
#define YELLOW 	7
#define SW 		2
#define SW2		5

int mode = 0;
int intv = 0;
int tim; // delay time interval(ms)
int ps[40]; // ps(pin state) : default 0, pin number : 40

void Toggle(int pin)
{
	ps[pin] = !ps[pin];
	digitalWrite(pin,ps[pin]);
}

void gpioisr2()
{
	digitalWrite(RED, 0);
	digitalWrite(YELLOW, 0);
	digitalWrite(GREEN, 0);
	printf("LED OFF\n");
	exit(0);
}

void gpioisr()
{
	if(++intv > 8) intv = 0;
	printf("GPIO interrupt occured...\n");
}


int main()
{
	wiringPiSetup();	// Pin number use case (wPi)
	pinMode(RED, OUTPUT); 
	pinMode(GREEN, OUTPUT);
	pinMode(YELLOW, OUTPUT);
	pinMode(SW, INPUT); //Switch 
	wiringPiISR(SW, INT_EDGE_FALLING, gpioisr); // registration GPIO ISR
	wiringPiISR(SW2, INT_EDGE_FALLING, gpioisr2);
	
	for(;;) // while(1)
	{ 
		tim = (9-intv) * 100;
		if(mode)
		{
			Toggle(RED);	delay(tim);
			Toggle(GREEN);	delay(tim);
			Toggle(YELLOW);	delay(tim);
		}
		else
		{
			Toggle(YELLOW);	delay(tim);
			Toggle(GREEN);	delay(tim);
			Toggle(RED);	delay(tim);
		}
	}
	return 0;
}
