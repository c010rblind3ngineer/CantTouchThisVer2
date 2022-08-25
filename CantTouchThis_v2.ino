/* Arduino 'Can't Touch This' Version 2
   Components:
                - Arduino Nano
                - D1 Mini (ESP8266) module
                - ADXL335
                - Passive Buzzer
                - Push button tactile switch
                - Red LED
                - 220Ohm resistor
                - 330Ohm resistor
                - 10kOhm resistor
                - Breadboard
                - Some jumper wires

   Created on 23 August 2022 by c010blind3ngineer
*/
#define trigPin 6    // this will be the pin that triggers the D1 Mini pin D1
#define buzzerPin 9
#define LEDpin 8
#define btnPin 7

int X_axis = A0;
int Y_axis = A1;
int Z_axis = A2;
const int deg_acc = 3;
boolean trigAlarm = false;
int x, y, z;
int t = 0;

int STILL[4];

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(LEDpin, OUTPUT);
  pinMode(btnPin, INPUT);
  pinMode(trigPin, OUTPUT);
  Serial.begin(9600);
  while (digitalRead(btnPin) != HIGH) {}
}

void loop() {
  if (digitalRead(btnPin) == HIGH) {
    Serial.print("Calibrating");
    delay(500);
    int i = 0;    // reset 'i' counter
    while (i < 3) {   // read XYZ readings 3 times, it also gives the User time to stabilise the device properly
      Serial.print(".");
      STILL[0] = analogRead(X_axis);
      STILL[1] = analogRead(Y_axis);
      STILL[2] = analogRead(Z_axis);
      delay(500);
      i++;
    }
    digitalWrite(LEDpin, HIGH);
    tone(buzzerPin, 2000);
    delay(100);
    digitalWrite(LEDpin, LOW);
    noTone(buzzerPin);
    delay(100);
    digitalWrite(LEDpin, HIGH);
    tone(buzzerPin, 2000);
    delay(100);
    digitalWrite(LEDpin, LOW);
    noTone(buzzerPin);
    trigAlarm = false;
    t = 0;
    digitalWrite(trigPin, LOW);
  }
  // Read XYZ axis values
  x = analogRead(X_axis);
  y = analogRead(Y_axis);
  z = analogRead(Z_axis);

  // Check to see if the device is in the same position when the User set it initially
  if ((x > (STILL[0] - deg_acc)) && (x < (STILL[0] + deg_acc)) && (y > (STILL[1] - deg_acc)) && (y < (STILL[1] + deg_acc)) && (z > (STILL[2] - deg_acc)) && (z < (STILL[2] + deg_acc)) ) {
    // You can uncomment the lines below to see the XYZ values in the Serial Monitor
    //    Serial.print(x);
    //    Serial.print("\t");
    //    Serial.print(y);
    //    Serial.print("\t");
    //    Serial.print(z);
    //    Serial.println();
  }
  else {
    trigAlarm = true;
    while(t < 1){ // will only trigger pin 6 on the Arduino Nano once
      digitalWrite(trigPin, HIGH);  // trigger pin D1 on the D1 Mini (ESP8266) module
      t = 1;
    }
  }
  // Alarm goes off when someone moves the device out of position
  if (trigAlarm == true) {
    digitalWrite(LEDpin, HIGH);
    tone(buzzerPin, 2000);
    delay(100);
    digitalWrite(LEDpin, LOW);
    noTone(buzzerPin);
  }
  delay(100);
}
