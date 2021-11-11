#include <PZEM004Tv30.h>
PZEM004Tv30 pzem(D1, D2);
void updatePzem();
void setupPzem() {  
    
}

uint32_t pzemTimer = millis();
void loopPzem() {

  if(millis() - pzemTimer > 2000){
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
        setValue("pzemVoltage",String(voltage));
    } else {
        Serial.println("Error reading voltage");
    }
    float current = pzem.current();
    if( !isnan(current) ){
        setValue("pzemCurrent",String(current));
    } else {
        Serial.println("Error reading current");
    }
    float power = pzem.power();
    if( !isnan(power) ){
        setValue("pzemPower",String(power));
        sumPower+=power;
        countPower+=1;
        if(millis() - oneHoursTimer > 1000*3600){
            oneHoursTimer = millis();
            float avgPower = sumPower/countPower;
            // addData(avgPower, "pzemchart-power", "Công suất", true, "#ff0000", 24);
            sumPower=0;
            countPower=0;
        }
    } else {
        Serial.println("Error reading power");
    }
    float energy = pzem.energy();
    if( !isnan(energy) ){
        setValue("pzemEnergy",String(energy));
    } else {
        Serial.println("Error reading energy");
    }
    float frequency = pzem.frequency();
    if( !isnan(frequency) ){
        setValue("pzemFrequency",String(frequency));
    } else {
        Serial.println("Error reading frequency");
    }
    float pf = pzem.pf();
    if( !isnan(pf) ){
        setValue("pzemPf",String(pf));
    } else {
        Serial.println("Error reading power factor");
    }

}
