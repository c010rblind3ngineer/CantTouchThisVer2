/* Arduino 'Can't Touch This' Version 2
   Components:
                - Arduino Nano
                - D1 Mini (ESP8266) module
                - ADXL335
                - Passive Buzzer
                - Push button tactile switch
                - Red LED
                - 220Ohm resistor
                - 330Ohm resistor
                - 10kOhm resistor
                - Breadboard
                - Some jumper wires

   Created on 23 August 2022 by c010blind3ngineer
*/
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

#define btnPin D1

// Wifi network station credentials
#define WIFI_SSID "Linksys12286"
#define WIFI_PASSWORD "tmajrdeb5c"
// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "5505113357:AAHuwfJZjntrTBF0mRua6rDmzO9N2MgsZmM"

// Use @myidbot (IDBot) to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "1093565987"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);


void setup() {
  pinMode(btnPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // active LOW, means it will ON when it is LOW. We set it OFF (HIGH) it first.

  // attempt to connect to Wifi network:
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
  }

  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    delay(100);
    now = time(nullptr);
  }
}

void loop() {
  if (digitalRead(btnPin) == HIGH) {
    bot.sendMessage(CHAT_ID, "Movement detected!", "");
  }
}
