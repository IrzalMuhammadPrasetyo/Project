  #include "CTBot.h";
CTBot myBot;

String ssid = "Galaxy Note9cccf";
String pass = "12345678";
String token = "5119193014:AAFm2X-7LNaIrw0H99hM1yFMG3DXquuyWwQ";

#define led 5

const char* Perintah_On = "/NyalakanLampu";
const char* Perintah_Off = "/MatikanLampu";

int ON = LOW, OFF = HIGH;

void setup() {
  Serial.begin(115200);
  Serial.println("Memulai TelegramBot");
  
myBot.wifiConnect(ssid, pass);
myBot.setTelegramToken(token);

if (myBot.testConnection())   
        Serial.println("\nKoneksi Ke BOT OK"); else Serial.println("\nTidak Terkoneksi Ke BOT");
           pinMode(led, OUTPUT);
           
           digitalWrite(led, OFF);
     
      Serial.println("Perintah Telegram Siap Di Fungsikan");
}

void loop() {
  TBMessage msg;

  
  if (myBot.getNewMessage(msg)) {                                                               
    if (msg.text.equalsIgnoreCase(Perintah_On)) {                                             
        digitalWrite(led, ON);                                                        
          myBot.sendMessage(msg.sender.id, "Lampu Menyala");}          
    
    else if (msg.text.equalsIgnoreCase(Perintah_Off)) {                                       
            digitalWrite(led, OFF);                                                   
              myBot.sendMessage(msg.sender.id, "Lampu Mati");}                             
  
    else {                                                                                      
     String Balasan;
      Balasan = (String)"Selamat Datang " + msg.sender.username + (String)"🖐"
                "\nPada konten kontrol lampu berbasis IoT dengan Laboratorium uPCI."
                "\nGunakan Perintah Berikut:"
                "\n\n💡Lampu💡 :\n\t"
                  + String(Perintah_On)+" ⬅ On\n\t"
                  + String(Perintah_Off)+" ⬅ Off\n"
                  
                "\nTerima Kasih sudah berkunjung ke Laboratorium uPCI."
                  "\nSampai jumpa di konten selanjutnya😊\n"
            
      ;myBot.sendMessage(msg.sender.id, Balasan);             
    }
  }

 Serial.println("Chek Looping");
  // wait 500 milliseconds
  delay(500);
}
