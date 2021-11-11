#include <Arduino.h>
#include "webserver.h"
#include "wifi.h"
#include "store.h"
#include "update.h"
#include "ws.h"
// #include "mqtt.h"
#include "system.h"
#include "timer.h"
// #include "io.h"
#include "pzem.h"
void setup(void) {
  delay(3000);
  Serial.begin(115200);
  Serial.println();
  Serial.println("1");
  setupStore();
  Serial.println("2");
  setupWifi();
  Serial.println("3");
  setupWebserver();
  Serial.println("4");
  setupUpdate();
  Serial.println("5");
  setupWS();
  Serial.println("6");
  // setupMqtt();
  Serial.println("7");
  setupSystem();
  Serial.println("8");
  setupTimer();
  Serial.println("9");
  // setupIO();
  Serial.println("10");

  Serial.println("booted");
  setOnStoreChange([](String id, String val, bool isChange){
    DynamicJsonDocument doc(512);
    JsonObject objData = doc.to<JsonObject>();
    objData[id] = val.toFloat();
    String ret;

    serializeJson(objData, ret);
    webSocket.broadcastTXT(ret);
  });
  // setOnMqttIncome([](String topic, String msg){
  //   Serial.println(topic + ": "+ msg);
  //   DynamicJsonDocument doc(512);
  //   auto error = deserializeJson(doc, msg);
  //   if(error)
  //     return;
  //   JsonObject objData = doc.as<JsonObject>();
  //   String id = objData["id"];
  //   if(id.startsWith("schedule"))
  //     setValue(id, objData["value"], true);
  //   else
  //     setValue(id, objData["value"]);

  // });
  setOnWSTextIncome([](String msg){
    DynamicJsonDocument doc(512);
    auto error = deserializeJson(doc, msg);
    if(error)
      return;
    JsonObject objData = doc.as<JsonObject>();
    String id = objData["id"];
    if(id.startsWith("schedule"))
      setValue(id, objData["value"], true);
    else
      setValue(id, objData["value"]);
  });
}
uint32_t mainTimer = millis();
void loop(void) {
  if(millis() - mainTimer > 3000){
    mainTimer = millis();
  }
  loopWebserver();
  loopWS();
  // loopMqtt();
  loopTimer();
  loopPzem();
}