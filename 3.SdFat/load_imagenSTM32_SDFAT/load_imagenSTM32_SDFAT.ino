//#include <SPI.h>
//#include "SdFat.h"
#include <GD23Z32.h>

File archivo;
//SdFat SD2(2);  const uint8_t SD2_CS = PB12;   // SPI2 F103
SdFat SD(2);  const uint8_t SD_CS = PA11;     // SPI2 F767

void setup()
{
  SD2.begin(SD2_CS, SD_SCK_MHZ(18));
  GD.begin();
  archivo = SD2.open("tree.jpg");  

  GD.cmd_loadimage(0, 0);
  GD.loadSdFat(archivo); 
}

void loop()
{
  GD.Clear();
  GD.Begin(BITMAPS);
  GD.Vertex2ii(0, 0);
  GD.swap();
}

