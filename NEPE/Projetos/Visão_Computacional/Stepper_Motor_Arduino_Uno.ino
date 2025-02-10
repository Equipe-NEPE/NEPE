#define DIR 2
#define PUL 3
#define MAG1 4
#define MAG2 5
#define LED 6
#define BOT 7
#define PIN1 8
#define PIN2 9
#define PIN3 10
float time;

void setup() {
  Serial.begin(115200);
  pinMode(DIR, OUTPUT);
  pinMode(PUL, OUTPUT);
  pinMode(MAG1, OUTPUT);
  pinMode(MAG2, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(BOT, INPUT_PULLUP);
  pinMode(PIN1, INPUT);
  pinMode(PIN2, INPUT);
  pinMode(PIN3, INPUT);
  digitalWrite(MAG1, LOW);
}

void loop() {
  time = 12;
  digitalWrite(MAG2, HIGH);
  int pin1State = digitalRead(PIN1);
  int pin2State = digitalRead(PIN2);
  int pin3State = digitalRead(PIN3);
  delay(5000);

  if (pin1State == LOW && pin2State == HIGH && pin3State == LOW) {
    digitalWrite(MAG2, LOW);
    parafuso();
    delay(1000);
  } 
  else if (pin1State == HIGH && pin2State == HIGH && pin3State == HIGH) {
    digitalWrite(MAG2, LOW);
    arruela();
    delay(1000);
  } 
  else if (pin1State == HIGH && pin2State == LOW && pin3State == HIGH) {
    digitalWrite(MAG2, LOW);
    porca();
    delay(1000);
  }
  else if (pin1State == LOW && pin2State == LOW && pin3State == LOW) {
    return 0;
  }
}

void parafuso() {
  digitalWrite(DIR, HIGH);

  for (float i = 0; i <= 105; i += 1) {
    digitalWrite(PUL, HIGH);
    delay(time);
    digitalWrite(PUL, LOW);
    delay(time);
    if (i >= 80){
      time = 35;
    }
  }

  delay(500);
  digitalWrite(MAG1, HIGH);
  delay(500);
  digitalWrite(DIR, HIGH);
  time = 10;

  for (float i = 0; i <= 25; i += 1) {
    digitalWrite(PUL, HIGH);
    delay(time);
    digitalWrite(PUL, LOW);
    delay(time);
  }

  delay(500);
  digitalWrite(MAG1, LOW);
  delay(500);
  digitalWrite(DIR, LOW);

  for (float i = 0; i <= 105 + 25; i += 1) {
    digitalWrite(PUL, HIGH);
    delay(time);
    digitalWrite(PUL, LOW);
    delay(time);
  }
}

void arruela() {
  digitalWrite(DIR, HIGH);
  for (float i = 0; i <= 100; i += 1) {
    digitalWrite(PUL, HIGH);
    delay(time);
    digitalWrite(PUL, LOW);
    delay(time);
  }
  delay(500);
  digitalWrite(MAG1, HIGH);
  delay(500);
  digitalWrite(DIR, HIGH);
  for (float i = 0; i <= 70; i += 1) {
    digitalWrite(PUL, HIGH);
    delay(time);
    digitalWrite(PUL, LOW);
    delay(time);
  }
  delay(500);
  digitalWrite(MAG1, LOW);
  delay(500);
  digitalWrite(DIR, LOW);
  for (float i = 0; i <= 100 + 70; i += 1) {
    digitalWrite(PUL, HIGH);
    delay(time);
    digitalWrite(PUL, LOW);
    delay(time);
  }
}

void porca() {
  digitalWrite(DIR, HIGH);
  for (float i = 0; i <= 100; i += 1) {
    digitalWrite(PUL, HIGH);
    delay(time);
    digitalWrite(PUL, LOW);
    delay(time);
  }
  delay(500);
  digitalWrite(MAG1, HIGH);
  delay(500);
  digitalWrite(DIR, HIGH);
  for (float i = 0; i <= 50; i += 1) {
    digitalWrite(PUL, HIGH);
    delay(time);
    digitalWrite(PUL, LOW);
    delay(time);
  }
  delay(500);
  digitalWrite(MAG1, LOW);
  delay(500);
  digitalWrite(DIR, LOW);
  for (float i = 0; i <= 100 + 50; i += 1) {
    digitalWrite(PUL, HIGH);
    delay(time);
    digitalWrite(PUL, LOW);
    delay(time);
  }
}