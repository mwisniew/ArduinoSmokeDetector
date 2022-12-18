/*
 * EMailSender library for Arduino, esp8266 and esp32
 *
 * https://www.mischianti.org/category/my-libraries/emailsender-send-email-with-attachments/
 *
 * This project was based on the Gmail send example of the EMailSender library.
 * The smoke detector code was created by me.
 */

#include "Arduino.h"
#include <EMailSender.h>
#include <ESP8266WiFi.h>

int sensorPin = A0;
int ST = 400;

const char* ssid = "SSID";
const char* password = "PASSWORD";

uint8_t connection_state = 0;
uint16_t reconnect_interval = 10000;

EMailSender emailSend("your_email@gmail.com", "email_password");

uint8_t WiFiConnect(const char* nSSID = nullptr, const char* nPassword = nullptr)
{
    static uint16_t attempt = 0;
    Serial.print("Connecting to ");
    if(nSSID) {
        WiFi.begin(nSSID, nPassword);
        Serial.println(nSSID);
    }

    uint8_t i = 0;
    while(WiFi.status()!= WL_CONNECTED && i++ < 50)
    {
        delay(200);
        Serial.print(".");
    }
    ++attempt;
    Serial.println("");
    if(i == 51) {
        Serial.print("Connection: TIMEOUT on attempt: ");
        Serial.println(attempt);
        if(attempt % 2 == 0)
            Serial.println("Check if access point available or SSID and Password\r\n");
        return false;
    }
    Serial.println("Connection: ESTABLISHED");
    Serial.print("Got IP address: ");
    Serial.println(WiFi.localIP());
    return true;
}

void Awaits()
{
    uint32_t ts = millis();
    while(!connection_state)
    {
        delay(50);
        if(millis() > (ts + reconnect_interval) && !connection_state){
            connection_state = WiFiConnect();
            ts = millis();
        }
    }
}

void setup()
{
    Serial.begin(115200);

    connection_state = WiFiConnect(ssid, password);
    if(!connection_state)  // if not connected to WIFI
        Awaits();          // constantly trying to connect
  pinMode(sensorPin, INPUT);
    
}
void loop(){
  int sensorRead = analogRead(sensorPin);
  Serial.print("Pin A0: ");
  Serial.println(sensorRead);

  if (sensorRead > ST) {
    EMailSender::EMailMessage message;
    message.subject = "Smoke Detected!";
    message.message = "The smoke detector detected smoke above set level and sent you an email!";

    EMailSender::Response resp = emailSend.send("send-to-email@gmail.com", message);

    Serial.println("Sending status: ");

    Serial.println(resp.status);
    Serial.println(resp.code);
    Serial.println(resp.desc);
    delay(100000);
    } else {
      Serial.print("Not enough smoke!");
    }
}

