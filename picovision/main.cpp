#include "pico/stdlib.h"
#include <cstdio>
#include <iterator>
#include <sstream>
#include "hardware/gpio.h"

#include "drivers/dv_display/dv_display.hpp"
#include "libraries/pico_graphics/pico_graphics_dv.hpp"


#define DISPLAY_WIDTH 640
#define DISPLAY_HEIGHT 480
#define FRAME_WIDTH 640
#define FRAME_HEIGHT 480

using namespace pimoroni;

DVDisplay display;
PicoGraphics_PenDV_RGB555 graphics(FRAME_WIDTH, FRAME_HEIGHT, display);

Pen BLACK = graphics.create_pen(0, 0, 0);
Pen WHITE = graphics.create_pen(255, 255, 255);

const uint16_t maxStars = 500;

int f,x,y,z,p,i;
float s,r;
int distance =0;

int height = 30;

uint colours[16][3] = {
   {0,0,0},{0,0,192},{192,0,0},{192,0,192},{0,192,0},{0,192,192},{192,192,0},{192,192,192},
   {64,64,64},{0,0,255},{255,0,0},{255,0,255},{0,255,0},{0,255,255},{255,255,0},{255,255,255}
   
};
int32_t points[maxStars][3];
int main() {
   stdio_init_all();
   printf("Hello World\n");

   
   printf("Init Video...\n");
   display.preinit();
   display.init(DISPLAY_WIDTH, DISPLAY_HEIGHT, DVDisplay::MODE_RGB555, FRAME_WIDTH, FRAME_HEIGHT);
   printf("Done!\n");
   
   for (p =0 ;p<2;p++)
   {
      graphics.set_pen(BLACK);
      graphics.clear();
      display.flip();
   }
   for (f =0 ;f<maxStars;f++)
   {
      points[f][0] = (rand()%256000)-128000;
      points[f][1] = (rand()%192000)-96000;
      points[f][2] = (rand()%1000);
   }

   
   while(true) 
   {
      graphics.set_pen(BLACK);
      graphics.clear();
      graphics.set_pen(WHITE);
      for (f=0; f <maxStars;f++)
      {
         z =points[f][2];
         i = (z+distance)%1000;
         x = (points[f][0])/(i); //*((z+distance)));
         y = (points[f][1])/(i); //*((z+distance)));
         
            p = 250-(i)/4; //250
            for (s = 1; s<6;s++)
            {
               r=1+(s/100);               
               graphics.set_pen(graphics.create_pen(p,p/s,p/s));
               graphics.pixel(Point(x*r+320,y*r+240));
               r=1-(s/100);               
               graphics.set_pen(graphics.create_pen(p/s,p/s,p));
               graphics.pixel(Point(x*r+320,y*r+240));
               /*r=1.03;
               graphics.set_pen(graphics.create_pen(p/2,p/2,p));
               graphics.pixel(Point(x*r+320,y*r+240));
               r=1.015;
               graphics.set_pen(graphics.create_pen(p/2,p/2,p));
               graphics.pixel(Point(x*r+320,y*r+240));
               r=0.985;
               graphics.set_pen(graphics.create_pen(p,p/2,p/2));
               graphics.pixel(Point(x*r+320,y*r+240));
               r=0.97;
               graphics.set_pen(graphics.create_pen(p,p/2,p/2));
               graphics.pixel(Point(x*r+320,y*r+240));
               r=0.95;
               graphics.set_pen(graphics.create_pen(p,p/5,p/5));
               graphics.pixel(Point(x*r+320,y*r+240));
               */
            }

            graphics.set_pen(graphics.create_pen(p,p,p));
            graphics.pixel(Point(x+320,y+240));

      }
      
      display.flip();
      sleep_ms(1);
      distance-=8;
      if (distance <0)
      {
         distance=999;
      }
   }
}
