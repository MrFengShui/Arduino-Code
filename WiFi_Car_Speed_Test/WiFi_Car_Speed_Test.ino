#include <Servo.h>

char key, tmpKey;
// motor one
int enA = 10;
int in1 = 9;
int in2 = 8;
// motor two
int in3 = 7;
int in4 = 6;
int enB = 5;
// servo motor pin
int servoPin = A5;
int angle = 180;
int speed = 255;

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
  myServo.write(180);
  
}

void loop() {

  if (Serial.available() > 0) {
    key = Serial.read();    
    Serial.print("The Command: ");
    Serial.println(key);

    if (key == 'w' || key == 'x' || key == 'a' || key == 'd' || key == 's' 
        || key == 'z' || key == 'c' || key == 'j' || key == 'k' 
        || key == 'u' || key == 'i') {
      tmpKey = key;
    }
  }

  delay(100);

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

  if (key == 'n') {
    activate(HIGH, LOW, HIGH, LOW, 25);
    activate(LOW, LOW, LOW, LOW, 10);
    key = '\0';
  }

  if (key == 'j') {
    activate(HIGH, LOW, HIGH, LOW, 250);
    activate(LOW, LOW, LOW, LOW, 10);
    key = '\0';
  }

  if (key == 'm') {
    activate(HIGH, LOW, HIGH, LOW, 15);
    activate(LOW, LOW, LOW, LOW, 10);
    key = '\0';
  }

  if (key == 'b') {
    activate(LOW, HIGH, LOW, HIGH, 25);
    activate(LOW, LOW, LOW, LOW, 10);
    key = '\0';
  }

  if (key == 'k') {
    activate(LOW, HIGH, LOW, HIGH, 250);
    activate(LOW, LOW, LOW, LOW, 10);
    key = '\0';
  }

  if (key == 'v') {
    activate(LOW, HIGH, LOW, HIGH, 15);
    activate(LOW, LOW, LOW, LOW, 10);
    key = '\0';
  }

  if (key == 'u') {
    activate(LOW, LOW, HIGH, LOW, 100);
    activate(LOW, LOW, LOW, LOW, 10);
    key = '\0';
  }

  if (key == 'i') {
    activate(HIGH, LOW, LOW, LOW, 100);
    activate(LOW, LOW, LOW, LOW, 10);
    key = '\0';
  }

  if (key == 'o') {
    angle -= 10;
    myServo.write(angle);
    delay(1000);
    key = '\0';
  }

  if (key == 'l') {
    angle = 180;
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
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  delay(time);
}

