#include<SoftwareSerial.h>
SoftwareSerial BT(0, 1);
#define buzzer 9
#define flm 6
#define gas_sensor A0
#define pump 8
#define ENA 3
#define IN1 4
#define IN2 5
#define ENB 10
#define IN3 11
#define IN4 12

void motorControl1(int speedA, int in1, int in2) {
  analogWrite(ENA, speedA);  // Set the motor speed
  digitalWrite(IN1, in1);  // Set the motor direction
  digitalWrite(IN2, in2);  // Set the motor direction
}
void motorControl2(int speedA, int in1, int in2) {
  analogWrite(ENB, speedA);  // Set the motor speed
  digitalWrite(IN3, in1);  // Set the motor direction
  digitalWrite(IN4, in2);  // Set the motor direction
}
void setup() {
  BT.begin(9600);
  pinMode(flm, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}
void loop() {
  int flame = digitalRead(flm);
  unsigned int sensorValue = analogRead(gas_sensor);  // Read the analog value from sensor
  unsigned int gas = map(sensorValue, 0, 1023, 0, 255);
  delay(1000);
  if (flame == 0) {
    BT.print("Fire! Take Action.");
    BT.print(",");
    motorControl2(120, HIGH, LOW);
    motorControl1(120, HIGH, LOW);
    delay(200);
    motorControl2(0, LOW, LOW);
    motorControl1(0, LOW, LOW);
    delay(200);

    digitalWrite(pump, LOW);

    delay(5000);
    

  }
  else {
    BT.print("It's Safe Here!");
    BT.print(",");
    digitalWrite(pump, HIGH);
  }
  if (gas >= 55) {
    digitalWrite(buzzer, HIGH);
  }
  else {
    digitalWrite(buzzer, LOW);
  }
  BT.print(gas);
  BT.print(";");
}
