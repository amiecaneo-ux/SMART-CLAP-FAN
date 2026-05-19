// SMART CLAP FAN CONTROL

// sound sensor ini
int soundPin = A0;

// motor Pins
int IN1 = 3;
int IN2 = 4;
int ENA = 5;

// LED Pins
int greenLED = 6;
int yellowLED = 7;
int redLED = 8;

// speed Level
int speedLevel = 1;

// SOUND

// sensitivity nya sagin
int threshold = 300;

// para ma-prevent yung multiple detections
bool clapLock = false;

// basta time tracking daa ini
unsigned long lastClapTime = 0;

// basta delay ini for between valid claps
unsigned long clapDelay = 800;

void applySpeed();

void setup() {
  // motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  // LED pins
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  // motor direction
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // ma-start ang speed nya sa level 1
  applySpeed();
}

void loop() {
  // tig-read nya yung sound sensor
  int soundValue = analogRead(soundPin);

  // nag de-detect kang clap
  if (soundValue > threshold &&
      !clapLock &&
      millis() - lastClapTime > clapDelay) {

    clapLock = true;
    lastClapTime = millis();

    // change speed
    speedLevel++;

    // mabalik sya sa speed 1 after kang speed 3
    if (speedLevel > 3) {
      speedLevel = 1;
    }

    applySpeed();
    delay(200);
  }

  // reset clap lock
  if (soundValue < threshold - 20) {
    clapLock = false;
  }
}

// APPLY MOTOR SPEED

void applySpeed() {

  // turn OFF muna ang LEDs bago mag start
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);

  // SPEED 1
  if (speedLevel == 1) {

    analogWrite(ENA, 85);
    digitalWrite(greenLED, HIGH);
  }

  // SPEED 2
  else if (speedLevel == 2) {

    analogWrite(ENA, 170);
    digitalWrite(yellowLED, HIGH);
  }

  // SPEED 3
  else if (speedLevel == 3) {

    analogWrite(ENA, 255);
    digitalWrite(redLED, HIGH);
  }
}