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

Servo myServo;

void setup() {
  
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Serial.begin(115200);

  myServo.attach(servoPin);
  myServo.write(angle);
  
}

void loop() {

  if (Serial.available() > 0) {
    key = Serial.read();
    
    if (key != '\r' && key != '\n') {
      Serial.print("The Command: ");
      Serial.println(key);
    }
  }

  delay(100);

  if (key == 'o') {
    angle += 10;
    myServo.write(angle);
    delay(1000);
    key = '\0';
  }

  if (key == 'l') {
    angle = 0;
    myServo.write(angle);
    delay(1000);
    key = '\0';
  }

  if (key == 'w') {
    activate(HIGH, LOW, HIGH, LOW, 10);
  }

  if (key == 'x') {
    activate(LOW, HIGH, LOW, HIGH, 10);
  }

  if (key == 'a') {
    activate(LOW, LOW, HIGH, LOW, 10);
  }

  if (key == 'd') {
    activate(HIGH, LOW, LOW, LOW, 10);
  }

  if (key == 'z') {
    activate(LOW, HIGH, HIGH, LOW, 10);
  }

  if (key == 'c') {
    activate(HIGH, LOW, LOW, HIGH, 10);
  }

  if (key == 's') {
    activate(LOW, LOW, LOW, LOW, 10);
  }

}

void activate(int pin1, int pin2, int pin3, int pin4, int time) {
  digitalWrite(in1, pin1);
  digitalWrite(in2, pin2);  
  digitalWrite(in3, pin3);
  digitalWrite(in4, pin4); 
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  delay(time);
}
