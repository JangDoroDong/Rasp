#include <stdio.h>
#include <wiringPi.h>

#define TRIG 8
#define ECHO 9
#define Buz 28

double Dist()
{
	//TRIG Signal
	digitalWrite(TRIG, 1);
	delayMicroseconds(10);
	digitalWrite(TRIG, 0);
	delayMicroseconds(200);
	
	//Wait for Echo Signal
	while(digitalRead(ECHO) != 1); // Wait for Echo High 
	int t1 = micros(); // Get current Time (in micro-second)
	while(digitalRead(ECHO) != 0); // Wait for Echo Low
	int t2 = micros(); // Get end Time
	return (t2 - t1) * 0.017;
}

int main(int argc, char **argv)
{
	wiringPiSetup(); // Pin numbering method : wPi
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);
	pinMode(Buz, OUTPUT);
	
	for(;;)
	{
		printf("Distance : %f(cm) \n", Dist());
		delay(500);
	}
	return 0;
}

