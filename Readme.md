# Processor Info Display – ESP32 with TFT, Keypad, and SD Card

This project is a simple embedded system using an **ESP32**, a **TFT display**, a **4x4 membrane keypad**, and a **microSD card**. It displays information about various processors stored on the SD card. Users can enter a number using the keypad to view detailed information about a specific processor.

---

## 📦 Features

- Reads processor data from a file on a microSD card.
- Displays processor names and descriptions on a TFT display.
- Accepts user input via a 4x4 membrane keypad.
- Displays error messages for invalid input.
- Can reset the screen to the welcome message using the `#` key.

---

## 🛠️ Hardware Requirements

- **ESP32 development board**
- **TFT display** (SPI, compatible with [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI))
- **4x4 membrane keypad**
- **MicroSD card module**
- **Wires, breadboard**, or PCB as needed

---

## 🔌 Pin Configuration

### TFT Display
| Signal | ESP32 Pin |
|--------|-----------|
| CS     | GPIO 5    |
| DC     | GPIO 16   |
| RST    | GPIO 4    |
| BLK    | GPIO 21   |

### Keypad
| Row / Column | ESP32 Pin |
|--------------|-----------|
| Row 0        | GPIO 12   |
| Row 1        | GPIO 13   |
| Row 2        | GPIO 14   |
| Row 3        | GPIO 27   |
| Col 0        | GPIO 26   |
| Col 1        | GPIO 25   |
| Col 2        | GPIO 33   |
| Col 3        | GPIO 32   |

### microSD Card
| Signal | ESP32 Pin |
|--------|-----------|
| CS     | GPIO 5    |

> ⚠️ Ensure TFT and SD card do not share the same CS pin if they're on the same SPI bus. Use separate SPI buses or manage CS manually.

---

## 📂 SD Card File Format

The SD card must contain a file named:  
/procesory.txt
Each line in the file should contain a processor name and its description, separated by a **semicolon (`;`)**:

**Example:**

Intel 8086;16-bit processor introduced in 1978
AMD Ryzen 5 3600;6-core desktop processor with SMT

---

## 🔧 Installation & Setup

1. Install the following Arduino libraries:
   - [`TFT_eSPI`](https://github.com/Bodmer/TFT_eSPI)
   - [`Keypad`](https://www.arduino.cc/reference/en/libraries/keypad/)
   - [`SD`](https://www.arduino.cc/en/Reference/SD)

2. Connect your hardware according to the pin configuration above.

3. Format your SD card to FAT32 and create the `procesory.txt` file.

4. Upload the code to your ESP32 using the Arduino IDE.

---

## 🎮 How to Use

- On startup, the TFT will display a welcome message.
- Press any digit (1–9) on the keypad to view information about a processor (based on its order in the file).
- Press `#` to return to the welcome screen.
- If an invalid number is entered (e.g. 0 or out-of-range), an error message is shown.

---

## 📸 Example

```plaintext
Welcome!
> [User presses "2"]
Ryzen 5 3600
6-core desktop processor with SMT
