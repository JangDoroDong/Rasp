#include <stdio.h>
#include <wiringPi.h>

#define wPi_PWM1 23

int PSC = 19;
int RANGE = 100;
int DUTY = 50;

enum {DO, Do, RE, Re, MI, FA, Fa, SOL, Sol, RA, Ra, SI};
int pitch[] = {262,277,294,311,330,349,370,392,415,440,466,494};
int range[12];
int song[] = {MI,DO,RE,MI,RE,DO,RE,SI,DO,RE,MI,RE,DO,SI, -1};
int rhythm[] = {4, 2, 1, 4, 2, 1, 2, 1, 2, 2, 2, 2, 2, 2};

void calcRange() 
{
    for (int i = 0; i < 12; i++) 
    {
        range[i] = 19200000 / (PSC * pitch[i]); // 19200000 is the base clock frequency
    }
}

void playSound(int um, int rhythm) {
    pwmSetClock(PSC); // Set prescaler
    pwmSetRange(range[um]); 
    pwmWrite(wPi_PWM1, range[um] / 2); 
    delay(rhythm * 100);
    pwmWrite(wPi_PWM1, 0); // Turn off PWM after the delay
}

int main() {
    wiringPiSetup();
    pinMode(wPi_PWM1, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    calcRange();
    
    for (int i = 0; song[i] != -1; i++) {
        playSound(song[i], rhythm[i]); 
    }
    
    return 0;
}
