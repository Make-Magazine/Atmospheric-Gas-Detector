/*

Maker Shed Atmospheric Gas Detector Kit Test Code
by Eric Weinhoffer

For a schematic, view page 21 of the book "Environmental Monitoring with Arduino," 
which is included in the Atmospheric Gas Detector Kit. The only difference in the schematic 
is how you hook up the LCD - here the RX from the LCD goes to Digital Pin 1 (TX) on the Arduino.

This sketch is purely to get you going with the Sparkfun LCD and reading data from the sensors.
For information on how to store data to an SD Card or the Arduino's EEPROM, refer to the book.

To adjust the contrast on your Sparkfun LCD, turn it over and use a small screwdriver to adjust the small, metal potentiometer.
I'd recommend unplugging the power rail of the circuit while the code is uploading, in order to avoid any transmitting issues.

For more information on the Sparkfun LCD, go here: http://playground.arduino.cc/Learning/SparkFunSerLCD

*/

#include <SoftwareSerial.h>
#include <SerLCD.h>
#define txPin 2

const int gasPin1 = A5;
const int gasPin2 = A4;
const int heaterPin1 = 12;
const int heaterPin2 = 9;
const int BuffTime = 10; // This is the rough time (in seconds) before the readings will show up on the LCD
int gasVal1 = 0;
int gasVal2 = 0;
int count = 0;

void setup()
{
  Serial.begin(9600);
  backlightOn(); 
  pinMode(heaterPin1, OUTPUT);
  pinMode(heaterPin2, OUTPUT);
  digitalWrite(heaterPin1, HIGH); // Turns heater in MQ-6 on.
  digitalWrite(heaterPin2, HIGH); // Turns heater in MQ-2 on.
}

void loop()
{  
  while (count < BuffTime/.05) // Loop for hiding the sensor readouts while they level out
  {
    gasVal1 = analogRead(gasPin1);
    gasVal2 = analogRead(gasPin2);
    selectLineOne();
    Serial.print("Buffering...");
    delay(50);
    count ++; // Adds one to "count"
    clearLCD(); // Clears the LCD screen
  }
  gasVal1 = analogRead(gasPin1); // Reads the first gas sensor and assigns the value to gasVal1
  gasVal2 = analogRead(gasPin2); // Reads the second gas sensor and assigns the value to gasVal2
  delay(50);
  selectLineOne();
  Serial.print("MQ-6: ");
  Serial.print(gasVal1,DEC);  
  selectLineTwo();
  Serial.print("MQ-2: ");  
  Serial.print(gasVal2,DEC); 
  delay(50); 
}

void selectLineOne()
{
   Serial.write(0xFE);   // command flag
   Serial.write(128);    // position
   delay(10);
}

void selectLineTwo()
{
   Serial.write(0xFE);   // command flag
   Serial.write(192);    // position
   delay(10);
}

void clearLCD()
{
   Serial.write(0xFE);   // command flag
   Serial.write(0x01);   // clear command.
   delay(10);
}

void backlightOn()
{  //turns on the backlight
   Serial.write(0x7C);   // command flag for backlight stuff
   Serial.write(140);    // brightness level. (140 = 40%, 150 = 73%, 157 = 100%) 
   delay(10);
}

void backlightOff()
{  //turns off the backlight
   Serial.write(0x7C);   // command flag for backlight stuff
   Serial.write(128);     // light level for off.
   delay(10);
}

