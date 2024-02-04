from picographics import PicoGraphics, PEN_RGB555, WIDESCREEN
import pngdec
from time import sleep
from machine import Pin, SPI
import sdcard
import os

# set up the SD card
sd_spi = SPI(1, sck=Pin(10, Pin.OUT), mosi=Pin(11, Pin.OUT), miso=Pin(12, Pin.OUT))
sd = sdcard.SDCard(sd_spi, Pin(15))
os.mount(sd, "/sd")

# dimentions for the screen
DISPLAY_WIDTH = 800
DISPLAY_HEIGHT = 480

# Optional FRAME size which is larger than the screen 
FRAME_WIDTH=1600
FRAME_HEIGHT=1280
SCROLL_OFFSET_START=657

#using namespace pimoroni;

# start the display with the PEN depth WIDTh and HEIGHT
##display = PicoGraphics(PEN_RGB555, DISPLAY_WIDTH, DISPLAY_HEIGHT)
# Optionaly we could add the FRAME dimentions to this with the 2 extra parameters passed at the end.
display = PicoGraphics(PEN_RGB555, DISPLAY_WIDTH, DISPLAY_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT)

# Lets set a bitmap font for text
display.set_font("bitmap8")


png = pngdec.PNG(display)
# define colours
# this could be done directly in line
# but this is easier
BLACK    = display.create_pen(0, 0, 0)
WHITE    = display.create_pen(250, 250, 250)

IMAGE = "/sd/chopin-scroll/output_000.png"
IMAGE2 = "/sd/chopin-scroll/output_005.png"
button_y = machine.Pin(9, machine.Pin.IN, machine.Pin.PULL_UP)
button_y = machine.Pin(9, machine.Pin.IN, machine.Pin.PULL_UP)

#with open("/sd/output.png", "r") as f:
#    data = f.read()
#    print(data)
#    f.close()
#try:
    #png.open_file(IMAGE)
    # cool crab is 500 x 255px - if your image is a different size you might need to tweak the position
#except OSError as e:
    #print(f"{e} - image not found.")
#try:
    #png.open_file(IMAGE2)
    # cool crab is 500 x 255px - if your image is a different size you might need to tweak the position
#except OSError as e:
    #print(f"{e} - image not found.")
    
    
    
for ff in range(2):
    display.set_pen(BLACK)
    display.clear()
    display.set_pen(WHITE)
    display.text("piano scroll.",0,95,320,1)
    
    display.update()

for ff in range(2):
    if ff ==0:
       png.open_file(IMAGE)  
    else:
       png.open_file(IMAGE2)  
    png.decode(2, 0)

    display.set_scroll_group_for_lines(1, 0, 260)
    display.set_scroll_group_for_lines(2, 262, 434)
    display.set_scroll_group_for_lines(3, 434, 480)
    display.set_scroll_group_for_lines(4, 260, 262)
    
    display.set_scroll_group_offset(1, 0, SCROLL_OFFSET_START)
    display.set_scroll_group_offset(2, 0, SCROLL_OFFSET_START)
    display.set_scroll_group_offset(3, 0, 660)
    display.set_scroll_group_offset(4, 0, 900)
    
    display.update()
    button = 0
    scroll_offset = SCROLL_OFFSET_START

display.update()

while True: 
     #button_y.value() == 1:
     #print("Y is pressed")
    sleep(0.02)
    if display.is_button_x_pressed():
        button = 3
    else:
        button = 0            
    if scroll_offset < 88:

        scroll_offset = scroll_offset = SCROLL_OFFSET_START
        display.update()
        
    #buffer.set_scroll_group_offset(1, 0, scroll_offset)
    display.set_scroll_group_offset(1, 0, scroll_offset)
    display.set_scroll_group_offset(2, 0, scroll_offset)
    scroll_offset = scroll_offset -1

    
while True:
    
    # set the pen to BLACK
    display.set_pen(BLACK)
    # The pen can also be setup directly inline with the following
    ## display.set_pen(display.create_pen(0, 0, 0)) "
    # But is is much easier to define if before our main content.
    
    # Lets clear the screen
    display.clear()
    # Not to set the pen to something that will contrast withne backgroud we just cleared.
    display.set_pen(WHITE)
    # Display some text at
    # X=0
    # y= 95
    # Length of 100 pixel ( this will wrapped at 320 crating multiplue line of not more than 320 pixls )
    # Font size of 1
    display.text("AHOY THERE, This is all you need to get something basic working.",0,95,320,1)
    
    # Update the screen
    # This will flip the buffers between the CPU and GPU
    display.update()
    # The Text we just wrote was on the CPU and flipping the butters we now see it dispalyed on screen
    # the anternate butffer is ready to be for content
    
    # Only one buffer can be seem by either the CPU or GPU at any one time
    # This means you may need to render somethings on both buffers or you may get a flickering effect

    # That it, just 13 lines of code and you are off.