#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTPIN 8            // DHT11 data pin is connected to Arduino pin 8
#define DHTTYPE DHT11       // DHT11 sensor is used

DHT dht(DHTPIN, DHTTYPE);   // Initialize DHT library
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

char temperature[] = "Temperature= 0.0 C";
char humidity[] = "Humidity= 00%";

const float temperatureThreshold = 30.0;

void setup() {
  lcd.begin(16, 2);       
  dht.begin();
  lcd.print("Reading Data...");
}

void loop() {
  delay(2000);        
  float tempC = dht.readTemperature();
  float humidityValue = dht.readHumidity();
  
  if (isnan(tempC) || isnan(humidityValue)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Error reading data");
    delay(2000);
    lcd.clear();
    lcd.print("Reading Data...");
    return;
  }

 
  dtostrf(tempC, 4, 1, temperature + 13);
  

  int hum = (int)humidityValue;
  humidity[9] = '0' + hum / 10;
  humidity[10] = '0' + hum % 10;
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(temperature);
  lcd.setCursor(0, 1);
  lcd.print(humidity);


  if (tempC > temperatureThreshold) {
    lcd.setCursor(0, 1);
    lcd.print("ALERT!           ");
  }
}
