#include <Adafruit_DRV2605.h>
#include <Wire.h>

Adafruit_DRV2605 drv;

int PotPin = 0;
uint8_t effect = 0;
 
void setup() {
  Serial.begin(9600);
  drv.begin();
  drv.selectLibrary(1);
  drv.setMode(DRV2605_MODE_INTTRIG);
}
 
void loop() {
  int PotValue = analogRead(PotPin);
   
  if(PotValue < 100){
    Serial.print("vibration effect: nothing");
  }
  else if(PotValue < 300){
    effect = 51;
    drv.setWaveform(0, effect);
    Serial.print("vibration effect: 20%"); 
    drv.setWaveform(1, 0); 
    drv.go();
  }
  else if(PotValue < 500){
    effect = 50;
    drv.setWaveform(0, effect);
    Serial.print("vibration effect: 40%");
    drv.setWaveform(1, 0); 
    drv.go();
  }
  else if(PotValue < 700){
    effect = 49;
    drv.setWaveform(0, effect);
    Serial.print("vibration effect: 60%");
    drv.setWaveform(1, 0); 
    drv.go();
  }
  else if(PotValue < 900){
    effect = 48;
    drv.setWaveform(0, effect);
    Serial.print("vibration effect: 80%");
    drv.setWaveform(1, 0); 
    drv.go();
  }
  else{
    effect = 47;
    drv.setWaveform(0, effect);
    Serial.print("vibration effect: 100%");
    drv.setWaveform(1, 0); 
    drv.go();
  }

  Serial.print("\tpotential value: "); 
  Serial.println(PotValue);
  
  delay(250);
  
  
}
