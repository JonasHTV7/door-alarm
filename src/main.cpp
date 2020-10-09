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
bool open_allowed = false; // Status

const int blink_time = 375;
const int check_time = 200;
const int alarm_time = blink_time / 1.3;
const int alarm_wait = 30;
bool alarm_confirm = true;

// Functions

void check_key() {
  key_status = digitalRead(button);
}

void check_door() {
  door_open = digitalRead(sensor);
}

void alarm_prompt() {
  Serial.println("Alarm prompting");
  for (int i = 0; i < alarm_wait; i++)
  {
    Serial.print("Waiting-");
    tone(buzzor, 523, 500); // C5 4th
    delay(1000);
    check_key();
    if (key_status == HIGH) {
      Serial.println("Alarm disabled");
      alarm_confirm = false;
      tone(buzzor, 523, 250); // C5 4th
      delay(325);
      tone(buzzor, 587, 250); // D5 4th
      delay(325);
      break;
    }
  }
  if (alarm_confirm == true) {alarmTune();}
  else {alarm_confirm = true;}
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
  
  if (door_open == HIGH) { // Door is open
    if (key_status == HIGH) { // Button is pressed
      if (open_allowed == true) { // Already open
        greenLight();
      }
      else /* open_allowed == false */ { // Door has been opened
        greenLight();
        openingTune();
        open_allowed = true;
      }
    }
    else /* key_status == LOW */ { // Button is not pressed
      if (open_allowed == true) { // Door stayed open
        greenLight();
      }
      else /* open_allowed == false */ { // Door has been breached
        redLight();
        alarm_prompt();
      }    
    }
  }
  else /* door_open == false */ { // Door is closed
    if (key_status == HIGH) { // Button is pressed
      if (open_allowed == true) { // Door is unlocked
        greenLight();
      }
      else /* open_allowed == false */ { // Door has been unlocked
        greenLight();
        open_allowed = true;
      }
    }
    else /* key_status == LOW */ { // Button is not pressed
      if (open_allowed == true) { // Door has been closed
        redLight();
        closingTune();
        open_allowed = false;
      }
      else /* open_allowed == false */ { // Door is larmed
        redLight();
      }
    }
  }
  delay(check_time);
}