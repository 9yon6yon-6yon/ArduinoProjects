#include <DHT.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SPI.h>
#include <MFRC522.h>

#define DHTPIN D2

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float humidityData;
float temperatureData;

const char* ssid = "COOLIOV1";//
const char* password = "8787878713";
char server[] = "192.168.147.242";
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
  Serial.print(WiFi.localIP());
  delay(1000);
  Serial.println("connecting...");
}
void loop()
{
  humidityData = dht.readHumidity();
  temperatureData = dht.readTemperature();
  Sending_To_phpmyadmindatabase();
  delay(2000); // interval
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
