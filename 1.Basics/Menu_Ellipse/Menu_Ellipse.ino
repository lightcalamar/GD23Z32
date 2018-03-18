//#include <GD2UD.h>
#include <GD23Z32.h>

#include "H1ico.h"
#include "Icons2.h"
#include "money.h"
#include "Radio1.h"
#include "Radio2.h"
#include "Ricon1.h"

char GrupoJPG1[21][15]={"B002.jpg","Fondo003.jpeg","tree.jpg","zx13.jpg","selfie.jpg"};
int IDJPG=0;

//Fondo de pantalla
File Filefondoarchivo;
//Fondo de pantalla

SdFat SD2(3);  const uint8_t SD2_CS = PA15;   // chip select for sd2

//                        0            1             2            3            4              5 //IDAsset
char ChAsset[6][11]={"money.gd2", "Icons2.gd2", "Ricon1.gd2", "H1ico.gd2", "Radio1.gd2", "Radio2.gd2"};  File FileAsset;
int NumAssets;          //10            14          14            8             10           9
int IDAsset=3;

uint32_t ram;
float FRAM, SRAM;

float pi= 3.141592654;

int A[20];
int B[20];
int XX0[20], YY0[20], RadioR[20];
float EEX[20], EEY[20];
float TT[20];
float DeltaD[20];

//Menu elíptico
//parametros de centroide del menu elíptico
  int MCa= 250, MCb= 120, MCX= 250, MCY=190;
  float MCV = -0.01;  //0.025; 0.01;  -0.025;  0.005 velocidad y dirección de rotación
//parametros de centroide del menu elíptico  

int DESPMCX= 100, DESPMCY= -180;

int movx=0, separacionpanel=5;
