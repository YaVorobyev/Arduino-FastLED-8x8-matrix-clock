#include <FastLED.h>

#include "DHT.h"

#define kolvosv 64
#define ledpin 4
#define smesh 4
#define smeshy 8
#define kpin 5



CRGB leds[kolvosv];

DHT dht(6, DHT11);


//библиотека модуля ряльн временеф
#include <iarduino_RTC.h>
iarduino_RTC time(RTC_DS3231);

byte cicl;

bool symlb[]{
  0,0,0,0,0,0,1,0,
  0,1,1,0,0,1,0,1,
  0,0,0,1,0,0,1,0,
  0,0,0,1,0,0,0,0,
  0,1,1,0,0,0,0,0
};

bool numlb[]{
  //0
  0,1,0,0,0,0,0,0,
  1,0,1,0,0,0,0,0,
  1,0,1,0,0,0,0,0,
  1,0,1,0,0,0,0,0,
  0,1,0,0,0,0,0,0,
  
  //1
  0,1,0,0,0,0,0,0,
  0,1,1,0,0,0,0,0,
  0,1,0,0,0,0,0,0,
  0,1,0,0,0,0,0,0,
  1,1,1,0,0,0,0,0,
  
  //2
  0,1,1,0,0,0,0,0,
  1,0,0,0,0,0,0,0,
  0,1,0,0,0,0,0,0,
  0,0,1,0,0,0,0,0,
  1,1,1,0,0,0,0,0,
  
  //3
  0,1,1,0,0,0,0,0,
  1,0,0,0,0,0,0,0,
  0,1,1,0,0,0,0,0,
  1,0,0,0,0,0,0,0,
  0,1,1,0,0,0,0,0,
  
  //4
  1,0,1,0,0,0,0,0,
  1,0,1,0,0,0,0,0,
  1,1,1,0,0,0,0,0,
  1,0,0,0,0,0,0,0,
  1,0,0,0,0,0,0,0,
  
  //5
  1,1,1,0,0,0,0,0,
  0,0,1,0,0,0,0,0,
  0,1,1,0,0,0,0,0,
  1,0,0,0,0,0,0,0,
  0,1,1,0,0,0,0,0,

  //6
  1,1,0,0,0,0,0,0,
  0,0,1,0,0,0,0,0,
  1,1,1,0,0,0,0,0,
  1,0,1,0,0,0,0,0,
  1,1,1,0,0,0,0,0,

  //7
  1,1,1,0,0,0,0,0,
  1,0,0,0,0,0,0,0,
  0,1,0,0,0,0,0,0,
  0,1,0,0,0,0,0,0,
  0,0,1,0,0,0,0,0,

  //8
  1,1,1,0,0,0,0,0,
  1,0,1,0,0,0,0,0,
  1,1,1,0,0,0,0,0,
  1,0,1,0,0,0,0,0,
  1,1,1,0,0,0,0,0,

  //9
  1,1,1,0,0,0,0,0,
  1,0,1,0,0,0,0,0,
  1,1,0,0,0,0,0,0,
  1,0,0,0,0,0,0,0,
  0,1,1,0,0,0,0,0
};
int x = 0;
bool mv=1;

byte a = 0;
byte b = 0;
int t;
int h;
byte rej;
byte cvet;
unsigned long mls;
unsigned long cmls;
unsigned long smls;
bool mch;
bool kn;

void setup() {
   dht.begin();
  Serial.begin(9600);
  FastLED.addLeds <WS2812B,ledpin, GRB> (leds,kolvosv);
  time.begin();
  mls = millis();

}

void loop() {

  

   time.gettime();
   if(millis()>=cmls+66){
    if(kn!=digitalRead(kpin)){
      kn = digitalRead(kpin);
      if(kn == 1)rej++;
      if(rej==3)rej=0;
    }
    if(cvet==255)cvet=0;
    cvet++;
    cmls=millis();
   }
   
   if(millis()>= mls +250){
    if(mv ==1)x++;
    if(mv==0)x--;
    if(x<=0)mv=1;
    if(x>=11)mv=0;
    mls = millis();
   }
   
  
  a = time.hours; 
  Serial.println(a);
   b = time.minutes; 
  Serial.println(b);

 if(millis()>=smls+100){
  t = dht.readTemperature();
  Serial.println(t);
  smls = millis();
  }
  
  // put your main code here, to run repeatedly:
  for(cicl=0;cicl<kolvosv;cicl++){
    leds[cicl].setHSV(25,255,10);
  }
  for(cicl=0;cicl<kolvosv;cicl++){

    if( rej == 0){
    // десятки
    
    if(numlb[cicl+a/10*40]==1 and cicl<40 and (cicl+smesh+x)/8==(cicl)/8 )leds[cicl+smesh+x+smeshy].setHSV(map(cvet,180,255,0,255),255,200);
    //единицы
    if(numlb[cicl+a%10*40]==1 and cicl<40 and (cicl+x)/8==(cicl)/8 )leds[cicl+x+smeshy].setHSV(map(cvet,180,255,0,255),255,200);

    if(numlb[cicl+b/10*40]==1 and cicl<40 and cicl+x+smesh-10>=0 and(cicl+smesh+x-10 )/8==cicl/8 )leds[cicl+smesh+x-10+smeshy].setHSV(map(cvet,50,180,0,255),255,200);
    //единицы
    if(numlb[cicl+b%10*40]==1 and cicl<40 and cicl+x-10>=0 and (cicl+x-10)/8==cicl/8 )leds[cicl+x-10+smeshy].setHSV(map(cvet,50,180,0,255),255,200);
    }
    if(rej==1){
      
      if(numlb[cicl+t/10*40]==1 and cicl<40  and cicl+x+smesh>=0 and(cicl+smesh+x )/8==cicl/8 )leds[cicl+smesh+x].setHSV(15,255,200);
      if(numlb[cicl+t%10*40]==1 and cicl<40  and cicl+x>=0 and(cicl+x)/8==cicl/8 )leds[cicl+x].setHSV(15,255,200);
      if(symlb[cicl]==1 and cicl<40 and cicl+x-9>=0 and (cicl+x-9 )/8==(cicl)/8 )leds[cicl+x -9 ].setHSV(30,255,200);
    }
    }
    if(rej == 0){
  if((8+x-2)/8==1 )leds[8+x-2+smeshy].setHSV(255,0,180);
  if((8*3+x-2)/8==3  )leds[8*3+x-2+smeshy].setHSV(255,0,180);}

  
  FastLED.show();
 
}
