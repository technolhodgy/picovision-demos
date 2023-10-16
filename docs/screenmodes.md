# PicoVision Demos - Screenmodes

### Setting up and changing screen modes.
You can get the full list of modes from the micropython docs.
https://github.com/pimoroni/picovision/blob/main/docs/hardware.md

I first wrote this in C++ and the Pirate overlords liked it and wanted to include with the the shiping firmare.
- [C++ example](screenmodes/main/cpp)

But the examples are all in micropython, so I created another version for that.
- [screenmodes.py](micropython/screenmodes.py)

I create an list of screen resolutions plus a flag of 0 for normal modes or 1 for widescreen.

Using button A and X will move up and down the list and Y will select.
After selection the PicoVision will stop the display and reset in the selected mode.
There is a time out (just like on you PC) just incase your monitor cannot display the mode.
Hoevery if you can see the mode change you can press Y again to confirm the selection.

If you are not using the WIDESCREEN buld of micropython, trying to select a WIDESCREEN mode will result in the selector turning that line RED and displaying 'unsupported Wide Only' message. 

