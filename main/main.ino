#define LED             4
#define START_STOP_BTN  2
#define STEP_BTN        3

// Encoder
#define CLK             6
#define DT              5
long oldPosition = 0;

bool clock = false;

bool led_on = false;

class Timer{
  private:
    unsigned long _startMillis = 0;
    unsigned int _timerDuration;
  public:
    Timer(unsigned int duration){
      _timerDuration = duration;
    }
    void start(){ // start the timer             
      _startMillis = millis();
    }
    void restart(){ // restart the timer
      _startMillis = millis();
    }
    void changeDuration(unsigned int newTimerDuration){
        _startMillis = millis();
        _timerDuration = newTimerDuration;
    }
    unsigned int getDuration(){ // return the duration of the timer
      return _timerDuration;
    }
    bool checkTimeOver() {; // check if the timer is over and return a bool value
      if (millis() - _startMillis >= _timerDuration){
        return true;
      } else {
        return false;
      }
    }
};

Timer ledTimer(100);

void setup() {
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    pinMode(START_STOP_BTN, INPUT);
    pinMode(STEP_BTN, INPUT);
    attachInterrupt(digitalPinToInterrupt(START_STOP_BTN), stop_loop, RISING);
}

void loop() {
    if(!clock){
        led_on = false;
    }
    if(ledTimer.checkTimeOver() && clock){
        led_on = !led_on;
        ledTimer.restart();
    }
    digitalWrite(LED, led_on);

    check_step_btn();
}

void check_step_btn(){
    while(digitalRead(STEP_BTN)){
        clock = false;
        digitalWrite(LED, HIGH);
    }
    delay(100);
    if(!digitalRead(STEP_BTN)){
        digitalWrite(LED, LOW);
    }
}

// ISR
void stop_loop() {
    uint16_t wait_ms = 1000;
    clock = !clock;
    delayMicroseconds(wait_ms * 1000);
}