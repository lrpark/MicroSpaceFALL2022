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
  Serial.begin(115200);

  ///////// PROPULSION SUBSYSTEM  ////////
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
  // Serial.println("Readings:");
/////////////////////////////////////////


}
void loop() {
  
  // Read in all sensor measurements
  readSensors();

  // Send sensor measurements to Raspberri Pi
  sendMeasurementsToPi();

  // Receive serial commands from Raspberri Pi
  receiveCommandsFromPi();

  // Send commands to actuators connected to Arduino
  sendActuatorCommands();

}


void readSensors() {

  ////////// Sensor reading code ////////////


  ////////// PROPULSION MASS MEASUREMENTS //////////

  float mass = scale.get_units()










 /////////////////////////////////////////////

  Serial.print("Sensor measurement read by Arduino\n");
  delay(100); // Read at 10 Hz

}

void sendActuatorCommands() {

 ////////// Actuator command code ////////////

 ///////// PROPULSION SOLENOID ACTUATION //////

  //Solenoid stuff
  digitalWrite(solPin, HIGH);
  delay(5000);
  digitalWrite(solPin, LOW);
  delay(1000);


 //////////////////////////////////////////////


 /////////////////////////////////////////////


  Serial.print("Arudino sent actuator command\n");
  delay(100); // Send at 10 Hz
}

void sendMeasurementsToPi() {
  Serial.println("Measurement from Arduino\n");
  delay(50);
}


void receiveCommandsFromPi() {

 if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    Serial.print("You sent me: ");
    Serial.println(data);
  }
}

