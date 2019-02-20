#include </home/pi/wiringPi/wiringPi/wiringPi.h>

#define  BUFSIZE  128

#define LedPin0 0
#define LedPin1 1
#define LedPin2 2
#define LedPin3 3

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


            lcd = lcdInit (2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);



    seconds = time(NULL);
    starttime=seconds;
    printf("startovne sekundy: %ld\n", starttime);




     seconds = time(NULL);
    etapaStarttime=seconds;



	while(x == 1){





		fd = open("/sys/bus/w1/devices/28-020f9177242c/w1_slave", O_RDONLY);
        //fd = open("/home/pi/Documents/123", O_RDONLY); //test
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
			}
		}

		for(i=0;i<sizeof(buf);i++){
			if(buf[i] == 't'){
				for(j=0;j<sizeof(tempBuf);j++){
					tempBuf[j] = buf[i+2+j];
				}
			}
		}

		temp = (float)atoi(tempBuf) /1000 ;

		printf("%.3f C\n",temp);

		close(fd);

		sleep(1);



    lcdPosition(lcd, 9, 0);
    lcdPrintf(lcd, "%.1f C", temp);

            if(temp<=24.0)
                    {
            digitalWrite(LedPin0, LOW); //led on
            delay(1);
            digitalWrite(LedPin1, LOW); //led on
            delay(500);
            digitalWrite(LedPin0, HIGH); //led off
            delay(1);
            digitalWrite(LedPin1, HIGH); //led off
            delay(100);


            printf("pod\n");

                  }

    else if(temp>24.0){

digitalWrite(LedPin0, HIGH); //led off
delay(100);
digitalWrite(LedPin1, HIGH); //led off
delay(100);
printf("nad\n");


    }



	seconds = time(NULL);
    printf("aktualne sekundy: %ld\n", seconds);
    nowtime=seconds;

    dlzkavaru=nowtime-starttime;
    //dlzkavaru=dlzkavaru/60;

    //printf("cas od zaciatku: %.0f\n", dlzkavaru);



  inputSecond=dlzkavaru;

  //5
  hours1 = (inputSecond/secondsInHour);
  //6
  remainingSeconds = inputSecond - (hours1 * secondsInHour);
  minutes1 = remainingSeconds/secondsInMinute;
  //7
  remainingSeconds = remainingSeconds - (minutes1*secondsInMinute);
  seconds1 = remainingSeconds;
  //8
  printf("cas od zaciatku:  %d:%d:%d\n",hours1,minutes1,seconds1);

lcdPosition(lcd, 0, 0);
lcdPrintf(lcd, "%d:%d:%d",hours1,minutes1,seconds1);


  	seconds = time(NULL);
    printf("aktualne sekundy: %ld\n", seconds);
    nowtime=seconds;

    dlzkavaru=nowtime-etapaStarttime;
    //dlzkavaru=dlzkavaru/60;

    //printf("cas od zaciatku: %.0f\n", dlzkavaru);



  inputSecond=dlzkavaru;

  //5
  hours1 = (inputSecond/secondsInHour);
  //6
  remainingSeconds = inputSecond - (hours1 * secondsInHour);
  minutes1 = remainingSeconds/secondsInMinute;
  //7
  remainingSeconds = remainingSeconds - (minutes1*secondsInMinute);
  seconds1 = remainingSeconds;
  //8
  printf("cas od zaciatku etapy:  %d:%d:%d\n",hours1,minutes1,seconds1);



lcdPosition(lcd, 0, 1);
lcdPrintf(lcd, "%d:%d:%d",hours1,minutes1,seconds1);


	if (10<=dlzkavaru){
	x=0;
	}

	}     //koniec while

	printf("koniec etapy");

	return 0;
}
