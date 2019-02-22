#include </home/pi/wiringPi/wiringPi/wiringPi.h>

#define  BUFSIZE  128

#define LedPin0 0
#define LedPin1 1
#define LedPin2 2
#define LedPin3 3
#define ButtonPin 4

//#define BuzzPin 5
#define BuzzPin 1


#include <lcd.h>


#define LCD_RS  25               //Register select pin
#define LCD_E   24               //Enable Pin
#define LCD_D4  23               //Data pin 4
#define LCD_D5  22               //Data pin 5
#define LCD_D6  21               //Data pin 6
#define LCD_D7  14

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include </home/pi/wiringPi.h>

#include <time.h>


int main(void)
{
	float temp;
	int i, j;
    int fd;
	int ret;
    int lcd;
    int x=1;
	char buf[BUFSIZE];
	char tempBuf[5];

	time_t seconds;
    int starttime,nowtime;
    float dlzkavaru;
    int etapaStarttime;

    int inputSecond;
    int hours1,minutes1,seconds1;
    int remainingSeconds;
    int secondsInHour = 60 * 60;
    int secondsInMinute = 60;

        	if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
            printf("setup wiringPi failed !");
            return 1;
}
            printf("linker LedPin0 : GPIO %d(wiringPi pin)\n",LedPin0); //when initialize wiring successfully,print message to screen
            printf("linker LedPin1 : GPIO %d(wiringPi pin)\n",LedPin1);
            printf("linker LedPin2 : GPIO %d(wiringPi pin)\n",LedPin2);
            printf("linker LedPin3 : GPIO %d(wiringPi pin)\n",LedPin3);

            pinMode(LedPin0, OUTPUT);
            pinMode(LedPin1, OUTPUT);
            pinMode(LedPin2, OUTPUT);
            pinMode(LedPin3, OUTPUT);
            pinMode(BuzzPin, OUTPUT);
            pinMode(ButtonPin, INPUT);

            pullUpDnControl(ButtonPin, PUD_UP);


            lcd = lcdInit (2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);



    seconds = time(NULL);
    starttime=seconds;
    printf("startovne sekundy: %ld\n", starttime);




     seconds = time(NULL);
    etapaStarttime=seconds;



	while(x == 1){ //while 1

			fd = open("/sys/bus/w1/devices/28-020f9177242c/w1_slave", O_RDONLY);


		if(-1 == fd){
			perror("open device file error");
			return 1;
		}

		while(1){
			ret = read(fd, buf, BUFSIZE);
			if(0 == ret){
				break;
			}
			if(-1 == ret){
				if(errno == EINTR){
					continue;
				}
				perror("read()");
				close(fd);
				return 1;
			}}

		for(i=0;i<sizeof(buf);i++){
			if(buf[i] == 't'){
				for(j=0;j<sizeof(tempBuf);j++){
					tempBuf[j] = buf[i+2+j];
				}}}

		temp = (float)atoi(tempBuf) /1000 ;
            printf("%.3f C\n",temp);
		close(fd);



    lcdPosition(lcd, 10, 0);
    lcdPrintf(lcd, "%.1f C", temp);

    if(temp<=24.0){
    digitalWrite(LedPin0, LOW); //led on
            delay(1);

    }

    else if(temp>24.0){

    digitalWrite(LedPin0, HIGH); //led off
    delay(100);

        x=0;
    }
} //koniec while 1

x=1;
    while(x == 1){ //while 2







digitalWrite(BuzzPin, 1); //led on
delay(100);
for(i=1;i < 32767; i++){

if(digitalRead(ButtonPin) == 0)
{
x=0;
}}

digitalWrite(BuzzPin, 0); //led off 1
delay(100);
for(i=1;i < 32767; i++){
if(digitalRead(ButtonPin) == 0)
{
x=0;
}}

digitalWrite(BuzzPin, 1); //led on
delay(100);
for(i=1;i < 32767; i++){

if(digitalRead(ButtonPin) == 0)
{
x=0;
}}

digitalWrite(BuzzPin, 0); //led off 2
delay(100);
for(i=1;i < 32767; i++){
if(digitalRead(ButtonPin) == 0)
{
x=0;
}}

digitalWrite(BuzzPin, 1); //led on
delay(100);
for(i=1;i < 32767; i++){

if(digitalRead(ButtonPin) == 0)
{
x=0;
}}

digitalWrite(BuzzPin, 0); //led off 3

for(i=1;i < 32767; i++){

if(digitalRead(ButtonPin) == 0)
{
x=0;
}}

for(i=1;i < 32767; i++){


if(digitalRead(ButtonPin) == 0)
{
x=0;
}}
delay(100);
for(i=1;i < 32767; i++){

if(digitalRead(ButtonPin) == 0)
{
x=0;
}}
delay(100);
for(i=1;i < 32767; i++){

if(digitalRead(ButtonPin) == 0)
{
x=0;
}}
delay(100);
for(i=1;i < 32767; i++){

if(digitalRead(ButtonPin) == 0)
{
x=0;
}}
delay(100);
for(i=1;i < 32767; i++){

if(digitalRead(ButtonPin) == 0)
{
x=0;
}}
delay(100);
for(i=1;i < 32767; i++){


if(digitalRead(ButtonPin) == 0)
{
x=0;
}}
delay(100);
for(i=1;i < 32767; i++){

if(digitalRead(ButtonPin) == 0)
{
x=0;
}}
delay(100);
for(i=1;i < 32767; i++){

if(digitalRead(ButtonPin) == 0)
{
x=0;
}}
delay(100);
for(i=1;i < 32767; i++){

if(digitalRead(ButtonPin) == 0)
{
x=0;
}}
delay(100);
for(i=1;i < 32767; i++){

if(digitalRead(ButtonPin) == 0)
{
x=0;
}}
delay(100);

    lcdPosition(lcd, 0, 1);
    lcdPrintf(lcd, "Pridaj slad");


} //koniec while 2


    lcdPosition(lcd, 0, 0);             //premazanie displaya
    lcdPrintf(lcd, "                ");
    lcdPosition(lcd, 0, 1);
    lcdPrintf(lcd, "                ");

x=1;
seconds = time(NULL);
etapaStarttime=seconds;
    while(x == 1){ //while 3

			fd = open("/sys/bus/w1/devices/28-020f9177242c/w1_slave", O_RDONLY);

		if(-1 == fd){
			perror("open device file error");
			return 1;
		}

		while(1){
			ret = read(fd, buf, BUFSIZE);
			if(0 == ret){
				break;
			}
			if(-1 == ret){
				if(errno == EINTR){
					continue;
				}
				perror("read()");
				close(fd);
				return 1;
			}}

		for(i=0;i<sizeof(buf);i++){
			if(buf[i] == 't'){
				for(j=0;j<sizeof(tempBuf);j++){
					tempBuf[j] = buf[i+2+j];
				}}}

		temp = (float)atoi(tempBuf) /1000 ;
            printf("%.3f C\n",temp);
		close(fd);



    lcdPosition(lcd, 10, 0);
    lcdPrintf(lcd, "%.1f C", temp);

    if(temp<=24.0){
    digitalWrite(LedPin0, LOW); //led on
            delay(100);
    }

    else if(temp>24.0){

    digitalWrite(LedPin0, HIGH); //led off
    delay(100);
    }

   //cas
   seconds = time(NULL);
    printf("aktualne sekundy: %ld\n", seconds);
    nowtime=seconds;

    dlzkavaru=nowtime-etapaStarttime;


  inputSecond=dlzkavaru;

  hours1 = (inputSecond/secondsInHour);

  remainingSeconds = inputSecond - (hours1 * secondsInHour);
  minutes1 = remainingSeconds/secondsInMinute;

  remainingSeconds = remainingSeconds - (minutes1*secondsInMinute);
  seconds1 = remainingSeconds;

  printf("cas od zaciatku etapy:  %d:%d:%d\n",hours1,minutes1,seconds1);



lcdPosition(lcd, 0, 0);
lcdPrintf(lcd, "%d:%d:%d",hours1,minutes1,seconds1);

//dlzkavaru v minutach
dlzkavaru=dlzkavaru/60;

if (1<=dlzkavaru){
	x=0;
	}



} //koniec while 3



}
