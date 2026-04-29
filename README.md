# securitysystem
A custom motion sensor triggered security system that alerts me whenever someone enters my room. I made it because my sister kept entering myroom without me knowing so now I can catch her. It detects motion using a PIR sensor that will be soldered onto the PCB directly.

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

BOM:

<img width="584" height="408" alt="image" src="https://github.com/user-attachments/assets/0e73b356-8a5d-4e1c-8e20-e849bc25107f" />


Images:

<img width="876" height="565" alt="image" src="https://github.com/user-attachments/assets/176c0bf5-de1d-439b-a70b-26c5f3bd0718" />

<img width="923" height="700" alt="image" src="https://github.com/user-attachments/assets/7c5bf5ab-910c-42fd-bebc-ce68bf8178d0" />

<img width="731" height="660" alt="image" src="https://github.com/user-attachments/assets/5abf99ac-126d-4a1f-878a-35f364184533" />

<img width="430" height="674" alt="image" src="https://github.com/user-attachments/assets/dd42b169-50b9-40e8-aedd-0ba694a99438" />



