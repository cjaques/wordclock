/* LedStripGradient: Example Arduino sketch that shows
 * how to control an Addressable RGB LED Strip from Pololu.
 *
 * To use this, you will need to plug an Addressable RGB LED
 * strip from Pololu into pin 12.  After uploading the sketch,
 * you should see a pattern on the LED strip that fades from
 * green to pink and also moves along the strip.
 */
 
#include "PololuLedStrip.h"
#include <Wire.h>
#include "RTClib.h"

// =======================================================    GLOBALS 
// Real time clock
RTC_DS1307 rtc;

// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<7> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
#define LED_COUNT 144
rgb_color colors[LED_COUNT];

// inputs for buttons
int button1 = 10;
int button2 = 12;
int button1_state = 0;
int button2_state = 0;


// =======================================================    SETUP
void setup()
{    
//  
//  if (! rtc.isrunning()) {
//    Serial.println("RTC is NOT running!");}
  Wire.begin();
//  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
}

// =======================================================    VARS
DateTime now;


// =======================================================    MAIN LOOP
void loop()
{
  // read time
  now = rtc.now();

  // button pressed ? 
  if(digitalRead(button1) == HIGH)
  {
    if(button1_state == 0)
    {
      button1_state = 1;
      // change time here
      add_5min(now);
    }
  }
  else
  {
    button1_state = 0;
  }
   if(digitalRead(button2) == HIGH)
   {
    if(button2_state == 0)
    {
      button2_state = 1;
      // change time here
      subtract_5min(now); 
    }
  }
  else
  {
    button2_state = 0;
  }

  // read time
  now = rtc.now();

  // will directly update colors
  translateTime(now);

  // send colors to strip
  ledStrip.write(colors, LED_COUNT);  
   
  delay(20);
//  Serial.println();
  
}


// =======================================================    COLORS
rgb_color normal =    (rgb_color){ 160, 160, 160 };
rgb_color normal_strong =    (rgb_color){ 200, 200, 200 };
rgb_color off =       (rgb_color){ 0, 0, 0 };
rgb_color rose  =      (rgb_color){200, 30, 30};
rgb_color blueish  =      (rgb_color){10, 30, 150};


// =======================================================    ADJUST TIME
void add_5min(DateTime in){

  int m = in.minute();
  int h = in.hour();
  int diff = 5-(m+5)%5;
  Serial.print("m was : ");
  Serial.print(m);
  Serial.print("  h was : ");
  Serial.print(h);
  
  m = m+diff;
  if(m >= 60)
  {
    h +=1;
    h = h%24;
  }
    
  m = m%60;
  Serial.print("   new m : ");
  Serial.print(m);
  Serial.print("    new h : ");
  Serial.print(h);

  rtc.adjust(DateTime(2017,06,01,h,m,0));
}

void subtract_5min(DateTime in){
  int m = in.minute();
  int h = in.hour();

  if(m%5 == 0)
    m = m-5;
  else
    m = m%5;
  
  if(m < 0)
  {
    m = 55;
    h -=1;
    if (h==0)
      h = 23;
  }
    
  
  Serial.print("   new m : ");
  Serial.print(m);
  Serial.print("    new h : ");
  Serial.print(h);

  rtc.adjust(DateTime(2017,06,01,h,m,0));
}


// =======================================================    TRANSLATE TIME
void translateTime(DateTime in){
  int h = in.hour();
  int m = in.minute();

//  // DEBUG print time
//  Serial.print(h);Serial.print("  ");Serial.print(m);
//  Serial.println();

  
  // reset colors
  memset(colors,0,LED_COUNT*(3*sizeof(unsigned char)));
//  for (int i=0;i++;i<LED_COUNT)
//    colors[i] = off;
  

  // Il est
  colors[0]=colors[1]=normal_strong;
  colors[3]=colors[4]=colors[5]=normal;
  // chez les waltrr
  colors[127]=colors[126]=colors[125]=colors[123]=colors[122]=colors[121]=colors[120]=blueish;
  colors[132]=colors[133]=colors[134]=colors[135]=colors[136]=colors[137]=blueish;
  // Jade
  //colors[128]=colors[129]=colors[130]=colors[131]=rose;
  // Louise
  //colors[138]=colors[139]=colors[140]=colors[141]=colors[142]=colors[143]=rose;

  if(m >= 33)
    h += 1;
    
  printHours(h);
  printMinutes(m);
  
 
}

void printMinutes(int m){
  switch(m){
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
      colors[95]=colors[94]=colors[93]=colors[92]=normal; // cinq
      break;
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
      colors[91]=colors[90]=colors[89]=normal; // dix
      break;
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
      colors[118]=colors[119]=normal; // et
      colors[88]=colors[87]=colors[86]=colors[85]=colors[84]=normal; // quart --> add "et"?
      break;
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
      colors[96]=colors[97]=colors[98]=colors[99]=colors[100]=normal; // vingt
      break;
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
      colors[96]=colors[97]=colors[98]=colors[99]=colors[100]=normal; // vingt
      colors[101]=colors[102]=colors[103]=colors[104]=colors[105]=normal; // -cinq
      break;
    case 28:
    case 29:
    case 30:
    case 31:
    case 32:
      colors[118]=colors[119]=normal; // et
      colors[108]=colors[109]=colors[110]=colors[111]=colors[112]=normal; // demie
      break;
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
      colors[79]=colors[80]=colors[81]=colors[82]=colors[83]=normal; // moins
      colors[96]=colors[97]=colors[98]=colors[99]=colors[100]=normal; // vingt
      colors[101]=colors[102]=colors[103]=colors[104]=colors[105]=normal; // -cinq
      break;
    case 38:
    case 39:
    case 40:
    case 41:
    case 42:
      colors[79]=colors[80]=colors[81]=colors[82]=colors[83]=normal; // moins
      colors[96]=colors[97]=colors[98]=colors[99]=colors[100]=normal; // vingt
      break;
    case 43:
    case 44:
    case 45:
    case 46:
    case 47:
      colors[79]=colors[80]=colors[81]=colors[82]=colors[83]=normal; // moins
      colors[88]=colors[87]=colors[86]=colors[85]=colors[84]=normal; // quart 
      break;
    case 48:
    case 49:
    case 50:
    case 51:
    case 52:
      colors[79]=colors[80]=colors[81]=colors[82]=colors[83]=normal; // moins
      colors[91]=colors[90]=colors[89]=normal; // dix
      break;
    case 53:
    case 54:
    case 55:
    case 56:
    case 57:
      colors[79]=colors[80]=colors[81]=colors[82]=colors[83]=normal; // moins
      colors[95]=colors[94]=colors[93]=colors[92]=normal; // cinq
      break;
    
  }
}

void printHours(int h){
// heures
  colors[71]=colors[70]=colors[69]=colors[68]=colors[67]=colors[66]=normal;
  switch(h){
    case 12:
      colors[65]=colors[64]=colors[63]=colors[62]=normal;
      // switch heures off
      colors[71]=colors[70]=colors[69]=colors[68]=colors[67]=colors[66]=off;
      break;
    case 24:
    case 0:
      colors[72]=colors[73]=colors[74]=colors[75]=colors[76]=colors[77]=normal;
      // switch heures off
      colors[71]=colors[70]=colors[69]=colors[68]=colors[67]=colors[66]=off;
      break;
    case 1:
    case 13:
      colors[7]= normal;colors[8]=normal;colors[9]=normal;
      // switch "s" of "heures" off
      colors[66] = off;
      break;
    case 2:
    case 14:
      colors[23]=colors[22]=colors[21]=colors[20]=normal;
      break;
    case 3:
    case 15:
      colors[17]=colors[16]=colors[15]=colors[14]=colors[13]=normal;
      break;
    case 4:
    case 16:
      colors[26]=colors[27]=colors[28]=colors[29]=colors[30]=colors[31]=normal;
      break;      
    case 5:
    case 17:
      colors[32]=colors[33]=colors[34]=colors[35]=normal;
      break;
    case 6:
    case 18:
      colors[47]=colors[46]=colors[45]=normal;
      break;
    case 7:
    case 19:
      colors[44]=colors[43]=colors[42]=colors[41]=normal;
      break;
    case 8:
    case 20:
      colors[40]=colors[39]=colors[38]=colors[37]=normal;
      break;
    case 9:
    case 21:
      colors[48]=colors[49]=colors[50]=colors[51]=normal;
      break;
    case 10:
    case 22:
      colors[52]=colors[53]=colors[54]=normal;
      break;
    case 11:
    case 23:
      colors[56]=colors[57]=colors[58]=colors[59]=normal;
      break;
  }
}

// =======================================================    ANIM JADE
void animJade(){ 
  int LED_J = 4;
  int J0 = 128;
  byte time;
  int Count = 1000;
  
  for(int i=0;i<Count;i++){
    // gives this nice waving pattern 
    time = millis() >> 2;
    for(uint16_t i = 0; i < LED_J; i++)
    {
      byte x = time - 8*i;
      colors[J0+i] = (rgb_color){ x, 255 - x, x };
    }
    // actually send color to strip
    ledStrip.write(colors, LED_COUNT);  
  }
}
// =======================================================    ANIM LOUISE
void animLouise(){ 
  int LED_J = 6;
  int J0 = 138;
  byte time;
  int Count = 1000;
  
  for(int i=0;i<Count;i++){
    // gives this nice waving pattern 
    time = millis() >> 2;
    for(uint16_t i = 0; i < LED_J; i++)
    {
      byte x = time - 8*i;
      colors[J0+i] = (rgb_color){ x, 255 - x, x };
    }
    // actually send color to strip
    ledStrip.write(colors, LED_COUNT);  
  }
}
