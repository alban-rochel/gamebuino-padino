#ifndef PadController_H
#define PadController_H

class PadController
{
  public:

  enum PadButton
  {
    PadUp,
    PadDown,
    PadLeft,
    PadRight,
    Pad1,
    Pad2,
    Pad3,
    Pad4,
    Pad5,
    Pad6,
    Pad7,
    Pad8,
    Pad9,
    Pad10,
    Pad11,
    Pad12,
    Pad13,
    Pad14,
    Pad15,
    Pad16,
    Pad17,
    Pad18,
  } ;
  
  PadController(void);
  ~PadController(void);

  void init(void);
  void press(PadButton button);
  void release(PadButton button);
  void releaseAll(void);

  private:
  class Private;
  Private* d;
};

//extern PadController MyPadController;

#endif
