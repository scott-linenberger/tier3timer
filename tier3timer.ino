/* pin variables */
#define PIN_BUTTON 9
#define PIN_LED_BLUE 10
#define PIN_LED_GREEN 11
#define PIN_LED_RED 12

/* timeout variables */
uint32_t TIMEOUT_PRESS = 100;
uint32_t TIMEOUT_BLINK = 1000;
uint32_t TIMEOUT_BLINK_FAST = 500;
uint32_t TIMEOUT_TIMER = 5000;
uint32_t TIMER_THRESHOLD = 2000;

/* state variable: defaulted to 'off' */
uint8_t state = 0;

void setup() {
  Serial.begin(9600);

  /* init pins */
  initPins();

  /* turn led OFF */
  ledOff();
}

void loop() {
  /* check button */
  checkButton();

  /* handle state */
  handleState();
}

void handleState() {
  switch(state) {
    /* off */
    case 0:
      Serial.println("Handling state: off");
      stateOff();
      break;

    /* timer running */
    case 1:
      stateTimerActive();
      break;
      
    default:
      break;
  }
}

void affectState() {
  switch(state) {
    /* if off */
    case 0:
      /* turn timer on */
      state = 1;
      return;

    /* if timer on */
    case 1:
      /* reset timer */
      resetTimer();
      return;
  }
}

void checkButton() {
  Serial.println(digitalRead(PIN_BUTTON));
  
  /* check if button is pressed */
  if (digitalRead(PIN_BUTTON) == LOW) {
    /* button isn't pressed */
    return;
  }

  /* button is pressed */
  uint32_t timePressStarted = millis();

  /* hold while the button is pressed */
  while(digitalRead(PIN_BUTTON) == HIGH) {}

  /* check if button pressed long enough */
  if (millis() - timePressStarted < TIMEOUT_PRESS) {
    /* button wasn't pressed long enough */
    return;
  }

  Serial.println("Button pressed!");

  /* button was pressed long enough.. */
  affectState();
}

void stateOff(){
  Serial.println("State: off");
  /* set the LED blue */
  ledBlue();
}

void stateTimerActive() {

}

void resetTimer() {

}

void ledBlue() {
  digitalWrite(PIN_LED_RED, HIGH);
  digitalWrite(PIN_LED_GREEN, HIGH);
  digitalWrite(PIN_LED_BLUE, LOW);
}

void ledPurple() {
  digitalWrite(PIN_LED_RED, LOW);
  digitalWrite(PIN_LED_GREEN, HIGH);
  digitalWrite(PIN_LED_BLUE, LOW);
}

void ledOff() {
  digitalWrite(PIN_LED_RED, HIGH);
  digitalWrite(PIN_LED_GREEN, HIGH);
  digitalWrite(PIN_LED_BLUE, HIGH);
}

void initPins() {
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);
}