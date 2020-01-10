#define DRONE_ID 1

int MQ2 = A0;
int MQ4 = A1;
int MQ5 = A2;
int MQ6 = A3;
int MQ7 = A4;
int MQ8 = A5;
int MQ9 = A6;
int MQ135 = A7;

void setup() {
  pinMode(MQ2, INPUT);
  pinMode(MQ4, INPUT);
  pinMode(MQ5, INPUT);
  pinMode(MQ6, INPUT);
  pinMode(MQ7, INPUT);
  pinMode(MQ8, INPUT);
  pinMode(MQ9, INPUT);
  pinMode(MQ135, INPUT);
  Serial.begin(115200);
  Serial3.begin(9600);
}

void loop() {
  float GAS_MQ2 = analogRead(MQ2);
  float GAS_MQ4 = analogRead(MQ4);
  float GAS_MQ5 = analogRead(MQ5);
  float GAS_MQ6 = analogRead(MQ6);
  float GAS_MQ7 = analogRead(MQ7);
  float GAS_MQ8 = analogRead(MQ8);
  float GAS_MQ9 = analogRead(MQ9);
  float GAS_MQ135 = analogRead(MQ135);

  if (Serial3.available() > 0){
    String gpsData = Serial3.readStringUntil('\n');
    if (gpsData.startsWith("$GPRMC")){
      // |MQ2=100|MQ4=100|MQ5=100|MQ6=100|MQ7=100|MQ8=100|MQ9=100|MQ135=100
      String data = String(DRONE_ID) + "|" + gpsData + "|" + "MQ2=" + String(GAS_MQ2) + "|" + "MQ4=" + String(GAS_MQ4) + "|" + "MQ5=" + String(GAS_MQ5) + "|" + "MQ6=" + String(GAS_MQ6) + "|" + "MQ7=" + String(GAS_MQ7) + "|" + "MQ8=" + String(GAS_MQ8) + "|" + "MQ9=" + String(GAS_MQ9) + "|" + "MQ135=" + String(GAS_MQ135);
      // Serial.print("MQ2: ");
      // Serial.println(GAS_MQ2);
      // Serial.print("MQ4: ");
      // Serial.println(GAS_MQ4);
      // Serial.print("MQ5: ");
      // Serial.println(GAS_MQ5);
      // Serial.print("MQ6: ");
      // Serial.println(GAS_MQ6);
      // Serial.print("MQ7: ");
      // Serial.println(GAS_MQ7);
      // Serial.print("MQ8: ");
      // Serial.println(GAS_MQ8);
      // Serial.print("MQ9: ");
      // Serial.println(GAS_MQ9);
      // Serial.print("MQ135: ");
      // Serial.println(GAS_MQ135);
      // Serial.println("\n");
      Serial.println(data);
    }
  }
}
