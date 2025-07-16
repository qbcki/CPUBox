#include <Arduino.h>
#include <TFT_eSPI.h> // Library for TFT display
#include <Keypad.h>   // Library for membrane keypad
#include <SD.h>       // Library for SD card handling

// TFT display pin definitions
#define TFT_CS   5
#define TFT_DC   16
#define TFT_RST  4
#define TFT_BLK  21  // Optional, backlight

// microSD pin definitions
#define SD_CS    5  // Make sure SD CS does not conflict with TFT

TFT_eSPI tft = TFT_eSPI();  // Create TFT object

// Keypad pin definitions
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {12, 13, 14, 27}; // Rows
byte colPins[COLS] = {26, 25, 33, 32}; // Columns
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Data structure for processor info
struct Processor {
  String name;
  String description;
};

// Array of processors (later loaded from SD)
Processor processors[100]; // Assume no more than 100 processors
int processorCount = 0; // Current number of loaded processors

// Filename with data
const char *fileName = "/procesory.txt";

void setup() {
  Serial.begin(115200); // Initialize serial communication

  // Initialize TFT display
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.setCursor(0, 0);
  tft.println("Welcome!");

  // Initialize SD card
  if (!SD.begin(SD_CS)) {
    tft.println("SD Error!");
    Serial.println("SD Error!");
    return;
  }
  tft.println("SD card ready!");
  Serial.println("SD card ready!");

  // Load data from file
  loadDataFromFile();
}

void loop() {
  char key = keypad.getKey(); // Read character from keypad
  if (key) {
    Serial.print("Entered: ");
    Serial.println(key);
    if (isdigit(key)) {
      int processorNumber = key - '0'; // Convert character to number
      if (processorNumber > 0 && processorNumber <= processorCount) {
        displayInfo(processorNumber - 1); // Display processor info
      } else {
        displayMessage("Invalid number!");
      }
    } else if (key == '#') {
      // Reset display
      tft.fillScreen(TFT_BLACK);
      tft.setTextColor(TFT_WHITE);
      tft.setTextSize(2);
      tft.setCursor(0, 0);
      tft.println("Welcome!");
    }
  }
}

void displayInfo(int index) {
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0);
  tft.setTextSize(2);
  tft.println(processors[index].name);
  tft.setTextSize(1);
  tft.println(processors[index].description);
}

void displayMessage(String message) {
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0);
  tft.setTextSize(2);
  tft.println(message);
}

// Function to load data from file
void loadDataFromFile() {
  File file = SD.open(fileName, FILE_READ);
  if (!file) {
    Serial.println("Error opening file!");
    tft.println("File missing!");
    return;
  }

  int index = 0;
  while (file.available()) {
    String line = file.readStringUntil('\n');
    if (line.length() > 0) {
      int separator = line.indexOf(';'); // Assuming data is separated by semicolon
      if (separator > 0) {
        processors[index].name = line.substring(0, separator);
        processors[index].description = line.substring(separator + 1);
        index++;
      }
    }
  }
  processorCount = index;
  file.close();
  Serial.print("Loaded ");
  Serial.print(processorCount);
  Serial.println(" processors from file.");
}
