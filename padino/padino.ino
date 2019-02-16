#include <Gamebuino-Meta.h>

#include "PadController.h"

PadController myPad;

void setup() {
  gb.begin();
  gb.setFrameRate(100);

  myPad.init();
}

void loop() {
  while (!gb.update());

#define IMPLEMENT_BUTTON(gbButton, padButton) \
  if (gb.buttons.pressed(gbButton)) { \
    myPad.press(padButton); \
  } \
  else if (gb.buttons.released(gbButton)) { \
    myPad.release(padButton); \
  }

  IMPLEMENT_BUTTON(BUTTON_UP,     PadController::PadUp);
  IMPLEMENT_BUTTON(BUTTON_DOWN,   PadController::PadDown);
  IMPLEMENT_BUTTON(BUTTON_LEFT,   PadController::PadLeft);
  IMPLEMENT_BUTTON(BUTTON_RIGHT,  PadController::PadRight);
  IMPLEMENT_BUTTON(BUTTON_A,      PadController::Pad1);
  IMPLEMENT_BUTTON(BUTTON_B,      PadController::Pad2);
  IMPLEMENT_BUTTON(BUTTON_MENU,   PadController::Pad3);

}
