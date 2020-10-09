#include <Arduino.h>

// Pins

const int button = 2;
const int buzzor = 3;
const int sensor = 4;
const int green = 12; // Green light
const int red = 13; // Red light

// Constants and Variables

int door_open; // Magnetic sensor
int key_status; // Button
bool already_open = false; // Previous status

const int blink_time = 375;
const int check_time = 200;
const int alarm_time = blink_time / 1.3;

// Functions

void check_key() {
  key_status = digitalRead(button);
}

void check_door() {
  door_open = digitalRead(sensor);
}

void greenLight() {
  digitalWrite(green, HIGH);
  digitalWrite(red, LOW);
}

void redLight() {
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
}

void openingTune() {
  Serial.println("Opening Tune");
  tone(buzzor, 523, 250); // C5 4th
  delay(325);
  tone(buzzor, 587, 250); // D5 4th
  delay(325);
}

void closingTune() {
  Serial.println("Closing Tune");
  tone(buzzor, 262, 250); // C4 4th
  delay(325);
  tone(buzzor, 220, 250); // A3 4th
  delay(325);
}

void alarmTune() {
  Serial.println("Alarm Tune");
  while (key_status == LOW) {
    redLight();
    
    tone(buzzor, 988, alarm_time); // B5
    delay(blink_time);
    Serial.print("Wee-");
    
    greenLight();
    
    tone(buzzor, 1047, alarm_time); // C6
    delay(blink_time);
    Serial.print("Woo-");
    
    check_key();
  }
}

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
  check_door();
  check_key();
  
  if (key_status == HIGH) {
    // Button is pressed
    greenLight();
    
    if (door_open == HIGH) {
      // Door is open
      if (already_open == false) {
        // door has been opened
        // Serial.println("[Down][  Were ][ Open ]");
        already_open = true;
        
        // play opening tune
        openingTune();
      }
      else /* already_open == true */ {
        // Door were already open
        // Serial.println("[Down][Already][ Open ]");
      }
    }
    else /* (door_open == LOW) */ {
      // Door is closed
      if (already_open == true) {
        // Door has been closed
        // Serial.println("[Down][Already][Closed]");
        redLight();
        already_open = false;

        // play closing tune
        closingTune();
      }
      else /* (already_open == false) */ {
        // Door already closed
        // Serial.println("[Down][  Were ][Closed]");
      }
    }
  }
  else /* (key_status == LOW) */ {
    // Button is not pressed
    if (door_open == HIGH) {
      // Door is open
      if (already_open == true) {
        // Door were already open
        // Serial.println("[ Up ][Already][ Open ]");
        // alarm doesn't play
      }
      else /* (already_open == false) */ {
        // Door wasn't already open
        // Serial.println("[ Up ][  Were ][ Open ]");

        // play alarm
        alarmTune();
        
        // Blinks between green and red lights
        // loop intruder tune
        // stops when button is pressed a.k.a. key_status == true
      }
    }
    else /* (door_open == LOW) */ {
      // Door is closed
      if (already_open == true) {
        // Door has been closed
        // Serial.println("[ Up ][Already][Closed]");
        redLight();
        //play closing tune
        closingTune();
        already_open = false;
      }
      else /* (already_open == false) */ {
        // Door were already closed
        // Serial.println("[ Up ][  Were ][Closed]");
        redLight();
      } 
    } 
  }
  delay(check_time);
}