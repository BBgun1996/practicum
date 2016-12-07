#define buzzerPin PIN_PC0
#define buttonPin PIN_PC1
#define vibrationPin PIN_PC4
#define gasPin PIN_PC3

boolean buzzerState = false;

int buttonState = HIGH;
int buttonNextState = HIGH;
int vibrationState = 0;
int gasState = 0;

void setup() {
    pinMode(buzzerPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(vibrationPin, INPUT);
    pinMode(gasPin, INPUT);
}
 
void loop() {
    button();
    buzzer();
    vibration();
    gas();
}

void buzzer() {
    if(buzzerState == false) {
        digitalWrite(buzzerPin, LOW);
    } else {
        digitalWrite(buzzerPin, HIGH);
    }    
}

void button() {
    buttonNextState = digitalRead(buttonPin);
    //buttonState == LOW = กดswitch 

    if(buttonState != buttonNextState) {
        if(buttonState == HIGH) {
          buzzerState = !buzzerState;
        }
        buttonState = buttonNextState;
    }
}
    
void vibration() {
    vibrationState = analogRead(vibrationPin);
    
    if(vibrationState > 280) {
        buzzerState = true;
    }
}

void gas() {
    gasState = analogRead(gasPin);

    if(gasState > 1000) {
        buzzerState = true;
    }
}

