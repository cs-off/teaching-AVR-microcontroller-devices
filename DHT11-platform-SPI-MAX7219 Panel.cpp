#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#include <Wire.h>
#include <dht11.h>

dht11 sensor;
#define DHT11PIN 2                                              

byte SegDisplay;                                                  
byte RazrDisplay;                                                 

int pinCS = 9;
int numberOfHorizontalDisplays = 1;                              
int numberOfVerticalDisplays = 1;                                 

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

const byte g_digits[11] = {
 0b01111110,                                                      // = 0
 0b00110000,                                                      // = 1
 0b01101101,                                                      // = 2
 0b01111001,                                                      // = 3
 0b00110011,                                                      // = 4
 0b01011011,                                                      // = 5
 0b01011111,                                                      // = 6
 0b01110000,                                                      // = 7
 0b01111111,                                                      // = 8
 0b01111011,                                                      // = 9
 0b10000000                                                       // = .
};

void setup()
{
 matrix.setIntensity(7);
 Serial.begin(9600);
}

void loop()
{
  int disp = 0; 
  int chk = sensor.read(DHT11PIN 
  
  disp = sensor.temperature;                                                                              

  if (disp < 10)                                                  
  {
    Indicate(7, 10);                                              
    Indicate(6, 10);                                              
    Indicate(5, 10);                                              
    Indicate(4, disp);                                            
  }
  

  else if (disp < 100)                                           
  
  {
    Indicate(7, 10);                                             
    Indicate(6, 10);                                          
    Indicate(5, disp / 10);                                    
    Indicate(4, disp % 10);                                    
  }

  else if (chk < 1000)
  
  {
    Indicate(7, 10);
    Indicate(6, disp / 100);   
    Indicate(5, (disp % 100) / 10);
    Indicate(4, disp % 10);
  }
  

  else
  
  {
    Indicate(7, disp / 1000);
    Indicate(6, (disp % 1000) / 100);   
    Indicate(5, (disp % 100) / 10);
    Indicate(4, disp % 10);
  }

  
  delay(1000);
 
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
