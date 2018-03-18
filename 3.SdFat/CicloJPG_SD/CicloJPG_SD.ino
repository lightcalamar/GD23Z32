#include <GD23Z32.h>

unsigned long start;

File archivo;
//SdFat SD(2); const uint8_t SD_CS = PE15; 
//SdFat SD(2); const uint8_t SD_CS = PB12;  //F407, F103  SPI2
SdFat SD(2);  const uint8_t SD_CS = PA11;   // F767

void setup()
{
  SD.begin(SD_CS, SD_SCK_MHZ(36));
  GD.begin();
}

void loop(){
 Ciclo();
}

void CargaJPG()
{
   GD.Clear();
   GD.Begin(BITMAPS);  
   GD.Vertex2ii(0, 0); 
    GD.ColorRGB(255,255,255);  GD.cmd_number(30,360,31,OPT_CENTER|OPT_SIGNED,millis() - start);
   GD.swap();
}
