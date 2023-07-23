#include "DHT.h"      
#include "WiFi.h"
#include "HTTPClient.h"

#define DHTPIN 13       
#define DHTTYPE DHT22   
DHT dht(DHTPIN, DHTTYPE);     

#define echoPin 25
#define trigPin 26
long duration, distance;

const char* ssid="Redmi 9";
const char* pass="rizkijn123";

const char* host="semarbro.com";

void setup(){
  Serial.begin(115200);
  dht.begin(); 

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  WiFi.begin(ssid, pass);
  Serial.println("Connecting...");
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
    }
    Serial.println("Connected");
}
void loop(){
  float t = dht.readTemperature();
  float k = dht.readHumidity();
  
  Serial.print("\n");
  Serial.print(" Temperature: ");
  Serial.print(t);
  Serial.print("°C ");
  Serial.print(" || ");
  Serial.print(" Kelembaban: ");
  Serial.print(k);
  Serial.println("% ");


  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration/58.2;
  Serial.print(distance);
  Serial.print(" || ");

  if (distance <=24 ){
  Serial.println("Tempat Pakan Tersedia");
  }

else{
  Serial.println("Tempat Pakan Habis");
  }

  WiFiClient client;
  const int httpPort = 80;
  if( !client.connect(host, httpPort))
  {
    Serial.println("Connection Failed");
    return;
    }

  String Link;
  HTTPClient http;

  Link = "https://"+ String(host) +"/data/kirimdata2.php?suhu="+ String(t)+ "&kelembaban="+ String(k) + "&bahan="+ String(distance);
  http.begin(Link);
  http.GET();

  String respon = http.getString();
  Serial.println(respon);
  http.end();

  delay(500);
}
