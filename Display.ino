
////////////////////////////
#include <SoftwareSerial.h>     //Nötige Ressourcen laden
#include <MHZ19.h>
////////////////////////////

//////////////////////////////
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
//////////////////////////////

/////////////////
#define RX_PIN 11     //CO2-Sensor Pins
#define TX_PIN 12
/////////////////


///////////////////////
#define I2C_ADDR 0x27     
#define BACKLIGHT_PIN 3 
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0            //Display-Pins
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
///////////////////////

////////////////////////////////////////////////////////////////////////////////////
LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
MHZ19 vmCO2;                                                                            //Setup-Commands
SoftwareSerial mySerial(RX_PIN, TX_PIN);
int CO2;
////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////
void setup() {
  
  randomSeed(analogRead(0));
  Serial.begin(9600);
  mySerial.begin(9600);
  vmCO2.begin(mySerial);
  pinMode(1, OUTPUT);
  lcd.begin(24,4);
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home();
  lcd.setCursor(0, 0);
  lcd.print("Loading.");
  lcd.setCursor(0, 1);
  lcd.print(random(1, 9));
  lcd.setCursor(1, 1);
  lcd.print("%");
  delay(3000);
  lcd.clear();
  lcd.print("Loading..");
  lcd.setCursor(0, 1);
  lcd.print(random(10,70));
  lcd.setCursor(2, 1);
  lcd.print("%");
  delay(1000);
  lcd.clear();
  lcd.print("Loading...");
  lcd.setCursor(0, 1);
  lcd.print(random(71,99));
  lcd.setCursor(2, 1);
  lcd.print("%");
  delay(500);
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("Herzlich");
  delay(500);
  lcd.setCursor(5, 1);
  lcd.print("Willkommen");
  delay(500);
  lcd.setCursor(6, 2);
  lcd.print("zu ihrer");
  delay(500);
  lcd.setCursor(5, 3);
  lcd.print("CO2-Ampel!");
  delay(3000);
  lcd.clear();
}
///////////////////////////////////////////////////

///////////////////////////////////////
void loop() {
  
  CO2=vmCO2.getCO2();
  Serial.println(CO2);
  delay(500);

  lcd.setCursor(4, 0);
  lcd.print("Der CO2-Wert ");
  lcd.setCursor(6, 1);
  lcd.print("betraegt");
  lcd.setCursor(5, 2);
  lcd.print(CO2);
  lcd.setCursor(10, 2);
  lcd.print("ppm");
///////////////////////////////////////

///////////////////////////////////////
vmCO2.autoCalibration(false);
///////////////////////////////////////

///////////////////////////////////////
if(CO2<800) {
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Der CO2-Wert ");
  lcd.setCursor(6, 1);
  lcd.print("betraegt");
  lcd.setCursor(5, 2);
  lcd.print(CO2);
  lcd.setCursor(10, 2);
  lcd.print("ppm");
  lcd.setCursor(6, 3); 
  lcd.print("!Gut!");
  

}



if((CO2>=800) && (CO2<1000)) {
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Der CO2-Wert ");
  lcd.setCursor(6, 1);
  lcd.print("betraegt");
  lcd.setCursor(5, 2);
  lcd.print(CO2);
  lcd.setCursor(10, 2);
  lcd.print("ppm");
  lcd.setCursor(3, 3); 
  lcd.print("!Akzeptabel!");

}    
if(CO2>=1000) {
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Der CO2-Wert ");
  lcd.setCursor(6, 1);
  lcd.print("betraegt");
  lcd.setCursor(5, 2);
  lcd.print(CO2);
  lcd.setCursor(10, 2);
  lcd.print("ppm");
  lcd.setCursor(5, 3);
  lcd.print("!Zu Hoch!");
}
}

///////////////////////////////////////////////////
