// #include "HX711.h"

// #define calibration_factor 165000.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

// #define LOADCELL_DOUT_PIN  4
// #define LOADCELL_SCK_PIN  3
// #define fsrpin A0
// int solPin = 4;
// int flowPin=2;
// double flowRate;
// volatile int count;

// int l_hour;
// unsigned long currentTime;
// unsigned long cloopTime;

// String serial_in;

// HX711 scale;

//   void Flow()
//   {
//     count++;
//   }

#include <Wire.h>
#include <Adafruit_LIS3MDL.h>
#include <Adafruit_Sensor.h>

Adafruit_LIS3MDL lis3mdl;
#define LIS3MDL_CLK 13
#define LIS3MDL_MISO 12
#define LIS3MDL_MOSI 11
#define LIS3MDL_CS 10

double client_mag_meas_X;
double client_mag_meas_Y;
double client_mag_meas_Z;


void setup() {
  Serial.begin(115200);

  ///////// PROPULSION SUBSYSTEM  ////////
  // //Solenoid pin
  // pinMode(solPin, OUTPUT);
  // //Flowrate setup
  // pinMode(flowPin, INPUT);
  // attachInterrupt(0, Flow, RISING);
  // sei();
  // currentTime=millis();
  // cloopTime=currentTime;
  // // Scale stuff
  // scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  // scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  // scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  // // Serial.println("Readings:");
/////////////////////////////////////////

//////////////// MAG SETUP ///////////////////////////
  magnetometerSetup();
///////////////////////////////////////////////////

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

    lis3mdl.read();      // get X Y and Z data at once
    // Then print out the raw data
    // Serial.print("\nX:  "); Serial.print(lis3mdl.x); 
    // Serial.print("  \tY:  "); Serial.print(lis3mdl.y); 
    // Serial.print("  \tZ:  "); Serial.println(lis3mdl.z); 

    /* Or....get a new sensor event, normalized to uTesla */
    sensors_event_t event; 
    lis3mdl.getEvent(&event);

    client_mag_meas_X = (event.magnetic.x);
    client_mag_meas_Y = (event.magnetic.y);
    client_mag_meas_Z = (event.magnetic.z);

    /* Display the results (magnetic field is measured in uTesla) */
    // Serial.print("\tX: "); Serial.print(event.magnetic.x);
    // Serial.print(" \tY: "); Serial.print(event.magnetic.y); 
    // Serial.print(" \tZ: "); Serial.print(event.magnetic.z); 
    // Serial.println(" uTesla ");

    delay(100); 
    // Serial.println();


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
  
  String serial_data = "1," + String(client_mag_meas_X) + "," + String(client_mag_meas_Y) + "," + String(client_mag_meas_Z);
  Serial.println(serial_data);
  

  double depot_mag_meas_X = 0.03;
  double depot_mag_meas_Y = 0.05;
  double depot_mag_meas_Z = 0.07;

  serial_data = "2," + String(depot_mag_meas_X) + "," + String(depot_mag_meas_X) + "," + String(depot_mag_meas_X);
  Serial.println(serial_data);
  



  //////////////////////////////////////////////////

  //////////// PROPULSION SUBSYSTEM ////////////////

  // 11 = client scale mass
  // 12 = depot scale mass





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



void magnetometerSetup() {

  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens

    Serial.println("Adafruit LIS3MDL test!");
    
    // Try to initialize!
    // if (! lis3mdl.begin_I2C()) {          // hardware I2C mode, can pass in address & alt Wire
    if (! lis3mdl.begin_SPI(LIS3MDL_CS)) {  // hardware SPI mode
    //if (! lis3mdl.begin_SPI(LIS3MDL_CS, LIS3MDL_CLK, LIS3MDL_MISO, LIS3MDL_MOSI)) { // soft SPI
      Serial.println("Failed to find LIS3MDL chip");
      while (1) { delay(10); }
    }
    Serial.println("LIS3MDL Found!");

    lis3mdl.setPerformanceMode(LIS3MDL_MEDIUMMODE);
    Serial.print("Performance mode set to: ");
    switch (lis3mdl.getPerformanceMode()) {
      case LIS3MDL_LOWPOWERMODE: Serial.println("Low"); break;
      case LIS3MDL_MEDIUMMODE: Serial.println("Medium"); break;
      case LIS3MDL_HIGHMODE: Serial.println("High"); break;
      case LIS3MDL_ULTRAHIGHMODE: Serial.println("Ultra-High"); break;
    }

    lis3mdl.setOperationMode(LIS3MDL_CONTINUOUSMODE);
    Serial.print("Operation mode set to: ");
    // Single shot mode will complete conversion and go into power down
    switch (lis3mdl.getOperationMode()) {
      case LIS3MDL_CONTINUOUSMODE: Serial.println("Continuous"); break;
      case LIS3MDL_SINGLEMODE: Serial.println("Single mode"); break;
      case LIS3MDL_POWERDOWNMODE: Serial.println("Power-down"); break;
    }

    lis3mdl.setDataRate(LIS3MDL_DATARATE_155_HZ);
    // You can check the datarate by looking at the frequency of the DRDY pin
    Serial.print("Data rate set to: ");
    switch (lis3mdl.getDataRate()) {
      case LIS3MDL_DATARATE_0_625_HZ: Serial.println("0.625 Hz"); break;
      case LIS3MDL_DATARATE_1_25_HZ: Serial.println("1.25 Hz"); break;
      case LIS3MDL_DATARATE_2_5_HZ: Serial.println("2.5 Hz"); break;
      case LIS3MDL_DATARATE_5_HZ: Serial.println("5 Hz"); break;
      case LIS3MDL_DATARATE_10_HZ: Serial.println("10 Hz"); break;
      case LIS3MDL_DATARATE_20_HZ: Serial.println("20 Hz"); break;
      case LIS3MDL_DATARATE_40_HZ: Serial.println("40 Hz"); break;
      case LIS3MDL_DATARATE_80_HZ: Serial.println("80 Hz"); break;
      case LIS3MDL_DATARATE_155_HZ: Serial.println("155 Hz"); break;
      case LIS3MDL_DATARATE_300_HZ: Serial.println("300 Hz"); break;
      case LIS3MDL_DATARATE_560_HZ: Serial.println("560 Hz"); break;
      case LIS3MDL_DATARATE_1000_HZ: Serial.println("1000 Hz"); break;
    }
    
    lis3mdl.setRange(LIS3MDL_RANGE_4_GAUSS);
    Serial.print("Range set to: ");
    switch (lis3mdl.getRange()) {
      case LIS3MDL_RANGE_4_GAUSS: Serial.println("+-4 gauss"); break;
      case LIS3MDL_RANGE_8_GAUSS: Serial.println("+-8 gauss"); break;
      case LIS3MDL_RANGE_12_GAUSS: Serial.println("+-12 gauss"); break;
      case LIS3MDL_RANGE_16_GAUSS: Serial.println("+-16 gauss"); break;
    }

    lis3mdl.setIntThreshold(500);
    lis3mdl.configInterrupt(false, false, true, // enable z axis
                            true, // polarity
                            false, // don't latch
                            true); // enabled!


}




