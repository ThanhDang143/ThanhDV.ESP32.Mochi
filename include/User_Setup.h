// Driver and panel size
#define ST7789_DRIVER
#define ESP32_C3_DMA_ERROR_WORKAROUND

#define TFT_WIDTH 240
#define TFT_HEIGHT 240

// Pin mapping (verified working with color fills)
#define TFT_MOSI 6
#define TFT_SCLK 4
#define TFT_CS   -1

#define TFT_DC   2
#define TFT_RST  1
#define TFT_BL   3

#define TFT_BACKLIGHT_ON HIGH

// Ensure text fonts are compiled in
#define LOAD_GLCD    // Font 1 (built-in), required for basic text
#define LOAD_FONT2   // Small 16 px font
#define LOAD_FONT4   // Medium 26 px font
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF  // FreeFonts (optional)
#define SMOOTH_FONT // Anti-aliased fonts (needs FS)

// SPI performance
#define SPI_FREQUENCY       40000000
#define SPI_READ_FREQUENCY  20000000