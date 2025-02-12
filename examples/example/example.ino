#include "MillisTimer.h"

MillisTimer msTimer;
MillisTimer usTimer;

void setup()
{
  Serial.begin(115200);

  msTimer.begin(1000);
  usTimer.begin(1000000, MICRO_SECONDS);

  msTimer.start();
  usTimer.start();
}

void loop()
{
  if(msTimer.fire())
    Serial.println("ms");

  if(usTimer.fire())
    Serial.println("us");
}
