#include <LedControl.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>

const int pirPin = D6;
const int armButtonPin = D5;
const int buzzerPin = D4;
const int counterCLKPin = D8;
const int counterLOADPin = D9;
const int counterDINPin = D10;
const int pResistorPin = A0;

int motionCount = 0;
int lastUpdateId = 0;
unsigned long lastEventTime = 0;
unsigned long timeout = 10000;
bool motionDetected = false;
unsigned long eventStartTime = 0;
unsigned long windowStartTime = 0;
LedControl lc = LedControl(counterDINPin, counterCLKPin, counterLOADPin, 1);

int recentMotionCount = 0;

bool armed = true;
bool nightMode = false;
bool forceDisarmed = false;
bool lastButtonState = LOW;
bool bright = false;
bool lastArmedState = false;

const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";
const char* botToken = "BOT_TOKEN";
const char* chatID = "CHAT_ID";
const char* sheetURL = "WEB_APP_URL";

void sendTelegram(String message) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "https://api.telegram.org/bot" + String(botToken) + "/sendMessage?chat_id=" + String(chatID) + "&text=" + message;
    http.begin(url);
    http.GET();
    http.end();
  }
}

void logSheet(String message) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(sheetURL) + "?event=" + message;
    http.begin(url);
    http.GET();
    http.end();
  }
}

void checkTelegram() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "https://api.telegram.org/bot" + String(botToken) + "/getUpdates?offset=" + String(lastUpdateId);
    http.begin(url);
    http.GET();
    String response = http.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, response);

    if (doc["result"].size() > 0) {
      int updateId = doc["result"][0]["update_id"];
      String text = doc["result"][0]["message"]["text"];
      lastUpdateId = updateId + 1;

      if (text == "/arm") {
        nightMode = false;
        forceDisarmed = false;
        sendTelegram("Security System Armed");
        logSheet("Armed via Telegram");
      }
      if (text == "/disarm") {
        nightMode = false;
        forceDisarmed = true;
        sendTelegram("Security System Disarmed");
        logSheet("Disarmed via Telegram");
      }
      if (text == "/nightmode on") {
        nightMode = true;
        forceDisarmed = false;
        sendTelegram("Night Mode Enabled");
        logSheet("Night Mode Enabled via Telegram");
      }
      if (text == "/nightmode off") {
        nightMode = false;
        forceDisarmed = false;
        sendTelegram("Night Mode Disabled");
        logSheet("Night Mode Disabled via Telegram");
      }
      if (text == "/status") {
        String status = "Armed: " + String(armed ? "Yes" : "No") + "\nNight Mode: " + String(nightMode ? "On" : "Off") + "\nMotion Count: " + String(motionCount);
        sendTelegram(status);
      }
      if (text == "/motioncount") {
        String status = "Motion has been detected " + String(motionCount) + String(motionCount == 1 ? " time" : " times");
        sendTelegram(status);
      }
      if (text == "/reset") {
        motionCount = 0;
        String status = "Motion count has been reset";
        sendTelegram(status);
        logSheet("Motion Count Reset via Telegram");
      }
    }

    http.end();
  }
}

void buzzArmed() {
  digitalWrite(buzzerPin, HIGH);
  delay(2000);
  digitalWrite(buzzerPin, LOW);
  delay(1000);
  digitalWrite(buzzerPin, HIGH);
  delay(1000);
  digitalWrite(buzzerPin, LOW);
}

void buzzDisarmed() {
  digitalWrite(buzzerPin, HIGH);
  delay(1000);
  digitalWrite(buzzerPin, LOW);
  delay(1000);
  digitalWrite(buzzerPin, HIGH);
  delay(2000);
  digitalWrite(buzzerPin, LOW);
}

void buzzMotion() {
  digitalWrite(buzzerPin, HIGH);
  delay(3000);
  digitalWrite(buzzerPin, LOW);
}

void updateDisplay() {
  int remaining = motionCount;
  for (int i = 0; i < 8; i++) {
    lc.setDigit(0, i, remaining % 10, false);
    remaining /= 10;
  }
}

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(armButtonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);

  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  sendTelegram("Security system online");
  logSheet("System Online");

  Serial.println("Security system ready");
}

void loop() {

  if (WiFi.status() == WL_DISCONNECTED) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    }
    sendTelegram("Security system online");
    logSheet("WiFi Reconnected");
    Serial.println("Security system ready");
  }

  int motionState = digitalRead(pirPin);
  bool currentButtonState = digitalRead(armButtonPin);

  if (analogRead(pResistorPin) < 1250) {
    bright = true;
  } else {
    bright = false;
  }

  if (currentButtonState == LOW && lastButtonState == HIGH) {
    nightMode = !nightMode;
    forceDisarmed = false;
  }
  lastButtonState = currentButtonState;

  if (forceDisarmed == true) {
    armed = false;
  } else if (nightMode == false) {
    armed = true;
  } else {
    if (bright == true) {
      armed = false;
    } else {
      armed = true;
    }
  }

  if (armed != lastArmedState) {
    delay(200);
    if (armed == true) {
      Serial.print("System armed");
      sendTelegram("System armed");
      logSheet("System Armed");
      buzzArmed();
    } else {
      Serial.print("System disarmed");
      sendTelegram("System disarmed");
      logSheet("System Disarmed");
      buzzDisarmed();
    }
    lastArmedState = armed;
  }

  unsigned long currentTime = millis();

  if (recentMotionCount >= 3) {
    unsigned long elapsed = (currentTime - windowStartTime) / 1000;
    int minutes = elapsed / 60;
    int seconds = elapsed % 60;
    sendTelegram("Motion Detected " + String(recentMotionCount) + " times in the last " + String(minutes) + " minutes and " + String(seconds) + " seconds");
    logSheet("High Motion Alert: " + String(recentMotionCount) + " times in " + String(minutes) + "m " + String(seconds) + "s");
    recentMotionCount = 0;
    windowStartTime = currentTime;
  }

  if (armed == true && motionState == HIGH) {
    if (currentTime - lastEventTime > timeout) {
      if (motionCount < 99999999) {
        motionCount++;
        recentMotionCount++;
      }
      lastEventTime = currentTime;
      eventStartTime = currentTime;
      buzzMotion();
      Serial.print("Motion detected ");
      Serial.print(motionCount);
      Serial.println(" times");
      sendTelegram("Motion detected " + String(motionCount) + " times");
      logSheet("Motion Detected");
    }
  }

  updateDisplay();

  checkTelegram();
  delay(1000);
}