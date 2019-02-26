/* pin variables */
#define PIN_BUTTON 9
#define PIN_LED_BLUE 10
#define PIN_LED_GREEN 11
#define PIN_LED_RED 12

/* debouce variables */
uint32_t TIMEOUT_DEPRESS = 100;

/* state variables */
/* default initial state to off */
uint8_t state = 0;

/* alert variables */
uint32_t timestampLastBlinked = 0;
boolean isAlertOn = false;
boolean isTimerCritical = false;
#define TIMEOUT_BLINK 1000
#define TIMEOUT_BLINK_FAST 500

/* timer variables */
#define TIMEOUT_TIMER 3600000
#define TIMER_THRESHOLD 300000
uint32_t timestampTimerStarted = 0;

void setup() {
  /* init pins */
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);

  /* init the LED to off */
  ledOff();
}

void loop() {
  /* handle the current state */
  handleState();

  /* return right-away if the button isn't pressed */
  if (buttonState() == LOW) {
    return;
  }

  /* if the button is pressed..*/
  uint32_t timestampPressStarted = millis();

  while (buttonState() == HIGH) {
    /* count time while button is held */
  }

  /* check if the press was not held long enough */
  if (millis() - timestampPressStarted < TIMEOUT_DEPRESS) {
    return;
  }

  /* button was pressed, reset timer */
  resetTimer();
}

/* handle timer state */
void handleState() {
  switch (state) {
    case 0: /* timer is off */
      actionOff();
      break;

    case 1: /* timer is running */
      actionRunTimer();
      break;

    case 2: /* timer is alerting */
      actionAlert();
      break;
  }
}

boolean buttonState() {
  return digitalRead(PIN_BUTTON);
}

void actionAlert() {
  /* check if the bink timeout has passed */
  if (millis() - timestampLastBlinked >= TIMEOUT_BLINK) {
    /* toggle the alert */
    isAlertOn = !isAlertOn;

    /* reset the timestamp */
    timestampLastBlinked = millis();
  }

  if (isAlertOn == true) {
    ledRed();
  }

  if (isAlertOn == false) {
    ledOff();
  }
}

void actionOff() {
  /* turn the led off */
  ledBlue();
}

void actionRunTimer() {
  /* check if the timer has reached threshold */
  uint32_t timeRemaining = TIMEOUT_TIMER - (millis() - timestampTimerStarted);
  isTimerCritical = timeRemaining <= TIMER_THRESHOLD;


  /* check if the timer has finished */
  if (millis() - timestampTimerStarted >= TIMEOUT_TIMER) {
    /* set timer state to alerting */
    state = 2;
    return;
  }

  /* if the timer hasn't timed out..*/
  if (isTimerCritical == false) {
    ledGreen();
    return;
  }

  /* timer is critical */
  ledYellow();
}

void resetTimer() {
  /* set the state to timer running */
  state = 1;

  /* update the time started to now */
  timestampTimerStarted = millis();
}

void ledOff() {
  digitalWrite(PIN_LED_RED, HIGH);
  digitalWrite(PIN_LED_BLUE, HIGH);
  digitalWrite(PIN_LED_GREEN, HIGH);
}

void ledRed() {
  digitalWrite(PIN_LED_RED, LOW);
  digitalWrite(PIN_LED_BLUE, HIGH);
  digitalWrite(PIN_LED_GREEN, HIGH);
}

void ledGreen() {
  digitalWrite(PIN_LED_RED, HIGH);
  digitalWrite(PIN_LED_BLUE, HIGH);
  digitalWrite(PIN_LED_GREEN, LOW);
}

void ledBlue() {
  digitalWrite(PIN_LED_RED, HIGH);
  digitalWrite(PIN_LED_BLUE, LOW);
  digitalWrite(PIN_LED_GREEN, HIGH);
}

void ledYellow() {
  digitalWrite(PIN_LED_RED, LOW);
  digitalWrite(PIN_LED_BLUE, HIGH);
  digitalWrite(PIN_LED_GREEN, LOW);
}

void ledPurple() {
  digitalWrite(PIN_LED_RED, LOW);
  digitalWrite(PIN_LED_BLUE, LOW);
  digitalWrite(PIN_LED_GREEN, HIGH);
}

void ledCyan() {
  digitalWrite(PIN_LED_RED, HIGH);
  digitalWrite(PIN_LED_BLUE, LOW);
  digitalWrite(PIN_LED_GREEN, LOW);
}
