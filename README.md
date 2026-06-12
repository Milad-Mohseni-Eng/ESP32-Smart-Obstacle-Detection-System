# ESP32 Smart Obstacle Detection & Warning System

## Overview

The ESP32 Smart Obstacle Detection & Warning System is an embedded monitoring project built using the ESP32 development board and the IR-08H infrared obstacle detection sensor.

The system continuously monitors its surroundings and provides visual and audible alerts when an obstacle is detected.

An SSD1306 OLED display presents real-time system status, obstacle detection information, and event statistics.

---

## Features

- Real-time obstacle detection
- SSD1306 OLED status dashboard
- Three-state warning architecture
- Event counter
- Passive buzzer alarm
- Visual LED indicators
- Serial debugging output
- Low-cost hardware implementation

---

## Hardware Components

| Component | Quantity |
|------------|------------|
| ESP32 Development Board | 1 |
| IR-08H Obstacle Sensor | 1 |
| SSD1306 OLED Display | 1 |
| Passive Buzzer | 1 |
| Green LED | 1 |
| Orange LED | 1 |
| Blue LED | 1 |
| 220Ω Resistors | 3 |
| Breadboard | 1 |
| Jumper Wires | Several |

---

## Wiring

### IR-08H

| IR-08H | ESP32 |
|----------|----------|
| VCC | 3.3V |
| GND | GND |
| OUT | GPIO27 |

---

### OLED SSD1306

| OLED | ESP32 |
|--------|--------|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO21 |
| SCL | GPIO22 |

---

### LEDs

| LED | GPIO |
|--------|--------|
| Green | GPIO15 |
| Orange | GPIO2 |
| Blue | GPIO4 |

---

### Passive Buzzer

| Buzzer | ESP32 |
|----------|----------|
| Positive | GPIO14 |
| Negative | GND |

---

## System States

### Area Clear

- Green LED ON
- Orange LED OFF
- Blue LED OFF
- Buzzer OFF

OLED displays:

```text
AREA CLEAR
```

---

### Warning State

Obstacle detected for less than 2 seconds.

- Green LED OFF
- Orange LED ON
- Blue LED OFF
- Buzzer OFF

OLED displays:

```text
OBSTACLE DETECTED
```

---

### Alert State

Obstacle remains detected for more than 2 seconds.

- Green LED OFF
- Orange LED OFF
- Blue LED ON
- Passive buzzer activated

OLED displays:

```text
ALERT
BLOCKED
```

---

## Software Architecture

The project uses a finite-state style architecture.

Main states:

1. Clear
2. Warning
3. Alert

The system transitions automatically based on obstacle presence duration.

---

## Event Counter

The software tracks:

- Number of obstacle events
- Detection duration

This data is displayed on the OLED and Serial Monitor.

---

## Serial Monitor Example

```text
AREA CLEAR

Obstacle Count: 1 Time: 0 sec

Obstacle Count: 1 Time: 1 sec

Obstacle Count: 1 Time: 2 sec

Obstacle Count: 1 Time: 3 sec
```

---

## Libraries Required

Install:

### Adafruit SSD1306

### Adafruit GFX

Library Manager:

```text
Tools
→ Manage Libraries
```

Search:

```text
Adafruit SSD1306
```

and

```text
Adafruit GFX
```

---

## Future Improvements

- Wi-Fi notifications
- Telegram alerts
- Mobile dashboard
- Distance measurement integration
- Data logging to SD card
- Cloud monitoring
- Multi-sensor fusion

---

## Author

Milad Mohseni

---

## License

MIT License
