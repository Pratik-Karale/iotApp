#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Servo.h>
Servo servo;

//pins
const int servoPin=2;
const int room1LightPin=4;
const int room2LightPin=0;
const int room2FanPin=14;
const int flameSensorPin=12;
const int gardenPumpPin=13;
const int buzzerPin=15;
const int irSensorPin=16;

int irOnce=0;

const char* ssid     = "ESP8266-Access-Point";
const char* password = "123456789";


// Create AsyncWebServer object on port 80
AsyncWebServer server(80);


char * httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();
    int n = payload.length();
    char char_array[n + 1];
    strcpy(char_array, payload.c_str());

  return char_array;
}


const char* index_html= httpGETRequest("https://frigidqualifiedcore.jotarokujo54.repl.co/");

void setup(){
//  servo setup
servo.attach(servoPin); //D4

//pin mode setup
pinMode(room1LightPin,OUTPUT);
pinMode(room2LightPin,OUTPUT);
pinMode(room2FanPin,OUTPUT);
pinMode(flameSensorPin,INPUT);
pinMode(irSensorPin,INPUT);
pinMode(gardenPumpPin,OUTPUT);



  
  // Serial port for debugging purposes
  Serial.begin(115200);
 
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });
  server.on("/fire", HTTP_GET, [](AsyncWebServerRequest *request){
    std::string tmp = std::to_string(digitalRead(flameSensorPin));
    char const *num_char = tmp.c_str();
    request->send_P(200, "text/plain", num_char);
  });
//***********test led
  server.on("/test/light/start", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(BUILTIN_LED,1);
    request->send_P(200, "text/plain", "light started!");
  });
  server.on("/test/light/stop", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(BUILTIN_LED,0);
    request->send_P(200, "text/plain", "light started!");
  });


//  *************ROOM 1 *********************
//door
  server.on("/room1/door/start", HTTP_GET, [](AsyncWebServerRequest *request){
    servo.write(180);
    request->send_P(200, "text/plain", "door opened!");
  });
  server.on("/room1/door/stop", HTTP_GET, [](AsyncWebServerRequest *request){
    servo.write(0);
    request->send_P(200, "text/plain", "door closed!");
  });

//  light
  server.on("/room1/light/start", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(room1LightPin,1);
    request->send_P(200, "text/plain", "light started!");
  });
  server.on("/room1/light/stop", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(room1LightPin,0);
    request->send_P(200, "text/plain", "light stopped!");
  });


  
//  *************ROOM 2 *********************
//  light
  server.on("/room2/light/start", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(room2LightPin,1);
    request->send_P(200, "text/plain", "light started!");
  });
  server.on("/room2/light/stop", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(room2LightPin,0);
    request->send_P(200, "text/plain", "light stopped!");
  });

//  fan
  server.on("/room2/fan/start", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(room2FanPin,1);
    request->send_P(200, "text/plain", "light started!");
  });
  server.on("/room2/fan/stop", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(room2FanPin,0);
    request->send_P(200, "text/plain", "light started!");
  });




  
  //  *************GARDEN*********************
//  pump
    server.on("/garden/pump/start", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(gardenPumpPin,1);
    request->send_P(200, "text/plain", "light started!");
  });
  server.on("/garden/pump/stop", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(gardenPumpPin,0);
    request->send_P(200, "text/plain", "light started!");
  });



  // Start server
  server.begin();
}
 
void loop(){  
 if(digitalRead(flameSensorPin)){
  digitalWrite(buzzerPin,1);
 }else{
  digitalWrite(buzzerPin,0);
 }
 
 if(!digitalRead(irSensorPin) && !irOnce){
  irOnce=1;
  servo.write(180);
  delay(10000);
  servo.write(0);
  delay(1);
 }
 else if(digitalRead(irSensorPin)){
  irOnce=0;
 }
}
