#include <Gamebuino-Meta.h>
#include <SPI.h>
#include "PadController.h"

const uint8_t BTN_CS = 25;

PadController myPad;

bool status[8]; // pressed status (true = pressed)
PadController::PadButton buttons[8];

bool firstStepInLoop;

void setup()
{
  gb.begin();
  SPI.begin();
  pinMode(BTN_CS, OUTPUT);
  digitalWrite(BTN_CS, HIGH);

  for(uint32_t ii = 0; ii < 8; ++ii)
  {
    status[ii] = false;
  }
  buttons[0] = PadController::PadDown;
  buttons[1] = PadController::PadLeft;
  buttons[2] = PadController::PadRight;
  buttons[3] = PadController::PadUp;
  buttons[4] = PadController::Pad1;
  buttons[5] = PadController::Pad2;
  buttons[6] = PadController::Pad3;
  buttons[7] = PadController::Pad4;

  myPad.init();

  firstStepInLoop = true;

}

void loop()
{
  if(firstStepInLoop)
  {
    while(gb.update());
    firstStepInLoop = false;
  }
  //start SPI
  SPI.beginTransaction(SPISettings(12000000, MSBFIRST, SPI_MODE0));
  digitalWrite(BTN_CS, LOW);
  //wait for PL to recover
  delayMicroseconds(1);
  //get the buttons states from the shift register
  uint8_t buttonsData = SPI.transfer(1);
  //end SPI
  digitalWrite(BTN_CS, HIGH);
  SPI.endTransaction();

  for(unsigned int ii = 0; ii < 8; ++ii)
  {
    bool pressed = ((buttonsData & (1 << ii)) == 0);
    if(status[ii] != pressed)
    {
      status[ii] = pressed;
      if(pressed)
      {
        myPad.press(buttons[ii]);
      }
      else
      {
        myPad.release(buttons[ii]);
      }
    }
  }
  

/*#define IMPLEMENT_BUTTON(gbButton, padButton) \
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
  IMPLEMENT_BUTTON(BUTTON_MENU,   PadController::Pad3);*/
  

}
