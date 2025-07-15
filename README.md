# ESPER
*A small Internet-of-Things learning project*

---

## Project structure

| File | Purpose |
|------|---------|
| **`button.h`** | Sets up the button GPIO pins and provides helpers to read, append, and write the current light state. |
| **`dateTime.h`** | Declares `updateDateTime()` and `displayTime()` for keeping track of the real-time clock. |
| **`defines.h`** | Central place for all pin numbers, date/time constants, and other `#define` values. |
| **`fileFunc.h`** | Simple wrapper for saving data to `test.txt` and loading it back later. |
| **`getWifi.h`** | Handles connecting the ESP-based board to Wi-Fi. |
| **`includes.h`** | Convenience header that pulls in every other `*.h` file used by the project. |
| **`LED.h`** | Contains `shiftBlink()` which runs a short LED demo sequence. |
| **`light.h`** | Reads the analog value from the light-sensor pin and converts it to a usable number. |
| **`pins.h`** | Groups all `pinMode()` calls that configure the board’s output pins. |
| **`pitches.h`** | Maps musical note names to their corresponding frequencies for the buzzer. |
| **`sendData.h`** | Pushes light-sensor readings to the website and fetches:<br>— the buzzer frequency from the database<br>— the relay states for actuators. |
| **`songs.h`** | Scores the Pokémon battle-theme melody as an array of notes and durations. |
| **`sound.h`** | Uses an ultrasonic sensor to measure distance to the nearest object. |
| **`timedFunc.h`** | Periodic scheduler that, every *X* seconds, sends sensor data and refreshes actuator states. |

---

## Getting started

1. **Hardware** — An ESP-8266 or ESP-32, an LDR or similar light sensor, a couple of LEDs, a buzzer, and optional relays / ultrasonic sensor.  
2. **Software** — PlatformIO or the Arduino IDE, plus the ESP core and any required libraries.  
3. **Build** — Open the project folder in your IDE, adjust any pin numbers in `defines.h`, then upload to your board.  
4. **Wi-Fi** — Edit the SSID and password in `getWifi.h` (or in a separate secrets file).  
5. **Run** — Open the serial monitor to watch log messages and confirm the board is publishing data to your web endpoint.
