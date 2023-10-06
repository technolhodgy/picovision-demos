#include "pico/stdlib.h"
#include <cstdio>
#include <iterator>
#include <sstream>

#include "drivers/dv_display/dv_display.hpp"
#include "libraries/pico_graphics/pico_graphics_dv.hpp"

#define DISPLAY_WIDTH 640
#define DISPLAY_HEIGHT 480
#define FRAME_WIDTH 640
#define FRAME_HEIGHT 720

const int numModes = 12;
int modeSelect =0;
int modes[numModes][2] = {
   {320,240},
   {360,240},
   {360,288},
   {400,240},
   {960,270},
   {640,480},
   {720,480},
   {720,576},
   {800,450},
   {800,600},
   {968,540},
   {1280,720}
};

/*
720 x 576 - 5:4 - PAL
720 x 480 - 3:2 - NTSC
640 x 480 - 4:3 - VGA
Widescreen Modes

800 x 450 - 16:9
800 x 480 - 5:3 - WVGA
800 x 600 - 4:3 - SVGA
960 x 540 @ 50Hz - 16:9 - 540p / qHD
1280 x 720 @ 30Hz - 16:9 - Limited compatibility with displays

Pixel-doubled Resolutions

320 x 240 - 4:3 (640 x 480) - HVGA - Good for DOS, NES, SNES, SMS, SMD
360 x 240 - 3:2 (720 x 480)
360 x 288 - 5:4 (720 x 576) - Close to CIF
400 x 240 - 5:3 (800 x 480) - WQVGA
960 x 270 - 32:9 (960 x 540)
*/
using namespace pimoroni;

DVDisplay display;
PicoGraphics_PenDV_RGB555 graphics(DISPLAY_WIDTH, DISPLAY_HEIGHT, display);

Pen BLACK = graphics.create_pen(0, 0, 0);
Pen WHITE = graphics.create_pen(255, 255, 255);
int f,p;
char text[30];

int main() {
    stdio_init_all();
    printf("Hello World\n");
    
   constexpr uint BUTTON_Y = 9;
   gpio_init(BUTTON_Y);
   gpio_set_dir(BUTTON_Y, GPIO_IN);
   gpio_pull_up(BUTTON_Y);
   
    printf("Init Video...\n");
    display.preinit();
    display.init(DISPLAY_WIDTH, DISPLAY_HEIGHT, DVDisplay::MODE_RGB555, FRAME_WIDTH, FRAME_HEIGHT);
    printf("Done!\n");

    graphics.set_font("bitmap8");

    for (p = 0 ; p<2 ; p++)
    {
      graphics.set_pen(BLACK);
      graphics.clear();
      
      for (f = 0 ; f<DISPLAY_HEIGHT ; f++)
      {
         graphics.set_pen(graphics.create_pen(0,0,f /3 ));
         graphics.pixel_span({0,f}, DISPLAY_WIDTH);
         
      }
      graphics.set_pen(WHITE);
      graphics.text("Screen Mode Selector", Point(0, 0), FRAME_WIDTH);
      display.flip();
   }
    
    while(true) 
    {
      for (p = 0 ; p<2 ; p++)
      {
         graphics.set_pen(graphics.create_pen(32,32,32));               
         graphics.rectangle({16,33,158,numModes*20+8});
         for (f = 0; f<numModes;f++)
         {
            if ( f == modeSelect)
            {
               graphics.set_pen(graphics.create_pen(32,32,192));               
               if (!gpio_get(BUTTON_Y)) {
                  graphics.set_pen(graphics.create_pen(32,192,32));    
               }
            } else {
               graphics.set_pen(graphics.create_pen(96,96,96));
            }
            graphics.rectangle({20,f*20+37,150,20});
            graphics.set_pen(WHITE);
            sprintf(text,"%i x %i",modes[f][0],modes[f][1]);
            graphics.text(text, Point(30, f*20+40), FRAME_WIDTH);
         }
      display.flip();
      }
         if(display.is_button_a_pressed())
         {
            modeSelect++;
            while(display.is_button_a_pressed())
            {}
         }
         if(display.is_button_x_pressed())
         {
            modeSelect--;
            while(display.is_button_x_pressed())
            {}
         }
         if ( modeSelect < 0 ) {
            modeSelect =numModes-1;
         }
         modeSelect = modeSelect % numModes;
    }
    

    
}
