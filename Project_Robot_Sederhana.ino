#include <NewPing.h>
#include <Servo.h>
#define trigger 12
#define echo 13
#define max_jarak 300
#define IR 3

int speed1 = 9;
int speed2 = 11;
int motor1 = 5;
int motor2 = 4;
int motor3 = 6;
int motor4 = 7;

NewPing sonar(trigger, echo, max_jarak);

Servo myservo;

String voice;

void setup() {
Serial.begin(9600);

pinMode(motor1,OUTPUT);
pinMode(motor2,OUTPUT);
pinMode(motor3,OUTPUT);
pinMode(motor4,OUTPUT);

pinMode(9,OUTPUT);
pinMode(11,OUTPUT);

myservo.attach(10);
myservo.write(90);

pinMode(IR, INPUT);
}

void loop() {
  //int IR1 = digitalRead(IR);
  //Serial.println(IR1);

if(Serial.available()>0) {
  voice="";
  delay(2);
  voice = Serial.readString();
  delay(2);
  Serial.println(voice);
  
if (voice == "belok kiri") {
  left();
}else if(voice == "belok kanan") {
  right();
}else if(voice == "stop") {
  berhenti();
}
}

if(voice == "maju") {
  forward();
}
if(voice == "mundur") {
  backward();
}
}

void forward() {
int distance = sonar.ping_cm();
  
  if(distance < 10){
  berhenti();
  //voice="";
  }
  else{
  analogWrite(speed1, 150);
  analogWrite(speed2, 150);
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, LOW);
  delay(1500);
  }
}

void backward() {
  int IR_Sensor = digitalRead(IR);
  if(IR_Sensor == 0) {
    berhenti();
    //voice="";
  }
  else {
  analogWrite(speed1, 150);
  analogWrite(speed2, 150);
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, LOW);
  delay(1500);
  }
}

void left() {
  myservo.write(180);
  delay(500);
  myservo.write(90);
  delay(500);

int distance = sonar.ping_cm();

  if(distance < 10) {
    berhenti();
    //voice="";
  }
  else {
  analogWrite(speed1, 0);
  analogWrite(speed2, 150);
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, LOW);
  delay(700);
  analogWrite(speed1, 0);
  analogWrite(speed2, 0);
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, HIGH);
  }
}

void right() {
  myservo.write(0);
  delay(500);
  myservo.write(90);
  delay(500);

int distance = sonar.ping_cm();

 if(distance < 10) {
    berhenti();
    //voice="";
  }
  else {
  analogWrite(speed1, 150);
  analogWrite(speed2, 0);
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, HIGH);
  delay(700);
  analogWrite(speed1, 0);
  analogWrite(speed2, 0);
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, HIGH);
  }
 }

void berhenti() {
  analogWrite(speed1, 0);
  analogWrite(speed2, 0);
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, HIGH);
}
