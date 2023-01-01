#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP_Mail_Client.h>

#define WIFI_SSID "UIU-STUDENT"
#define WIFI_PASSWORD "12345678"

#define SMTP_server "smtp.gmail.com"
#define SMTP_Port 465


#define sender_email "autofarm8266@gmail.com"
#define sender_password "ypvoptshuwzoyxpr"

#define Recipient_email "official.net.work.cn@gmail.com"
#define doctor_email "asifkarim808@gmail.com"

SMTPSession smtp;
SMTP_Message message;
ESP_Mail_Session session;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  smtp.debug(1);
  session.server.host_name = SMTP_server ;
  session.server.port = SMTP_Port;
  session.login.email = sender_email;
  session.login.password = sender_password;
  session.login.user_domain = "";



}

void loop() {
  char val ;
  if (Serial.available() > 0) {
    val = Serial.read();
    if ((char)val == 'a') {



      /* Declare the message class */



      message.sender.name = "Auto Farm System";
      message.sender.email = sender_email;
      message.subject = "Farm status";
      message.addRecipient("Microcontrollerslab", Recipient_email);

      //Send HTML message
      String htmlMsg = "<div style=\"color:#0000FF;\"><h1>Hello Farmers!</h1><p>This is an for the ownars</p></div>";
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
     if ((char)val == 'b') {



      /* Declare the message class */



      message.sender.name = "Auto Farm System";
      message.sender.email = sender_email;
      message.subject = "Farm status";
      message.addRecipient("Microcontrollerslab", doctor_email);

      //Send HTML message
      String htmlMsg = "<div style=\"color:#0000FF;\"><h1>Hello Doctors!</h1><p>Doctor Email testing</p></div>";
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

}
