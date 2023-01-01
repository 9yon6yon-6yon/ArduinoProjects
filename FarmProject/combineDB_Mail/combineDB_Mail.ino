#include <Arduino.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP_Mail_Client.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SPI.h>
#include <MFRC522.h>
//db values
#define DHTPIN D2
#define DHTTYPE DHT11

//mail define

#define SMTP_server "smtp.gmail.com"
#define SMTP_Port 465


#define sender_email "autofarm8266@gmail.com"
#define sender_password "ypvoptshuwzoyxpr"

#define Recipient_email "official.net.work.cn@gmail.com"
#define doctor_email "asifkarim808@gmail.com"

DHT dht(DHTPIN, DHTTYPE);

SMTPSession smtp;
SMTP_Message message;
ESP_Mail_Session session;


int fire = 0;
int security = 0;

float humidityData;
float temperatureData;
float tmprtr;
const char* ssid = "UIU-STUDENT";//
const char* password = "12345678";
char server[] = "10.10.232.159";
WiFiClient client;

void setup()
{

  Serial.begin(115200);
  delay(10);
  dht.begin();

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  //server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
  delay(1000);
  Serial.println("connecting...");
  Serial.println();
  smtp.debug(1);
  session.server.host_name = SMTP_server ;
  session.server.port = SMTP_Port;
  session.login.email = sender_email;
  session.login.password = sender_password;
  session.login.user_domain = "";

}
void loop()
{
  int tmprt = analogRead(A0);
  float millivolts = tmprt * (500 / 1024.0);
  tmprtr = millivolts /10;
  
  humidityData = dht.readHumidity();
  temperatureData = dht.readTemperature();
  Sending_To_phpmyadmindatabase();
  delay(2000);


  if ( temperatureData > 30) {
    /* Declare the message class */
    message.sender.name = "Auto Farm Fire DEPT";
    message.sender.email = sender_email;
    message.subject = "Fire Alart";
    message.addRecipient("Microcontrollerslab", Recipient_email);

    //Send HTML message
    String htmlMsg = "<div style=\"color:#FF0000;\"><center><h1>DANGER DANGER</h1></center></div><p>There is a fire outbreak in the farm</p>";
    message.html.content = htmlMsg.c_str();
    message.html.content = htmlMsg.c_str();
    message.text.charSet = "us-ascii";
    message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;


    /* //Send simple text message
      String textMsg = "";//edit here
      message.text.content = textMsg.c_str();
      message.text.charSet = "us-ascii";
      message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
    */

    if (!smtp.connect(&session))
      return;


    if (!MailClient.sendMail(&smtp, &message))
      Serial.println("Error sending Email, " + smtp.errorReason());
  }
  if (tmprtr>34) {

    message.sender.name = "Auto Farm Medical";
    message.sender.email = sender_email;
    message.subject = "Patient needed help";
    message.addRecipient("Microcontrollerslab", doctor_email);

    //Send HTML message
    String htmlMsg = "<div style=\"color:#FF0000;\"><center><h1>Patient Alart!</h1></center></div><p>Please, check inside farm. Unexpected temperature detected</p>";
    message.html.content = htmlMsg.c_str();
    message.html.content = htmlMsg.c_str();
    message.text.charSet = "us-ascii";
    message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;


    /* //Send simple text message
      String textMsg = "";//edit here
      message.text.content = textMsg.c_str();
      message.text.charSet = "us-ascii";
      message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
    */

    if (!smtp.connect(&session))
      return;


    if (!MailClient.sendMail(&smtp, &message))
      Serial.println("Error sending Email, " + smtp.errorReason());

  }

}

void Sending_To_phpmyadmindatabase()   //CONNECTING WITH MYSQL
{
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    Serial.print("GET http://localhost/testcode/dht11.php?temperature=");
    client.print("GET http://localhost/testcode/dht11.php?temperature=");     //YOUR URL
    Serial.print(temperatureData);
    client.print(temperatureData);
    client.print("&humidity=");
    Serial.print("&humidity=");
    client.print(humidityData);
    Serial.print(humidityData);
     client.print("&lm35=");
    Serial.print("&lm35=");
    client.print(tmprtr);
    Serial.print(tmprtr);
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    Serial.println(" HTTP/1.1");
    client.println("Host: 192.168.147.242");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}
