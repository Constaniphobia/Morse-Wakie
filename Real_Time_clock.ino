#include "Wire.h"
#define DS3231_I2C_ADDRESS 0x68 

#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte decToBcd(byte val)
{
  return ((val/10*16) + (val%10));
}

int k = 0;
byte bcdToDec(byte val)
{
  return( (val/16*10) + (val%16));
}

void setup() 
{
  // put your setup code here, to run once:
  Wire.begin();
  lcd.begin(16, 2);
  Serial.begin(9600);
  //Ser Seconds, minutes, hours, day of week, date, month, year
  //setDS3231time(0,35,21, 4, 5, 4, 16);
}

void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0);
  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(dayOfWeek));
  Wire.write(decToBcd(dayOfMonth));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.endTransmission();
}

void readDS3231time(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);

  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}

void displayTime()
{
  byte second, minute,  hour, dayOfWeek, dayOfMonth, month, year;

   readDS3231time( &second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
   
   lcd.setCursor(0, 0);
   Serial.print(hour,DEC);
   lcd.print(hour,DEC);
   Serial.print(":");
   lcd.print(":");
   if(minute < 10)
   {
    Serial.print("0");
    lcd.print("0");
   }
   Serial.print(minute, DEC);
   lcd.print(minute, DEC);
   Serial.print(":");
   lcd.print(":");
   if(second < 10)
   {
    Serial.print("0");
    lcd.print("0");
   }
   
   Serial.print(second, DEC);
   lcd.print(second,DEC);
   Serial.print(" ");
   lcd.setCursor(0,1);
   Serial.print(dayOfMonth, DEC);
   lcd.print(dayOfMonth, DEC);
   Serial.print("/");
   lcd.print("/");
   Serial.print(month, DEC);
   lcd.print(month,DEC);
   Serial.print("/");
   lcd.print("/");
   Serial.print(year, DEC);
   lcd.print(year, DEC);
   Serial.print(" Day of week: ");
   lcd.setCursor(9,0);
   switch(dayOfWeek)
   {
      case 1:
        Serial.println("Sunday");
        lcd.print("Sun");
        break;
      case 2:
        Serial.println("Monday");
        lcd.print("Mon");
        break;
      case 3:
        Serial.println("Tuesday");
        lcd.print("Tue");
        break;
      case 4:
        Serial.println("Wednesday");
        lcd.print("Wed");
        break;
      case 5:
        Serial.println("Thursday");
        lcd.print("Thu");
        break;
      case 6:
        Serial.println("Friday");
        lcd.print("Fri");
        break;
      case 7:
        Serial.println("Saturday");
        lcd.print("Sat");
        break;
   }
   //This is for alarm
   if(second ==  50 && minute == 45 && hour == 20)
   {
    
      analogWrite(11, 5);               
   }
   if(second ==  0 && minute == 46 && hour == 20)
   {
    
        analogWrite(11, 0);              
   }
   
}
void loop() {
  // put your main code here, to run repeatedly:
  while(millis() % 1000 == 0)
  {
    displayTime();
  }
  

  
}
