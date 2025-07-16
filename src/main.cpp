
#include <Arduino.h>
#include <TFT_eSPI.h> // Biblioteka do wyświetlacza TFT
#include <Keypad.h>   // Biblioteka do klawiatury membranowej
#include <SD.h>       // Biblioteka do obsługi karty SD

// Definicje pinów wyświetlacza
#define TFT_CS   5
#define TFT_DC   16
#define TFT_RST  4
#define TFT_BLK  21  // Opcjonalnie, podświetlenie

// Definicje pinów microSD
#define SD_CS    5  // Upewnij się, że CS dla SD nie koliduje z TFT

TFT_eSPI tft = TFT_eSPI();  // Utworzenie obiektu TFT

// Definicje pinów klawiatury
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {12, 13, 14, 27}; // Rzędy
byte colPins[COLS] = {26, 25, 33, 32}; // Kolumny
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Dane procesorów (przykład - rozbuduj to!)
struct Procesor {
  String nazwa;
  String opis;
};

Procesor procesory[] = {
  {"Pentium III", "Procesor Intel Pentium III, 1 GHz"},
  {"Athlon XP", "Procesor AMD Athlon XP 2500+"},
  // Dodaj więcej procesorów...
};

const int liczbaProcesorow = sizeof(procesory) / sizeof(procesory[0]);

void setup() {
  Serial.begin(115200); // Inicjalizacja komunikacji szeregowej

  // Inicjalizacja wyświetlacza
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.setCursor(0, 0);
  tft.println("Witaj!");

  // Inicjalizacja karty SD
  if (!SD.begin(SD_CS)) {
    tft.println("Błąd SD!");
    return;
  }
  tft.println("Karta SD gotowa!");
}

void loop() {
  char key = keypad.getKey(); // Odczytanie znaku z klawiatury
  if (key) {
    Serial.print("Wprowadzono: ");
    Serial.println(key);
    if (isdigit(key)) {
      int numerProcesora = key - '0'; // Konwersja znaku na liczbę
      if (numerProcesora > 0 && numerProcesora <= liczbaProcesorow) {
        wyswietlInformacje(numerProcesora - 1); // Wyświetlenie informacji o procesorze
      } else {
        wyswietlKomunikat("Błędny numer!");
      }
    } else if (key == '#') {
      // Reset wyświetlacza
      tft.fillScreen(TFT_BLACK);
      tft.setTextColor(TFT_WHITE);
      tft.setTextSize(2);
      tft.setCursor(0, 0);
      tft.println("Witaj!");
    }
  }
}

void wyswietlInformacje(int index) {
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0);
  tft.setTextSize(2);
  tft.println(procesory[index].nazwa);
  tft.setTextSize(1);
  tft.println(procesory[index].opis);
}

void wyswietlKomunikat(String komunikat) {
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0);
  tft.setTextSize(2);
  tft.println(komunikat);
}
