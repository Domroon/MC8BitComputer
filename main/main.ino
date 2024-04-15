#define LED             4
#define START_STOP_BTN  3
#define STEP_BTN        A5

// Encoder
#define CLK             6
#define DT              5
int pos = 0;
int pos_before = 0;
int diff = 0;
int period_dura_ms = 500;
int frequency_hz = 1;
int frequency_max_hz = 50;
int frequency_min_hz = 4;
int frequency_step = 1;

// Clock LED
bool clock = false;
bool led_state = LOW;
bool ledbuiltin_state = LOW;

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

Timer ledTimer(period_dura_ms);
Timer serialTimer(1000);
Timer LED_buildin_timer(500);

void setup() {
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    pinMode(START_STOP_BTN, INPUT);
    pinMode(STEP_BTN, INPUT);
    attachInterrupt(digitalPinToInterrupt(START_STOP_BTN), stop_loop, RISING);
}

void loop() {
    change_led_builtin_state();
    // sendSerialInfo();
    check_step_btn();
    set_led_state();
    change_clk_frequency();
}

void check_step_btn(){
    while(digitalRead(STEP_BTN)){
        clock = false;
        digitalWrite(LED, HIGH);
        delay(100);
    }
    
    if(!digitalRead(STEP_BTN) && !clock){
        digitalWrite(LED, LOW);
    }
}

void set_led_state(){
  if(ledTimer.checkTimeOver() && clock){
    led_state = !led_state;
    digitalWrite(LED, led_state);
    ledTimer.restart();
  }
}

int convertGrayToBinary(){
  bool clk = digitalRead(CLK);
  bool dt = digitalRead(DT);
  if(dt == 0 && clk == 0){
    return 0;
  } else if(dt == 0 && clk == 1){
    return 1;
  } else if(dt == 1 && clk == 1){
    return 2;
  } else {
    return 3;
  }
}

float change_clk_frequency(){
  pos = convertGrayToBinary();

  // calculate the difference to previous position
  diff = pos_before - pos;

  // turned clockwise
  if (((diff == -1) || (diff == 3))) {
    pos_before = pos;
    if (frequency_hz*1000 <= frequency_max_hz*1000) {
      frequency_hz = frequency_hz + frequency_step; 
      period_dura_ms = calc_period_duration_in_ms(frequency_hz);
      ledTimer.changeDuration(period_dura_ms);
    }
            
  // turned counter-clockwise
  } else if (((diff == 1) || (diff == -3))) {
      pos_before = pos;
      if (frequency_hz*1000 > frequency_min_hz*1000){ 
        frequency_hz = frequency_hz - frequency_step; 
        period_dura_ms = calc_period_duration_in_ms(frequency_hz);
        ledTimer.changeDuration(period_dura_ms);
      }
        
  // in this case, an step has been missed
  // (best practice: ignore it!)
  } else if ((diff == 2) || (diff == -2)) {

  }
}

float calc_period_duration_in_ms(int frequency){
  float period_duration = (1/float(frequency)) * 1000;
  return period_duration;
}

void sendSerialInfo(){
  if(serialTimer.checkTimeOver() && clock){
    Serial.print("Frequency: ");
    Serial.print(frequency_hz);
    Serial.println(" Hz");

    Serial.print("Period-Duration: ");
    Serial.print(period_dura_ms);
    Serial.println(" ms");
    serialTimer.restart();
  }
}

void change_led_builtin_state(){
    if(LED_buildin_timer.checkTimeOver()){
        ledbuiltin_state = !ledbuiltin_state;
        digitalWrite(LED_BUILTIN, ledbuiltin_state);
        LED_buildin_timer.restart();
    }
}

// ISR
void stop_loop() {
    uint16_t wait_ms = 1000;
    clock = !clock;
    delayMicroseconds(wait_ms * 1000);
}