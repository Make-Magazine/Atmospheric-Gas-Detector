/*

Maker Shed Atmospheric Gas Detector Kit Smoke Alarm Code
by Eric Weinhoffer

The LCD will display a warning for high smoke levels when the sensor reads a value above the threshold - 475 by default.

For a schematic, view page 21 of the book "Environmental Monitoring with Arduino," 
which is included in the Atmospheric Gas Detector Kit. The only difference in the schematic 
is how you hook up the LCD - here the RX from the LCD goes to Digital Pin 7 on the Arduino, and TX
on the LCD goes to Digital Pin 6.

This sketch is a simple example of what you can do with the MQ-2 Gas Sensor and the Seeed LCD.
For information on how to store data to an SD Card or the Arduino's EEPROM, refer to the book.

For more information on the Seeed LCD, go here: http://www.seeedstudio.com/wiki/Grove_-_Serial_LCD_v1.0b

*/

#include <SerialLCD.h>
#if ARDUINO < 100
#include <NewSoftSerial.h> 
#else
#include <SoftwareSerial.h>
#endif

const int gasPin2 = A4;
const int heaterPin2 = 9;
const int BuffTime = 10; // This is the rough time (in seconds) before the readings will show up on the LCD
int gasVal2 = 0;
int count = 0;


SerialLCD slcd(6,7); // Assign pins the LCD is connected to: slcd(TX,RX)

void setup() 
{
  slcd.begin();
  pinMode(heaterPin2, OUTPUT);
  digitalWrite(heaterPin2, HIGH); // Turns heater in MQ-2 on.
}

void loop() 
{
  while (count < BuffTime/.05) // Loop for hiding the sensor readouts while they level out
  {
    gasVal2 = analogRead(gasPin2);
    slcd.setCursor(0, 0); // Sets the cursor to the first column and first row
    slcd.print("Buffering...");
    delay(50);
    count ++; // Adds one to "count"
    slcd.clear();  // Clears the LCD
  }
  slcd.setCursor(0, 0); // Sets the cursor to the first column and first row
  slcd.print("Smoke Level");
  slcd.setCursor(0, 1); // Sets the cursor to the first column and second row
  slcd.print("MQ-2: ");  
  gasVal2 = analogRead(gasPin2); // Reads the second gas sensor and assigns the value to gasVal2
  delay(50);
  slcd.setCursor(6, 1); // Sets the cursor to the sixth column and first row
  slcd.print(gasVal2,DEC); // Prints the gasVal2 value on the LCD
  delay(50); 
  while (gasVal2 > 475) // This is the threshold value for the alarm
  {
    gasVal2 = analogRead(gasPin2);
    slcd.setCursor(0, 0);
    slcd.print("DANGER DANGER");
    slcd.setCursor(0, 1);
    slcd.print("HIGH SMOKE LEVEL");
    delay(50);
    slcd.clear();
  }
}
