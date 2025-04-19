# RFID-Based Medical Equipment Tracking System with Location Monitoring

This project is a smart tracking system designed to monitor the movement and usage of critical medical equipment in real time. It combines RFID and GPS technologies with Wi-Fi-based data transmission to Google Sheets for centralized and live monitoring.

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

## System Architecture

1. **ESP32 (GPS Module)**
   - Continuously reads GPS data.
   - Sends current coordinates to Google Sheet via Wi-Fi.

2. **ESP8266 (RFID Module)**
   - Waits for tag scan.
   - Sends tag ID and timestamp to the same Google Sheet.
   - Both modules write to different columns of the same row via a common key (e.g., timestamp or scan count).

---

## 📂 Project Structure

RFID-GPS-Medical-Tracker/ ├── ESP32_GPS_Module/ │ └── gps_to_sheet.ino ├── ESP8266_RFID_Module/ │ └── rfid_to_sheet.ino ├── Images/ │ └── system_flowchart.png ├── README.md └── demo_video_link.txt


## 🚀 Getting Started

### 1. Set Up Google Sheets

- Create a Google Sheet with columns: `Timestamp`, `Tag ID`, `Latitude`, `Longitude`, `Map Link`.
- Use [Google Apps Script](https://script.google.com) to create a Web App that accepts POST requests and writes to the sheet.
- Deploy it and copy the Web App URL.

### 2. Flash Firmware

- Open the `.ino` files in Arduino IDE.
- Install required libraries:
  - `WiFi.h`, `HTTPClient.h`, `TinyGPS++`, `MFRC522`, etc.
- Replace placeholders in code with your:
  - Wi-Fi credentials
  - Google Script Web App URL
- Upload the code to your ESP32 and ESP8266 boards respectively.

### 3. Connect Modules

- Wire the GPS module to ESP32 UART pins.
- Connect RFID-RC522 to ESP8266 using SPI.
- Power up and open Serial Monitor for debug logs.

---

## 📊 Sample Output on Google Sheet

| Timestamp           | Tag ID       | Latitude  | Longitude | Map Link                            |
|---------------------|--------------|-----------|-----------|-------------------------------------|
| 2025-04-19 12:32:45 | E7 2A 1F B3  | 25.5911   | 85.1376   | [Open](https://maps.google.com/?q=...) |

---

## 🎥 Demo

▶️ [Watch Demo Video](https://your-link.com)

---

## 📸 System Flow Diagram

![System Flowchart](Images/system_flowchart.png)

---

## ✍️ Contributors

- **Shreya Reddy B R** - [@shreyareddybr](https://github.com/shreyareddybr)
- Team members can be listed here...
