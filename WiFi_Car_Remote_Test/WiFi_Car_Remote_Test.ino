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

<<<<<<< HEAD
char B_KEY = 'b';
char N_KEY = 'n';
char M_KEY = 'm';

char V_KEY = 'v';
char C_KEY = 'c';
char X_KEY = 'x';

char Q_KEY = 'q';
char A_KEY = 'a';
char W_KEY = 'w';
char S_KEY = 's';
char E_KEY = 'e';
char D_KEY = 'd';
char R_KEY = 'r';
char F_KEY = 'f';

char O_KEY = 'o';
char L_KEY = 'l';
char I_KEY = 'i';
char K_KEY = 'k';
char U_KEY = 'u';
char J_KEY = 'j';

=======
char A_KEY = 'a';
char B_KEY = 'b';
char C_KEY = 'c';
char D_KEY = 'd';
char E_KEY = 'e';
char I_KEY = 'i';
char J_KEY = 'j';
char K_KEY = 'k';
char L_KEY = 'l';
char M_KEY = 'm';
char N_KEY = 'n';
char O_KEY = 'o';
char Q_KEY = 'q';
char S_KEY = 's';
char U_KEY = 'u';
char V_KEY = 'v';
char W_KEY = 'w';
char X_KEY = 'x';
>>>>>>> bd34c9d42645c7410acb4a7c4d3a939c071e35aa
char Z_KEY = 'z';

const char* WEB = 
"<!DOCTYPE HTML>"
"<html>"
"<head>"
"<title>Arduino UNO WiFi Control</title>"
"<style>"
"html {background-color: #252525;width: 100%;}"
"div {display: flex;align-items: center;justify-content: space-between;}"
"header {color: crimson;font-family: Tahoma, Geneva, sans-serif;font-size: 36pt;font-weight: bold;width: 100%;text-align: center;}"
"a {background-color: crimson;border-width: 0;color: snow;font-family: Tahoma, Geneva, sans-serif;font-size: 12pt;font-weight: bold;display: flex;align-items: center;justify-content: center;text-decoration:none;text-align: center;width: 128px;height: 128px;}"
"a:hover {box-shadow: 0 5px 10px 0 rgba(255, 255, 255, 0.25), 0 5px 20px 0 rgba(255, 255, 255, 0.25);cursor: pointer;}"
"</style>"
"</head>"
"<body>"
"<header>Arduino Robot Web Controller</header>"
"<div>"
"<div>"
"<table>"
"<tr><td><a href=\"RotateLeft90\">ROTATE<br>LEFT90</a></td><td><a href=\"Forward\">FORWARD</a></td><td><a href=\"RotateRight90\">ROTATE<br>RIGHT90</a></td></tr>"
"<tr><td><a href=\"TurnLeft\">LEFT</a></td><td><a href=\"Stop\">STOP</a></td><td><a href=\"TurnRight\">RIGHT</a></td></tr>"
"<tr><td><a href=\"RotateLeft180\">ROTATE<br>LEFT180</a></td><td><a href=\"Backward\">BACKWARD</a></td><td><a href=\"RotateRight180\">ROTATE<br>RIGHT180</a></td></tr>"
"</table>"
"</div>"
"<div>"
"<table>"
<<<<<<< HEAD
"<tr><td><a href=\"Forward25\">FORWARD<br>25</a></td><td><a href=\"Forward35\">FORWARD<br>35</a></td><td><a href=\"Forward15\">FORWARD<br>15</a></td></tr>"
"<tr><td><a href=\"TurnLeft\">LEFT</a></td><td><a href=\"Stop\">STOP</a></td><td><a href=\"TurnRight\">RIGHT</a></td></tr>"
"<tr><td><a href=\"Backward25\">BACKWARD<br>25</a></td><td><a href=\"Backward35\">BACKWARD<br>35</a></td><td><a href=\"Backward15\">BACKWARD<br>15</a></td></tr>"
=======
"<tr><td><a href=\"Forward25\">FORWARD<br>25MS</a></td><td><a href=\"ForwardBit\">FORWARD<br>BIT</a></td><td><a href=\"Forward15\">FORWARD<br>15MS</a></td></tr>"
"<tr><td><a href=\"LeftBit\">LEFT<br>BIT</a></td><td><a href=\"Stop\">STOP</a></td><td><a href=\"RightBit\">RIGHT<br>BIT</a></td></tr>"
"<tr><td><a href=\"Backward25\">BACKWARD<br>25MS</a></td><td><a href=\"BackwardBit\">BACKWARD<br>BIT</a></td><td><a href=\"Backward15\">BACKWARD<br>15</a></td></tr>"
>>>>>>> bd34c9d42645c7410acb4a7c4d3a939c071e35aa
"</table>"
"</div>"
"</div>"
"<div>"
"<a href=\"GrabA60\">GRAB-A<br>60</a>"
"<a href=\"GrabA10\">GRAB-A<br>10</a>"
"<a href=\"ReleaseA\">GRAB-A<br>RELEASE</a>"
"<a href=\"ReleaseB\">GRAB-B<br>RELEASE</a>"
"<a href=\"GrabB10\">GRAB-B<br>10</a>"
"<a href=\"GrabB60\">GRAB-B<br>60</a>"
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

  res_fst_grab();
  res_snd_grab();
  lhs_control();
  rhs_control();

  server.on("/Stop", [](){
    digitalWrite(pin_3, LOW);
    digitalWrite(pin_4, LOW);
    digitalWrite(pin_7, LOW);
    digitalWrite(pin_8, LOW);
    mySerial.write(Z_KEY);
    server.send(200, "text/html", WEB);
  });
  
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void) {
  server.handleClient();
}

void res_fst_grab() {
  
  server.on("/GrabA60", [](){
    mySerial.write(B_KEY);
    server.send(200, "text/html", WEB);
  });

  server.on("/GrabA10", [](){
    mySerial.write(N_KEY);
    server.send(200, "text/html", WEB);
  });

  server.on("/ReleaseA", [](){
    mySerial.write(M_KEY);
    server.send(200, "text/html", WEB);
  });
  
}

void res_snd_grab() {
  
  server.on("/GrabB60", [](){
    mySerial.write(V_KEY);
    server.send(200, "text/html", WEB);
  });

  server.on("/GrabB10", [](){
    mySerial.write(C_KEY);
    server.send(200, "text/html", WEB);
  });

  server.on("/ReleaseB", [](){
    mySerial.write(X_KEY);
    server.send(200, "text/html", WEB);
  });
  
}

void lhs_control() {

  server.on("/Forward", [](){
<<<<<<< HEAD
    mySerial.write(Q_KEY);
=======
    mySerial.write(W_KEY);
>>>>>>> bd34c9d42645c7410acb4a7c4d3a939c071e35aa
    server.send(200, "text/html", WEB);
  });
  
  server.on("/Backward", [](){
<<<<<<< HEAD
    mySerial.write(A_KEY);
=======
    mySerial.write(X_KEY);
>>>>>>> bd34c9d42645c7410acb4a7c4d3a939c071e35aa
    server.send(200, "text/html", WEB);
  });
  
  server.on("/TurnLeft", [](){
<<<<<<< HEAD
    mySerial.write(O_KEY);
=======
    mySerial.write(A_KEY);
>>>>>>> bd34c9d42645c7410acb4a7c4d3a939c071e35aa
    server.send(200, "text/html", WEB);
  });
  
  server.on("/TurnRight", [](){
<<<<<<< HEAD
    mySerial.write(L_KEY);
    server.send(200, "text/html", WEB);
  });

  server.on("/RotateLeft90", [](){
    mySerial.write(I_KEY);
    server.send(200, "text/html", WEB);
  });

  server.on("/RotateRight90", [](){
    mySerial.write(K_KEY);
    server.send(200, "text/html", WEB);
  });

  server.on("/RotateLeft180", [](){
    mySerial.write(U_KEY);
    server.send(200, "text/html", WEB);
  });

  server.on("/RotateRight180", [](){
    mySerial.write(J_KEY);
=======
    mySerial.write(D_KEY);
    server.send(200, "text/html", WEB);
  });

  server.on("/LeftRotate", [](){
    mySerial.write(Z_KEY);
    server.send(200, "text/html", WEB);
  });

  server.on("/RightRotate", [](){
    mySerial.write(C_KEY);
    server.send(200, "text/html", WEB);
  });

  server.on("/Forward25", [](){
    mySerial.write(N_KEY);
    server.send(200, "text/html", WEB);
  });

  server.on("/ForwardBit", [](){
    mySerial.write(J_KEY);
    server.send(200, "text/html", WEB);
  });

  server.on("/Forward15", [](){
    mySerial.write(M_KEY);
    server.send(200, "text/html", WEB);
  });

  server.on("/Backward25", [](){
    mySerial.write(B_KEY);
    server.send(200, "text/html", WEB);
  });

  server.on("/BackwardBit", [](){
    mySerial.write(K_KEY);
>>>>>>> bd34c9d42645c7410acb4a7c4d3a939c071e35aa
    server.send(200, "text/html", WEB);
  });
  
}

<<<<<<< HEAD
void rhs_control() {

  server.on("/Forward35", [](){
    mySerial.write(R_KEY);
=======
  server.on("/Backward15", [](){
    mySerial.write(V_KEY);
    server.send(200, "text/html", WEB);
  });

  server.on("/LeftBit", [](){
    mySerial.write(U_KEY);
>>>>>>> bd34c9d42645c7410acb4a7c4d3a939c071e35aa
    server.send(200, "text/html", WEB);
  });

  server.on("/Forward25", [](){
    mySerial.write(W_KEY);
    server.send(200, "text/html", WEB);
  });

  server.on("/Forward15", [](){
    mySerial.write(E_KEY);
    server.send(200, "text/html", WEB);
  });

  server.on("/Backward35", [](){
    mySerial.write(F_KEY);
    server.send(200, "text/html", WEB);
  });

  server.on("/Backward25", [](){
    mySerial.write(S_KEY);
    server.send(200, "text/html", WEB);
  });

  server.on("/Backward15", [](){
    mySerial.write(D_KEY);
    server.send(200, "text/html", WEB);
  });
  
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

