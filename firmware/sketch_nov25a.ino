#include <util/delay.h>     /* for _delay_ms() */
#include <avr/pgmspace.h>   /* required by usbdrv.h */

#include "usbdrv.h"

#define buzzerPin PIN_PC0
#define buttonPin PIN_PC1
#define vibrationPin PIN_PC4
#define gasPin PIN_PC3

#define RQ_SET_LED         0
#define RQ_SET_LED_VALUE   1
#define RQ_GET_SWITCH      2
#define RQ_GET_LIGHT       3

boolean buzzerState = false;

int buttonState = HIGH;
int buttonNextState = HIGH;
int vibrationState = 0;
int gasState = 0;

/* ------------------------------------------------------------------------- */
/* ----------------------------- USB interface ----------------------------- */
/* ------------------------------------------------------------------------- */
usbMsgLen_t usbFunctionSetup(uint8_t data[8])
{
    usbRequest_t *rq = (void *)data;

    /* declared as static so they stay valid when usbFunctionSetup returns */
    static uint8_t switch_state;  

    if (rq->bRequest == RQ_GET_SWITCH)
    {
        switch_state = 1;
        usbMsgPtr = &switch_state;
        
        return 0;
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

