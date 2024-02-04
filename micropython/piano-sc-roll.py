from picographics import PicoGraphics, PEN_RGB555, WIDESCREEN
import pngdec

# dimentions for the screen
DISPLAY_WIDTH = 640
DISPLAY_HEIGHT = 480

# Optional FRAME size which is larger than the screen 
## FRAME_WIDTH=640
## FRAME_HEIGHT=480

#using namespace pimoroni;

# start the display with the PEN depth WIDTh and HEIGHT
display = PicoGraphics(PEN_RGB555, DISPLAY_WIDTH, DISPLAY_HEIGHT)
# Optionaly we could add the FRAME dimentions to this with the 2 extra parameters passed at the end.
## display = PicoGraphics(PEN_RGB555, DISPLAY_WIDTH, DISPLAY_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT)

# Lets set a bitmap font for text
display.set_font("bitmap8")

png = pngdec.PNG(display)
# define colours
# this could be done directly in line
# but this is easier
BLACK    = display.create_pen(0, 0, 0)
WHITE    = display.create_pen(250, 250, 250)

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