#include <GD23Z32.h>

uint32_t f0;

#define MF_SIZE 0x40000UL
#define MF_BASE (0x100000UL - MF_SIZE)
#define PTYPE uint32_t

class MoviePlayer
{
  PTYPE wp;
  Reader r;
  void loadsector() {
    byte buf[512];
    GD.__end();
    r.readsector(buf);
    GD.resume();
    GD.wr_n(MF_BASE + wp, buf, 512);
    wp = (wp + 512) & (MF_SIZE - 1);
  }

public:
  int begin(const char *filename) {
    GD.__end();
    if (!r.openfile(filename)) {
      Serial.println("Open failed");
      return 0;
    }
    GD.resume();

uint32_t t0 = millis();
    wp = 0;
    while (wp < (MF_SIZE - 512)) {
      loadsector();
    }
    uint32_t took = (millis() - t0);
Serial.println(took);
Serial.print(1000L * wp / took);
Serial.println(" bytes/s");

    GD.cmd_mediafifo(MF_BASE, MF_SIZE);
    GD.cmd_regwrite(REG_MEDIAFIFO_WRITE, wp);
GD.finish();

    // if (1) GD.cmd_playvideo(OPT_MEDIAFIFO); else GD.cmd_videostart();

f0 = millis();
    return 1;
  }
  int play() {
    if (r.eof()) {
      return 0;
    } else {
      byte buf[512];

      PTYPE fullness = (wp - GD.rd32(REG_MEDIAFIFO_READ)) & (MF_SIZE - 1);
      Serial.println(fullness);
      while (fullness < (MF_SIZE - 512)) {
        loadsector();
        fullness += 512;
        GD.wr32(REG_MEDIAFIFO_WRITE, wp);
      }
      return 1;
    }
  }
  void block() {
    GD.cmd_playvideo(OPT_MEDIAFIFO | OPT_FULLSCREEN);
    GD.flush();
    while (play())
      ;
    GD.cmd_memcpy(0, 0, 4);
    GD.finish();
  }
};

MoviePlayer mp;

class Dirsearch {
  struct dirent de;
  int index;

public:
  char name[13];
  void begin() {
    index = 0;
  }
  int get(const char *ext) {
    byte i;

    GD.__end();
    char e3[3];

    do {
      GD.SD.rdn((byte*)&de, GD.SD.o_root + index++ * 32, sizeof(de));
      for (i = 0; i < 3; i++)
        e3[i] = tolower(de.ext[i]);
    } while (de.name[0] &&
             ((de.name[0] & 0x80) || (memcmp(ext, e3, 3) != 0)));

    GD.resume();

    char *pc = name;
    for (i = 0; i < 8 && de.name[i] != ' '; i++)
      *pc++ = tolower(de.name[i]);
    *pc++ = '.';
    for (i = 0; i < 3 && de.ext[i] != ' '; i++)
      *pc++ = tolower(de.ext[i]);
    *pc++ = 0;
    Serial.println(de.name[0], HEX);
    Serial.println(name);

    return de.name[0];
  }
};

Dirsearch ds;

char *pickfile(char *ext)
{
  GD.Clear();
  ds.begin();
  for (byte i = 0; ds.get(ext); i++) {
    int x = (i % 3) * 160;
    int y = (i / 3) * 68;
    GD.Tag(i + 1);
    GD.cmd_button(x, y, 150, 60, 27, OPT_FLAT, ds.name);
  }
  GD.swap();

  do {
    GD.get_inputs();
  } while (!GD.inputs.tag);

  ds.begin();
  for (byte i = 0; i <= (GD.inputs.tag - 1); i++)
    ds.get(ext);
  Serial.println(GD.inputs.tag);
  Serial.println(ds.name);
  return ds.name;
}

void setup()
{
  GD.begin();

  if (0) {
    uint32_t t0 = GD.rd32(REG_CLOCK);
    delay(10000);
    Serial.println(GD.rd32(REG_CLOCK) - t0);
    for (;;);
  }

  // GD.wr32(REG_FREQUENCY, 44064659);
  // GD.wr32(REG_FREQUENCY, 65000000);

  char *avi = pickfile("avi");

  GD.Clear();
  GD.cmd_text(GD.w / 2, GD.h / 2, 31, OPT_CENTER, "Hello world");
  GD.BitmapHandle(0);
  GD.cmd_setbitmap(0, RGB565, 480, 208);
  GD.swap();

  GD.cmd_memset(0, 0x11, 2UL * 480 * 208);
GD.finish();
Serial.println(GD.rd32(REG_CMD_DL));
  while (1) {
    mp.begin(avi);
    mp.block();
    GD.Clear();
    GD.swap();
  }
GD.finish();
Serial.println(GD.rd32(REG_CMD_DL));

  GD.Clear();
  GD.swap();
}

void loop()
{
#if 1
  if (!mp.play()) {
    long nf = millis() - f0;
    Serial.println(nf);
    mp.begin("foo2.avi");
    // GD.Clear();
    // GD.cmd_text(GD.w / 2, GD.h / 2, 31, OPT_CENTER, "fin");
    // GD.cmd_number(GD.w / 2, 200, 28, OPT_CENTER, nf);
    // GD.swap();
    // for (;;);
  }
#else

  mp.play();
  GD.cmd_videoframe(0, 0xe0000UL);

  GD.ClearColorRGB(0x103000);
  GD.Clear();
  GD.Begin(BITMAPS);
  GD.Vertex2ii(0, 20, 0, 0);

  // GD.BitmapHandle(3);
  // GD.cmd_setbitmap(0, RGB565, 480, 208);
  // GD.BitmapSource(0);
  // GD.BitmapSize(NEAREST, BORDER, BORDER, 480, 208);
  // GD.BitmapLayout(RGB565, 2 * 480, 208);

  GD.swap();
#endif
}
