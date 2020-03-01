/*
 *  ##### Button Handler #########
 *  Andreas Hellerschmied, 2020-02-14
 *  (code adapted from https://www.instructables.com/id/Arduino-Button-Tutorial/)
 *  
 *  A ButtonHandler object handles four events:
 *  - EV_NONE           : no event
 *  - EV_SHORTPRESS     : button release before "longpress" time
 *  - EV_LONGPRESS_AUTO : After DEFAULT_LONGPRESS_LEN ms (or the non-dafault time)
 *  - EV_LONGPRESS      : button release after "longpress" time
 *   
 */


#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include <Arduino.h>

#define DEFAULT_LONGPRESS_LEN    1000  // Min nr of loops for a long press [ms]
#define EV_NONE                  0 // no event
#define EV_SHORTPRESS            1 // button release before "longpress" time
#define EV_LONGPRESS_AUTO        2 // After DEFAULT_LONGPRESS_LEN ms (or the non-dafault time)
#define EV_LONGPRESS             3 // button release after "longpress" time

// Class definition

class ButtonHandler {

  public:
    // Constructor
    // - e.g. ButtonHandler button1(BUTTON1_PIN);
    // - e.g. ButtonHandler button2(BUTTON2_PIN, LONGPRESS_LEN_MS); (longpress_len is optional!)
    ButtonHandler(int pin, int longpress_len=DEFAULT_LONGPRESS_LEN);

    // Initialization done after construction, to permit static instances
    // - has to be called in "setup()" 
    void init();

    // Handler, to be called in the "loop()"
    // - it returns the event, acording to the defined event code (int) 
    int handle();

  protected:
    boolean was_pressed;     // previous state
    boolean longpress_lock;   // flag: True, if button is pressed longer than DEFAULT_LONGPRESS_LEN (or the non-default value)
    const int pin;           // pin to which button is connected
    const int longpress_len; // longpress duration
    unsigned long start_time_pressed; // press running duration [ms]
};

#endif
