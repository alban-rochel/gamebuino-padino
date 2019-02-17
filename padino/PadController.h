#pragma once

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
    Pad4
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
