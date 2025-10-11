#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

const int CS_PIN = 8;

void setup()
{
  Serial.begin(115200);
  delay(1000);
  unsigned long start = millis();
  while (!Serial && millis() - start < 2000)
  {
    delay(1);
  }

  Serial.println("\nInitializing SD card...");

  SPI.begin();

  if (!SD.begin(CS_PIN))
  {
    Serial.println("Card Mount Failed");
    return;
  }
  Serial.println("SD card initialized.");

  File root = SD.open("/");
  if (root)
  {
    Serial.println("Files in root directory:");
    while (true)
    {
      File entry = root.openNextFile();
      if (!entry)
      {
        break;
      }
      Serial.print("  ");
      Serial.print(entry.name());
      if (entry.isDirectory())
      {
        Serial.println("/");
      }
      else
      {
        Serial.print("\t\t");
        Serial.println(entry.size(), DEC);
      }
      entry.close();
    }
    root.close();
  }
  else
  {
    Serial.println("error opening root directory");
  }
}

void loop()
{
  Serial.println("Test!!!!");
  delay(1000);
}