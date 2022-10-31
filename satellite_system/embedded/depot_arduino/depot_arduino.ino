void setup() {
  Serial.begin(115200);
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


 /////////////////////////////////////////////

  Serial.print("Sensor measurement read by Arduino\n");
  delay(100); // Read at 10 Hz

}

void sendActuatorCommands() {

 ////////// Actuator command code ////////////


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

