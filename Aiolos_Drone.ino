// Import LoRa Module Library
#include "RYLR896.h"

// Drone ID, for future use when using with multiple drones
#define DRONE_ID 1

int MQ2 = A0;
int MQ4 = A1;
int MQ5 = A2;
int MQ6 = A3;
int MQ7 = A4;
int MQ8 = A5;
int MQ9 = A6;
int MQ135 = A7;

// Define Serial interfaces for GPS and LoRa (easier configuration)
#define GPS_SERIAL Serial1
#define LORA_SERIAL Serial3

// Create global LoRa library object
RYLR896* lora;

void setup() {
  // Initialize Serial0 for debug messages
  Serial.begin(115200);
  Serial.println("Starting up...");
  // Set sensor pin modes
  pinMode(MQ2, INPUT);
  pinMode(MQ4, INPUT);
  pinMode(MQ5, INPUT);
  pinMode(MQ6, INPUT);
  pinMode(MQ7, INPUT);
  pinMode(MQ8, INPUT);
  pinMode(MQ9, INPUT);
  pinMode(MQ135, INPUT);
  Serial.println("Initializing communications...");
  // Initialize LoRa's serial interface outside the library because of
  // weird HardwareSerial.h behavior when called within another library.
  Serial3.begin(115200);
  // Initialize LoRa Library
  lora = new RYLR896(&LORA_SERIAL, 115200);
  // Set RF Parameters for close range message transmission 
  // (see: page 2, http://reyax.com/wp-content/uploads/2018/01/REYAX-Lora-AT-COMMAND-GUIDE_EN.pdf)
  lora->SetRFParamsLessThan3KM();
  // Set AES encryption passcode
  lora->SetAESPassword("FABC0002EEDCAA90FABC0002EEDCAA90");
  Serial.println("Initializing GPS...");
  // Initialize GPS' serial interface
  GPS_SERIAL.begin(9600);
  Serial.println("Setup completed!");
}

void loop() {
  // Read sensor values
  float GAS_MQ2 = analogRead(MQ2);
  float GAS_MQ4 = analogRead(MQ4);
  float GAS_MQ5 = analogRead(MQ5);
  float GAS_MQ6 = analogRead(MQ6);
  float GAS_MQ7 = analogRead(MQ7);
  float GAS_MQ8 = analogRead(MQ8);
  float GAS_MQ9 = analogRead(MQ9);
  float GAS_MQ135 = analogRead(MQ135);

  // Once we have available GPS data
  if (GPS_SERIAL.available() > 0){
    // Store NMEA sentence
    String gpsData = GPS_SERIAL.readStringUntil('\n');
    // Since we are only keeping GPRMC NMEA sentences, only enter
    // if we are on that sentence (see http://aprs.gids.nl/nmea/#rmc)
    if (gpsData.startsWith("$GPRMC")){
      // Construct message to send over LoRa
      String data = String(DRONE_ID) + "|" + gpsData + "|" + "MQ2=" + String(GAS_MQ2) + "|" + "MQ4=" + String(GAS_MQ4) + "|" + "MQ5=" + String(GAS_MQ5) + "|" + "MQ6=" + String(GAS_MQ6) + "|" + "MQ7=" + String(GAS_MQ7) + "|" + "MQ8=" + String(GAS_MQ8) + "|" + "MQ9=" + String(GAS_MQ9) + "|" + "MQ135=" + String(GAS_MQ135);
      // Print a debug message on Serial0 with the data we are about to send
      Serial.println(data);
      // Transmit message over LoRa
      lora->Send(data);
    }
  }
}
