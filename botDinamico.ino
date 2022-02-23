#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncTCP.h>
#include <FS.h>

uint8_t MotoreSxAvanti = D5;     // Enable dei motori
uint8_t MotoreSxIndietro = D6;
uint8_t MotoreDxAvanti = D2;
uint8_t MotoreDxIndietro = D3;
const char* ssid = "ASUS base";
const char* password = "marconovelliluisabarchetti.2011";
const char* input_parameter1 = "X";
const char* input_parameter2 = "Y";


AsyncWebServer httpServer(80);

void handleNotFound(AsyncWebServerRequest *request);
 
void serverRouting();

void setup() {
  Serial.begin (9600);
  Serial.setDebugOutput(true);

  pinMode(MotoreSxAvanti , OUTPUT);
  pinMode(MotoreSxIndietro , OUTPUT);
  pinMode(MotoreDxAvanti , OUTPUT);
  pinMode(MotoreDxIndietro , OUTPUT);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connettiti a: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

   Serial.print(F("Inizializing FS..."));
  if (SPIFFS.begin()){
    Serial.println(F("done."));
  }else{
    Serial.println(F("fail."));
  }
 
  Serial.println("Set routing for http server!");
  serverRouting();

  // se richiedo un numero random
  httpServer.on("/rand", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(random(1000)));
  });
  
  // richiesta di esempio personalizzata di prova
  httpServer.on("/index", HTTP_GET, [](AsyncWebServerRequest *request){    
    String inputMessage1;
    String inputMessage2;
      if (request->hasParam(input_parameter1) && request->hasParam(input_parameter2)) {
        inputMessage1 = request->getParam(input_parameter1)->value();
        inputMessage2 = request->getParam(input_parameter2)->value();
        Serial.println("X pos: " + inputMessage1 + " Y pos: " + inputMessage2);
        motore(inputMessage1.toInt(),inputMessage2.toInt());
        request->send(200, "text/plain", "next");
      }
    });
  
  httpServer.begin();
  Serial.println("HTTP server started");
}


void loop() {

}
