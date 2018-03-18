void Ciclo()
{
  start = millis();
  archivo = SD.open("6oBaa.jpg");       
  GD.cmd_loadimage(0, 0);
  GD.loadSdFat(archivo); 
  archivo.close();
  CargaJPG();  

  start = millis();       
  archivo = SD.open("6oBba.jpg");
  GD.cmd_loadimage(0, 0);
  GD.loadSdFat(archivo); 
  archivo.close();
  CargaJPG();

  start = millis();       
  archivo = SD.open("6oFb.jpg");
  GD.cmd_loadimage(0, 0);
  GD.loadSdFat(archivo); 
  archivo.close();
  CargaJPG();

  start = millis();       
  archivo = SD.open("6oGb.jpg");
  GD.cmd_loadimage(0, 0);
  GD.loadSdFat(archivo); 
  archivo.close();
  CargaJPG();

  start = millis();       
  archivo = SD.open("6oHaa.jpg");
  GD.cmd_loadimage(0, 0);
  GD.loadSdFat(archivo); 
  archivo.close();
  CargaJPG();
}  
