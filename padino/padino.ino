#include <Gamebuino-Meta.h>
#include <SPI.h>
#include "PadController.h"
#include "KeyboardPix.h"

const uint8_t BTN_CS = 25;
const uint8_t toggle = 0x8e;

PadController myPad;
KeyboardController myKeyboard;

bool status[8]; // pressed status (true = pressed)
PadController::PadButton buttons[8];
uint8_t keys[8];

bool gamepadMode;

Image gamepadImage = Image(gamepadData);
Image keyboardImage = Image(keyboardData);

uint8_t readButtons()
{
    //start SPI
    SPI.beginTransaction(SPISettings(12000000, MSBFIRST, SPI_MODE0));
    digitalWrite(BTN_CS, LOW);
    //wait for PL to recover
    delayMicroseconds(1);
    //get the buttons states from the shift register
    uint8_t buttonsStatus = SPI.transfer(1);
    //end SPI
    digitalWrite(BTN_CS, HIGH);
    SPI.endTransaction();

    return buttonsStatus;
}


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

  keys[0] = 's';
  keys[1] = 'a';
  keys[2] = 'd';
  keys[3] = 'w';
  keys[4] = 'j';
  keys[5] = 'k';
  keys[6] = 'l';
  keys[7] = KEY_RETURN;

  myPad.init();

  gamepadMode = true;

}

void loop()
{
  // initial display
  gb.display.drawImage(0, 0, gamepadMode ? gamepadImage : keyboardImage);
  while(gb.update()); // display

  uint8_t buttonStatus = 0xFF; // released

  while(true) // actual main loop
  {
    while(true) // while configuration unchanged
    {
      buttonStatus = readButtons();

      if(buttonStatus == toggle)
      {
        gamepadMode = !gamepadMode;
        break;
      }

      // handle button events
      for(unsigned int ii = 0; ii < 8; ++ii)
      {
        bool pressed = ((buttonStatus & (1 << ii)) == 0);
        if(status[ii] != pressed)
        {
          status[ii] = pressed;
          if(gamepadMode)
          {
            if(pressed)
            {
              myPad.press(buttons[ii]);
            }
            else
            {
              myPad.release(buttons[ii]);
            }
          }
          else
          {
            if(pressed)
            {
              myKeyboard.press(keys[ii]);
            }
            else
            {
              myKeyboard.release(keys[ii]);
            }
          }
        }
      } // end for(unsigned int ii = 0; ii < 8; ++ii)
      
    } // end while configuration unchanged

    // Update display
    gb.display.drawImage(0, 0, gamepadMode ? gamepadImage : keyboardImage);
    while(gb.update()); // display

    // Wait for buttons to be released before actually changing mode
    while(readButtons() != 0xFF);

    myPad.releaseAll();
    myKeyboard.releaseAll();
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
