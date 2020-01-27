const int buttonPin = 2;
const int ledPin =  4;

int buttonState = 0;
int buttonStateNew;
int buttonStateOld = 0;
int buttonSafeDelay = 100;

int ledState = 0;

unsigned long startMillis;
unsigned long currentMillis;
unsigned long timeDiff;
const unsigned long ledTimer = 5000; //5 secunde

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  startMillis = millis();
}

void loop() {

  buttonStateNew = digitalRead(buttonPin);

  currentMillis = millis();
  timeDiff = currentMillis - startMillis;

  if (timeDiff >= ledTimer && ledState == 1)
  {
    powerOffLed();
  }

  if (buttonStateOld == 0 && buttonStateNew == 1) {
    startMillis = currentMillis;

    if (ledState == 0) {
      powerOnLed();
    } else {
      powerOffLed();
    }

  }
  buttonStateOld = buttonStateNew;
  delay(buttonSafeDelay);
}

void powerOffLed()
{
  digitalWrite(ledPin, LOW);
  ledState = 0;
}

void powerOnLed()
{
  digitalWrite(ledPin, HIGH);
  ledState = 1;
}
