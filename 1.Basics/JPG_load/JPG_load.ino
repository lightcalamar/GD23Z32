#include <GD23Z32.h>

File archivo;
//SdFat SD(3); const uint8_t SD_CS = PA15;    //F429ZI, Core7XXI  SPI3
//SdFat SD(2); const uint8_t SD_CS = PB12;  //F407, F103        SPI2
SdFat SD(2);  const uint8_t SD_CS = PA11;   // F767

void setup()
{
  SD.begin(SD_CS, SD_SCK_MHZ(36));
  GD.begin();
  archivo = SD.open("tree.jpg");

  GD.cmd_loadimage(0, 0);
  GD.loadSdFat(archivo); 
  archivo.close();

   MP();
}
void loop(){}

void MP()
{
  while(1)
 {
   GD.Clear();
   GD.Begin(BITMAPS);
    GD.Vertex2ii(0, 0);
   GD.swap();
 }
}
