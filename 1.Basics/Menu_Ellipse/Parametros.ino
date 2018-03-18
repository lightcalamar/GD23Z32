#if defined(__arm__)
extern "C" char* sbrk(int incr);
static int FreeStack() {
  char top = 't';
  return &top - reinterpret_cast<char*>(sbrk(0));
}
#endif

char TX[50];
//int RAM = 131072;
void STM32a()
{
  ram = FreeStack();
  FRAM=ram;
  if(FRAM<=196608){SRAM=196608;}
              else{SRAM=327680;}
}

void STM32()
{
  STM32a();
  GD.ColorRGB(0x00ff00); sprintf(TX,"F_CPU: %d MHz", (F_CPU/1000000));  GD.cmd_text(GD.w - 105, 0, 26, 0, TX);

  GD.cmd_text(GD.w - 105, 16, 26, 0, "U_RAM:               %");  GD.printNfloat(GD.w - 35, 16, 100*(SRAM-FRAM)/SRAM, 2, 26);

  GD.ColorA(75);
  GD.printNfloat(200,  0, 100*(SRAM-FRAM)/SRAM, 6, 20);
  GD.printNfloat(200, 16, 100*(SRAM-FRAM)/SRAM, 6, 26);
  GD.printNfloat(200, 16+20, 100*(SRAM-FRAM)/SRAM, 6, 27);
  GD.printNfloat(200, 16+40, 100*(SRAM-FRAM)/SRAM, 6, 28);
  GD.printNfloat(200, 16+60, 100*(SRAM-FRAM)/SRAM, 6, 29);
  GD.printNfloat(200, 16+80, 100*(SRAM-FRAM)/SRAM, 6, 30);
  GD.printNfloat(200, 16+105, 100*(SRAM-FRAM)/SRAM, 6, 31);

  GD.cmd_romfont(14,32);
  GD.printNfloat(200, 16+145, 100*(SRAM-FRAM)/SRAM, 6, 14);

  GD.cmd_romfont(14,33);
  GD.printNfloat(200, 16+195, 100*(SRAM-FRAM)/SRAM, 6, 14);

  GD.cmd_romfont(14,34);
  GD.printNfloat(200, 16+255, 100*(SRAM-FRAM)/SRAM, 6, 14);
  GD.ColorA(255);
  
  sprintf(TX,"F_SPI1:  %d MHz", (FreqSPI1/1000000));  GD.cmd_text(GD.w - 105, 32, 26, 0, TX);
  sprintf(TX,"F_SPI3:  %d MHz", (FreqSD3/1000000));  GD.cmd_text(GD.w - 105, 48, 26, 0, TX);
}
