#include "HX711.h"

#define calibration_factor 165000.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define LOADCELL_DOUT_PIN  4
#define LOADCELL_SCK_PIN  3
#define fsrpin A0
int solPin = 4;
int flowPin=2;
double flowRate;
volatile int count;

int l_hour;
unsigned long currentTime;
unsigned long cloopTime;

HX711 scale;

  void Flow()
  {
    count++;
  }

void setup() {
  Serial.begin(9600);
  //Solenoid pin
  pinMode(solPin, OUTPUT);
  //Flowrate setup
  pinMode(flowPin, INPUT);
  attachInterrupt(0, Flow, RISING);
  sei();
  currentTime=millis();
  cloopTime=currentTime;
  // Scale stuff
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  Serial.println("Readings:");
}

void loop() {
  // Scale Stuff
  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 1); //scale.get_units() returns a float
  Serial.print(" lbs"); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.println();
  //Flowrate stuff
  currentTime = millis();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {
      cloopTime = currentTime; // Updates cloopTime
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      l_hour = (count * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      count = 0; // Reset Counter
      Serial.print(l_hour, DEC); // Print litres/hour
      Serial.println(" L/hour");
  
  //Solenoid stuff
  digitalWrite(solPin, HIGH);
  delay(5000);
  digitalWrite(solPin, LOW);
  delay(1000);
  
  }}

