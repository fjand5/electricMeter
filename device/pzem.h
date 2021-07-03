#include "./src/webserver.h"
#include "./src/config.h"
#include "./src/mqtt.h"
#include "./ui.h"

#include <PZEM004Tv30.h>
PZEM004Tv30 pzem(D1, D2);
void updatePzem();
void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    delay(2000);
    setupConfig();
    
    renderUI();
    
    setupWebserver();
    setupMqtt();
}

uint32_t pzemTimer = millis();
void loop() {
  loopWebserver();
  loopMqtt();

  if(millis() - pzemTimer > 1000){
      pzemTimer = millis();
      updatePzem();
  }
}

void updatePzem(){
    static uint32_t oneHoursTimer = millis();
    static float sumPower=0;
    static float countPower=0;

    float voltage = pzem.voltage();
    if( !isnan(voltage) ){
        setValue("pzem-voltage",String("Điện áp: ") + String(voltage) + " V");
    } else {
        Serial.println("Error reading voltage");
    }
    float current = pzem.current();
    if( !isnan(current) ){
        setValue("pzem-current",String("Dòng điện: ") + String(current) + " A");
    } else {
        Serial.println("Error reading current");
    }
    float power = pzem.power();
    if( !isnan(power) ){
        setValue("pzem-power",String("Công suất: ") + String(power) + " W");
        sumPower+=power;
        countPower+=1;
        if(millis() - oneHoursTimer > 1000*3600){
            oneHoursTimer = millis();
            float avgPower = sumPower/countPower;
            addData(avgPower, "pzem-chart-power", "Công suất", true, "#ff0000", 24);
            sumPower=0;
            countPower=0;
        }
    } else {
        Serial.println("Error reading power");
    }
    float energy = pzem.energy();
    if( !isnan(energy) ){
        setValue("pzem-energy",String("Tổng số điện: ") + String(energy) + " kWh");
    } else {
        Serial.println("Error reading energy");
    }
    float frequency = pzem.frequency();
    if( !isnan(frequency) ){
        setValue("pzem-frequency",String("Tần số: ") + String(frequency) + " Hz");
    } else {
        Serial.println("Error reading frequency");
    }
    float pf = pzem.pf();
    if( !isnan(pf) ){
        setValue("pzem-pf",String("Hệ số: ") + String(pf));
    } else {
        Serial.println("Error reading power factor");
    }

}
