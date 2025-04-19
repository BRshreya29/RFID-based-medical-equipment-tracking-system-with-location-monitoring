# RFID-Based Medical Equipment Tracking System with Location Monitoring

This project is a smart tracking system designed to monitor the movement and usage of critical medical equipment in real time. It combines RFID and GPS technologies with Wi-Fi-based data transmission to Google Sheets for centralized and live monitoring. 

The system has two separate circuits:
- **RFID Reader Circuit**: RFID scanning using ESP8266 + RC522 module.  
   ![RFID Reader Circuit](https://github.com/BRshreya29/RFID-based-medical-equipment-tracking-system-with-location-monitoring/blob/main/Scanner_circuit_diagram.png)
- **Device Attached to Equipment Circuit**: GPS location capture using ESP32 + NEO-6M GPS module.
   ![Device Attached Circuit](https://github.com/BRshreya29/RFID-based-medical-equipment-tracking-system-with-location-monitoring/blob/main/Device_attached_to_Equipment_circuit_diagram.png)

The data from both circuits is sent to the same Google Sheet via Wi-Fi and displayed with a map link for live tracking.

### Google Sheet Link
[Google Sheet - RFID Location Tracking](https://docs.google.com/spreadsheets/d/1G8bnSog_9L24DeqO9bnbIN_9HJ3Avwo1S7GBQ2KLZVw/edit?usp=sharing)

## Sample Output on Google Sheet

| Timestamp           | Tag ID        | Latitude  | Longitude | Map Link                 |
|---------------------|---------------|-----------|-----------|--------------------------|
| 2025-04-19 12:32:45 | OxygenTank-283|  25.5397  | 84.849556 | [Open](https://www.google.com/maps?q=25.539700,84.849556) |

---
Click on the link to open Maps.

## Features

- Real-time GPS location tracking using ESP32 and NEO-6M GPS module.
- RFID tag scanning using ESP8266 and RC522 module.
- Auto logging of scan data to Google Sheets with timestamp and location.
- Clickable Google Maps link for equipment location.
- Modular design with independent tracking and scanning units.

---

## Hardware Used

| Component         | Description                        |
|------------------|------------------------------------|
| ESP32-WROOM      | Wi-Fi microcontroller for GPS data |
| ESP8266 NodeMCU  | Wi-Fi microcontroller for RFID     |
| NEO-6M GPS       | GPS module for real-time location  |
| RFID-RC522       | RFID reader module                 |
| MFRC522 Tags     | RFID cards/tags for equipment      |
| Power Modules    | USB/3.3V regulated power supply    |

---

## Circuit Description

### Circuit 1: RFID Scanner with ESP8266
- **RFID-RC522 Connections**
  - SDA → D4
  - SCK → D5
  - MOSI → D7
  - MISO → D6
  - RST → D3
  - GND → GND
  - VCC → 3.3V

- **ESP8266 connects to Wi-Fi** and sends scanned tag ID to Google Sheets using IFTTT webhook.

### Circuit 2: GPS Module with ESP32
- **NEO-6M Connections**
  - VCC → 3.3V
  - GND → GND
  - TX → GPIO16
  - RX → GPIO17

- **ESP32 connects to Wi-Fi**, receives GPS data (latitude & longitude), and sends it to Google Sheets using another IFTTT webhook.


---

## Software Stack

- **Arduino IDE** for programming ESP32 and ESP8266
- **IFTTT Webhooks** to send data to Google Sheets
- **Google Sheets** to log scanned tag and location data
- **Libraries Used:**
  - `WiFi.h`
  - `HTTPClient.h`
  - `MFRC522.h`
  - `SPI.h`
  - `SoftwareSerial.h`
  - `TinyGPSPlus.h`

---


## Demo

▶️ [![Watch Demo Video](https://img.youtube.com/vi/7TRYzmLjbuI/0.jpg)](https://www.youtube.com/watch?v=7TRYzmLjbuI)

---

## Working Demo Description

When an RFID tag is scanned:
1. The ESP8266 reads the tag ID and sends it to Google Sheets.
2. The ESP32 continuously reads GPS coordinates and sends them along with timestamp and map link.
3. The data is recorded in real-time to the shared Google Sheet.

![System Flow Diagram](https://github.com/BRshreya29/RFID-based-medical-equipment-tracking-system-with-location-monitoring/blob/main/system_flow_diagram.jpg) 

---

**Made with dedication for our course project EE341 - Electromagnetic Theory at IIT Patna – bridging healthcare and technology through smart tracking solutions.**
