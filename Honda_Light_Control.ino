#include <EEPROM.h>

int ledr = 2;
int ledg = 1;
int ledb = 0;
int buzz = 3;
int button = 4;
int PIN_RED = 2;
int PIN_GREEN = 1;
int PIN_BLUE = 0;
int counter = 0;
int numColors = 255;

long previousMillis = 0;   
long interval = 15000;          
int stateswitch = 1;

int state = 1;
int buttonState = 0;      
int buttonpressed = 0;

void setup() {

    state = EEPROM.read(34);
    if (state > 7) {
        state =1;
    }

    pinMode(ledr, OUTPUT);  
    pinMode(ledg, OUTPUT);     
    pinMode(ledb, OUTPUT); 
    pinMode(buzz, OUTPUT);
    pinMode(button, INPUT);     
                
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
    buttonState = digitalRead(button);
    if (buttonState == HIGH) { 
        if (buttonpressed == 1){
        }else{
            buttonpressed = 1;
            if (state == 7) {
                state =1;
            }else{
                state = (state+1);
            }
            EEPROM.write(34, state);


            if (state == 1) {
                tone(buzz, 1000, 1150);
            }else if (state == 7){
                tone(buzz, 900, 150);
                delay(100);
                tone(buzz, 800, 150);
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
            }else{
                tone(buzz, 700, 250);
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
            } else if (stateswitch == 1) {
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

