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
int f,x,y;
char text[30];
int height = 30;
uint p;
int leds[8] = {0,0,0,0,0,0,0,0};

uint colours[16][3] = {
   {0,0,0},{0,0,192},{192,0,0},{192,0,192},{0,192,0},{0,192,192},{192,192,0},{192,192,192},
   {64,64,64},{0,0,255},{255,0,0},{255,0,255},{0,255,0},{0,255,255},{255,255,0},{255,255,255}
   
};

int main() {
   stdio_init_all();
   printf("Hello World\n");
   printf("Init Video...\n");
   display.preinit();
   display.init(DISPLAY_WIDTH, DISPLAY_HEIGHT, DVDisplay::MODE_RGB555, FRAME_WIDTH, FRAME_HEIGHT);
   printf("Done!\n");
   // DVDisplay::define_sprite(uint16_t sprite_data_idx, uint16_t width, uint16_t height, uint16_t* data)
//display.define_sprite(1, 16, 16, sprite1);
   
   constexpr uint BUTTON_Y = 9;
   gpio_init(BUTTON_Y);
   gpio_set_dir(BUTTON_Y, GPIO_IN);
   gpio_pull_up(BUTTON_Y);
   


   
   for (f = 0; f<2;f++)
   {

      graphics.set_pen(BLACK);
      graphics.clear();
      graphics.set_pen(WHITE);
      graphics.text("Hello PicoVision Boilerplate!", Point(0, 0), FRAME_WIDTH);
      display.flip();
   }
   while ( gpio_get(BUTTON_Y ) )
   {}

   for (f = 0; f<2;f++)
   {
         for (int x =0 ; x <480 ; x ++)
         {

            graphics.set_pen(graphics.create_pen(255-(x/2),255-(x/2),(x/2)+16));
            graphics.pixel_span({0,x}, FRAME_WIDTH);

            
         }
      display.flip();
   }
   //while ( true)
   //{
   
   int dd =0;
         for (f = 0; f<8;f++)
         {
            display.set_gpio_hi_dir(f,0);
            display.set_gpio_hi_pull_down(f,1);
 
         }
         display.set_gpio_29_dir(0);
         display.set_gpio_29_pull_up(1);
         
   while ( true)
   {
         //display.set_gpio_29_dir(1);
         //display.set_gpio_29_value(255);
         
         //display.set_gpio_29_dir(1);
         //display.set_gpio_29_value(0);
         p = display.get_gpio_hi();
            graphics.set_pen(BLACK); 
            graphics.rectangle({0,0,50,200});
         for (f=0;f<8;f++)
         {
            sprintf(text,"%u",p&(1<<f));
            graphics.set_pen(WHITE); 
            graphics.text(text, Point(0, f*20), FRAME_WIDTH);
         }
         display.enable_gpio_29_adc();
         // display.enable_gpio_29_adc() and display.get_gpio_29_adc()
         p = (display.get_gpio_29_adc()*1000)/3.3;
         
            sprintf(text,"%lu",p);
            graphics.set_pen(WHITE); 
            graphics.text(text, Point(0, 180), FRAME_WIDTH);
          
         display.flip();
         sleep_ms(50);
         for (f = 0; f<8;f++)
         {
          //  display.set_gpio_hi_dir(f,1);
         //   display.set_gpio_hi(f,1);
         }
         //display.set_gpio_29_dir(1);
         //display.set_gpio_29_value(0);
         //sleep_ms(100);


   //}
   }
   /*
   while(true) 
   {
      for (x=0; x <160;x++)
      {
         //for (f = 0; f<2;f++)
         //{
         display.setup_scroll_group(Point(0,    x),1,0,160,640,0);
         display.setup_scroll_group(Point(0,320-x),2,0,320,640,160);
         display.setup_scroll_group(Point(0,    x),3,0,480,640,320);
         //display.setup_scroll_group(Point(0,    0),4,0,500,640,440);
         //display.flip();
         sleep_ms(15);
      //}
      }
   }
   */
}
