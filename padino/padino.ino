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

  if (gb.buttons.pressed(BUTTON_A)) {
    myPad.press(PadController::Pad1);
  }
  else if (gb.buttons.released(BUTTON_A)) {
    myPad.release(PadController::Pad1);
  }
}
