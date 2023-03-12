uint32_t click_number;
long start_timestamp;

void setup() {
    Serial.begin(115200);
    initializee();
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(180000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);

    uint16_t vCPM = collectCPM();
    Serial.print("CPM: ");
    Serial.println(vCPM);
    Serial.print("nSvh: ");
    Serial.println(tonSvh(vCPM));
}


void click_registration() {
    click_number++;
}

void initializee() {
    pinMode(D2, INPUT);
    click_number = 0;
    attachInterrupt(digitalPinToInterrupt(D2), click_registration, FALLING);
    start_timestamp = millis();
}


uint16_t collectCPM() {
    float CPM;
    uint32_t delta_time;
    long current_timestamp = millis();
    uint32_t current_click_number = click_number;
    click_number = 0;
    delta_time = current_timestamp - start_timestamp;
    start_timestamp = current_timestamp;
    CPM = ((60000)/float(delta_time-1)) * current_click_number;
   
    return (uint16_t) CPM;
}

uint16_t tonSvh(uint16_t CPMi) {
    return (float(CPMi / 153.8)) * 1000;
}
