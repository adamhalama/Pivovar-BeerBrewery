#define  BUFSIZE  128

#define LedPin0 0
#define LedPin1 1

#define ButtonPin 4
#define ButtonPin1 28 // na dalsie tlacidla
#define ButtonPin2 29 // na dalsie tlacidla

#define BuzzPin 5

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
#include <wiringPi.h>

#include <time.h>

int zahriev(int t;);
int udrztRmut(int t, int c);
int udrztChmel(int t, int c);
int peepanieSlad();
int peepanieChmel();
float teplota();
int vysladzanie(int t);
int NastavenieTeplotyCasu(int vstup, int CasORteplota);

float temp;
int lcd;
int Tx;
int Txi;
int TxHlas;
int rmutStarttime;

int iSlad;
int iChmel;

int iTeplota=-1;
int iCas=0;
int iChmelovar=0;

int casChmelovar1;
int casChmelovar2;
int casChmelovar3;
int casChmelovar4;
int celkovyCasChmelovar;

    int t0=60;
    int t1=22, c1=0;
    int t2=22, c2=0;
    int t3=22, c3=0;
    int t4=22, c4=0;
    int t5=22, c5=0;

    int cht1=100, chc1=10;
    int cht2=100, chc2=10;
    int cht3=100, chc3=10;
    int cht4=100, chc4=10;
    int cht5=100, chc5=10;

int main(void)
{
	time_t seconds;
	int nowtime;
	int dlzkavaru;
    int x=1;
    int starttime;


    int inputSecond;
    int hours1,minutes1,seconds1;
    int remainingSeconds;
    int secondsInHour = 60 * 60;
    int secondsInMinute = 60;

    //tx teplota v stupnoch C
    //cx cas v minutach



    iSlad=0;
    iChmel=0;

    int vstup = 0;




        	if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
            printf("setup wiringPi failed !");
            return 1;
    }
            printf("linker LedPin0 : GPIO %d(wiringPi pin)\n",LedPin0); //when initialize wiring successfully,print message to screen
            printf("linker LedPin1 : GPIO %d(wiringPi pin)\n",LedPin1);


            pinMode(LedPin0, OUTPUT);
            pinMode(LedPin1, OUTPUT);
            pinMode(BuzzPin, OUTPUT);
            pinMode(ButtonPin, INPUT);
            pinMode(ButtonPin1, INPUT);
            pinMode(ButtonPin2, INPUT);

            pullUpDnControl(ButtonPin, PUD_UP);
            pullUpDnControl(ButtonPin1, PUD_UP);
            pullUpDnControl(ButtonPin2, PUD_UP);

            lcd = lcdInit (4, 20, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);


    digitalWrite(LedPin0, HIGH); //rele off
    digitalWrite(LedPin1, HIGH);

    lcdPosition(lcd, 3, 1);
    lcdPrintf(lcd,"Ak chcete zacat");
    lcdPosition(lcd, 4, 2);
    lcdPrintf(lcd,"stlacte tlacidlo");
    while (x == 1){
    if(digitalRead(ButtonPin) == 0){
    x=0;
}
 }
    lcdClear(lcd);
    teplota();
    lcdPosition(lcd, 9, 2);
    lcdPrintf(lcd,"%.0f", temp);
    delay(330);
    teplota();
    lcdPosition(lcd, 9, 2);
    lcdPrintf(lcd,"%.0f", temp);
    delay(330);
    teplota();
    lcdPosition(lcd, 9, 2);
    lcdPrintf(lcd,"%.0f", temp);
    delay(330);
    lcdClear(lcd);

//nastavenie teplot a casov na rmutovanie
t0=NastavenieTeplotyCasu(60, 0);

t1=NastavenieTeplotyCasu(60, 1);
c1=NastavenieTeplotyCasu(10, 2);

t2=NastavenieTeplotyCasu(t1, 1);
c2=NastavenieTeplotyCasu(10, 2);

t3=NastavenieTeplotyCasu(t2, 1);
c3=NastavenieTeplotyCasu(10, 2);

t4=NastavenieTeplotyCasu(t3, 1);
c4=NastavenieTeplotyCasu(10, 2);

t5=NastavenieTeplotyCasu(t4, 1);
c5=NastavenieTeplotyCasu(10, 2);

//nastavenie casov na chmelovar
celkovyCasChmelovar=NastavenieTeplotyCasu(70, 3);

casChmelovar1=NastavenieTeplotyCasu(celkovyCasChmelovar, 4);

casChmelovar2=NastavenieTeplotyCasu(casChmelovar1, 4);

casChmelovar3=NastavenieTeplotyCasu(casChmelovar2, 4);

casChmelovar4=NastavenieTeplotyCasu(casChmelovar3, 4);

chc1=celkovyCasChmelovar-casChmelovar1;
chc2=celkovyCasChmelovar-casChmelovar2-chc1;
chc3=celkovyCasChmelovar-casChmelovar3-chc1-chc2;
chc4=celkovyCasChmelovar-casChmelovar4-chc1-chc2-chc3;
chc5=celkovyCasChmelovar-chc1-chc2-chc3-chc4;

printf("\n%d %d \n%d %d \n%d %d\n", t1, c1, t2, c2, t3, c3, t4, c4);

printf("nieco");
lcdPosition(lcd, 0, 1);
lcdPrintf(lcd, "r1:%d/%d", t1, c1);
lcdPosition(lcd, 0, 2);
lcdPrintf(lcd, "r2:%d/%d", t2, c2);
lcdPosition(lcd, 0, 3);
lcdPrintf(lcd, "r3:%d/%d", t3, c3);
lcdPosition(lcd, 12, 1);
lcdPrintf(lcd, "r4:%d/%d", t4, c4);
lcdPosition(lcd, 12, 2);
lcdPrintf(lcd, "r5:%d/%d", t5, c5);
lcdPosition(lcd, 9, 3);
lcdPrintf(lcd, "teplota/cas");

lcdPosition(lcd, 0, 3);
lcdPrintf(lcd, "");

    Tx=c1+c2+c3+c4;
    Txi=1;
    TxHlas=Tx-20;

    seconds = time(NULL);
    starttime=seconds;
    printf("startovne sekundy: %d\n", starttime);

zahriev(t0);

peepanieSlad(t0);

zahriev(t1);
seconds = time(NULL);
rmutStarttime=seconds; //zaciatok Rmutovania

udrztRmut(t1,c1);

zahriev(t2);

udrztRmut(t2,c2);

zahriev(t3);

udrztRmut(t3,c3);

zahriev(t4);

udrztRmut(t4,c4);

zahriev(t5);

udrztRmut(t5,c5); //koniec Rmutovania

if (t5=0){
if (t4=0){
if (t3=0) {t3=t2;} t4=t3;} t5=t4; }

vysladzanie(t5);

zahriev(cht1); //zaciatok chmelovaru

udrztChmel(cht1, chc1);


udrztChmel(cht2, chc2);


udrztChmel(cht3, chc3);


udrztChmel(cht4, chc4);


udrztChmel(cht5, chc5); //koniec chmelovaru

digitalWrite(BuzzPin, 1); //led on
delay(150);
digitalWrite(BuzzPin, 0); //led off
delay(100);
digitalWrite(BuzzPin, 1); //led on
delay(150);
digitalWrite(BuzzPin, 0); //led off
delay(200);
digitalWrite(BuzzPin, 1); //led on
delay(500);
digitalWrite(BuzzPin, 0); //led off

digitalWrite(LedPin0, HIGH); //led off
digitalWrite(LedPin1, HIGH);

seconds = time(NULL);
    printf("aktualne sekundy: %ld\n", seconds);
    nowtime=seconds;

    dlzkavaru=nowtime-starttime;


  inputSecond=dlzkavaru;

  hours1 = (inputSecond/secondsInHour);

  remainingSeconds = inputSecond - (hours1 * secondsInHour);
  minutes1 = remainingSeconds/secondsInMinute;

  remainingSeconds = remainingSeconds - (minutes1*secondsInMinute);
  seconds1 = remainingSeconds;

  printf("cas od zaciatku t1:  %d:%d:%d\n",hours1,minutes1,seconds1);

lcdPosition(lcd, 1, 1);
lcdPrintf(lcd, "Celkovy cas varenia");
lcdPosition(lcd, 6, 2);
lcdPrintf(lcd, "%d:%d:%d ",hours1,minutes1,seconds1);


return 0;


} //koniec main

float teplota(){


	int i, j;
	int fd;
	int ret;
	char buf[BUFSIZE];
	char tempBuf[5];


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

		temp = (float)atoi(tempBuf);

		temp = temp /1000;

		if (temp>=120){
		temp=temp/10;
		}

            printf("%.3f C\n",temp);
		close(fd);

		return temp;

}

int zahriev(int t){

    int x;



x=1;
	while(x == 1){ //stupanie na zaciatocnu teplotu t1=======================================================================================================================

	teplota();


    lcdPosition(lcd, 0, 0);
    lcdPrintf(lcd, "%.1f C", temp);

   if (temp<100){

    lcdPosition(lcd, 6, 0);
    lcdPrintf(lcd, "-->");
    delay(150);} //ak je teplota vyssia ako 100 tak sa zaciatok sipky posuva o jedno

    lcdPosition(lcd, 6, 0);
    lcdPrintf(lcd, " -->");
    delay(150);
    lcdPosition(lcd, 6, 0);
    lcdPrintf(lcd, "  -->");
    delay(150);
    lcdPosition(lcd, 6, 0);
    lcdPrintf(lcd, "   -->");
    delay(150);
    lcdPosition(lcd, 6, 0);
    lcdPrintf(lcd, "    -->");
    delay(150);
    if (t<100){
    lcdPosition(lcd, 6, 0);
    lcdPrintf(lcd, "     -->");
    delay(200);
    lcdPosition(lcd, 11, 0);
    lcdPrintf(lcd, "   ");

    lcdPosition(lcd, 14, 0);
    lcdPrintf(lcd, "%d.0 C", t);}//print pozadovanej teploty ked je menia ako 100
    else {
    delay(200);
    lcdPosition(lcd, 10, 0);
    lcdPrintf(lcd, "   ");
    lcdPosition(lcd, 13, 0);
    lcdPrintf(lcd, "%d.0 C", t);}//print pozadovanej teploty ked je vacsia ako 100



    if(temp<t-2){
    digitalWrite(LedPin0, LOW); //led on
    digitalWrite(LedPin1, LOW);
}
    else if(temp<t){

    digitalWrite(LedPin0, LOW); //led on
    digitalWrite(LedPin1, HIGH); //led off

}
    else if(temp>=t){
    digitalWrite(LedPin0, HIGH); //led off
    digitalWrite(LedPin1, HIGH);
    x=0;
    delay(100);

    }


} //koniec while

    lcdClear(lcd);
    digitalWrite(LedPin0, HIGH); //led off
    digitalWrite(LedPin1, HIGH);
    return 0;
} //koniec funkcie

int udrztRmut(int t, int c){


    int x;

	time_t seconds;
    int nowtime;
    float dlzkavaru;
    int etapaStarttime;


    int inputSecond;
    int hours1,minutes1,seconds1;
    int remainingSeconds;
    int secondsInHour = 60 * 60;
    int secondsInMinute = 60;


    pinMode(BuzzPin, OUTPUT);
    pinMode(ButtonPin, INPUT);

    pullUpDnControl(ButtonPin, PUD_UP);

    iSlad++;

digitalWrite(BuzzPin, 1); //led on
delay(100);
digitalWrite(BuzzPin, 0); //led on
delay(100);
digitalWrite(BuzzPin, 1); //led on
delay(100);
digitalWrite(BuzzPin, 0); //led on
delay(100);


seconds = time(NULL);
etapaStarttime=seconds;
x=1;
    while(x == 1){ //while 3 t1=======================================================================================================================

			teplota();

    delay(100);
    lcdPosition(lcd, 0, 0);
    lcdPrintf(lcd, "%.1f C", temp);


    if (t>=100){
    delay(100);
    lcdPosition(lcd, 13, 0);
    lcdPrintf(lcd, "%d.0 C", t);
    }//print pozadovanej teploty ked je vacsia ako 100

    else {
    delay(100);
    lcdPosition(lcd, 14, 0);
    lcdPrintf(lcd, "%d.0 C", t);
    }


    if(temp<t){
    digitalWrite(LedPin0, LOW); //led on
            delay(100);

    }

    else{

    digitalWrite(LedPin0, HIGH); //led off
    delay(100);
    }


if(Txi == 1){
   //cas
   seconds = time(NULL);
    printf("aktualne sekundy: %ld\n", seconds);
    nowtime=seconds;

    dlzkavaru=nowtime-rmutStarttime;



  inputSecond=dlzkavaru;

  hours1 = (inputSecond/secondsInHour);

  remainingSeconds = inputSecond - (hours1 * secondsInHour);
  minutes1 = remainingSeconds/secondsInMinute;

  remainingSeconds = remainingSeconds - (minutes1*secondsInMinute);
  seconds1 = remainingSeconds;
  dlzkavaru=dlzkavaru/60;

printf("\n %.3f \n", dlzkavaru);
printf("\n %d \n", TxHlas);
  if (dlzkavaru>=TxHlas){


    lcdPosition(lcd, 7, 1);
    lcdPrintf(lcd, "Pripr.");
    lcdPosition(lcd, 1, 2);
    lcdPrintf(lcd, "vysladzovaciu vodu");
    lcdPosition(lcd, 2, 3);
    lcdPrintf(lcd, "a drz tlacidlo");

digitalWrite(BuzzPin, 1); //led on
delay(100);
digitalWrite(BuzzPin, 0); //led on
delay(100);
digitalWrite(BuzzPin, 1); //led on
delay(100);
digitalWrite(BuzzPin, 0); //led on
delay(100);
digitalWrite(BuzzPin, 1); //led on
delay(100);
digitalWrite(BuzzPin, 0); //led on
sleep(1);
digitalWrite(BuzzPin, 1); //led on
delay(100);
digitalWrite(BuzzPin, 0); //led on
delay(100);
digitalWrite(BuzzPin, 1); //led on
delay(100);
digitalWrite(BuzzPin, 0); //led on
delay(100);
digitalWrite(BuzzPin, 1); //led on
delay(100);
digitalWrite(BuzzPin, 0); //led on

if(digitalRead(ButtonPin) == 0)
{
Txi=0;
    lcdPosition(lcd, 7, 1);
    lcdPrintf(lcd, "      ");
    lcdPosition(lcd, 1, 2);
    lcdPrintf(lcd, "                  ");
    lcdPosition(lcd, 2, 3);
    lcdPrintf(lcd, "               ");
printf("%d", Txi);
}
}
}

lcdPosition(lcd, 4, 2);
lcdPrintf(lcd, "Rmutovanie %d", iSlad);


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


lcdPosition(lcd, 0, 1);
lcdPrintf(lcd, "%d:%d:%d ",hours1,minutes1,seconds1);

    inputSecond=c*60; //premenenie vstupneho casu teda konecneho casu etapy na sekundy
    hours1 = (inputSecond/secondsInHour);

    remainingSeconds = inputSecond - (hours1 * secondsInHour);
    minutes1 = remainingSeconds/secondsInMinute;

    remainingSeconds = remainingSeconds - (minutes1*secondsInMinute);
    seconds1 = remainingSeconds;
    lcdPosition(lcd, 14, 1);
    lcdPrintf(lcd, "%d:%d:%d",hours1,minutes1,seconds1);



//dlzkavaru v minutach
dlzkavaru=dlzkavaru/60;

if (dlzkavaru>=c){
	x=0;
	}

} //koniec while 3

    lcdClear(lcd);
digitalWrite(BuzzPin, 1); //led on
delay(100);
digitalWrite(BuzzPin, 0); //led on
delay(100);
digitalWrite(BuzzPin, 1); //led on
delay(100);
digitalWrite(BuzzPin, 0); //led on
delay(100);
digitalWrite(BuzzPin, 1); //led on
delay(100);
digitalWrite(BuzzPin, 0); //led on
    return Txi;


}

int udrztChmel(int t, int c){

    int x=1;


    time_t seconds;
    int nowtime;
    float dlzkavaru;
    int etapaStarttime;


    int inputSecond;
    int hours1,minutes1,seconds1;
    int remainingSeconds;
    int secondsInHour = 60 * 60;
    int secondsInMinute = 60;

    iChmel++;

peepanieChmel(t);

seconds = time(NULL);
etapaStarttime=seconds;
x=1;
    while(x == 1){ //while 3 t1=======================================================================================================================

			teplota();

    delay(100);
    lcdPosition(lcd, 0, 0);
    lcdPrintf(lcd, "%.1f C", temp);


    if (t>=100){
    delay(100);
    lcdPosition(lcd, 13, 0);
    lcdPrintf(lcd, "%d.0 C", t);
    }//print pozadovanej teploty ked je vacsia ako 100

    else {
    delay(100);
    lcdPosition(lcd, 14, 0);
    lcdPrintf(lcd, "%d.0 C", t);
    }


    if(temp<t){
    digitalWrite(LedPin0, LOW); //led on

            delay(100);

    }

    else{

    digitalWrite(LedPin0, HIGH); //led off

    delay(100);
    }


    lcdPosition(lcd, 5, 2);
    lcdPrintf(lcd, "Chmelovar %d", iChmel);



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

  printf("cas od zaciatku:  %d:%d:%d\n",hours1,minutes1,seconds1);


lcdPosition(lcd, 0, 1);
lcdPrintf(lcd, "%d:%d:%d ",hours1,minutes1,seconds1);

    inputSecond=c*60; //premenenie vstupneho casu teda konecneho casu etapy na sekundy
    hours1 = (inputSecond/secondsInHour);

    remainingSeconds = inputSecond - (hours1 * secondsInHour);
    minutes1 = remainingSeconds/secondsInMinute;

    remainingSeconds = remainingSeconds - (minutes1*secondsInMinute);
    seconds1 = remainingSeconds;
    lcdPosition(lcd, 14, 1);
    lcdPrintf(lcd, "%d:%d:%d",hours1,minutes1,seconds1);


    lcdPosition(lcd, 2, 3);
    lcdPrintf(lcd, "Celkovy cas %dmin", celkovyCasChmelovar);


//dlzkavaru v minutach
dlzkavaru=dlzkavaru/60;

if (dlzkavaru>=c){
	x=0;
	}



} //koniec while 3


    lcdClear(lcd);
    return 0;
}

int peepanieSlad(int t){
	int i;
    int x;

    float temp;

    pinMode(BuzzPin, OUTPUT);
    pinMode(ButtonPin, INPUT);

    pullUpDnControl(ButtonPin, PUD_UP);
x=1;
    while(x == 1){ //while 2 potvdenie pridania sladu=======================================================================================================================


    lcdPosition(lcd, 1, 0);
    lcdPrintf(lcd, "Teplota dosiahnuta");
    lcdPosition(lcd, 4, 1);
    lcdPrintf(lcd, "pridaj  slad");
    lcdPosition(lcd, 5, 2);
    lcdPrintf(lcd, "a nasledne");
    lcdPosition(lcd, 3, 3);
    lcdPrintf(lcd, "stlac tlacidlo");

    teplota();

    if(temp<t){
    digitalWrite(LedPin0, LOW); //led on

            delay(100);

    }

    else{

    digitalWrite(LedPin0, HIGH); //led off

    delay(100);
    }

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
printf("som tu 564\n");
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



} //koniec while 2

    lcdClear(lcd);
    return 0;
}

int peepanieChmel(int t){
	int i;
    int x;

    pinMode(BuzzPin, OUTPUT);
    pinMode(ButtonPin, INPUT);


    pullUpDnControl(ButtonPin, PUD_UP);
x=1;
    while(x == 1){ //while 2 potvdenie pridania sladu=======================================================================================================================


    lcdPosition(lcd, 4, 0);
    lcdPrintf(lcd, "Pridaj chmel");
    lcdPosition(lcd, 4, 1);
    lcdPrintf(lcd, "podla receptu");
    lcdPosition(lcd, 1, 2);
    lcdPrintf(lcd, "a potvrd stlacenim");
    lcdPosition(lcd, 6, 3);
    lcdPrintf(lcd, "tlacitka");


   teplota();

    if(temp<t){
    digitalWrite(LedPin0, LOW); //led on

            delay(100);

    }

    else{

    digitalWrite(LedPin0, HIGH); //led off

    delay(100);
    }



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



} //koniec while 2

    lcdClear(lcd);
    return 0;
}

int vysladzanie(int t){
	int i;
    int x;

    pinMode(ButtonPin, INPUT);
    pullUpDnControl(ButtonPin, PUD_UP);
x=1;
    while(x == 1){ //while  vysladzanie=======================================================================================================================

    teplota();

    lcdPosition(lcd, 2, 0);
    lcdPrintf(lcd, "Zacni vysladzat");
    lcdPosition(lcd, 3, 1);
    lcdPrintf(lcd, "a po skonceni");
    lcdPosition(lcd, 3, 2);
    lcdPrintf(lcd, "stlac tlacidlo");
    lcdPosition(lcd, 7, 3);
    lcdPrintf(lcd, "%.1f C", temp);



    if(temp<t){
    digitalWrite(LedPin0, LOW); //led on
            delay(100);

    }

    else{

    digitalWrite(LedPin0, HIGH); //led off
    delay(100);
    }




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



} //koniec while

    lcdClear(lcd);
    return 0;
}

int NastavenieTeplotyCasu(int vstup, int CasORteplota){
int y;
int x=1;
            pullUpDnControl(ButtonPin, PUD_UP);
            pullUpDnControl(ButtonPin1, PUD_UP);
            pullUpDnControl(ButtonPin2, PUD_UP);

            if (CasORteplota == 0){
            iTeplota++;
            y=0;
            printf("&&&&&&&&&&&&&TEPLOTA t0  &&&&&&&&&&&&&&&\,");
            }
            if (CasORteplota == 1){
            iTeplota++;
            y=1;
            printf("&&&&&&&&&&&&&TEPLOTA&&&&&&&&&&&&&&&\,");
            }
            else if (CasORteplota == 2){
            iCas++;
            y=2;
            printf("&&&&&&&&&&&&&&&CAS&&&&&&&&&&&&&\n");
            }
             else if (CasORteplota == 3){
            y=3;
            printf("&&&&&&&&&&&&&CHMEL CLEKOVA DLZKA&&&&&&&&&&&&&&&\n");
            }
            else if (CasORteplota == 4){
            iChmelovar++;
            y=4;
            printf("&&&&&&&&&&&&&CHMEL&&&&&&&&&&&&&&&\n");
            }


          while (x == 1){

            if(digitalRead(ButtonPin1) == 0){
            vstup++;
            delay(150);
            printf("%d\n", vstup);
            }

            if (digitalRead(ButtonPin2) == 0){
            vstup--;
            delay(150);
            printf("%d\n", vstup);
            }
            if (digitalRead(ButtonPin) == 0){
            x=0;
            delay(300);
            }
            else {
            x=1;
            }
            //if(x=1)
                        delay(100);
            printf("%d\n", vstup);

            lcdPosition(lcd, 6, 0);
            lcdPrintf(lcd, "Nastavte");

            if (y == 0){
            lcdPosition(lcd, 1, 1);
            lcdPrintf(lcd, "teplotu pri ktorej");
            lcdPosition(lcd, 3, 2);
            lcdPrintf(lcd, "pridavame slad");
            lcdPosition(lcd, 7, 3);
            lcdPrintf(lcd, "%d.0 C ", vstup);
            }
            else if (y == 1){
            lcdPosition(lcd, 0, 1);
            lcdPrintf(lcd, "teplotu rmutovania %d", iTeplota);
            lcdPosition(lcd, 7, 2);
            lcdPrintf(lcd, "%d.0 C ", vstup);
            }
            else if (y == 2){
            lcdPosition(lcd, 1, 1);
            lcdPrintf(lcd, "dlzku rmutovania %d", iCas);
            lcdPosition(lcd, 7, 2);
            lcdPrintf(lcd, "%d min ", vstup);
            }
            else if (y == 3){
            lcdPosition(lcd, 4, 1);
            lcdPrintf(lcd, "celkovu dlzku");
            lcdPosition(lcd, 5, 2);
            lcdPrintf(lcd, "chmelovaru");
            lcdPosition(lcd, 7, 3);
            lcdPrintf(lcd, "%d min ",vstup);
            }
            else if (y == 4){
            lcdPosition(lcd, 0, 1);
            lcdPrintf(lcd, "dlzku varenia chmelu");
            lcdPosition(lcd, 1, 2);
            lcdPrintf(lcd, "ktory sypeme ako %d.",iChmelovar);
            lcdPosition(lcd, 7, 3);
            lcdPrintf(lcd, "%d min ",vstup);
            }
            }
            printf("konecny vystup%d\n", vstup);
            lcdClear(lcd);
            return vstup;
}
