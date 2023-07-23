#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#define echo 11
#define trig 12
#define buzzer 3

#define lebar 128 
#define tinggi 64
#define reset -1
Adafruit_SH1106 display(reset);

long durasi, jarak;

void setup() {
  Serial.begin(9600);

  pinMode(buzzer, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
 
  mlx.begin();
  
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {
 digitalWrite(trig, LOW);
 delayMicroseconds(2);
 digitalWrite(trig, HIGH);
 delayMicroseconds(10);
 digitalWrite(trig, LOW);

 durasi = pulseIn(echo, HIGH);
 jarak = durasi/58.8;

if (jarak <= 7){
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);

  Serial.println(jarak);
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(5, 5);
  display.print("Suhu Tubuh");
  display.setTextSize(3);
  display.setCursor(6, 35);
  display.print(mlx.readObjectTempC()*1.090);
  Serial.println(mlx.readObjectTempC()*1.090);
  display.setTextSize(2);
  display.print((char)247);
  display.setTextSize(3);
  display.print("C");
  display.display(); 
  
  delay(3000);
  } 
  
 else{
  
  display.clearDisplay();
  display.setTextSize(3);
  display.setCursor(33, 10);
  display.print("Chek");
  display.setTextSize(2);
  display.setCursor(5, 40);
  display.print("Suhu Tubuh");
  display.display(); 
 }
}
