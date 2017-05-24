#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#define WIFISSID "ROB421_TEAM_15"
#define WIFIPASS "1234567890"

MDNSResponder mdns;
ESP8266WebServer server(80);
SoftwareSerial mySerial(D2, D1);

int pin_3 = D3;
int pin_4 = D4;
int pin_7 = D7;
int pin_8 = D8;

const char* WEB = 
"<!DOCTYPE HTML>"
"<html>"
"<head>"
"<title>Arduino UNO WiFi Control</title>"
"<style>"
"html {background-color: #252525;width: 100%;}"
"div {display: flex;align-items: center;justify-content: center;}"
"header {color: crimson;font-family: Tahoma, Geneva, sans-serif;font-size: 36pt;font-weight: bold;width: 100%;text-align: center;}"
"a {background-color: crimson;border-width: 0;color: snow;font-family: Tahoma, Geneva, sans-serif;font-size: 24pt;font-weight: bold;display: flex;align-items: center;justify-content: center;text-decoration:none;width: 256px;height: 256px;}"
"a:hover {box-shadow: 0 5px 10px 0 rgba(255, 255, 255, 0.25), 0 5px 20px 0 rgba(255, 255, 255, 0.25);cursor: pointer;}"
"</style>"
"</head>"
"<body>"
"<header>Arduino Robot Web Controller</header>"
"<div>"
"<table>"
"<tr><td><a href=\"DecreaseSpeed\">DECREASE<br>SPEED</a></td><td><a href=\"Forward\">FORWARD</a></td><td><a href=\"IncreaseSpeed\">INCREASE<br>SPEED</a></td></tr>"
"<tr><td><a href=\"TurnLeft\">LEFT</a></td><td><a href=\"Stop\">STOP</a></td><td><a href=\"TurnRight\">RIGHT</a></td></tr>"
"<tr><td><a href=\"LeftRotate\">LEFT<br>ROTATE</a></td><td><a href=\"Backward\">BACKWARD</a></td><td><a href=\"RightRotate\">RIGHT<br>ROTATE</a></td></tr>"
"<tr><td><a href=\"ForwardBit\">FORWARD<br>BIT</a></td><td><a href=\"#\"></a></td><td><a href=\"BackwardBit\">BACKWARD<br>BIT</a></td></tr>"
"</div>"
"</body>"
"</html>";
  
void setup(void) {
  // preparing GPIOs
  pinMode(pin_3, OUTPUT);
  digitalWrite(pin_3, LOW);
  pinMode(pin_4, OUTPUT);
  digitalWrite(pin_4, LOW);
  pinMode(pin_7, OUTPUT);
  digitalWrite(pin_7, LOW);
  pinMode(pin_8, OUTPUT);
  digitalWrite(pin_8, LOW);
  delay(1000);
  
  Serial.begin(115200);
  mySerial.begin(115200);
  
  WiFi.mode(WIFI_AP);
  WiFi.softAP(WIFISSID, WIFIPASS);
//  WiFi.begin();
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(WIFISSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  
  if (mdns.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", []() {
    server.send(200, "text/html", WEB);
  });

  server.on("/DecreaseSpeed", [](){
    mySerial.write(113);
    server.send(200, "text/html", WEB);
  });

  server.on("/IncreaseSpeed", [](){
    mySerial.write(101);
    server.send(200, "text/html", WEB);
  });
  
  server.on("/Forward", [](){
    signalControl(HIGH, LOW, LOW, LOW);
    mySerial.write(119);
    server.send(200, "text/html", WEB);
  });
  
  server.on("/Backward", [](){
    signalControl(LOW, LOW, LOW, HIGH); 
    mySerial.write(120);
    server.send(200, "text/html", WEB);
  });
  
  server.on("/TurnLeft", [](){
    signalControl(LOW, HIGH, LOW, LOW);
    mySerial.write(97);
    server.send(200, "text/html", WEB);
  });
  
  server.on("/TurnRight", [](){
    signalControl(LOW, LOW, HIGH, LOW);
    mySerial.write(100);
    server.send(200, "text/html", WEB);
  });

  server.on("/LeftRotate", [](){
    signalControl(HIGH, LOW, LOW, HIGH);
    mySerial.write(122);
    server.send(200, "text/html", WEB);
  });

  server.on("/RightRotate", [](){
    signalControl(LOW, HIGH, HIGH, LOW);
    mySerial.write(99);
    server.send(200, "text/html", WEB);
  });

  server.on("/ForwardBit", [](){
    mySerial.write(106);
    server.send(200, "text/html", WEB);
  });

  server.on("/BackwardBit", [](){
    mySerial.write(107);
    server.send(200, "text/html", WEB);
  });

  server.on("/Stop", [](){
    digitalWrite(pin_3, LOW);
    digitalWrite(pin_4, LOW);
    digitalWrite(pin_7, LOW);
    digitalWrite(pin_8, LOW);
    mySerial.write(115);
    server.send(200, "text/html", WEB);
  });
  
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void) {
  server.handleClient();
} 

void signalControl(int pin3, int pin4, int pin7, int pin8) {
  if (digitalRead(pin_3) == HIGH) {
    digitalWrite(pin_3, LOW);
  }

  if (digitalRead(pin_4) == HIGH) {
    digitalWrite(pin_4, LOW);
  }

  if (digitalRead(pin_7) == HIGH) {
    digitalWrite(pin_7, LOW);
  }

  if (digitalRead(pin_8) == HIGH) {
    digitalWrite(pin_8, LOW);
  }
  
  digitalWrite(pin_3, pin3);
  digitalWrite(pin_4, pin4);
  digitalWrite(pin_7, pin7);
  digitalWrite(pin_8, pin8);
  delay(100);
}

