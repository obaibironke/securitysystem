# securitysystem
A custom motion sensor triggered security system that alerts me whenever someone enters my room. 

Hardware:

Custom PCB
XIAO ESP32-S3
PIR motion sensor
Photoresistor
MAX7219 8-digit display
Active buzzer
Arm/disarm button
Power switch
Custom enclosure

Features:

WiFi connectivity with auto-reconnect
Telegram bot alerts for motion, arm/disarm, system online
Telegram bot commands
Google Sheets event logging
Night mode that auto-disarms in daylight using photoresistor
Force disarm via Telegram
High motion alert that triggers when 3+ detections in a window
Motion counter displayed on 8-digit display, capped at 99999999
Different buzzer patterns for armed, disarmed, and motion detected
Motion timeout to prevent spam detection


