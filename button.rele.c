#include <wiringPi.h>
#include <stdio.h>

#define LedPin 5
#define ButtonPin 4

int main(void)

{

if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen

printf("setup wiringPi failed !");

return 1;

}

pinMode(LedPin, OUTPUT);
pinMode(ButtonPin, INPUT);

pullUpDnControl(ButtonPin, PUD_UP); //pull up to 3.3V,make GPIO1 a stable level
while(1)

{

digitalWrite(LedPin, 0);
if(digitalRead(ButtonPin) == 0)

{
delay(1000);
//indicate that button has pressed down
digitalWrite(LedPin, 1); //led on
delay(100);
digitalWrite(LedPin, 0); //led on
delay(100);
digitalWrite(LedPin, 1); //led on
delay(100);
digitalWrite(LedPin, 0); //led on
delay(100);
digitalWrite(LedPin, 1); //led on
delay(100);
digitalWrite(LedPin, 0); //led on


}

}

return 0;
}
