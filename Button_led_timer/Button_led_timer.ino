const int buttonPin = 2;
const int ledPin =  4;
const int event1Pin = 3;


int buttonState = 0;
int buttonStateNew;
int buttonStateOld = 0;
int buttonSafeDelay = 100;

int ledState = 0;
int event1State = 0;

unsigned long startMillis;
unsigned long currentMillis;
unsigned long timeDiff;
const unsigned long ledTimer = 5000; //10 secunde
const unsigned long event1Timer = 5000; //10 secunde
const unsigned long eventStartDelay = 5000; // porneste la 5 sec dupa ce a fost apasat butonul , pe asta il folosim daca e nevoie


void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(event1Pin, OUTPUT);

  startMillis = millis();
}

void loop() {

  buttonStateNew = digitalRead(buttonPin);

  currentMillis = millis();
  timeDiff = currentMillis - startMillis;

  if (timeDiff >= ledTimer && ledState == 1)
  {
    stopLed();
    startEvent1();
  }

  if (timeDiff >= (event1Timer + ledTimer) && event1State == 1)
  {
    stopEvent1();
  }

  if (buttonStateOld == 0 && buttonStateNew == 1) {
    startMillis = currentMillis;

    if (ledState == 0 && event1State == 0) {
      startLed();
    } else  {
      stopAll();
    }

  }

  buttonStateOld = buttonStateNew;
  delay(buttonSafeDelay);
}

void stopLed()
{
  digitalWrite(ledPin, LOW);
  ledState = 0;
}

void startLed()
{
  digitalWrite(ledPin, HIGH);
  ledState = 1;
}

void triggerEvents()
{
  int startEventTime = startMillis + eventStartDelay;
  if (ledState == 1 && currentMillis >= startEventTime) {
    startEvent1();
  }
}

void stopAll()
{
  stopLed();
  stopEvent1();
}

void startEvent1()
{
  digitalWrite(event1Pin, HIGH);
  event1State = 1;
}

void stopEvent1()
{
  digitalWrite(event1Pin, LOW);
  event1State = 0;
}
