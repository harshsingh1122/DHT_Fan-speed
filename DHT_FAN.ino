#include <DHT.h>

#define DHTPIN 2   // DHT11 data pin connected to digital pin 2
#define FAN_PIN 9   // Fan control pin (PWM)
#define DHTTYPE DHT11   // DHT type

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(FAN_PIN, OUTPUT);
  analogWrite(FAN_PIN, 0);  // Start with the fan off
  dht.begin();
}

void loop() {
  delay(2000);  // Delay for 2 seconds to stabilize DHT11 sensor

  float temperature = dht.readTemperature();
  
  if (!isnan(temperature)) {
    int fanSpeed;

    if (temperature <= 20) {
      fanSpeed = 20;
    } else if (temperature <= 40) {
      fanSpeed = map(temperature, 20, 40, 20, 90);  // Map temperature to PWM range (20% to 90%)
    } else {
      fanSpeed = 90;
    }

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C, Fan Speed: ");
    Serial.println(fanSpeed);

    analogWrite(FAN_PIN, fanSpeed);
  } else {
    Serial.println("Error reading temperature.");
  }
}
