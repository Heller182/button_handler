#include "button_handler.h"



ButtonHandler::ButtonHandler(int p, int lp)
: pin(p), longpress_len(lp)
{
}

void ButtonHandler::init()
{
  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH); // pull-up
  was_pressed = false;
  start_time_pressed = 0;
  longpress_lock = false;
}

int ButtonHandler::handle()
{
  int event;
  int now_pressed = !digitalRead(pin);
  //unsigned long end_time_pressed = 0;
  

  if (!now_pressed && was_pressed) {
    // handle release event
    if ((millis() - start_time_pressed) < longpress_len)
      event = EV_SHORTPRESS;
    else {
      event = EV_LONGPRESS;
    }
  }
  else
    event = EV_NONE;

    /*
  // update press running duration
  if ((now_pressed) && (!was_pressed)) {
    start_time_pressed = millis();
  }
  else {
    if (!now_pressed) {
      start_time_pressed = 0;
    }
  }
  */

  // update press running duration
  if (now_pressed) {
    if (!was_pressed) {
      start_time_pressed = millis();
    }
    else {
      if ((millis() - start_time_pressed) > DEFAULT_LONGPRESS_LEN) {
        if (!longpress_lock) { 
          event = EV_LONGPRESS_AUTO;
          longpress_lock = true;
        }
      }
    }
  }
  else {
    start_time_pressed = 0;
    longpress_lock = false;
  }

  // remember state, and we're done
  was_pressed = now_pressed;
  return event;
}
