#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <ESP8266WebServerSecure.h>

const char *ssid = "jk";
const char *password = "riya1234";
const char *dname = "esp8266";


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


BearSSL::ESP8266WebServerSecure server(443);
ESP8266WebServer serverHTTP(80);

static const char serverCert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIC6jCCAlOgAwIBAgIUFXvm/qJVeXQQpXLCnFSlO+7Sed8wDQYJKoZIhvcNAQEL
BQAwejELMAkGA1UEBhMCUk8xCjAIBgNVBAgMAUIxEjAQBgNVBAcMCUJ1Y2hhcmVz
dDEbMBkGA1UECgwST25lVHJhbnNpc3RvciBbUk9dMRYwFAYDVQQLDA1PbmVUcmFu
c2lzdG9yMRYwFAYDVQQDDA1lc3A4MjY2LmxvY2FsMB4XDTIyMDcyNTA3NTkwOVoX
DTIzMDcyNTA3NTkwOVowejELMAkGA1UEBhMCUk8xCjAIBgNVBAgMAUIxEjAQBgNV
BAcMCUJ1Y2hhcmVzdDEbMBkGA1UECgwST25lVHJhbnNpc3RvciBbUk9dMRYwFAYD
VQQLDA1PbmVUcmFuc2lzdG9yMRYwFAYDVQQDDA1lc3A4MjY2LmxvY2FsMIGfMA0G
CSqGSIb3DQEBAQUAA4GNADCBiQKBgQDhH8+4WA5qAE9BHIlZUK/gLmuuvsOQuhKu
U/qhfJFJvfR1p9d51uLHxWHyPa+cj5pV7N1a9FVLbgsFgi436Qvqr54cS9JMD74M
sE7JJI1ggfxE9KZQc7rmnWYrcO8fBRpsSRtfCr7lXLQMJTqGkFYh38N6AW1fph4V
3MREj15i7QIDAQABo20wazAdBgNVHQ4EFgQUOZkwy3zwJyz1XQr3PFvFxXkCVp0w
HwYDVR0jBBgwFoAUOZkwy3zwJyz1XQr3PFvFxXkCVp0wDwYDVR0TAQH/BAUwAwEB
/zAYBgNVHREEETAPgg1lc3A4MjY2LmxvY2FsMA0GCSqGSIb3DQEBCwUAA4GBAGmu
O0spVKmow7aIDW+ihxX2T1+V7LsMa7vozo7CbdI2q2F5M6G+zJWPLl67OWzDEmBs
NetZhL9Z7EtND7DYcle/dvvgD6ic5Fmp6Sxe2qaj3keVBZSDHq0+XOdtU47m+a2m
KKoBdO4hRcrCF5Q20H0IbzRLyjElJj7zO6L0EVR8
-----END CERTIFICATE-----
)EOF";

static const char serverKey[] PROGMEM =  R"EOF(
-----BEGIN PRIVATE KEY-----
MIICdwIBADANBgkqhkiG9w0BAQEFAASCAmEwggJdAgEAAoGBAOEfz7hYDmoAT0Ec
iVlQr+Aua66+w5C6Eq5T+qF8kUm99HWn13nW4sfFYfI9r5yPmlXs3Vr0VUtuCwWC
LjfpC+qvnhxL0kwPvgywTskkjWCB/ET0plBzuuadZitw7x8FGmxJG18KvuVctAwl
OoaQViHfw3oBbV+mHhXcxESPXmLtAgMBAAECgYA4QZPN1Ctd78/eTHxCFnisw8zi
8Qa7ztPGPnQeEJvZ2p8RG60r5DfthfSQ7TtKG1SM7lDuXqpF3Czi5oIYNKNmPPry
cDwjL9jNlPuvJM2wAAPs+P7vw9dIaqxPYvyW2mvrdzgbsRgWYCq2RNJT6Kej3HkF
riB0ZOvLfL/wlrqWoQJBAPtPnkM3nZoUukBBjxh8Nd6hyaiIhIgYQLE60RqnhNb9
8XVBSIQ5usQNT0QhRT1dlUoZuAT5X0VkEKdGceIE1KUCQQDlUxzdP6LQc0rQEqoi
YEgTwxLI/9GZJW8yXB9upl0vZYdEqCFq5wdryXrvwHixGKYH/rqrDo8y2D7hnvDx
/FqpAkA1NaJYsQnZedIFkNvvXz04qiC8YktNVXU9ESr87cMekh3xqaTk+iQlJnxF
/JVgbNQTIGbqBrK5SnqMMEokhMlRAkEAik7UK8RDiADg8Bkxr0XucqzGWZ+gZAMl
y3OwKWYA8aMEMC5O6VCpMyLzGEI3CGhbSpshLiW7y+iMFDtuCiQu8QJBAPY8aEWM
hg3lAba5trHG6QLwzivNUm+nIhY/VhYSOcbQNo/C/0Y7rnn/xWJDUo8JRojg63jD
P1wZqgpXOdlfoqs=
-----END PRIVATE KEY-----
)EOF";

bool connectToWifi() {
  byte timeout = 50;

  Serial.println("\n\n");

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  for (int i = 0; i < timeout; i++) {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\nConnected to WiFi");
      Serial.print("Server can be accessed at https://");
      Serial.print(WiFi.localIP());
      if (MDNS.begin(dname)) {
        // https://superuser.com/questions/491747/how-can-i-resolve-local-addresses-in-windows
        Serial.print(" or at https://");
        Serial.print(dname);
        Serial.println(".local");
      }
      return true;
    }
    delay(5000);
    Serial.print(".");
  }

  Serial.println("\nFailed to connect to WiFi");
  Serial.println("Check network status and access data");
  Serial.println("Push RST to try again");
  return false;
}

void showWebpage() {

  server.send(200, "text/html", R"rawliteral(
<!DOCTYPE html><html lang="en"><head> <meta http-equiv="X-UA-Compatible" content="IE=edge"> <meta name="viewport" content="width=device-width, initial-scale=1.0"> <title>Automagic</title> <script src="//cdnjs.cloudflare.com/ajax/libs/annyang/2.6.1/annyang.min.js"></script><link rel="stylesheet" href="https://pratik-karale.github.io/iotApp/main.css"></head><body> <nav><h2>Automagic</h2></nav><div class="room" data-room="room1"> <h3 class="room-title">Room#1</h3><br><button class="room-btn" data-btn="door" data-active="0">1F6AA</button> <button class="room-btn" data-btn="light" data-active="0">1F4A1</button> </div><div class="room" data-room="room2"> <h3 class="room-title">Room#2</h3><br><button class="room-btn" data-btn="fan" data-active="0">1F343</button> <button class="room-btn" data-btn="light" data-active="0">1F4A1</button> </div><div class="room" data-room="garden"> <h3 class="room-title">Garden</h3><br><button class="room-btn" data-btn="pump" data-active="0">1F4A7</button> </div><button id="mic-btn" data-active="0">1F3A4</button> <script src="https://pratik-karale.github.io/iotApp/main.js"></script></body></html>
)rawliteral");
}

void secureRedirect() {
  serverHTTP.sendHeader("Location", String("https://esp8266.local"), true);
  serverHTTP.send(301, "text/plain", "");
}

void setup() {
  if (!connectToWifi()) {
    delay(60000);
    ESP.restart();
  }
  Serial.println("ye connected");

  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");

  serverHTTP.on("/", secureRedirect);
  serverHTTP.begin();

  server.getServer().setRSACert(new BearSSL::X509List(serverCert), new BearSSL::PrivateKey(serverKey));
  server.on("/", showWebpage);

//***********test led
  server.on("/test/light/start", HTTP_GET, [](){
    digitalWrite(BUILTIN_LED,1);
    server.send(200, "text/html", "test light started");
  });
  server.on("/test/light/stop", HTTP_GET, [](){
    digitalWrite(BUILTIN_LED,0);
    server.send(200, "text/html", "test light off");
  });

//server.on("/room1/light/start", HTTP_GET, [](){
//    digitalWrite(room1LightPin,1);
//    server.send(200, "text/plain", "light started!");
//  });
//  server.on("/room1/light/stop", HTTP_GET, [](){
//    digitalWrite(room1LightPin,0);
//    server.send(200, "text/plain", "light stopped!");
//  });


  Serial.println("Server is ready");
}

void loop() {
  serverHTTP.handleClient();
  server.handleClient();
  MDNS.update();
}
