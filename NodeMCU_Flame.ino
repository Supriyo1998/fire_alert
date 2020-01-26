//Pin Configuration
//D0->A0
//VCC->3v

#include <ESP8266WiFi.h>

int flame_sensor = A0;
int flame_detected;
const int threshold=200;

//const char* ssid = "TP-Link_F744";
//const char* password = "00264235";

const char* ssid = "Airtel-E5573-E0FE";
const char* password = "sinha@123";

//int ledPin = D1;

String apiKey = "VPHULBLKNJ1CQKS5";
const char* server = "api.thingspeak.com";
WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  //pinMode(ledPin, OUTPUT);
  pinMode(flame_sensor, INPUT);
}

void loop() {
  if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
  { 
    flame_detected = analogRead(flame_sensor);
    if (flame_detected>threshold)
    {
      Serial.println((String)"Threshold Value at normal: "+flame_detected);
      Serial.println("No flame detected. stay cool");
      
      //digitalWrite(ledPin, HIGH);
      /*String postStr = apiKey;
      postStr +="&field1=";
      postStr += String(0);
      postStr += "\r\n\r\n";
   
      client.print("POST /update HTTP/1.1\n");
      client.print("Host: api.thingspeak.com\n");
      client.print("Connection: close\n");
      client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
      client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.print("Content-Length: ");
      client.print(postStr.length());
      client.print("\n\n");
      client.print(postStr);
      delay(15000);
      Serial.println("Waiting...");*/
    }
    else
    {
      Serial.println(flame_detected);
      Serial.println("Flame detected...! take action immediately.");
      //digitalWrite(ledPin, LOW);
      //delay(200);
  
      String postStr = apiKey;
      postStr +="&field1=";
      postStr += String(3);
      postStr += "\r\n\r\n";
   
      client.print("POST /update HTTP/1.1\n");
      client.print("Host: api.thingspeak.com\n");
      client.print("Connection: close\n");
      client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
      client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.print("Content-Length: ");
      client.print(postStr.length());
      client.print("\n\n");
      client.print(postStr);
      delay(15000);
      Serial.println("Waiting...");
    }
  }
   client.stop();
}
