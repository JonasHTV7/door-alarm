#include <Arduino.h>

const int button = 2;
const int buzzor = 3;
const int sensor = 4;
const int green = 12; // Green light
const int red = 13; // Red light

int door_open; // Magnetic sensor
int key_status; // Button
bool already_open = false; // Previous status

void setup() {
  // put your setup code here, to run once:
  pinMode(button, INPUT);
  pinMode(sensor, INPUT_PULLUP);
  pinMode(sensor, OUTPUT);
  pinMode(buzzor, INPUT);
  pinMode(buzzor, OUTPUT);

  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  door_open = digitalRead(sensor);
  key_status = digitalRead(button);
  
  if (key_status == HIGH) {
    Serial.println("Button is pressed");
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    
    if (door_open == HIGH) {
      Serial.println("Door is open");
      if (already_open == false) {
        // door has been opened
        // play opening tune
        already_open = true;
      }
      else /* already_open == true */ {
        Serial.println("Door were already open");
      }
    }
    else /* (door_open == LOW) */ {
      Serial.println("Door is closed");
      if (already_open == true) {
        Serial.println("Door has been closed");
        // play closing tune
        already_open = false;
      }
      else /* (already_open == false) */ {
        Serial.println("Door already closed");
      }
    }
  }
  else /* (key_status == LOW) */ {
    Serial.println("Button is not pressed");
    if (door_open == HIGH) {
      Serial.println("Door is open"); 
      if (already_open == true) {
        Serial.println("Door were already open");
        // alarm doesn't play
      }
      else /* (already_open == false) */ {
        Serial.println("Door wasn't already open");
        // Blinks between green and red lights
        // loop intruder tune
        // stops when button is pressed a.k.a. key_status == true
      }
    }
    else /* (door_open == LOW) */ {
      Serial.println("Door is closed");
      if (already_open == true) {
        Serial.println("Door has been closed");
        digitalWrite(red, HIGH);
        digitalWrite(green, LOW);
        //play closing tune
        already_open = false;
      }
      else /* (already_open == false) */ {
        Serial.println("Door were already closed");
      } 
    } 
  }
}