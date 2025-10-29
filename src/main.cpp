#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SD.h>

// Tạo đối tượng tft từ thư viện
TFT_eSPI tft = TFT_eSPI();

// Khai báo phần cứng cho SDCard
const int SDCARD_PIN_CS = 7;
const int SDCARD_PIN_SCK = 4;
const int SDCARD_PIN_MISO = 5;
const int SDCARD_PIN_MOSI = 6;

// Khai báo hàm
void initTFT(); // Khởi tạo màn hình
void initSD(); // Khởi tạo SDCard
void listDir(fs::FS &fs, const char * dirname, uint8_t levels); // Hàm hiển thị các tệp trong SD // Dùng để test chưa cần quan tâm nhiều

void setup() {
  initTFT();
  initSD();
}

int count = 0;
void loop() {}

void initTFT()
{
  tft.init(); 
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN);
  tft.setTextSize(1);
  tft.setCursor(0, 0);
  tft.println("Init TFT success!!!");
}

void initSD()
{
  SPI.end();
  SPI.begin(SDCARD_PIN_SCK, SDCARD_PIN_MISO, SDCARD_PIN_MOSI, SDCARD_PIN_CS);

  tft.print("Initializing SD card using CS pin: ");
  tft.println(SDCARD_PIN_CS);

  if (!SD.begin(SDCARD_PIN_CS, SPI)) {
    tft.setTextColor(TFT_RED);
    tft.println("SD mount failed (wiring/freq).");
    return;
  }

  tft.setTextColor(TFT_GREEN);
  tft.println("SD card initialized.");

  uint8_t type = SD.cardType();
  if (type == CARD_NONE) {
    tft.setTextColor(TFT_RED);
    tft.println("No SD card detected.");
    return;
  }
  tft.printf("Type: %s\n", type == CARD_MMC ? "MMC" :
                         type == CARD_SD  ? "SDSC" :
                         type == CARD_SDHC? "SDHC/SDXC" : "UNKNOWN");
  tft.printf("Size: %llu MB\n", SD.cardSize() / (1024ULL * 1024ULL));

  tft.println("Filesystem Content:");
  listDir(SD, "/", 0);
  tft.println("\n--- Test Complete ---");
}

// Hàm liệt kê nội dung thư mục (lấy từ ví dụ của thư viện SD)
void listDir(fs::FS &fs, const char * dirname, uint8_t levels) {
  tft.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    tft.println("Failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    tft.println("Not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      tft.print("  DIR : ");
      tft.println(file.name());
      if (levels) {
        listDir(fs, file.path(), levels - 1);
      }
    } else {
      tft.print("  FILE: ");
      tft.print(file.name());
      tft.print("\tSIZE: ");
      tft.println(file.size());
    }
    file = root.openNextFile();
  }
}