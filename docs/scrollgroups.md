# PicoVision Demos - Screenmodes

###Setting up and changing Scroll Groups.

Using up to 7 scroll groups to get effects without using to much CPU or GPU time.

[scrollgroups.py](micropython/scrollgroups.py) is a demo showing off all 7 of the Scrollgroups in action.
While you iniialize your screen with DISPLAY_WIDTH & DISPLAY_HEIGHT 
- display = PicoGraphics(PEN_RGB555, DISPLAY_WIDTH, DISPLAY_HEIGHT)

To use Scroll Groups you can also add varibles for FRAME_WIDTH & FRAME HEIGHT which are larger than the screen area and can be moved via (X,Y) offsets.
- display = PicoGraphics(PEN_RGB555, DISPLAY_WIDTH, DISPLAY_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT)

The top 4 groups (1-4) create a parallax effect of four lines of clouds moving at diffent speeds.
This is achived by pre rendering 4 lines of clouds in 4 different sizes, and then changing nothing more than an (X) offset position to scroll the image accorss the screen. 

The botton 3 groups (5-7) are moving in both (X & Y) offsets to create a very simple wave effect.
Again prerended to screen by over lapping circles in shaeds of blue.

Scroll Group (0) is a static group and cannot be moved by an offset.
With group (0)  50 pixels high accross the screen the area is constantly cleared and redrawn every frame.
With the other 7 groups doing there thing with very little effort there is plenty CPU time to draw more than a little ship.

The Scroll Groups also can have wrapping positions to when either end of the wrap is reached the other end is wrapped around seamlessly.

Search Youtube for 'REM Shinny happy People' for an example of how realy old movie used the wrapped image background for a continuous movement effect.
This is basically what the Scroll Groups wrapping will do with Pixels, but they can wrap the X and the Y. 
If both are used at the same time you will have diagonal movment.



