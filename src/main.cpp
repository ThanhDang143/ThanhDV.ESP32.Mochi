#include <Arduino.h>
#include <TFT_eSPI.h>

// Khởi tạo đối tượng tft từ thư viện
TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(115200);
  delay(300);

  Serial.println("Start init TFT!!!");
  tft.init();
  Serial.println("Init TFT OK!!!");

  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN);
  tft.setTextSize(2);
  tft.setCursor(0, 0);
  tft.println("Hello World!");
}

void loop() {
  Serial.println("Looping...");
  delay(1000);
}