#include <GD23Z32.h>

void setup()
{
  GD.begin();
}

void loop()
{
  GD.ClearColorRGB(0x000055);
  GD.Clear();
  GD.cmd_text(GD.w / 2, GD.h / 2, 31, OPT_CENTER, "Hello world");
  GD.swap();
}
