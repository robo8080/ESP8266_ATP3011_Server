#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <AquesTalk.h>
#include <Wire.h>  // I2Cライブラリ 必須！

AquesTalk atp;  // 音声合成のインスタンス

const char* ssid = "****************";
const char* password = "****************";

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}

void handleNotFound(){
   String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void handle_speech() {
  String message = server.arg("say");
  message = message + "\n";
  Serial.println(message);

  ////////////////////////////////////////
  // 音声の発声
  ////////////////////////////////////////
  int len = message.length();
  char buff[len];
  message.toCharArray(buff,len);  
  atp.Synthe(buff);  // 引数に指定のテキストを発声
  
  ////////////////////////////////////////
  // 発声終了まで待つ
  ////////////////////////////////////////
  while(atp.IsBusy()) delay(1); // Busyを返す間ループ
  server.send(200, "text/plain", String("OK"));
}

void setup(void){
  Serial.begin(115200);

  ////////////////////////////////////////
  // AquesTalk pico LSIの応答チェック
  // LSIが応答するか最初にチェックしておく
  ////////////////////////////////////////
  if( !atp.IsActive() ){
    // 音声合成LSIから応答が得られない。配線等をチェック
    Serial.println("\nNo response.");
  }
  else {
    Serial.println("\nActive");
  }
  
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  // And as regular external functions:
  server.on("/speech", handle_speech);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
