#include "DHT.h"
#include <LiquidCrystal_I2C.h> // Library for LCD

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows
int RXLED = 17; // The RX LED has a defined Arduino pin
int TXLED = 30; // The TX LED has a defined Arduino pin
int SOIL_PIN = A0;
const int AirValue = 620;   //you need to replace this value with Value_1
const int WaterValue = 310;  //you need to replace this value with Value_2
int soilMoistureValue = 0;
int soilmoisturepercent = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init(); // initialize the lcd
  lcd.backlight();
}

void loop() {
   //soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
  //Serial.print(soilmoisturepercent);
  //Serial.println("%");
  delay(2000);
  Serial.println();
  
  // Soil moisture
  soilMoistureValue = analogRead(A0);
  Serial.print("Soil moisture: ");
  Serial.println(soilMoistureValue);
  lcdPrint("Soil moisture", soilMoistureValue, " ");
 
  delay(5000);
  
  float h = dht.readHumidity();
  delay(500);
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) { // Check if any reads failed and exit early (to try again).
    Serial.println(F("Failed to read from DHT sensor!"));
  }
  float hic = dht.computeHeatIndex(t, h, false); // Compute heat index in Celsius
  
  Serial.print(F("Air Humidity: "));
  Serial.print(h);
  Serial.print("% ");
  lcdPrint("Air Humidity ", h, "% ");

  delay(5000);
  
  Serial.println();
  Serial.print(F("Air Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  lcdPrint("Air Temperature ", t, "C "); 

  delay(5000);
  
  Serial.println();
  Serial.print(F("Air Heat index: "));
  Serial.print(hic);
  Serial.println(F("°C "));
  lcdPrint("Air Heat Index ", hic, "C "); 
  
}

int lcdPrint(String desc, int value, String u){
  lcd.clear();
  //lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.home();
  lcd.print(desc);        // print message at (0, 0)
  lcd.setCursor(0, 1);    // move cursor to   (2, 1)
  lcd.print(value + u);
  return 0;
}
