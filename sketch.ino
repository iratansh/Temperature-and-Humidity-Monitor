// Temp and Humidity Monitor with OLED display

#include <dht.h> 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define dataPin 2
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
dht DHT;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Stop program if display initialization fails
  }
  display.clearDisplay();
  display.setTextSize(1); // Set text size
  display.setTextColor(SSD1306_WHITE); // Set text color
}

void loop() {
  // Read data from DHT sensor
  DHT.read22(dataPin);
  float t = DHT.temperature; 
  float h = DHT.humidity;    

  // Clear the display
  display.clearDisplay();

  // Display temperature
  display.setCursor(0, 0); // Set cursor to top-left
  display.print("Temperature: ");
  display.print(t);
  display.println(" C");

  // Display humidity
  display.setCursor(0, 10); // Move cursor to next line
  display.print("Humidity: ");
  display.print(h);
  display.println(" %");

  display.display(); // Updates display

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %");

  delay(2000);
}

