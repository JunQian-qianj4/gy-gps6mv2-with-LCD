#include "TinyGPS++.h"
#include "SoftwareSerial.h"
#include "LiquidCrystal.h"

const int  rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

SoftwareSerial gpsRead(4,3); // Rx-pin 4 , TxPin 3
TinyGPSPlus gps;
void setup() {
  Serial.begin(115200);
  gpsRead.begin(9600);
  Serial.println("GPS Start");

  lcd.begin(16,2);
  
}

void loop() 
{
//--------------------------------
  while(gpsRead.available())
  {
    gps.encode(gpsRead.read());
  }
  if(gps.location.isUpdated())
  {
    Serial.println("Satellite count:");
    Serial.println(gps.satellites.value());
    Serial.println("Latitude:");
    Serial.println(gps.location.lat(),6); 
    Serial.println("longitude:");
    Serial.println(gps.location.lng(),6);
    Serial.println("Speed KMPH:");
    Serial.println(gps.speed.kmph());
    Serial.println("Altitude Meters:");
    Serial.println(gps.altitude.meters());
    Serial.println("");
  }
//------------------------------------
  lcd.setCursor(0,0);
  lcd.print("Speed: ");
  lcd.print("       Latitude :");
  lcd.print(gps.location.lat(),6);

  lcd.setCursor(0,1);
  lcd.print(gps.speed.kmph());
  lcd.print(" KM/H");
  lcd.print("      longitude:");
  lcd.print(gps.location.lng(),6);
  lcd.scrollDisplayLeft();
  
  delay(500);

  
}
