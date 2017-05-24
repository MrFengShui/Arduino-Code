#include <SoftwareSerial.h>
#include <Servo.h>

char key;
// connect motor controller pins to Arduino digital pins
// motor one
int enA = 10;
int in1 = 9;
int in2 = 8;
// motor two
int enB = 5;
int in3 = 7;
int in4 = 6;
// servo motor pin
int servoPin = A5;
int angle = 0;

SoftwareSerial mySerial(2, 3);
Servo myServo;

void setup()
{
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Serial.begin(115200);
  mySerial.begin(115200);

  myServo.attach(servoPin);
  myServo.write(angle);
  
}

void loop()
{

//  if (mySerial.available() > 0) {
//    key = mySerial.read();
//    Serial.print("The Command: ");
//    Serial.println(key);
//  } else {
//    Serial.println("Waiting for Command From WiFi...");
//  }

  if (Serial.available() > 0) {
    key = Serial.read();
    Serial.print("The Command: ");
    Serial.println(key);
  }

  delay(100);

  if (key == 'o') {
    myServo.attach(servoPin);
    angle += 10;
    myServo.write(angle);
    delay(1000);
    myServo.detach();
    key = '\0';
  }

  if (key == 'l') {
    myServo.attach(servoPin);
    angle = 0;
    myServo.write(angle);
    delay(1000);
    myServo.detach();
  }

  if (key == 'w') {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);  
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }

  if (key == 'x') {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);  
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH); 
  }

  if (key == 'a') {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);  
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW); 
  }

  if (key == 'd') {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);  
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW); 
  }

  if (key == 'z') {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);  
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW); 
  }

  if (key == 'c') {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);  
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH); 
  }

  if (key == 's') {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);  
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW); 
  }

  analogWrite(enA, 255);
  analogWrite(enB, 255);
  delay(10);
}
