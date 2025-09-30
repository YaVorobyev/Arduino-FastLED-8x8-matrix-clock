//библиоека дя работы с матрицей 
#include <FastLED.h>
#define kolvosv 64
#define ledpin 4


#define smesh 4
#define smeshy 8

#define kpin 5

//бибиотека датчикаважости и температуры
#include "DHT.h"
#define DHTpin 6
DHT dht(DHTpin, DHT11);


CRGB leds[kolvosv];




//библиотека модуля ряльн временеф
#include <iarduino_RTC.h>
iarduino_RTC time(RTC_DS3231);


byte cicl;

bool symlb[]{
  //*C
  0,0,0,0,0,0,1,0,
  0,1,1,0,0,1,0,1,
  0,0,0,1,0,0,1,0,
  0,0,0,1,0,0,0,0,
  0,1,1,0,0,0,0,0,

  //%1слой
  0,0,0,0,0,0,1,0,
  0,0,0,0,0,1,0,1,
  0,0,0,1,0,0,1,0,
  0,0,1,0,1,0,0,0,
  0,0,0,1,0,0,0,0,
  //%2слой
  0,0,0,1,0,0,0,0,
  0,0,0,0,1,0,0,0,
  0,0,0,0,1,1,0,0,
  0,0,0,0,0,1,0,0,
  0,0,0,0,0,0,1,0
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
byte tcv;
byte hcv;
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
  //инициаизация датчика
   dht.begin();
  
  //инициаизация матрицы
  FastLED.addLeds <WS2812B,ledpin, GRB> (leds,kolvosv);
  //Модуль реального времени
  time.begin();
  //внутренний счет времени
  mls = millis();
  cmls = millis();
  smls = millis();
  //Серийный порт для отладки (9600 бодд)
  Serial.begin(9600);

}

void loop() {
  
  time.gettime();
    a = time.hours; 
  Serial.println(a);
   b = time.minutes; 
  Serial.println(b);
  
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
   
  if(millis()>=smls+1000){
    if(rej==1){
  t = dht.readTemperature();
  h = dht.readHumidity();
  tcv = map(t,0,50,170,0);
  hcv = map(h,20,95,51,255);
  Serial.println(t);
  
  smls = millis();}
  }
  
  
  // put your main code here, to run repeatedly:
  for(cicl=0;cicl<kolvosv;cicl++){
    leds[cicl].setHSV(25,255,10);
  }
  for(cicl=0;cicl<kolvosv;cicl++){
  if(cicl<40){
    //отображение времени
    if( rej == 0){
    // десятки часов
    
    if(numlb[cicl+a/10*40]==1  and (cicl+smesh+x)/8==(cicl)/8 )leds[cicl+smesh+x+smeshy].setHSV(map(cvet,180,255,0,255),255,200);
    //единицы часов
    if(numlb[cicl+a%10*40]==1 and (cicl+x)/8==(cicl)/8 )leds[cicl+x+smeshy].setHSV(map(cvet,180,255,0,255),255,200);
    //десятки минут
    if(numlb[cicl+b/10*40]==1  and cicl+x+smesh-10>=0 and(cicl+smesh+x-10 )/8==cicl/8 )leds[cicl+smesh+x-10+smeshy].setHSV(map(cvet,50,180,0,255),255,200);
    //единицы минут
    if(numlb[cicl+b%10*40]==1  and cicl+x-10>=0 and (cicl+x-10)/8==cicl/8 )leds[cicl+x-10+smeshy].setHSV(map(cvet,50,180,0,255),255,200);
    }
    //отображение температуры
    if(rej==1){
      
      if(numlb[cicl+t/10*40]==1   and cicl+x+smesh>=0 and(cicl+smesh+x )/8==cicl/8 )leds[cicl+smesh+x].setHSV(tcv,255,200);
      if(numlb[cicl+t%10*40]==1  and cicl+x>=0 and(cicl+x)/8==cicl/8 )leds[cicl+x].setHSV(tcv,255,200);
      if(symlb[cicl]==1  and cicl+x-9>=0 and (cicl+x-9 )/8==(cicl)/8 )leds[cicl+x -9 ].setHSV(tcv,255,200);
    }
    if(rej==2){
       if(numlb[cicl+h/10*40]==1   and cicl+x+smesh>=0 and(cicl+smesh+x )/8==cicl/8 )leds[cicl+smesh+x].setHSV(158,hcv,200);
      if(numlb[cicl+h%10*40]==1  and cicl+x>=0 and(cicl+x)/8==cicl/8 )leds[cicl+x].setHSV(158,hcv,200);
      if(symlb[cicl+40]==1  and cicl+x-9>=0 and (cicl+x-9 )/8==(cicl)/8 )leds[cicl+x -9 ].setHSV(158,hcv,200);
      if(symlb[cicl+80]==1  and cicl+x-9>=0 and (cicl+x-9 )/8==(cicl)/8 )leds[cicl+x -9 ].setHSV(100,255,67);
    }
    }}
    if(rej == 0){
  if((8+x-2)/8==1 )leds[8+x-2+smeshy].setHSV(255,0,180);
  if((8*3+x-2)/8==3  )leds[8*3+x-2+smeshy].setHSV(255,0,180);}

  //вывод в дисплей
  FastLED.show();
 
}
