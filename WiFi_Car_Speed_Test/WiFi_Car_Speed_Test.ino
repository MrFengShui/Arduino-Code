#include <Servo.h>

// motor one
int enA = 10;
int in1 = 9;
int in2 = 8;
// motor two
int in3 = 5;
int in4 = 4;
int enB = 3;
// servo motor pin
int servoPin_1 = A5;
int servoPin_2 = A0;
int angle = 180;
char key;
int speed = 255;
Servo myServo_1, myServo_2;

void setup() {

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(115200);
  myServo_1.attach(servoPin_1);
  myServo_1.write(0);
  myServo_2.attach(servoPin_2);
  myServo_2.write(angle);

}

void loop() {

  if (Serial.available() > 0) {
    key = Serial.read();
    Serial.print("The Command: ");
    Serial.println(key);
  }
  //  Gripper A Action  
  if (key == 'b') {
    if (!myServo_1.attached()) {
      myServo_1.attach(servoPin_1);
      angle = 0;
      myServo_1.write(angle);
    }
    
    angle += 50;
    myServo_1.write(angle);
    delay(1000);
    key = '\0';
  }
  
  if (key == 'n') {
    if (!myServo_1.attached()) {
      myServo_1.attach(servoPin_1);
      angle = 0;
      myServo_1.write(angle);
    }
    
    angle += 10;
    myServo_1.write(angle);
    delay(1000);
    key = '\0';
  }

  if (key == 'm') {
    angle = 0;
    myServo_1.write(angle);
    delay(1000);
    myServo_1.detach();
    key = '\0';
  }
  // Gripper B Action
  if (key == 'v') {
    if (!myServo_2.attached()) {
      myServo_2.attach(servoPin_2);
      angle = 180;
      myServo_2.write(angle);
    }
    
    angle -= 60;
    myServo_2.write(angle);
    delay(1000);
    key = '\0';
  }
  
  if (key == 'c') {
    if (!myServo_2.attached()) {
      myServo_2.attach(servoPin_2);
      angle = 180;
      myServo_2.write(angle);
    }
    
    angle -= 10;
    myServo_2.write(angle);
    delay(1000);
    key = '\0';
  }

  if (key == 'x') {
    angle = 180;
    myServo_2.write(angle);
    delay(1000);
    myServo_2.detach();
    key = '\0';
  }
  // Move Forward
  if (key == 'q') {
    activate(LOW, HIGH, HIGH, LOW, 1000);
  }
  // Move Backward
  if (key == 'a') {
    activate(HIGH, LOW, LOW, HIGH, 1000);
  }
  // Move Forward 350ms
  if (key == 'r') {
    activate(LOW, HIGH, HIGH, LOW, 350);
    activate(LOW, LOW, LOW, LOW, 1000);
    key = '\0';
  }
  // Move Backward 350ms
  if (key == 'f') {
    activate(HIGH, LOW, LOW, HIGH, 350);
    activate(LOW, LOW, LOW, LOW, 1000);
    key = '\0';
  }
  // Move Forward 250ms
  if (key == 'w') {
    activate(LOW, HIGH, HIGH, LOW, 250);
    activate(LOW, LOW, LOW, LOW, 1000);
    key = '\0';
  }
  // Move Backward 250ms
  if (key == 's') {
    activate(HIGH, LOW, LOW, HIGH, 250);
    activate(LOW, LOW, LOW, LOW, 1000);
    key = '\0';
  }
  // Move Forward 150ms
  if (key == 'e') {
    activate(LOW, HIGH, HIGH, LOW, 150);
    activate(LOW, LOW, LOW, LOW, 1000);
    key = '\0';
  }
  // Move Backward 150ms
  if (key == 'd') {
    activate(HIGH, LOW, LOW, HIGH, 150);
    activate(LOW, LOW, LOW, LOW, 1000);
    key = '\0';
  }
  // Turn Left
  if (key == 'o') {
    activate(LOW, LOW, HIGH, LOW, 250);
    activate(LOW, LOW, LOW, LOW, 1000);
    key = '\0';
  }
  // Turn Right
  if (key == 'l') {
    activate(LOW, HIGH, LOW, LOW, 250);
    activate(LOW, LOW, LOW, LOW, 1000);
    key = '\0';
  }
  // Rotate Left 90 Degree
  if (key == 'i') {
    activate(HIGH, LOW, HIGH, LOW, 500);
    activate(LOW, LOW, LOW, LOW, 1000);
    key = '\0';
  }
  // Rotate Right 90 Degree
  if (key == 'k') {
    activate(LOW, HIGH, LOW, HIGH, 500);
    activate(LOW, LOW, LOW, LOW, 1000);
    key = '\0';
  }
  // Rotate Left 180 Degree
  if (key == 'u') {
    activate(HIGH, LOW, HIGH, LOW, 1000);
    activate(LOW, LOW, LOW, LOW, 1000);
    key = '\0';
  }
  // Rotate Right 180 Degree
  if (key == 'j') {
    activate(LOW, HIGH, LOW, HIGH, 1000);
    activate(LOW, LOW, LOW, LOW, 1000);
    key = '\0';
  }
  // Stop
  if (key == 'z') {
    activate(LOW, LOW, LOW, LOW, 1000);
  }

}

void activate(int pin1, int pin2, int pin3, int pin4, int time) {
  
  digitalWrite(in1, pin1);
  digitalWrite(in2, pin2);  
  digitalWrite(in3, pin3);
  digitalWrite(in4, pin4); 
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  delay(time);
  
}

