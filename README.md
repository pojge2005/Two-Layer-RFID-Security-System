# Two-Layer-RFID-Security-System
The first layer, followed by a password (e.g., "1234") via keypad as the second layer, built with PIC18F4520 microcontroller, 16x2 LCD, EM-18 RFID module, and 4x4 keypad for access control like door locks. This matches your prior PIC18F4520 implementation where valid RFID prompts password entry, granting access on match or denying otherwise 
# Project Summary
This project implements a two-layer security system using RFID card verification followed by password authentication through a keypad. Built on the PIC18F4520 microcontroller with a 16x2 LCD for user interface, it provides secure access by first validating the RFID tag and then prompting for a numeric PIN. Access is granted when both checks pass, activating a relay to control door locking mechanisms.

# Key Features
Dual authentication: RFID card scanning plus 4-digit password entry

Real-time feedback via 16x2 LCD display for user prompts and status

Configurable authorized RFID card list and password

Relay control for door lock actuation on successful authentication

Secure keypad input with masked password entry and access denial on failure

Easy hardware integration with EM-18 RFID module, matrix keypad, and PIC18F4520 MCU
# Two-Layer Security System
![Demo GIF if available]

## Features
- RFID (EM-18) + Password (4x4 keypad)
- PIC18F4520, LCD feedback
- Relay for door lock

## Hardware
- Schematic: /docs/circuit.png

## Software
- XC8 compiler, MPLAB X
- Build: `make`

## Demo
LCD flow: "Scan Card" → Valid → "Enter PIN" → "Access Granted"
Two-Layer RFID & Password Security System

PIC18F4520-based dual authentication: RFID card + 4-digit PIN for secure access control.​

Features
Layer 1: RFID (EM-18 module) scans unique card UID; invalid cards show "Invalid Card" on LCD.

Layer 2: Valid RFID prompts "Enter Password" via 4x4 keypad (default: 1234).

Feedback: 16x2 LCD displays "Scan Card", "Access Granted"/"Access Denied"; relay activates lock on success.

Security: UART-based RFID read, masked keypad input, timeout/reset on failure.​

Hardware Requirements
Component	Details	Connection
Microcontroller	PIC18F4520	Core
RFID Module	EM-18 (UART)	TX → RC7 (RX), VCC/GND
LCD	16x2 HD44780	RS=RB0, EN=RB1, D4-D7=RB4-RB7
Keypad	4x4 Matrix	Rows: RA0-RA3, Cols: RA4-RA7
Relay	5V Module	RB2 (control)
Crystal	4MHz	OSC1/OSC2 ​
Schematic: circuit.pdf

Software Setup
IDE: MPLAB X with XC8 compiler.

Build: Clone repo, open TwoLayerSecurity.X, compile/flash via PICkit3.

Config: Edit config.h for your RFID UID (AUTHORIZED_CARD_ID[] = {0xXX,0xXX,...}) and PIN.
nstallation & Demo
Wire per schematic, power 5V supply.

Flash .hex to PIC18F4520.

Demo flow: LCD "Scan Card" → Tap valid RFID → "Enter Password" → 1234 → "Access Granted" + relay ON (5s).
Idle: "Scan RFID Card"
↓ Valid UID
"Enter Password: ****"
↓ Match (1234)
"Access Granted" → Relay ON
↓ Mismatch/Invalid
"Access Denied" → Reset

Future Enhancements
Add buzzer/LED indicators.

EEPROM for multiple cards/PINs.

ESP8266 for IoT logging.
