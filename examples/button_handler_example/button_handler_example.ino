//////////////////////////////////////////////////////////////////////////////
// Arduino button tutorial 4.
//
// Demonstrates:
// - detection of releasing edge
// - distinction of short press and long press
// - OO implementation, supporting arbitrary number of buttons
//
// Push-buttons must be connected as follows:
//              __,__
//   Pin2 ------o   o------ GND
//              __,__
//   Pin3 ------o   o------ GND
//
// (C) 2011 By P. Bauermeister, adapted by Andreas Hellerschmied (2020)
// This example code is in the public domain.
//////////////////////////////////////////////////////////////////////////////

// Adapt these to your board and application timings:

#include <button_handler.h>

#define BUTTON1_PIN               2  // Button 1
#define BUTTON2_PIN               3  // Button 2

#define LONGPRESS_LEN_MS         1000   // Min nr of loops for a long press (default = 1000)
#define DELAY                    20  // Delay per loop in ms


// Instanciate button objects
ButtonHandler button1(BUTTON1_PIN);
ButtonHandler button2(BUTTON2_PIN, LONGPRESS_LEN_MS);

void setup()
{
  Serial.begin(9600);

  // init buttons pins; I suppose it's best to do here
  button1.init();
  button2.init();
}

void print_event(const char* button_name, int event)
{
  if (event)
    Serial.print(button_name);
  Serial.print(".SLR"[event]);
  //Serial.print(event);
}

void loop()
{
  // handle button
  int event1 = button1.handle();
  int event2 = button2.handle();

  // do other things
  print_event("1", event1);
  print_event("2", event2);

  // add newline sometimes
  static int counter = 0;
  if ((++counter & 0x1f) == 0)
    Serial.println();

  delay(DELAY);
}
