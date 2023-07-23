//Library yang digunakan
  #include <WiFi.h>
  #include <FirebaseESP32.h>
  #include <Wire.h>
  #include <LiquidCrystal_I2C.h>
  #include <DHT.h>

//Lcd I2C
  LiquidCrystal_I2C lcd(0x27, 20, 4);
  byte Simbol_derajat = B11011111;

//DHT22
  #define DHTTYPE DHT22
  #define DHTPIN 13
  float kelembaban, suhu;
  DHT dht(DHTPIN, DHTTYPE);

//pH
  #define PHSensorPin A7 
  float calibration_value = 21.47 - 0.7;
  int phval = 0; 
  unsigned long int avgval; 
  int buffer_arr[10],temp;
  float ph_act;

//W
  int nilai;

//TDS
  #define TdsSensorPin A3
  #define VREF 5.0    
  #define SCOUNT  30  
  int analogBuffer[SCOUNT]; 
  int analogBufferTemp[SCOUNT];
  int analogBufferIndex = 0,copyIndex = 0;
  float averageVoltage = 0,tdsValue = 0,temperature = 25;

//Pin relay yang digunakan
  #define relay1  19
  #define relay2  18
  #define relayA  32
  #define relayB  33

//Konek wifi
  #define FIREBASE_HOST "https://webtav2-default-rtdb.asia-southeast1.firebasedatabase.app/"
  #define FIREBASE_AUTH "o7SZMW3vxW5SvIQot5zxlzQuomhUMVYcVINSfnLj"
  #define WIFI_SSID "Helmi"
  #define WIFI_PASSWORD "12345678"

//Firebase
  FirebaseData firebaseData;
  FirebaseJson sh;
  FirebaseJson klbbn;
  FirebaseJson ph;
  FirebaseJson wl;
  FirebaseJson tds;

void setup () {
//Serial monitor
  Serial.begin (115200);

//Deklarasi pin yang digunakan
  pinMode(TdsSensorPin,INPUT);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relayA, OUTPUT);
  pinMode(relayB, OUTPUT);

  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relayA, HIGH);
  digitalWrite(relayB, HIGH);
  
//Untuk lcd
  lcd.init();
  lcd.backlight();

//DHT22
  dht.begin();

//Tampilan awal lcd
  lcd.setCursor(6, 2);
  lcd.print("Ovaponic");
  delay(5000);
  lcd.clear();

//Proses konek wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Menghubungkan Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
    lcd.setCursor(0, 1);
    lcd.print("Menghubungkan");
    lcd.setCursor(12, 2);
    lcd.print("Wi-Fi...");
  }
  Serial.println();
  Serial.print("terhubung dengan IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
  
  Serial.println("------------------------------------");
  Serial.println("Terhubung...");
  
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Terhubung");
  lcd.setCursor(5, 2);
  lcd.print(WiFi.localIP());
  delay(3000);
  lcd.clear();
}

void loop() { 
//Pemanggilan fungsi 
  Dht();
  pH();
  W();
  TDS();
  delay(50);
  
//Sistem relay sensor ph
  if(ph_act < 5){
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  delay(1000);

  lcd.setCursor(4,2);
  lcd.print(ph_act);
  }
  else if(ph_act > 7){
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  delay(1000);

  lcd.clear();
  lcd.setCursor(4,2);
  lcd.print(ph_act);
  }
  else{    
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  }

//Sistem relay TDS
  if(tdsValue <= 1400){
  digitalWrite(relayA, LOW);
  digitalWrite(relayB, LOW);
  delay(1000);
  }
  else{
  digitalWrite(relayA, HIGH);
  digitalWrite(relayB, HIGH);

  lcd.clear();
  lcd.setCursor(5,3);
  lcd.print(tdsValue,0);
  }

//Menampilkan water level di lcd
  lcd.setCursor(0,0);
  lcd.print("Ketinggian Air: ");
  
  if(nilai <= 2040) {
  lcd.setCursor(16, 0);
  lcd.print("L");
  }
  else{
  lcd.setCursor(16, 0);
  lcd.print("H");
  }

//Menampilkan sensor DHT di lcd
  lcd.setCursor(0, 1);
  lcd.print("S: ");
  lcd.setCursor(3, 1);
  lcd.print(suhu);
  lcd.setCursor(8,1);
  lcd.write(Simbol_derajat);
  lcd.setCursor(9,1);
  lcd.print("C");
  lcd.setCursor(11, 1);
  lcd.print("K: ");
  lcd.setCursor(14, 1);
  lcd.print(String(kelembaban) + "%");

//Menampilkan sensor pH di lcd
  lcd.setCursor(0,2);
  lcd.print("pH: ");
  lcd.setCursor(4,2);
  lcd.print(ph_act);
  lcd.setCursor(9,2);
  lcd.print("pH");

//Menampilkan sensor TDS di lcd
  lcd.setCursor(0,3);
  lcd.print("TDS: ");
  lcd.setCursor(5,3);
  lcd.print(tdsValue,0);
  lcd.setCursor(10,3);
  lcd.print("ppm");

//Pengiriman data ke firebase
  sh.set("Suhu", suhu);
  klbbn.set("Kelembaban", kelembaban);
  ph.set("pH", ph_act);
  wl.set("Water Level", nilai);
  tds.set("TDS", tdsValue);
  Firebase.updateNode(firebaseData,"Data_1",sh);
  Firebase.updateNode(firebaseData,"Data_1",klbbn);
  Firebase.updateNode(firebaseData,"Data_1",ph);
  Firebase.updateNode(firebaseData,"Data_1",wl);
  Firebase.updateNode(firebaseData,"Data_1",tds);
}

//Sensor DHT22
void Dht(){
  kelembaban = dht.readHumidity();
  suhu = dht.readTemperature();

  Serial.println("Sensor DHT 22:");
  Serial.print("Kelembaban : " + String(kelembaban) + "%");
  Serial.println(", Temperature : " + String(suhu) + "°C\n\t");
}

//Sensor pH
void pH(){
  for(int i=0;i<10;i++){ 
  buffer_arr[i]=analogRead(PHSensorPin);
  delay(30);
  }
  for(int i=0;i<9;i++){
    for(int j=i+1;j<10;j++){
      if(buffer_arr[i]>buffer_arr[j]){
        temp=buffer_arr[i];
        buffer_arr[i]=buffer_arr[j];
        buffer_arr[j]=temp;
       }
     }
   }
  avgval=0;
  for(int i=2;i<8;i++)
  avgval+=buffer_arr[i];
  float volt=(float)avgval*3.3/4095/6; 
  ph_act = -5.70 * volt + calibration_value;

  Serial.print("pH Val:");
  Serial.print(ph_act);
  Serial.println(" pH\n\t");
}

//Sensor Water Level
void W(){
  nilai = analogRead(A6);
  Serial.println("Water Lavel: ");
  
  if(nilai <= 2040) {
  Serial.print("Nilai: ");
  Serial.print(nilai);
  Serial.println(" || LOW\n\t"); 
  }
  else{
  Serial.print("Nilai: ");
  Serial.print(nilai);
  Serial.println(" || HIGH\n\t");
  }
}

//Sensor TDS
void TDS(){
   static unsigned long analogSampleTimepoint = millis();
   if(millis()-analogSampleTimepoint > 40U)
   {
     analogSampleTimepoint = millis();
     analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);   
     analogBufferIndex++;
     if(analogBufferIndex == SCOUNT) 
         analogBufferIndex = 0;
   }   
   static unsigned long printTimepoint = millis();
   if(millis()-printTimepoint > 800U)
   {
      printTimepoint = millis();
      for(copyIndex=0;copyIndex<SCOUNT;copyIndex++)
      analogBufferTemp[copyIndex]= analogBuffer[copyIndex];
      averageVoltage = getMedianNum(analogBufferTemp,SCOUNT) * (float)VREF /4095; 
      float compensationCoefficient=1.0+0.02*(temperature-25.0);   
      float compensationVolatge=averageVoltage/compensationCoefficient;  
      tdsValue=(133.42*compensationVolatge*compensationVolatge*compensationVolatge - 255.86*compensationVolatge*compensationVolatge + 857.39*compensationVolatge)*0.5; 
      Serial.println ("Sensor TDS: ");
      Serial.print("TDS Value: ");
      Serial.print(tdsValue,0);
      Serial.println(" ppm\n\t");
   }
}

int getMedianNum(int bArray[], int iFilterLen) 
{
  int bTab[iFilterLen];
  for(byte i = 0; i<iFilterLen; i++)
  bTab[i] = bArray[i];
  int i, j, bTemp;
  for(j = 0; j < iFilterLen - 1; j++) {
    for(i = 0; i < iFilterLen - j - 1; i++) {
      if(bTab[i] > bTab[i + 1]) {
        bTemp = bTab[i];
        bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
          }
        }
      }
  if((iFilterLen & 1) > 0)
  bTemp = bTab[(iFilterLen - 1) / 2];
  else
  bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
  return bTemp;
 }
