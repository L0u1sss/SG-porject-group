#include <TridentTD_LineNotify.h>
#define SSID        "DCI-F3"
#define LINE_TOKEN  "aW6A6TxJcbFCBEhDNMYii0C6Zscs40WcXips63FHFlG"

const int motionSensorIN = 25;
const int motionSensorOUT = 33;
int previousValueIN = 0;
int previousValueOUT = 0;
int nIN=0;
int nOUT=0;
#define AO_PIN 36

void setup() {
  Serial.begin(9600);
  pinMode(motionSensorIN, INPUT);
  pinMode(motionSensorOUT, INPUT);
  Serial.println(LINE.getVersion());
  WiFi.begin(SSID);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    delay(100);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());

  LINE.setToken(LINE_TOKEN);

}

void loop() {
  int pirIN=digitalRead(motionSensorIN);
  int pirOUT=digitalRead(motionSensorOUT);
  int lightValue = analogRead(AO_PIN);
  //check IN
 if((previousValueIN != pirIN) && (previousValueIN == 0)){
  previousValueIN = pirIN;
  nIN++;
 }
 if((previousValueIN != pirIN) && (previousValueIN == 1)){
  previousValueIN = 0;
 }
 //check OUT
 if((previousValueOUT != pirOUT) && (previousValueOUT == 0)){
  previousValueOUT = pirOUT;
  nOUT++;
 }
 if((previousValueOUT != pirOUT) && (previousValueOUT == 1)){
  previousValueOUT = 0;
 }
 int nLEFT=nIN-nOUT;
 if((nLEFT<=0) && (lightValue <= 2000)){
  LINE.notify("มาปิดไฟ!!! TURN OFF THE LIGHT!!!");
  LINE.notifyPicture("https://i.pinimg.com/236x/09/cf/fc/09cffc7924974d6e1ecafb6bef295644.jpg");
 }
 Serial.println("---------------------");
 Serial.print("previousValeIN: ");
 Serial.println(previousValueIN);
 Serial.print("pirIN: ");
 Serial.println(pirIN);
 Serial.print("numberIN: ");
 Serial.println(nIN);
 Serial.println(" ");
 Serial.print("previousValeOUT: ");
 Serial.println(previousValueOUT);
 Serial.print("pirOUT: ");
 Serial.println(pirOUT);
 Serial.print("numberOUT: ");
 Serial.println(nOUT);
 Serial.println(" ");
 Serial.print("The AO value: ");
 Serial.println(lightValue);
 Serial.println(nLEFT);
 Serial.println("---------------------");
 delay(3000);
  }
