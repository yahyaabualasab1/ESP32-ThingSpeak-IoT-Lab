# ESP32 DHT22 ThingSpeak IoT Lab

An ESP32 project that reads temperature and humidity from a DHT22 sensor and sends the readings to ThingSpeak every 20 seconds.

## Components and wiring

| DHT22 pin | ESP32 pin |
| --- | --- |
| VCC | 3V3 |
| GND | GND |
| SDA (data) | GPIO 15 |

The Wokwi circuit is included in `diagram.json`.

## Run the project

1. Open the [Wokwi simulation](https://wokwi.com/projects/478964288849283073), or import the included sketch, circuit, and library files into a Wokwi ESP32 project.
2. Create a ThingSpeak channel with **Field 1** for temperature in degrees Celsius and **Field 2** for relative humidity in percent.
3. In your working copy of `sketch.ino`, replace `YOUR_THINGSPEAK_WRITE_API_KEY` with the channel's Write API Key. Keep your key private and do not commit it.
4. The simulation uses the `Wokwi-GUEST` Wi-Fi network with an empty password. For physical hardware, set your own Wi-Fi credentials and adjust `WiFi.begin(...)` if the network uses a different channel.
5. Start the simulation and open the serial monitor at **115200 baud**. Readings are sent every **20 seconds**. A successful update returns HTTP 200 and a positive ThingSpeak entry ID.

## Project files

- `sketch.ino`: sensor readings, Wi-Fi connection, and ThingSpeak HTTP updates.
- `diagram.json`: ESP32 and DHT22 circuit for Wokwi.
- `libraries.txt`: Wokwi library configuration, including the library providing `DHTesp.h`.
- `wokwi-project.txt`: original simulation link.
- `screenshots/`: location for project screenshots.

The published sketch uses a placeholder for the ThingSpeak Write API Key. Configure it locally before running.
