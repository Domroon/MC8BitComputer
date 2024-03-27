#define LED 4


void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED, OUTPUT);
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(LED, LOW);
    delay(200);
}
