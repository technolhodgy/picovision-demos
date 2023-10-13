import time
import pngdec
from picographics import PicoGraphics, PEN_RGB555, WIDESCREEN
import random


t_start = time.ticks_ms()

DISPLAY_WIDTH = 320
DISPLAY_HEIGHT = 240

FRAME_WIDTH=1280
FRAME_HEIGHT=720



# Palette Colours - Full Colour
PALETTE_COLOUR = [
    (0xff, 0xff, 0xff),
    (0x2f, 0x2c, 0x1e),
    (0xff, 0x00, 0x29),
    (0x41, 0x3d, 0x2e),
    (0x50, 0x4a, 0x30),
    (0x15, 0x68, 0x06),
    (0x12, 0x75, 0x00),
    (0x7f, 0x68, 0x03),
    (0x1a, 0x88, 0x05),
    (0x00, 0xbf, 0x00),
    (0x8b, 0x8b, 0x8b),
    (0xbf, 0x9c, 0x00),
    (0x06, 0xdc, 0x06),
    (0xdc, 0xb4, 0x06),
    (0xff, 0xff, 0xff),
    (0x3b, 0x32, 0x1d)
]

numModes = 16
currentMode = 0
modeSelect = 0
modes = [
   (320,240),
   (360,240),
   (360,288),
   (400,225),
   (400,240),
   (400,300),
   (480,270),
   (960,270),
   (640,480),
   (720,480),
   (720,576),
   (800,450),
   (800,480),
   (800,600),
   (960,540),
   (1280,720)
]

display = PicoGraphics(PEN_RGB555, DISPLAY_WIDTH, DISPLAY_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT)
png = pngdec.PNG(display)

modeChange = 0
button_y = machine.Pin(9, machine.Pin.IN, machine.Pin.PULL_UP)

BLACK    = display.create_pen(0, 0, 0)
WHITE    = display.create_pen(250, 250, 250)
DARKGREY = display.create_pen(32,32,32)
GREY     = display.create_pen(96,96,96)
SKYBLUE  = display.create_pen(32,32,192)
GREEN    = display.create_pen(32,192,32)

display.set_font("bitmap8")


while True:
    
   for p in range (2):
      display.set_pen(0)
      display.clear()
      
      for f in range (720):
         display.set_pen(display.create_pen(0, 0, int(f/3)))
         display.line(0,f,FRAME_WIDTH,f)  
      
      display.set_pen(WHITE)
      display.text("Pimoroni Screen Mode Selector",0,0,300,1)

      display.update()

   while True:
      if display.is_button_a_pressed():
         print("X is pressed")
         modeSelect -=1
         if modeSelect <0:
            modeSelect = numModes -1
         while display.is_button_a_pressed():
            m=0
      if display.is_button_x_pressed():
         print("A is pressed")
         modeSelect +=1
         if modeSelect > numModes-1:
            modeSelect = 0
         while display.is_button_x_pressed():
            m=0

      display.set_pen(DARKGREY)
      display.rectangle(14, 22, 137, numModes*10+14)
      for f in range(numModes):
         display.set_pen(GREY)
         if  f == modeSelect:
            if button_y.value():
               display.set_pen(SKYBLUE)
            else:
               modeChange = 1
               
         display.rectangle(20,f*10+29,125,10)
         display.set_pen(WHITE)
         modeText ="{width:} x {height:}".format(width=modes[f][0],height=modes[f][1])
         display.text(modeText,30,f*10+29,300,1)
         if  currentMode == f:
           display.text(">",22,f*10+29,300,1)
           display.text("<",137,f*10+29,300,1)

     
      display.update()
      if modeChange:
         display.set_pen(GREEN)
         display.rectangle(20,modeSelect*10+29,125,10)
         display.rectangle(30,0,125,10)
         display.set_pen(WHITE)
         display.text("Mode Change",30,modeSelect*10+29,300,1)
         while button_y.value() == 0:
             m=0
             display.update()
          
      
    
    
    
