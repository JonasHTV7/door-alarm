#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  /* const int sensor_pin = number
  const int button_pin = number 
  boolean key_status = false (button press)
  boolean door_open = false (magnetic sensor)
  boolean already_open = false (previous status)
  boolean disable_alarm = false () */
}

void loop() {
  // put your main code here, to run repeatedly:
  if (/* key_status == true */)
  {
    /* button is pressed,
    turn on green light,
    turn off red light,
    disable_alarm = true */
    
    if (/* door_open == true */)
    {
      /* door is open */

      if (/* already_open == false */)
      {
        /* door has been opened,
        play opening tune,
        already_open = true */
      }
      else /* already_open == true */
      {
        /* door is already open */
      }
      
    }
    else /* door_open == false */
    {
      /* door is closed */

      if (/* already_open == true */)
      {
        /* door has closed,
        play closing tune,
        already_open = false */
      }
      else /* already_open == false */
      {
        /* door already closed */
      }

    }
    
  }
  else /* key_status == false */
  {
    /* button is not pressed */

    if (/* door_open == true */)
    {
      /* door is open */

      if (/* already_open == true */)
      {
        /* door already open,
        alarm doesn't play */
      }
      else /* already_open == false */
      {
        /* door wasn't already open,
        blinks between green and red lights,
        loop intruder tune,
        stops when button is pressed a.k.a. key_status == true*/
      }
      
    }
    else /* door_open == false */
    {
      /* door is closed */

      if (/* already_open == true */)
      {
        /* door has been closed,
        play closing tune,
        turn on red light,
        turn off green light,
        already_open = false */
      }
      else /* already_open == false */
      {
        /* door already closed, */
      }
      
      
    }
    
  }
  
}