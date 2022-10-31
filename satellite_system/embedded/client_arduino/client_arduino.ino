String serial_in;

// Global temp variables

double client_mag_meas[] = {0.0, 0.0, 0.0};       
double depot_mag_meas[] = {0.0, 0.0, 0.0};     

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

  client_mag_meas = {0.03, 0.05, 0.07};
  for(int i = 0; i < 2; i++){
    String serial_data = "1," + String(i) + "," + String(client_mag_meas[i], 3);
    Serial.println(serial_data);
  }

  depot_mag_meas = {0.02, 0.04, 0.06};
  for(int i = 0; i < 2; i++){
    String serial_data = "2," + String(i) + "," + String(depot_mag_meas[i], 3);
    Serial.println(serial_data);
  }



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

