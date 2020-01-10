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

  if (Serial.available()>0) {
    int x=Serial.read();
    if (x=='1') {
      Serial.print("MQ2: ");
      Serial.println(GAS_MQ2);
      Serial.print("MQ4: ");
      Serial.println(GAS_MQ4);
      Serial.print("MQ5: ");
      Serial.println(GAS_MQ5);
      Serial.print("MQ6: ");
      Serial.println(GAS_MQ6);
      Serial.print("MQ7: ");
      Serial.println(GAS_MQ7);
      Serial.print("MQ8: ");
      Serial.println(GAS_MQ8);
      Serial.print("MQ9: ");
      Serial.println(GAS_MQ9);
      Serial.print("MQ135: ");
      Serial.println(GAS_MQ135);
      Serial.println("\n");
    }
  }

  if (Serial3.available() > 0){
    String gpsData = Serial3.readStringUntil('\n');
    if (gpsData.startsWith("$GPRMC")){
      Serial.println(gpsData);
    }
  }
}
