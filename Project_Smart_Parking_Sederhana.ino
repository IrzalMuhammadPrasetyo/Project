#define t1 2
#define e1 3
#define t2 4
#define e2 5
#define t3 6
#define e3 7
#define t4 8
#define e4 9

#define led1 10
#define led2 11
#define led3 12
#define led4 13

long waktu1, jarak1, waktu2, jarak2, waktu3, jarak3, waktu4, jarak4;

void setup()
{
  pinMode(t1, OUTPUT);
  pinMode(e1, INPUT);
  pinMode(t2, OUTPUT);
  pinMode(e2, INPUT);
  pinMode(t3, OUTPUT);
  pinMode(e3, INPUT);
  pinMode(t4, OUTPUT);
  pinMode(e4, INPUT);
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop(){
if (jarak1<=10) {
  alat1();
}else if (jarak2<10) {
  alat2();
}else if(jarak3<10) {
  alat3;
}else if(jarak4<10) {
  alat4();
  }
}

void alat1(){
digitalWrite(t1, LOW);
delayMicroseconds(2);
digitalWrite(t1, HIGH);
delayMicroseconds(10);
digitalWrite(t1, LOW);
  
waktu1 = pulseIn(e1, HIGH);
jarak1 = waktu1/58.2;
  
  digitalWrite(led1, HIGH);
}       

void alat2(){
digitalWrite(t2, LOW);
delayMicroseconds(2);
digitalWrite(t2, HIGH);
delayMicroseconds(10);
digitalWrite(t2, LOW);
  
waktu2 = pulseIn(e2, HIGH);
jarak2 = waktu2/58.2;
  
  digitalWrite(led2, HIGH);
}
  
void alat3(){
digitalWrite(t3, LOW);
delayMicroseconds(2);
digitalWrite(t3, HIGH);
delayMicroseconds(10);
digitalWrite(t3, LOW);
  
waktu3 = pulseIn(e3, HIGH);
jarak3 = waktu3/58.2;
    
  digitalWrite(led3, HIGH);
}
        
void alat4(){
digitalWrite(t1, LOW);
delayMicroseconds(2);
digitalWrite(t1, HIGH);
delayMicroseconds(10);
digitalWrite(t1, LOW);
  
waktu4 = pulseIn(e1, HIGH);
jarak4 = waktu4/58.2;
  
  digitalWrite(led4, HIGH);
}
