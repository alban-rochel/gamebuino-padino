#include "PadController.h"
#include "HID.h"

static const uint8_t _hidReportDescriptor[] PROGMEM = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x05,                    // USAGE (Game Pad)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x85, 0x03,                    //   REPORT_ID (3)
    0x09, 0x01,                    //   USAGE (Pointer)
    0xa1, 0x00,                    //   COLLECTION (Physical)
    0x09, 0x30,                    //     USAGE (X)
    0x09, 0x31,                    //     USAGE (Y)
    0x15, 0xff,                    //     LOGICAL_MINIMUM (-1)
    0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
    0x95, 0x02,                    //     REPORT_COUNT (2)
    0x75, 0x02,                    //     REPORT_SIZE (2)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0xc0,                          //   END_COLLECTION
    0x95, 0x02,                    //   REPORT_COUNT (2)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)
    0x05, 0x09,                    //   USAGE_PAGE (Button)
    0x19, 0x01,                    //   USAGE_MINIMUM (Button 1)
    0x29, 0x12,                    //   USAGE_MAXIMUM (Button 18)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x95, 0x12,                    //   REPORT_COUNT (18)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0xc0                           // END_COLLECTION
};

class PadController::Private
{
  public:
  Private()
  {
    report[0] = previousReport[0] = 0;
    report[1] = previousReport[1] = 0;
    report[2] = previousReport[2] = 0;
  }
  uint8_t report[3];

  void send(void)
  {
    if((report[0] != previousReport[0]) || (report[1] != previousReport[1]) || (report[2] != previousReport[2]))
    {
      HID().SendReport(3,report,3);
      previousReport[0] = report[0];
      previousReport[1] = report[1];
      previousReport[2] = report[2];
    }
  }

  private:
  uint8_t previousReport[3];
};

PadController::PadController():
  d(new Private)
{
  static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
  HID().AppendDescriptor(&node);
}

PadController::~PadController()
{
  releaseAll();
  delete d;
}

void PadController::init(void)
{
  
}

void PadController::press(PadController::PadButton button)
{
  switch(button)
  {
    case PadDown:
    d->report[0] = (d->report[0] & 0b11110011) | 0b00000100;
    break;
    
    case PadUp:
    d->report[0] = (d->report[0] & 0b11110011) | 0b00001100;
    break;
    
    case PadLeft:
    d->report[0] = (d->report[0] & 0b11111100) | 0b00000011;
    break;
    
    case PadRight:
    d->report[0] = (d->report[0] & 0b11111100) | 0b00000001;
    break;

    case Pad1:
    d->report[0] = (d->report[0] & 0b10111111) | 0b01000000;
    break;
    
    case Pad2:
    d->report[0] = (d->report[0] & 0b01111111) | 0b10000000;
    break;
    
    case Pad3:
    d->report[1] = (d->report[1] & 0b11111110) | 0b00000001;
    break;
    
    case Pad4:
    d->report[1] = (d->report[1] & 0b11111101) | 0b00000010;
    break;
    
    case Pad5:
    d->report[1] = (d->report[1] & 0b11111011) | 0b00000100;
    break;
    
    case Pad6:
    d->report[1] = (d->report[1] & 0b11110111) | 0b00001000;
    break;
    
    case Pad7:
    d->report[1] = (d->report[1] & 0b11101111) | 0b00010000;
    break;
    
    case Pad8:
    d->report[1] = (d->report[1] & 0b11011111) | 0b00100000;
    break;
    
    case Pad9:
    d->report[1] = (d->report[1] & 0b10111111) | 0b01000000;
    break;
    
    case Pad10:
    d->report[1] = (d->report[1] & 0b01111111) | 0b10000000;
    break;

    case Pad11:
    d->report[2] = (d->report[2] & 0b11111110) | 0b00000001;
    break;
    
    case Pad12:
    d->report[2] = (d->report[2] & 0b11111101) | 0b00000010;
    break;
    
    case Pad13:
    d->report[2] = (d->report[2] & 0b11111011) | 0b00000100;
    break;
    
    case Pad14:
    d->report[2] = (d->report[2] & 0b11110111) | 0b00001000;
    break;
    
    case Pad15:
    d->report[2] = (d->report[2] & 0b11101111) | 0b00010000;
    break;
    
    case Pad16:
    d->report[2] = (d->report[2] & 0b11011111) | 0b00100000;
    break;
    
    case Pad17:
    d->report[2] = (d->report[2] & 0b10111111) | 0b01000000;
    break;
    
    case Pad18:
    d->report[2] = (d->report[2] & 0b01111111) | 0b10000000;
    break;
    

    default: break;
  }

  d->send();
}

void PadController::release(PadController::PadButton button)
{
    switch(button)
  {
    case PadUp:
    case PadDown:
    d->report[0] = (d->report[0] & 0b11110011);
    break;
    
    case PadLeft:
    case PadRight:
    d->report[0] = (d->report[0] & 0b11111100);
    break;

    case Pad1:
    d->report[0] = (d->report[0] & 0b10111111);
    break;
    
    case Pad2:
    d->report[0] = (d->report[0] & 0b01111111);
    break;
    
    case Pad3:
    d->report[1] = (d->report[1] & 0b11111110);
    break;
    
    case Pad4:
    d->report[1] = (d->report[1] & 0b11111101);
    break;
    
    case Pad5:
    d->report[1] = (d->report[1] & 0b11111011);
    break;
    
    case Pad6:
    d->report[1] = (d->report[1] & 0b11110111);
    break;
    
    case Pad7:
    d->report[1] = (d->report[1] & 0b11101111);
    break;
    
    case Pad8:
    d->report[1] = (d->report[1] & 0b11011111);
    break;
    
    case Pad9:
    d->report[1] = (d->report[1] & 0b10111111);
    break;
    
    case Pad10:
    d->report[1] = (d->report[1] & 0b01111111);
    break;

    case Pad11:
    d->report[2] = (d->report[2] & 0b11111110);
    break;
    
    case Pad12:
    d->report[2] = (d->report[2] & 0b11111101);
    break;
    
    case Pad13:
    d->report[2] = (d->report[2] & 0b11111011);
    break;
    
    case Pad14:
    d->report[2] = (d->report[2] & 0b11110111);
    break;
    
    case Pad15:
    d->report[2] = (d->report[2] & 0b11101111);
    break;
    
    case Pad16:
    d->report[2] = (d->report[2] & 0b11011111);
    break;
    
    case Pad17:
    d->report[2] = (d->report[2] & 0b10111111);
    break;
    
    case Pad18:
    d->report[2] = (d->report[2] & 0b01111111);
    break;

    default: break;
  }

  d->send();
}

void PadController::releaseAll(void)
{

}

//PadController MyPadController;
