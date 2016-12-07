#include<usbdrv.h>

#define buzzerPin     PIN_PC0
#define buttonPin     PIN_PC1
#define vibrationPin  PIN_PC4
#define gasPin        PIN_PC3

#define RQ_SET_BUZZER      0
#define RQ_GET_BUZZER      1
#define RQ_GET_VIBRATION   2
#define RQ_GET_GAS         3

boolean buzzerState = false;
boolean vibrationWarning = false;
boolean gasWarning = false;

int buttonState = HIGH;
int buttonNextState = HIGH;
int vibrationState = 0;
int gasState = 0;

/* ------------------------------------------------------------------------- */
/* ----------------------------- USB interface ----------------------------- */
/* ------------------------------------------------------------------------- */
usbMsgLen_t usbFunctionSetup(uint8_t data[8]) {
    usbRequest_t *rq = (void *)data;

    /* declared as static so they stay valid when usbFunctionSetup returns */
    static uint8_t buzzer_state;
    static uint8_t vibration_state;
    static uint8_t gas_state;  

    if (rq->bRequest == RQ_GET_BUZZER)
    {
        buzzer_state = buzzerState;
        
        /* point usbMsgPtr to the data to be returned to host */
        usbMsgPtr = &buzzer_state;

        /* return the number of bytes of data to be returned to host */
        return 1;
    } else if (rq->bRequest == RQ_GET_VIBRATION)
    {
        vibration_state = vibrationWarning;
        usbMsgPtr = &vibration_state;

        /* return the number of bytes of data to be returned to host */
        return 1;
    } else if (rq->bRequest == RQ_GET_GAS)
    {
        vibration_state = gasWarning;
        usbMsgPtr = &gas_state;

        /* return the number of bytes of data to be returned to host */
        return 1;
    }

    /* default for not implemented requests: return no data back to host */
    return 0;
}

void setup() {
    pinMode(buzzerPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(vibrationPin, INPUT);
    pinMode(gasPin, INPUT);

    usbInit();


    /* enforce re-enumeration, do this while interrupts are disabled! */
    usbDeviceDisconnect();
    _delay_ms(300);
    usbDeviceConnect();

    /* enable global interrupts */
    sei();

     Serial.begin(9600);
}

void loop() {
    usbPoll();
    button();
    buzzer();
    vibration();
    gas();
}

void buzzer() {
    if(buzzerState == false) {
        digitalWrite(buzzerPin, LOW);
        buzzerState = false;
        vibrationWarning = false;
        gasWarning = false;
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
//    Serial.println(vibrationState);
    
    if(vibrationState > 280) {
        buzzerState = true;
        vibrationWarning = true;
    }
}

void gas() {
    gasState = analogRead(gasPin);
    Serial.println(gasState);
    if(gasState > 1000) {
        buzzerState = true;
        gasWarning = true;
    }
}
