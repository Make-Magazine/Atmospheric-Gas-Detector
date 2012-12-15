/*

Maker Shed Atmospheric Gas Detector Kit Test Code
by Eric Weinhoffer

For a schematic, view page 21 of the book "Environmental Monitoring with Arduino," 
which is included in the Atmospheric Gas Detector Kit. The only difference in the schematic 
is how you hook up the LCD - here the RX from the LCD goes to Digital Pin 7 on the Arduino, and TX
on the LCD goes to Digital Pin 6.

This sketch is purely to get you going with the Seeed LCD and reading data from the sensors.
For information on how to store data to an SD Card or the Arduino's EEPROM, refer to the book.

For more information on the Seeed LCD, go here: http://www.seeedstudio.com/wiki/Grove_-_Serial_LCD_v1.0b

*/

#include <SerialLCD.h>
#if ARDUINO < 100
#include <NewSoftSerial.h> 
#else
#include <SoftwareSerial.h>
#endif

const int gasPin1 = A5;
const int gasPin2 = A4;
const int heaterPin1 = 12;
const int heaterPin2 = 9;
const int BuffTime = 10; // This is the rough time (in seconds) before the readings will show up on the LCD
int gasVal1 = 0;
int gasVal2 = 0;
int count = 0;


SerialLCD slcd(6,7); // Assign pins the LCD is connected to: slcd(TX,RX)

void setup() 
{
  slcd.begin();
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
    slcd.setCursor(0, 0); // Sets the cursor to the first column and first row
    slcd.print("Buffering...");
    delay(50);
    count ++; // Adds one to "count"
    slcd.clear();  // Clears the LCD
  }
  slcd.setCursor(0, 0); // Sets the cursor to the first column and first row
  slcd.print("MQ-6: ");
  slcd.setCursor(0, 1); // Sets the cursor to the first column and second row
  slcd.print("MQ-2: ");  
  gasVal1 = analogRead(gasPin1); // Reads the first gas sensor and assigns the value to gasVal1
  gasVal2 = analogRead(gasPin2); // Reads the second gas sensor and assigns the value to gasVal2
  delay(50);
  slcd.setCursor(6, 0); // Sets the cursor to the sixth column and first row
  slcd.print(gasVal1,DEC); // Prints the gasVal1 value on the LCD
  slcd.setCursor(6, 1); // Sets the cursor to the sixth column and second row
  slcd.print(gasVal2,DEC); // Prints the gasVal2 value on the LCD
  delay(50); 
}

