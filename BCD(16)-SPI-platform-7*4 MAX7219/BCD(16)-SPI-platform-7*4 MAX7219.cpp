#include <SPI.h>
#include <SPI_Bus.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#include <Wire.h>
byte SegDisplay;                                                 
byte RazrDisplay;                                                
int pinCS = 9;
int numberOfHorizontalDisplays = 1;                               
int numberOfVerticalDisplays = 1;                                
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);
const byte g_digits[17] = {
 0b01111110,      // = 0
 0b00110000,      // = 1
 0b01101101,      // = 2
 0b01111001,      // = 3
 0b00110011,      // = 4
 0b01011011,      // = 5
 0b01011111,      // = 6
 0b01110000,      // = 7
 0b01111111,      // = 8
 0b01111011,      // = 9
 0b01110111,      // = A 
 0b00011111,      // = b
 0b01001110,      // = C
 0b00111101,      // = d
 0b01001111,      // = E
 0b01000111,      // = F
 0b10000000       // = .
};
SPI_Bus reg(_16bit, 10, MSBFIRST);
float b = 0;
float j = 0;
float c = 0;
float d1 = 0;
float d2 = 0;
float d3 = 0;
float d4 = 0;
void setup()
{
  reg.setSelectionPolicy(SPI_Bus::SELECT_BEFORE);
  matrix.setIntensity(15);
}
void loop()
{
  static uint32_t last_input_states = 0;
  uint32_t states = reg.read32bits();
  if (states != last_input_states)
  {
    uint32_t changed = states ^ last_input_states;
    last_input_states = states;
    b = 0;
    j = 0;
    c = 0;
    d1 = 0;
      for (int i = 0; i < 4; ++i)
      {
        int a = ((int)~states & 1);
        Serial.print(a); 
        b=pow(2,j);
        c=a*b; 
        d1=d1+c;
        j=j+1;
        changed >>= 1;
        states >>= 1;
      }
    b = 0;
    j = 0;
    c = 0;
    d2 = 0;
      for (int i = 4; i < 8; ++i)
      {
        int a = ((int)~states & 1);
        Serial.print(a); 
        b=pow(2,j);
        c=a*b; 
        d2=d2+c; 
        j=j+1;
        changed >>= 1;
        states >>= 1;
      }
    b = 0;
    j = 0;
    c = 0;
    d3 = 0;
      for (int i = 8; i < 12; ++i)
      {
        int a = ((int)~states & 1);
        Serial.print(a); 
        b=pow(2,j);
        c=a*b;
        d3=d3+c;
        j=j+1; 
        changed >>= 1;
        states >>= 1;
      }
    b = 0;
    j = 0;
    c = 0;
    d4 = 0;
      for (int i = 12; i < 16; ++i)
      {
        int a = ((int)~states & 1);
        Serial.print(a); 
        b=pow(2,j);
        c=a*b;
        d4=d4+c;
        j=j+1;
        changed >>= 1;
        states >>= 1;
      }
  }
}

void Indicate(int y,int i)
  {
    matrix.setIntensity(7);  
    matrix.setRotation( 0, 1 );
      for ( int x = 0; x < 8; x++ ) 
        {
        matrix.drawPixel(x, y, g_digits[i] & (B00000001<<x));  
        }
      
    matrix.write();     
  }
