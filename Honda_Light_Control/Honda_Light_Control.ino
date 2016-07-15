#include <EEPROM.h>

/* This sketch was made for an ATtiny85 */

int ledr = 2; // Red light NO pwm
int ledg = 1; // Green light w pwm
int ledb = 0; // Blue light w pwm
int button = 4; // Analog pin 4

int counter = 0;
int numColors = 255;

long previousMillis = 0;   
long interval = 15000;          
int stateswitch = 1;

int state = 1;
int buttonState = 0;      
int buttonpressed = 0;

void setup() {
  
    /* Get the last state from EEPROM. */

    state = EEPROM.read(34);
    if (state > 7) {
        state = 1;
    }
    pinMode(ledr, OUTPUT);  
    pinMode(ledg, OUTPUT);     
    pinMode(ledb, OUTPUT); 
    pinMode(button, INPUT);     
  
    /* When the ATtiny gets power the leds cycle through a color sequence. */
          
    digitalWrite(ledr, HIGH);    
    digitalWrite(ledg, LOW);    
    digitalWrite(ledb, LOW); 
    delay(250);
    digitalWrite(ledr, LOW);    
    digitalWrite(ledg, HIGH);    
    digitalWrite(ledb, LOW); 
    delay(250);
    digitalWrite(ledr, LOW);    
    digitalWrite(ledg, LOW);    
    digitalWrite(ledb, HIGH);  
    delay(250);
    digitalWrite(ledr, HIGH);    
    digitalWrite(ledg, LOW);    
    digitalWrite(ledb, LOW); 
    delay(250);
    digitalWrite(ledr, LOW);    
    digitalWrite(ledg, HIGH);    
    digitalWrite(ledb, LOW); 
    delay(250);
    digitalWrite(ledr, LOW);    
    digitalWrite(ledg, LOW);    
    digitalWrite(ledb, HIGH);  
    delay(250);
    digitalWrite(ledr,LOW);    
    digitalWrite(ledg, LOW);    
    digitalWrite(ledb, LOW); 
    delay(250);
    updateled();
}

void loop() {
  
    /* This handles the button press and keeps up with the count. It also
    writes this value to EEPROM so the next time the car turns on the RGB 
    strip will go back to the last selection. */
  
    buttonState = digitalRead(button);
    if (buttonState == HIGH) { 
        if (buttonpressed == 1){
        }else{
            buttonpressed = 1;
            if (state == 7) {
                state = 1;
            }else{
                state = (state + 1);
            }
            EEPROM.write(34, state);
            if (state == 7){
                delay(100);     
                digitalWrite(ledr, HIGH);    
                digitalWrite(ledg, LOW);    
                digitalWrite(ledb, LOW); 
                delay(100);
                digitalWrite(ledr, LOW);    
                digitalWrite(ledg, HIGH);    
                digitalWrite(ledb, LOW); 
                delay(100);
                digitalWrite(ledr, LOW);    
                digitalWrite(ledg, LOW);    
                digitalWrite(ledb, HIGH);  
                delay(100);
                stateswitch = random(1, 4); 
            }
            updateled();
        }
    }else{
      buttonpressed = 0;
      if (state == 7){
          updateled();
      }
    }
    delay(100);     
}

void updateled() {

    /* This controls the RGB led strips by keeping the count of button presses
    in the 'state' variable. The lights are only controlled from one button in
    the car's dash. The ATtiny85 this circut was designed for only has 
    two PWM pins so my color choices are more limited. */
    
    if (state == 1) {
        digitalWrite(ledr, LOW);    
        digitalWrite(ledg, LOW);    
        digitalWrite(ledb, LOW);  
    } else if (state == 2) {
        digitalWrite(ledr, HIGH);    
        digitalWrite(ledg, LOW);    
        digitalWrite(ledb, LOW);   
    } else if (state == 3) {
        analogWrite(ledr, 0);   
        analogWrite(ledg, 100);  
        analogWrite(ledb, 0);  
    } else if (state == 4) {
        analogWrite(ledr, 0);   
        analogWrite(ledg, 0);  
        analogWrite(ledb, 100);  
    } else if (state == 5) {
        digitalWrite(ledr, HIGH);    
        analogWrite(ledg, 95);  
        analogWrite(ledb, 0);
    } else if (state == 6) {
        digitalWrite(ledr, HIGH);    
        digitalWrite(ledg, HIGH);    
        digitalWrite(ledb, HIGH);  
    } else if (state == 7) {
        unsigned long currentMillis = millis();
        if(currentMillis - previousMillis > interval) {
            previousMillis = currentMillis;   
            stateswitch = stateswitch+1; 
            if (stateswitch == 1){
                digitalWrite(ledr, HIGH);    
                digitalWrite(ledg, LOW);    
                digitalWrite(ledb, LOW); 
            } else if (stateswitch == 2) {
                analogWrite(ledr, 0);   
                analogWrite(ledg, 100);  
                analogWrite(ledb, 0);  
            } else if (stateswitch == 3) {
                analogWrite(ledr, 0);   
                analogWrite(ledg, 0);  
                analogWrite(ledb, 100);  
            } else if (stateswitch == 4) {
                digitalWrite(ledr, HIGH);    
                analogWrite(ledg, 95);  
                analogWrite(ledb, 0);
            } else if (stateswitch == 5) {
                digitalWrite(ledr, HIGH);    
                digitalWrite(ledg, HIGH);    
                digitalWrite(ledb, HIGH);
                stateswitch = 0;
            }
        }
    } 
}

