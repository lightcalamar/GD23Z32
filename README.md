GD23Z32 library for STM32Fx
===========================

Library for graphics GPU FT81x with MCU´s STM32Fx, Team FT81xmania, https://ft81xmania.com/comunidad/

FAQ
---

**How do I use GD with a 800x480 display?**

After calling ``GD.begin()`` you can set the scanout registers for 800x480 like this:

    GD.wr16(vc.REG_HCYCLE, 928);
    GD.wr16(vc.REG_HOFFSET, 88);
    GD.wr16(vc.REG_HSIZE, 800);
    GD.wr16(vc.REG_HSYNC0, 0);
    GD.wr16(vc.REG_HSYNC1, 48);
    GD.wr16(vc.REG_VCYCLE, 525);
    GD.wr16(vc.REG_VOFFSET, 32);
    GD.wr16(vc.REG_VSIZE, 480);
    GD.wr16(vc.REG_VSYNC0, 0);
    GD.wr16(vc.REG_VSYNC1, 3);
    GD.wr16(vc.REG_CSPREAD, 1);
    GD.wr16(vc.REG_DITHER, 1);
    GD.wr16(vc.REG_PCLK_POL, 0);
    GD.wr16(vc.REG_PCLK, 4);


**How do I change the select pin assignments?**

To change the GPU select from pin 8, modify ``#define CS`` at the start of ``transports/wiring.h``

To change microSD select from pin 9, modify ``#define SD_PIN`` at the start of ``GD2.cpp``

**How do you run in portrait mode?**

After calling ``GD.begin()`` set the orientation like this::

    GD.cmd_setrotate(2);

to enter portrait mode. The argument controls orientation, 0 and 1 are landscape. 2 and 3 are portrait.
