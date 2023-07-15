#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Motor PINs
#define ENA D0
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4
#define ENB D5
 
bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;
int Speed;
char auth[] = "4bv_8AGLE5qem7LEhVre6-_R2rIacuvg"; //Enter your Blynk application auth token (My id for rc car template)
//char auth[] = "icilissTr-UVC-n9h7O9Crp2az2lDmlb";
char ssid[] = "faeq"; //Enter your WIFI name
char pass[] = "asdzxc12345"; //Enter your WIFI passowrd
float vref = 3.3;
float resolution = (vref)/1024;
 
void setup() {
  Serial.begin(115200);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
 WiFi.begin(ssid, pass);

  Serial.println("WiFi connected");  
  Blynk.begin(auth, ssid, pass,"blynk.cloud",80);
}
 
BLYNK_WRITE(V0) {
  forward = param.asInt();
}
 
BLYNK_WRITE(V1) {
  backward = param.asInt();
}
 
BLYNK_WRITE(V3) {
  left = param.asInt();
}
 
BLYNK_WRITE(V2) {
  right = param.asInt();
}
 
BLYNK_WRITE(V4) {
  Speed = param.asInt();
}
 
void smartcar() {
  if (forward == 1) {
    carforward();
    Blynk.virtualWrite(V6,"Forward");
    Serial.println("carforward");
  } else if (backward == 1) {
    carbackward();
    Blynk.virtualWrite(V6,"Backward");
    Serial.println("carbackward");
  } else if (left == 1) {
    carturnleft();
    Blynk.virtualWrite(V6,"Left");
    Serial.println("carfleft");
  } else if (right == 1) {
    carturnright();
    Blynk.virtualWrite(V6,"Right");
    Serial.println("carright");
    
  } else if (forward == 0 && backward == 0 && left == 0 && right == 0) {
    carStop();
    Blynk.virtualWrite(V6,"Stop");
    Serial.println("carstop");
  }
}
void loop() {
  Blynk.run();
  smartcar();
  temp();
}
 
void carforward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carbackward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carturnleft() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carturnright() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void temp()
{
float temperature = analogRead(A0);
 temperature = (temperature*resolution);
 temperature = temperature*1000;
 Serial.println(temperature);
 Blynk.virtualWrite(V5,temperature);
 delay(250);
}
/*
 My id for rc car template
 #define BLYNK_TEMPLATE_ID "TMPL3ljAQn9yn"
#define BLYNK_TEMPLATE_NAME "rc car"
#define BLYNK_AUTH_TOKEN "4bv_8AGLE5qem7LEhVre6-_R2rIacuvg"*/
