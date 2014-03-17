control-switch-matrix
=====================

A Windows command line tool to control the Ligawo(R) HDMI Matrix 4x2 Switch Matrix via Serial Connection (over USB)

HDMI Switch Matrix Controller 1.0 by eL_Bart0(-[at]-)dietunichtguten.org

**Usage**
sendToMatrix.exe COM-Port COMMAND.\n");

E.g.: sendToMatrix.exe com3 LED

Toggles the state of the LED display on Ligawo(R) HDMI Matrix 4x2\n\n");

**Available commands for the Ligawo(R) HDMI Matrix**
A1, A2, A3, A4, B1, B2, B3, B4, PW, 2C, 5C, CLE, MT, SA, SB, LED, SAV

Refer to the switches manual for their function.

**Additional Information**
This tool could possibly work with other HDMI switch matrices which support serial communication over USB.
Feel free to contact me if you come accross a similar designed device which is not yet supported.

Should your switchs manual list other codes, just give them a try. Basically this tool forwards every command directly over COM port.

-- eL_Bart0
