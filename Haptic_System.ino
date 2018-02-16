#include <Adafruit_DRV2605.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

Adafruit_SSD1306 display(-1);   // reset pin not used on 4-pin OLED module, -1 = no reset pin
#if (SSD1306_LCDHEIGHT != 64)   // 128 x 64 pixel display
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

Adafruit_DRV2605 drv;

int FSRAnalogPin = 0;         // set the analog input pin
uint8_t effect = 0;           // initialize the variable for waveform effect

unsigned long resistance = 0; // intialize the resistance and condutance variables for force calculation
unsigned long conductance = 0;
int pulldownR = 10000;        // define the resistance for the pull down resistor in ohms
long force = 0;               // initialze the measured force variable

 
void setup() {
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);    // define the OLED display TWI address
  display.clearDisplay();
  
  drv.begin();                // initialize the motor driver
  drv.selectLibrary(1);
  drv.setMode(DRV2605_MODE_INTTRIG);
}

void default_display(void){   // set up a function that displays default messages
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,3);
  display.print("HapticFeedback System");
  display.setCursor(0,20);
  display.print("Vibration lvl:");
  display.setCursor(0,30);
  display.print("Force: ");
  display.display();
}

void vibration_display(int value){     // set up a function for displaying the vibration level
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(90,20);
  display.print(value);
  display.print("/5");
  display.display();  
}

void wave_effect(uint8_t effect_value){     // set up a function that outputs corresponding waveform effect
  drv.setWaveform(0, effect_value);
  drv.setWaveform(1, 0);
  drv.go();
}

void force_calc(int FSR){
  int voltage = map(FSR, 0, 1023, 0, 5000); // convert the FSR value to 5000 mV
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(60,30);
  if(voltage == 0){         // if the voltage is zero, no pressure is applied
    display.print("no pressure");  
  }
  // formula for calculating resistance: 
  // resistance = ((V - U) * R) / U
  // V = 5000 mV, U is the measured voltage, R (pulldown resistance) = 10000 ohms 
  else{         
    resistance = 5000 - voltage;  
    resistance *= pulldownR;
    resistance /= voltage;
    conductance = 1000000 / resistance;    // caculate the conductance in micromhos
    // force vs conductance have two different behaviours depending on applied force
    // details can be found on the data sheet:
    // https://cdn-learn.adafruit.com/assets/assets/000/010/126/original/fsrguide.pdf
    if(conductance <= 1000){      
      force = conductance / 80;
    }
    else{
      force = conductance - 1000; 
      force /= 30; 
    }
    display.print(force);
  }
  display.display();
}
void loop() {
  default_display();        // calls the default message
  int FSRvalue = analogRead(FSRAnalogPin);
//  Serial.println(FSRvalue); // display the FSR value on serial monitor for easy debugging
  
  force_calc(FSRvalue);     // display the calcualted force
  
  if(FSRvalue < 100){       // if-else statements for determining the vibration level
    vibration_display(0);
  }
  else if(FSRvalue < 300){
    effect = 51;
    wave_effect(effect);
    vibration_display(1); 
  }
  else if(FSRvalue < 500){
    effect = 50;
    wave_effect(effect);
    vibration_display(2);
  }
  else if(FSRvalue < 700){
    effect = 49;
    wave_effect(effect);
    vibration_display(3);
  }
  else if(FSRvalue < 900){
    effect = 48;
    wave_effect(effect);
    vibration_display(4);
  }
  else{
    effect = 47;
    wave_effect(effect);
    vibration_display(5);
  }
  display.clearDisplay();   //clear display to refresh it 

  delay(200);
    
}
