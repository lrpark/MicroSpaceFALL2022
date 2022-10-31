String serial_in;

// Global temp variables

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
  // Serial.println("Measurement from Arduino\n");

  
  /////////// ALIGNMENT SUBSYSTEM ///////////////////

  // 1 = client magnetometer
  // 2 = depot magnetometer

  double client_mag_meas_X = 0.02;
  double client_mag_meas_Y = 0.04;
  double client_mag_meas_Z = 0.06;
  
  String serial_data = "1," + String(client_mag_meas_X) + "," + String(client_mag_meas_Y) + "," + String(client_mag_meas_Z);
  Serial.println(serial_data);
  
  
  double depot_mag_meas_X = 0.03;
  double depot_mag_meas_Y = 0.05;
  double depot_mag_meas_Z = 0.07;

  serial_data = "1," + String(depot_mag_meas_X) + "," + String(depot_mag_meas_X) + "," + String(depot_mag_meas_X);
  Serial.println(serial_data);
  



  //////////////////////////////////////////////////

  //////////// PROPULSION SUBSYSTEM ////////////////





  /////////////////////////////////////////////////



  delay(50);
}


void receiveCommandsFromPi() {

 if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    Serial.print("You sent me: ");
    Serial.println(data);
  }
}

