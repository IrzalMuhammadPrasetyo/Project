#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int ledred = 13;
int ledgreen = 12;
int buzzer = 11;
int ledyellow = 10;
int MQ2pin = A0;

void setup() {
  lcd.begin();
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {
int sensorValue = analogRead(MQ2pin); 
  Serial.print("Gas:");
  Serial.println(sensorValue);
  
  lcd.setCursor(4,0);
  lcd.print("Gas :");
  lcd.print(sensorValue);

  if(sensorValue > 550 && sensorValue < 780){
    digitalWrite(ledyellow,HIGH);
    digitalWrite(ledred,LOW);
    digitalWrite(ledgreen,LOW);
    tone(buzzer, 3000, 200);
    lcd.setCursor(0,1);
    lcd.print("WASPADA ");
  }
  
  else if(sensorValue > 780){
    digitalWrite(ledred,HIGH);
    tone(buzzer, 1000, 200);
    digitalWrite(ledgreen,LOW);
    digitalWrite(ledyellow,LOW);
    lcd.setCursor(0,1);
    lcd.print("BAHAYA ");
  } 
  
  else{
    digitalWrite(ledgreen,HIGH);
    digitalWrite(ledred,LOW);
    digitalWrite(ledyellow,LOW);
    noTone(buzzer);
    lcd.setCursor(0,1);
    lcd.print("AMAN   ");
  } 
  delay(100);
}
