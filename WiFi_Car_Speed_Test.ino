#include <SoftwareSerial.h>
#include <Servo.h>

char key, tmpKey;
int speed = 135;
int enA = 10;
int in1 = 9;
int in2 = 8;
int in3 = 7;
int in4 = 6;
int enB = 5;
int servoPin = A5;
int angle = 0;

SoftwareSerial mySerial(2, 3);
Servo myServo;

void setup() {

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Serial.begin(115200);
  mySerial.begin(115200);
  
}

void loop() {
  
//  if (Serial.available()) {
//    key = char(Serial.read());
//    Serial.print("You Press: ");
//    Serial.println(key);
//
//    if (key == 'w' || key == 'x' || key == 'a' || key == 'd' || key == 's' || key == 'z' || key == 'c' || key == 'j' || key == 'k') {
//      tmpKey = key;
//    }
//  }

  if (mySerial.available() > 0) {
    key = mySerial.read();
    Serial.print("The Command: ");
    Serial.println(key);

    if (key == 'w' || key == 'x' || key == 'a' || key == 'd' || key == 's' || key == 'z' || key == 'c' || key == 'j' || key == 'k') {
      tmpKey = key;
    }
  }

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

  if (key == 'q') {
    if (speed > 0 && speed <= 255) {
      speed -= 15;
      key = tmpKey;
    } else {
      Serial.println("Stop Now");
    }
  }

  if (key == 'e') {
    if (speed >= 0 && speed < 255) {
      speed += 15;
      key = tmpKey;
    } else {
      Serial.println("Full Speed Now");
    }
  }

  if (key == 'j') {
    activate(HIGH, LOW, HIGH, LOW);
    analogWrite(enA, speed);
    analogWrite(enB, speed);
    delay(500); 
    activate(LOW, LOW, LOW, LOW);
    key = '\0';
  }

  if (key == 'k') {
    activate(LOW, HIGH, LOW, HIGH);
    analogWrite(enA, speed);
    analogWrite(enB, speed);
    delay(500); 
    activate(LOW, LOW, LOW, LOW);
    key = '\0';
  }

  if (key == 'w') {
    activate(HIGH, LOW, HIGH, LOW);
  }

  if (key == 'x') {
    activate(LOW, HIGH, LOW, HIGH);
  }  

  if (key == 'a') {
    activate(LOW, LOW, HIGH, LOW);
  }

  if (key == 'd') {
    activate(HIGH, LOW, LOW, LOW);
  }

  if (key == 'z') {
    activate(LOW, HIGH, HIGH, LOW);
  }  

  if (key == 'c') {
    activate(HIGH, LOW, LOW, HIGH);
  }

  if (key == 's') {
    activate(LOW, LOW, LOW, LOW);
  }
  
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  delay(10);
  
}

void activate(int pin1, int pin2, int pin3, int pin4) {
  digitalWrite(in1, pin1);
  digitalWrite(in2, pin2);  
  digitalWrite(in3, pin3);
  digitalWrite(in4, pin4); 
}

