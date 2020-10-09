#include <Arduino.h>

const int button = 2;
const int buzzor = 3;
const int sensor = 4;
const int green = 12; // Green light
const int red = 13; // Red light

int door_open; // Magnetic sensor
int key_status; // Button
bool already_open = false; // Previous status

const int blink_time = 500;
const int check_time = 250;
const int alarm_time = blink_time / 1.3;

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
    // Button is pressed
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    
    if (door_open == HIGH) {
      // Door is open
      if (already_open == false) {
        // door has been opened
        // Serial.println("[Down][  Were ][ Open ]");
        already_open = true;
        
        // play opening tune
        Serial.println("Opening Tune");
        tone(buzzor, 247, 250);
        delay(325);
        tone(buzzor, 262, 250);
        delay(325);
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
        digitalWrite(red, HIGH);
        digitalWrite(green, LOW);
        already_open = false;

        // play closing tune
        Serial.println("Closing Tune");
        tone(buzzor, 262, 250);
        delay(325);
        tone(buzzor, 247, 250);
        delay(325);
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
        Serial.println("Alarm");
        while (key_status == LOW) {
          digitalWrite(red, HIGH);
          digitalWrite(green, LOW);
          
          tone(buzzor, 247, alarm_time);
          delay(blink_time);
          Serial.print("Wee");
          
          if (key_status == LOW) {key_status = digitalRead(button);}
          
          digitalWrite(red, LOW);
          digitalWrite(green, HIGH);
          
          tone(buzzor, 262, alarm_time);
          delay(blink_time);
          Serial.print("Woo");
          
          if (key_status == LOW) {key_status = digitalRead(button);}
        }
        
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
        digitalWrite(red, HIGH);
        digitalWrite(green, LOW);
        //play closing tune
        Serial.println("Closing Tune");
        already_open = false;
      }
      else /* (already_open == false) */ {
        // Door were already closed
        // Serial.println("[ Up ][  Were ][Closed]");
        digitalWrite(red, HIGH);
        digitalWrite(green, LOW);
      } 
    } 
  }
  delay(check_time);
}