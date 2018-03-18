#include <GD23Z32.h>

void setup()
{
  GD.begin();
}

void loop()
{
  MoviePlayer mp;

  mp.begin("fun-1500.avi");
  mp.play();
}
