int Buzzer = 8;
int Sensor = A5;
int st = 190;


void setup() {
  // put your setup code here, to run once:
  pinMode(Buzzer, OUTPUT);
  pinMode(Sensor, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int analogSensor = analogRead(Sensor);
  Serial.print("Pin A5: ");
  Serial.println(analogSensor);
  if (analogSensor > st) {
    tone(Buzzer, 1000, 200);
  } else {
    noTone(Buzzer);
  }
  delay(100);
}