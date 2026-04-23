# securitysystem
A custom motion sensor triggered security system that alerts me whenever someone enters my room. I made it because my sister kept entering myroom without me knowing so now I can catch her.

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

Name	Purpose	Quantity	Total Cost (USD)
AMS1117-3.3 SOT-223			1.89
10ï¿½F electrolytic caps			3.84
Ceramic caps			1.13
Slide switch			1.57
2.54mm pin headers			1.33
2-pin screw terminal			2.57
AAA battery holder			2.15
MAX7219 8-digit display			0.73
PIR sensor			1.89
PCB			2
XIAO ESP32-S3			7.49
<img width="385" height="349" alt="image" src="https://github.com/user-attachments/assets/ca06b7bf-8076-458d-a723-27c29b009f4d" />



Images:

<img width="876" height="565" alt="image" src="https://github.com/user-attachments/assets/176c0bf5-de1d-439b-a70b-26c5f3bd0718" />

<img width="791" height="562" alt="image" src="https://github.com/user-attachments/assets/7e1d0820-4f1b-4016-a3f8-51a14ed01b8e" />

<img width="530" height="544" alt="image" src="https://github.com/user-attachments/assets/d4010b5f-89dd-4224-83a4-fb4b6594ef88" />

<img width="712" height="743" alt="image" src="https://github.com/user-attachments/assets/a821f635-fbf2-4413-9f0e-e756a9e56249" />





