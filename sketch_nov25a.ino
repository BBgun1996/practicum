#define buzzerPin PIN_PC0
#define buttonPin PIN_PB0
#define vibrationPin PIN_PC1
#define gasPin PIN_PC4

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
    
//    if(buttonState == LOW) {
//        if(buttonNextState == HIGH) {
//             buttonState = HIGH;
//        }
//    } else if(buttonState == HIGH) {
//      if(buttonNextState == LOW) {
//             buttonState = LOW;
//             buzzerState = !buzzerState;
//      }
//    }

    if(buttonState != buttonNextState) {
        buttonState = buttonNextState;
        if(buttonState == LOW) {
          buzzerState = !buzzerState;
        }
    }
}
    
void vibration() {
    vibrationState = analogRead(vibrationPin);
    
    if(vibrationState > 1000) {
        buzzerState = true;
    }
}

void gas() {
    gasState = digitalRead(gasPin);

    if(gasState == HIGH) {
        //buzzerState = false;
    }
}

