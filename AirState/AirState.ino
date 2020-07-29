#include <Wire.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <Wire.h>
#include <arduino.h>
#include <math.h>
#include "SparkFunBME280.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

BME280 sensor;
#define TEMP_DRIFT 1.8

void setup() {
    Wire.begin();
    sensor.settings.commInterface = I2C_MODE; 
    sensor.settings.I2CAddress =0x76;
    sensor.settings.runMode = 3; 
    sensor.settings.tStandby = 0;
    sensor.settings.filter = 0;
    sensor.settings.tempOverSample = 1 ;
    sensor.settings.pressOverSample = 1;
    sensor.settings.humidOverSample = 1;
    delay(10);
    sensor.beginI2C();
    sensor.setMode(MODE_SLEEP);

    lcd.begin(16, 2);
    lcd.setCursor(0, 0);

    // LCD birghtness
    analogWrite(10, 280);
}

void loop() {
    sensor.setMode(MODE_FORCED);
    lcd.setCursor(0, 0);
    lcd.print("Temp :");
    lcd.print(sensor.readTempC() - TEMP_DRIFT);
    lcd.setCursor(0, 1);
    lcd.print("Humi :");
    lcd.print(sensor.readFloatHumidity());

    delay(15000);
}