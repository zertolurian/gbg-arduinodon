**ArduiNodon Documentation**

#### **Overview**

##### **What is this?**

This is a documentation of functions within the “ArduiNodon” Arduino library which is used to automate operations in Game Builder Garage using Mouse and Keyboard commands.

##### **How to use?**

The latest version of the library can be found [here](https://drive.google.com/drive/u/0/folders/12L4yaKkD2xbmFYjoMopuojUfn0_tv6xE)**.**  
Updates are also usually posted in the **Arduino Scripts for GBG** forum in the VideoDojo Discord server.

Right at the start of any script, resetScreen() must be called to initialize the screen position.  
Next, run all the Nodon creation commands first.  
Once all Nodons have been created, use createConnection() and createObjectConnection() to create all the necessary connections.  
Once all connections have been made, use editObject() to edit the position, rotation, size, and a few other settings.

It is recommended to run the script in X/Z view instead of X/Y so that Person Nodons are square-shaped and Objects don’t snap to Y=0.  
When calling a Shake Nodon, make sure one has been called beforehand so that the safety pop-up does not appear while the script is running.

##### **Changelog**

- 8/9/24  
  - v1.0 release  
- 6/12/26  
  - Documentation  
    - Fixed typo in createObjectConnection function  
    - Fixed Map Range Limits  
    - Fixed missing Visible parameter in Touch Sensor  
  - ArduiNodon Sketch v1.1  
    - Improved number inputting to avoid unnecessary digits  
    - Updated minimum delay for Switch 2 speed  
    - Fixed bug with inconsistent screen zoom  
    - Fixed \= Comparison not being created correctly  
    - Added overwriteMode and deleteNodon function  
    - Allowed repeated runs by re-pressing button  
    - Moved all function definitions to the bottom to reduce scrolling  
    - Added Offset Distance functionality for Camera Nodons  
    - Removed unnecessary delays when editing objects  
    - Added special handling for Texture Nodons with multiple connections  
  - ArduiNodon UI v1.0  
    - Released\!

#### **General User Functions**

##### **resetScreen**

**resetScreen(*posX*, *posZ*, *zoom*)**  
Initializes the mouse, screen position, and zoom.  
Parameters:

- **posX**: *float*, *range*: \[-100.0, 100.0\], *default*: 0.0  
  - World X coordinate of where the screen will be repositioned.  
- **posY**: *float*, *range*: \[-100.0, 100.0\], *default*: 0.0  
  - World Y or Z coordinate of where the screen will be repositioned.  
- **zoom**: *byte*, *range*: \[0, 23\], *default*: 4  
  - Number of times the screen will be zoomed in.  
  - Currently, the other functions in the library are only supported for zoom==4.

Notes:

- This must always be called immediately after startup.  
- The posX and posY parameters are rounded to the nearest 0.2, to snap exactly to the Nodon grid at zoom==4.  
- It is recommended to set the magnitudes of posX and posY to be less than or equal to 90.0 to ensure that no Nodons may be attempted to be placed outside the borders of the Programming Screen space.

##### **createConnection**

**createConnection(*gridX1*, *gridY1*, *gridX2*, *gridY2*, *inPort*, *outPort*)**  
Creates a signal connection between two Nodons.  
Parameters:

- **gridX1**: *byte*, *range*: \[0,18\]  
  - Grid X position of Nodon output port to grab connection from.  
- **gridY1**: *byte*, *range*: \[0,10\]  
  - Grid Y position of Nodon output port to grab connection from.  
- **gridX2**: *byte*, *range*: \[0,18\]  
  - Grid X position of Nodon input port to drag connection to.  
- **gridY2**: *byte*, *range*: \[0,10\]  
  - Grid Y position of Nodon input port to drag connection to.  
- **inPort**: *byte*, *range*: \[0, 3\], *default*: 0  
  - Defines which input port the connection will be dragged to the Nodon at *\[gridX2, gridY2\]*  
  - The following are the general mappings for each value:  
    - 0 \= middle/top  
    - 1 \= top  
    - 2 \= bottom/middle  
    - 3 \= bottom

| Input Count | inPort \== 0 | inPort \== 1 | inPort \== 2 | inPort \== 3 |
| :---- | :---: | :---: | :---: | :---: |
| One Input | Middle | ??? | Middle | Middle |
| Two Inputs | Top | Top | Bottom | Bottom |
| Three Inputs | Middle | Top | Bottom | Bottom |
| Four Inputs | Upper Middle | Top | Lower Middle | Bottom |

- **outPort**: *byte*, *range*: \[0, 2\], *default*: 0  
  - Defines which output port the connection will be taken from the Nodon at *\[gridX1, gridY1\]*  
  - The following are the general mappings for each value:  
    - 0 \= middle/top  
    - 1 \= top  
    - 2 \= bottom

| Output Count | outPort \== 0 | outPort \== 1 | outPort \== 2 |
| :---- | :---: | :---: | :---: |
| One Output | Middle | ??? | ??? |
| Two Outputs | Top | Top | Bottom |
| Three Outputs | Middle | Top | Bottom |

Notes:

- The default of inPort and outPort are 0 so that the parameters can be omitted when connecting between two middle ports, which is most of the time.  
  - The outPort parameter is put after the inPort parameter so that it can be omitted when connecting from a middle output port, which is the only port for most Nodons.  
- See [Characterization of createConnection](#characterization-of-createconnection) for more details

##### **createObjectConnection**

**createObjectConnection(*gridX1*, *gridY1*, *gridX2*, *gridY2*)**  
Creates an object connection between two Nodons.  
Parameters:

- **gridX1**: *byte*, *range*: \[0,18\]  
  - Grid X position of Nodon bottom port to grab connection from.  
- **gridY1**: *byte*, *range*: \[0,10\]  
  - Grid Y position of Nodon bottom port to grab connection from.  
- **gridX2**: *byte*, *range*: \[0,18\]  
  - Grid X position of Nodon top port to drag connection to.  
- **gridY2**: *byte*, *range*: \[0,10\]  
  - Grid Y position of Nodon top port to drag connection to.

Notes:

- Fortunately, bottom connections are always grabbed first regardless if there’s a top connection in the same spot.

##### **editObject** {#editobject}

**editObject(*gridX*, *gridY*, *sizeX*, *sizeY*, *sizeZ*, *rotX*, *rotY*, *rotZ*, *posX*, *posY*, *posZ*, *fancyAppearance, screenViewpoint*)**  
Edits the size, rotation, and position of a created Nodon. Can also edit the Appearance setting for Fancy Object Nodons.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position of Nodon to edit.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position of Nodon to edit.  
- **sizeX**: *float*, *range*: \[0.0, 200.0\], *default*: 0.0  
  - Value that the X size setting will be edited to.  
  - If set to 0.0, the X size setting will not be changed.  
  - Also used for X Offset Distance for Camera Nodons.  
- **sizeY**: *float*, *range*: \[0.0, 200.0\], *default*: 0.0  
  - Value that the Y size setting will be edited to.  
  - If set to 0.0, the Y size setting will not be changed.  
  - Also used for Y Offset Distance for Camera Nodons.  
- **sizeZ**: *float*, *range*: \[0.0, 200.0\], *default*: 0.0  
  - Value that the Z size setting will be edited to.  
  - If set to 0.0, the Z size setting will not be changed.  
  - Also used for Z Offset Distance for Camera Nodons.  
- **rotX**: *float*, *range*: \[-180.0, 180.0\], *default*: 0.0  
  - Value that the X rotation setting will be edited to.  
  - If set to 0.0, the X rotation setting will not be changed.  
- **rotY**: *float*, *range*: \[-180.0, 180.0\], *default*: 0.0  
  - Value that the Y rotation setting will be edited to.  
  - If set to 0.0, the Y rotation setting will not be changed.  
- **rotZ**: *float*, *range*: \[-180.0, 180.0\], *default*: 0.0  
  - Value that the Z rotation setting will be edited to.  
  - If set to 0.0, the Z rotation setting will not be changed.  
- **posX**: *float*, *range*: \[-100.0, 100.0\], *default*: 404.0  
  - Value that the X position setting will be edited to.  
  - If set to 404.0, the X position setting will not be changed.  
- **posY**: *float*, *range*: \[-100.0, 100.0\], *default*: 404.0  
  - Value that the Y position setting will be edited to.  
  - If set to 404.0, the Y position setting will not be changed.  
- **posZ**: *float*, *range*: \[-100.0, 100.0\], *default*: 404.0  
  - Value that the Z position setting will be edited to.  
  - If set to 404.0, the Z position setting will not be changed.  
- **fancyAppearance**: *byte*, *range*: \[0, 31\], *default*: 0  
  - (Fancy Object only) “Appearance” setting that the Fancy Object will be changed to.  
    - 0: Crate  
    - 1: Shipping Container  
    - 2: Dice  
    - 3: Panel  
    - 4: Treasure Chest  
    - 5: Television  
    - 6: Joy-Con (R)  
    - 7: Joy-Con (L)  
    - 8: Soccer Ball  
    - 9: Golf Ball  
    - 10: Balloon  
    - 11: Apple  
    - 12: Turnip  
    - 13: Fish  
    - 14: Fluffball  
    - 15: Alien  
    - 16: Traveler  
    - 17: Cheerleader  
    - 18: Diver  
    - 19: Mermaid  
    - 20: Robot  
    - 21: Sorceress  
    - 22: Yeti  
    - 23: Sumo Wrestler  
    - 24: Hoop  
    - 25: Arrow  
    - 26: Rocket  
    - 27: Pencil  
    - 28: Tuna  
    - 29: Chick  
    - 30: Hippo  
    - 31: Bear  
- **screenViewpoint**: *byte*, *range*: \[0, 2\], *default*: 0  
  - (Game Screen only) “Viewpoint” setting that the Game Screen will be changed to.  
    - **0: No change**  
    - 1: Side view  
    - 2: Overhead view

Notes:

- These settings are not set during Nodon creation since they may change the positions of the Nodon’s ports \- thus, this function must only be called once all connections have been made.  
- This also automatically locks the Nodon so that they won’t interfere with future editObject commands.  
- The size, rotation, and position parameters are ordered like that so that the rotation and especially the position parameters may be omitted when they do not need to be changed.  
- The ignore value for size is set to 0.0 since it is easy to remember and is not a valid size.  
- The ignore value for position is set to 404.0 since 0.0 is a valid position, so an easy to remember number larger than 100.0 was necessary.  
- The maximum size is 200 because of the World Nodon.

#### **Input Nodon Functions**

##### **createConstantNodon**

**createConstantNodon(*gridX*, *gridY*, *value*);**  
Create and place a Constant Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **value**: *float*, *range*: \[-1000.0, 1000.0\], *default*: 1.0  
  - “Output Value” setting value.

##### **createButtonNodon**

**createButtonNodon(*gridX*, *gridY*, *timing*, *controlNum*, *enA*, *enB*, *enX*, *enY*, *enRight*, *enDown*, *enUp*, *enLeft*, *enL*, *enR*, *enZL*, *enZR*, *enL3*, *enR3*, *enSLL*, *enSRL*, *enSLR*, *enSRR*);**  
Create and place a Button Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **timing**: *boolean*, *range*: \[0,1\], *default*: 1  
  - “Output Timing” setting.  
    - 0: On press  
    - **1: While pressed**  
- **controlNum**: *byte*, *range*: \[0,5\], *default*: 5  
  - “Controller Number” setting.  
    - 0: Controller 1  
    - 1: Controller 2  
    - 2: Controller 3  
    - 3: Controller 4  
    - 4: Console  
    - **5**: Auto  
- **enA**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “A” button setting.  
- **enB**: *boolean*, *range*: \[0,1\], *default*: 0  
  - Enables the “B” button setting.  
- **enX**: *boolean*, *range*: \[0,1\], *default*: 0  
  - Enables the “X” button setting.  
- **enY**: *boolean*, *range*: \[0,1\], *default*: 0  
  - Enables the “Y” button setting.  
- **enRight**: *boolean*, *range*: \[0,1\], *default*: 0  
  - Enables the “Right” button setting.  
- **enDown**: *boolean*, *range*: \[0,1\], *default*: 0  
  - Enables the “Down” button setting.  
- **enUp**: *boolean*, *range*: \[0,1\], *default*: 0  
  - Enables the “Up” button setting.  
- **enLeft**: *boolean*, *range*: \[0,1\], *default*: 0  
  - Enables the “Left” button setting.  
- **enL**: *boolean*, *range*: \[0,1\], *default*: 0  
  - Enables the “L” button setting.  
- **enR**: *boolean*, *range*: \[0,1\], *default*: 0  
  - Enables the “R” button setting.  
- **enZL**: *boolean*, *range*: \[0,1\], *default*: 0  
  - Enables the “ZL” button setting.  
- **enZR**: *boolean*, *range*: \[0,1\], *default*: 0  
  - Enables the “ZR” button setting.  
- **enL3**: *boolean*, *range*: \[0,1\], *default*: 0  
  - Enables the “L3” button setting.  
- **enR3**: *boolean*, *range*: \[0,1\], *default*: 0  
  - Enables the “R3” button setting.  
- **enSLL**: *boolean*, *range*: \[0,1\], *default*: 0  
  - Enables the left Joy-Con “SL” button setting.  
- **enSRL**: *boolean*, *range*: \[0,1\], *default*: 0  
  - Enables the left Joy-Con “SR” button setting.  
- **enSLR**: *boolean*, *range*: \[0,1\], *default*: 0  
  - Enables the right Joy-Con “SL” button setting.  
- **enSRR**: *boolean*, *range*: \[0,1\], *default*: 0  
  - Enables the right Joy-Con “SR” button setting.

Notes:

- By default, the Nodon will be set to only have “A” enabled.  
- A bit array wasn’t used here since it would be unintuitive what the order of bits would be when writing this function in the IDE.

##### **createStickNodon**

**createStickNodon(*gridX*, *gridY*, *controlNum*, *DorA*, *lowerIn*, *upperIn*, *dirResponse*, *LorR*);**  
Create and place a Stick Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **controlNum**: *byte*, *range*: \[0,5\], *default*: 5  
  - “Controller Number” setting.  
    - 0: Controller 1  
    - 1: Controller 2  
    - 2: Controller 3  
    - 3: Controller 4  
    - 4: Console  
    - **5: Auto**  
- **DorA**: *boolean*, *range*: \[0,1\], *default*: 1  
  - “Output” setting.  
    - 0: Digital  
    - **1: Analog**  
- **lowerIn**: *float*, *range*: \[0.0,1.0\], *default*: 0.1  
  - Lower “Range” setting value.  
- **upperIn**: *float*, *range*: \[0.0,1.0\], *default*: 1.0  
  - Upper “Range” setting value.  
- **dirResponse**: *byte*, *range*: \[0,6\], *default*: 5  
  - “Direction of Response” setting.  
    - 0: Any  
    - 1: Up  
    - 2: Down  
    - 3: Left  
    - 4: Right  
    - **5: Up/Down**  
    - 6: Left/Right  
- **LorR**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Which Stick?” setting.  
    - **0: Left Stick**  
    - 1: Right Stick

Notes:

- By default, the Nodon will be set to Left Stick, Up/Down.

##### **createIfTouchedNodon**

**createIfTouchedNodon(*gridX*, *gridY*, *timing*, *touchWhere*);**  
Create and place an If Touched Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **timing**: *boolean*, *range*: \[0,1\], *default*: 1  
  - “Output Timing” setting.  
    - 0: On touch  
    - **1: While touched**  
- **touchWhere**: *boolean*, *range*: \[0,1\], *default*: 1  
  - “Touch Where to Output?” setting.  
    - 0: This Nodon  
    - **1: Anywhere**

##### **createTouchPositionNodon**

**createTouchPositionNodon(*gridX*, *gridY*);**  
Create and place a Touch Position Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.

##### **createShakeNodon**

**createShakeNodon(*gridX*, *gridY*, *checkWhat*, *controlNum*, *DorA*, *lowerIn*, *upperIn*, *dirResponse*);**  
Create and place a Shake Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **checkWhat**: *byte*, *range*: \[0,3\], *default*: 0  
  - “Check What?” setting.  
    - **0: Auto**  
    - 1: Console  
    - 2: Joy-Con (L)  
    - 3: Joy-Con (R)  
- **controlNum**: *byte*, *range*: \[0,3\], *default*: 0  
  - “Controller Number” setting.  
    - **0: Controller 1**  
    - 1: Controller 2  
    - 2: Controller 3  
    - 3: Controller 4  
- **DorA**: *boolean*, *range*: \[0,1\], *default*: 1  
  - “Output” setting.  
    - 0: Digital  
    - **1: Analog**  
- **lowerIn**: *float*, *range*: \[0.0,1.0\], *default*: 0.1  
  - Lower “Range” setting value.  
- **upperIn**: *float*, *range*: \[0.0,1.0\], *default*: 1.0  
  - Upper “Range” setting value.  
- **dirResponse**: *byte*, *range*: \[0,6\], *default*: 6  
  - “Direction of Response” setting.  
    - 0: X-  
    - 1: X+  
    - 2: Y-  
    - 3: Y+  
    - 4: Z-  
    - 5: Z+  
    - **6: Any Direction**

Notes:

- The first time that a Shake Nodon is seen during a session of playing GBG causes a safety pop-up to show up, which would break the Arduino script. Make sure to see the pop-up first before using any scripts that call this Nodon.

##### **createTiltNodon**

**createTiltNodon(*gridX*, *gridY*, *checkWhat*, *controlNum*, *DorA*, *lowerIn*, *upperIn*, *axisRotation*, *mode*);**  
Create and place a Tilt Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **checkWhat**: *byte*, *range*: \[0,3\], *default*: 0  
  - “Check What?” setting.  
    - **0: Auto**  
    - 1: Console  
    - 2: Joy-Con (L)  
    - 3: Joy-Con (R)  
- **controlNum**: *byte*, *range*: \[0,3\], *default*: 0  
  - “Controller Number” setting.  
    - **0: Controller 1**  
    - 1: Controller 2  
    - 2: Controller 3  
    - 3: Controller 4  
- **DorA**: *boolean*, *range*: \[0,1\], *default*: 1  
  - “Output” setting.  
    - 0: Digital  
    - **1: Analog**  
- **lowerIn**: *float*, *range*: \[0.0,1.0\], *default*: 0.0  
  - Lower “Range” setting value.  
- **upperIn**: *float*, *range*: \[0.0,1.0\], *default*: 1.0  
  - Upper “Range” setting value.  
- **axisRotation**: *byte*, *range*: \[0,2\], *default*: 2  
  - “Axis of Rotation” setting.  
    - 0: X  
    - 1: Y  
    - **2: Z**  
- **mode**: *boolean*, *range*: \[0,1\], *default*: 1  
  - “Mode” setting.  
    - **0: Tilt**  
    - 1: Angle of rotation

##### **createIfFaceUpNodon**

**createIfFaceUpNodon(*gridX*, *gridY*, *checkWhat*, *controlNum*, *DorA*, *lowerIn*, *upperIn*, *whichSide*);**  
Create and place an If Face Up Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **checkWhat**: *byte*, *range*: \[0,3\], *default*: 0  
  - “Check What?” setting.  
    - **0: Auto**  
    - 1: Console  
    - 2: Joy-Con (L)  
    - 3: Joy-Con (R)  
- **controlNum**: *byte*, *range*: \[0,3\], *default*: 0  
  - “Controller Number” setting.  
    - **0: Controller 1**  
    - 1: Controller 2  
    - 2: Controller 3  
    - 3: Controller 4  
- **DorA**: *boolean*, *range*: \[0,1\], *default*: 1  
  - “Output” setting.  
    - 0: Digital  
    - **1: Analog**  
- **lowerIn**: *float*, *range*: \[0.0,1.0\], *default*: 0.5  
  - Lower “Range” setting value.  
- **upperIn**: *float*, *range*: \[0.0,1.0\], *default*: 1.0  
  - Upper “Range” setting value.  
- **whichSide**: *byte*, *range*: \[0,5\], *default*: 1  
  - “Axis of Rotation” setting.  
    - 0: Left  
    - **1: Front**  
    - 2: Top  
    - 3: Right  
    - 4: Back  
    - 5: Bottom

##### **createRotationSpeedNodon**

**createRotationSpeedNodon(*gridX*, *gridY*, *checkWhat*, *controlNum*, *DorA*, *lowerIn*, *upperIn*, *axisRotation*, *dirResponse*);**  
Create and place a Rotation Speed Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **checkWhat**: *byte*, *range*: \[0,3\], *default*: 0  
  - “Check What?” setting.  
    - **0: Auto**  
    - 1: Console  
    - 2: Joy-Con (L)  
    - 3: Joy-Con (R)  
- **controlNum**: *byte*, *range*: \[0,3\], *default*: 0  
  - “Controller Number” setting.  
    - **0: Controller 1**  
    - 1: Controller 2  
    - 2: Controller 3  
    - 3: Controller 4  
- **DorA**: *boolean*, *range*: \[0,1\], *default*: 1  
  - “Output” setting.  
    - 0: Digital  
    - **1: Analog**  
- **lowerIn**: *float*, *range*: \[0.0,1.0\], *default*: 0.1  
  - Lower “Range” setting value.  
- **upperIn**: *float*, *range*: \[0.0,1.0\], *default*: 1.0  
  - Upper “Range” setting value.  
- **axisRotation**: *byte*, *range*: \[0,2\], *default*: 2  
  - “Axis of Rotation” setting.  
    - 0: X  
    - 1: Y  
    - **2: Z**  
    - 3: Any  
- **dirResponse**: *byte*, *range*: \[0,2\], *default*: 2  
  - “Direction of Response” setting.  
    - 0: \+  
    - 1: \-  
    - **2: \+/-**

##### **createIRMotionCameraNodon**

**createIRMotionCameraNodon(*gridX*, *gridY*, *controlNum*, *disRecognize*, *mirrored*);**  
Create and place a IR Motion Camera Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **controlNum**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Controller Number” setting.  
    - **0: Controller 1**  
    - 1: Controller 2  
- **disRecognize**: *byte*, *range*: \[0,3\], *default*: 2  
  - “Distance to Recognize” setting.  
    - 0: IR off  
    - 1: Near  
    - **2: Normal**  
    - 3: Near & far  
- **mirrored**: *boolean*, *range*: \[0,1\], *default*: 0  
  - Enables the “↔” setting.

##### **createObjectBreakNodon**

**createObjectBreakNodon(*gridX*, *gridY*, *checkNormal*, *checkFancy*);**  
Create and place an Object Break Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **checkNormal**: *byte*, *range*: \[0, 63\], *default*: 7  
  - Bit array to enable non-Fancy Objects in the “Check What?” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **checkFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 0  
  - Bit array to enable Fancy Objects in the “Check What?” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details

##### **createOnStartNodon**

**createOnStartNodon(*gridX*, *gridY*);**  
Create and place an On Start Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.

#### **Middle Nodon Functions**

##### **createCalculatorNodon**

**createCalculatorNodon(*gridX*, *gridY*, *calcMethod*);**  
Create and place a Calculator Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **calcMethod**: *byte*, *range*: \[0, 3\], *default*: 0  
  - “Calculation Method” setting.  
    - **0: \+**  
    - 1: −  
    - 2: ×  
    - 3: ÷

##### **createMapNodon**

**createMapNodon(*gridX*, *gridY*, *lowerIn*, *upperIn*, *lowerOut*, *upperOut*, *invert*, *limitless*);**  
Create and place a Map Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **lowerIn**: *float*, *range*: \[-1000.0,1000.0\], *default*: 0.0  
  - Lower “Input Range” setting value.  
- **upperIn**: *float*, *range*: \[-1000.0,1000.0\], *default*: 1.0  
  - Upper “Input Range” setting value.  
- **lowerOut**: *float*, *range*: \[-1000.0,1000.0\], *default*: \-1.0  
  - Lower “Output Range” setting value.  
- **upperOut**: *float*, *range*: \[-1000.0,1000.0\], *default*: 1.0  
  - Upper “Output Range” setting value.  
- **invert**: *boolean*, *range*: \[0,1\], *default*: 0  
  - Enables the “↔” setting.  
- **limitless**: *boolean*, *range*: \[0,1\], *default*: 1  
  - “Range Restriction” setting.  
    - 0: Enable  
    - **1: Disable**

Notes:

- As a rule of thumb, parameter index 0 is assigned to the leftmost option for non-toggleable settings \- the “Range Restriction” setting is oddly not a toggleable option and is a binary choice, with the left option being “Enable”.  
- There is an extra check in the code to determine if the lower or upper parameter should be set first, since the default settings limit what values can be inputted into the ranges first.

##### **createDigitizeNodon**

**createDigitizeNodon(*gridX*, *gridY*, *stages*);**  
Create and place a Digitize Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **stages**: *byte*, *range*: \[2,50\], *default*: 2  
  - “Stages” setting value.

##### **createSquareRootNodon**

**createSquareRootNodon(*gridX*, *gridY*);**  
Create and place a Square Root Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.

##### **createAbsoluteValueNodon**

**createAbsoluteValueNodon(*gridX*, *gridY*);**  
Create and place an Absolute Value Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.

##### **createInversionNodon**

**createInversionNodon(*gridX*, *gridY*);**  
Create and place a \+- Inversion Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.

##### **createTriggerFrom0Nodon**

**createTriggerFrom0Nodon(*gridX*, *gridY*);**  
Create and place a Trigger from 0 Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.

##### **createPositionToAngleNodon**

**createPositionToAngleNodon(*gridX*, *gridY*);**  
Create and place a Position → Angle Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.

##### **createAngleToPositionNodon**

**createAngleToPositionNodon(*gridX*, *gridY*);**  
Create and place an Angle → Position Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.

##### **createAngleDifferenceNodon**

**createAngleDifferenceNodon(*gridX*, *gridY*);**  
Create and place an Angle Difference Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.

##### **createComparisonNodon**

**createComparisonNodon(*gridX*, *gridY*, *method*);**  
Create and place a Comparison Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **method**: *byte*, *range*: \[0,4\], *default*: 0  
  - “Comparison Method” setting.  
    - **0: \=**  
    - 1: \>  
    - 2: \<  
    - 3: ≥  
    - 4: ≤

Notes:

- In the Nodon menu, the \< Comparison is listed before the \> Comparison; inside the Comparison Nodon settings however, it is the opposite and that is what’s used as the order in the method parameter

##### **createANDNodon**

**createANDNodon(*gridX*, *gridY*);**  
Create and place a AND Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.

##### **createNOTNodon**

**createNOTNodon(*gridX*, *gridY*);**  
Create and place a NOT Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.

##### **createFlagNodon**

**createFlagNodon(*gridX*, *gridY*);**  
Create and place a Flag Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.

##### **createCounterNodon**

**createCounterNodon(*gridX*, *gridY*, *startVal*, *mode*, *lowerRange*, *upperRange*, *timing*);**  
Create and place a Counter Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **startVal**: *int*, *range*: \[-1000,1000\], *default*: 0  
  - “Starting Value” setting value.  
- **mode**: *byte*, *range*: \[0,3\], *default*: 0  
  - “Mode” setting.  
    - **0: No limit**  
    - 1: Range  
    - 2: Loop  
    - 3: Bounce  
- **lowerRange**: *int*, *range*: \[-1000,1000\], *default*: 0  
  - Lower “Count Range” setting value.  
- **upperRange**: *int*, *range*: \[-1000,1000\], *default*: 1000  
  - Upper “Count Range” setting value.  
- **timing**: *boolean*, *range*: \[0,1\], *default*: 1  
  - “Count Timing” setting.  
    - 0: On change from 0  
    - **1: While not 0**

##### **createRandomNodon**

**createRandomNodon(*gridX*, *gridY*, *timing*, *outputRange*);**  
Create and place a Random Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **timing**: *boolean*, *range*: \[0,1\], *default*: 1  
  - “Update Timing” setting.  
    - 0: On change from 0  
    - **1: While not 0**  
- **outputRange**: *int*, *range*: \[1,1000\], *default*: 10  
  - “Output Range” setting value.

##### **createTimerNodon**

**createTimerNodon(*gridX*, *gridY*, *outDelay*, *outDuration*);**  
Create and place a Timer Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **outDelay**: *float*, *range*: \[0.0,100.0\], *default*: 1.0  
  - “Output after How Many Seconds?” setting value.  
- **outDuration**: *float*, *range*: \[0.0,100.0\], *default*: 0.0  
  - “Continue Output for How Long?” setting value.

##### **createBullseyeNodon**

**createBullseyeNodon(*gridX*, *gridY*, *DorA*, *lowerRange*, *upperRange*, *eyeShape*);**  
Create and place a Bull’s-Eye Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **DorA**: *boolean*, *range*: \[0,1\], *default*: 1  
  - “Output” setting.  
    - 0: Digital  
    - **1: Analog**  
- **lowerRange**: *float*, *range*: \[0.0,1.0\], *default*: 0.0  
  - Lower “Range” setting value.  
- **upperRange**: *float*, *range*: \[0.0,1.0\], *default*: 1.0  
  - Upper “Range” setting value.  
- **eyeShape**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Bull’s-Eye Shape” setting.  
    - **0: Circle**  
    - 1: Rectangle

Notes:

- There is currently no functionality to resize and move Nodons for Marker logic.

##### **createWormholeEntranceNodon**

**createWormholeEntranceNodon(*gridX*, *gridY*, *id*);**  
Create and place a Wormhole Entrance Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **id**: *byte*, *range*: \[0,25\], *default*: 0  
  - “Wormhole ID” setting.  
    - **0: A**  
    - 1: B  
    - 2: C  
    - 3: D  
    - 4: E  
    - 5: F  
    - 6: G  
    - 7: H  
    - 8: I  
    - 9: J  
    - 10: K  
    - 11: L  
    - 12: M  
    - 13: N  
    - 14: O  
    - 15: P  
    - 16: Q  
    - 17: R  
    - 18: S  
    - 19: T  
    - 20: U  
    - 21: V  
    - 22: W  
    - 23: X  
    - 24: Y  
    - 25: Z

##### **createWormholeExitNodon**

**createWormholeExitNodon(*gridX*, *gridY*, *id*);**  
Create and place a Wormhole Exit Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **id**: *byte*, *range*: \[0,25\], *default*: 0  
  - “Wormhole ID” setting.  
    - **0: A**  
    - 1: B  
    - 2: C  
    - 3: D  
    - 4: E  
    - 5: F  
    - 6: G  
    - 7: H  
    - 8: I  
    - 9: J  
    - 10: K  
    - 11: L  
    - 12: M  
    - 13: N  
    - 14: O  
    - 15: P  
    - 16: Q  
    - 17: R  
    - 18: S  
    - 19: T  
    - 20: U  
    - 21: V  
    - 22: W  
    - 23: X  
    - 24: Y  
    - 25: Z

##### **createCommentNodon**

**createCommentNodon(*gridX*, *gridY*, *comment*);**  
Create and place a Comment Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **comment**: *String*, *default*: “Comment”  
  - “Comment” setting.

#### **Output Nodon Functions**

##### **createPlaySoundNodon**

**createPlaySoundNodon(*gridX*, *gridY*, *category*, *subColumn, subRow*);**  
Create and place a Play Sound Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **category**: *byte*, *range*: \[0,25\], *default*: 11  
  - “Effects” or “Keyboard Instruments” setting.  
    - 0: Percussion  
    - 1: Alarms  
    - 2: Machines  
    - 3: Collision  
    - 4: Funny  
    - 5: System sounds  
    - 6: Ambient  
    - 7: Animals  
    - 8: Voice  
    - 9: SFX  
    - 10: Jingles  
    - 11: Piano  
    - 12: Organ  
    - 13: Trumpet  
    - 14: Recorder  
    - 15: Harp  
    - 16: Violin  
    - 17: Violin (spiccato)  
    - 18: Acoustic guitar  
    - 19: Electric guitar  
    - 20: Muted guitar  
    - 21: Bell  
    - 22: Chiptune  
    - 23: Cat  
    - 24: Man  
    - 25: Woman  
- **subColumn**: *byte*, *range*: \[0,12\], *default*: 0  
  - If the category setting is 10 or less, this will dictate the column of the sound that will be selected, starting from the left at 0\.  
  - If the category setting is 11 or greater, this will dictate the pitch setting.  
    - 0: C  
    - 1: C\#  
    - 2: D  
    - 3: D\#  
    - 4: E  
    - 5: F  
    - 6: F\#  
    - 7: G  
    - 8: G\#  
    - 9: A  
    - 10: A\#  
    - 11: B  
    - 12: High C  
- **subRow**: *byte*, *range*: \[0,5\], *default*: 0  
  - The row of the sound that will be selected, starting from the top at 0\.

##### **createBackgroundMusicNodon**

**createBackgroundMusicNodon(*gridX*, *gridY*, *theme*, *melody*, *mainAcc*, *subAcc*, *rhythm*);**  
Create and place a Background Music Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **theme**: *byte*, *range*: \[0,10\], *default*: 6  
  - “Theme” setting.  
    - 0: Strolling  
    - 1: Skipping  
    - 2: Steady  
    - 3: Sunshine  
    - 4: Valor  
    - 5: Tension  
    - **6: Excited**  
    - 7: Mad dash  
    - 8: Party time  
    - 9: Rivalry  
    - 10: Ambient  
- **melody**: *byte*, *range*: \[0,3\], *default*: 0  
  - “Melody” setting.  
    - **0: Row 1**  
    - 1: Row 2   
    - 2: Row 3  
    - 3: Silent  
- **mainAcc**: *byte*, *range*: \[0,3\], *default*: 0  
  - “Main Accompaniment” setting.  
    - **0: Row 1**  
    - 1: Row 2   
    - 2: Row 3  
    - 3: Silent  
- **subAcc**: *byte*, *range*: \[0,3\], *default*: 0  
  - “Sub Accompaniment” setting.  
    - **0: Row 1**  
    - 1: Row 2   
    - 2: Row 3  
    - 3: Silent  
- **rhythm**: *byte*, *range*: \[0,3\], *default*: 0  
  - “Rhythm” setting.  
    - **0: Row 1**  
    - 1: Row 2   
    - 2: Row 3  
    - 3: Silent

##### **createVibrationNodon**

**createVibrationNodon(*gridX*, *gridY*, *controlNum*, *LorR*, *freq*);**  
Create and place a Vibration Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **controlNum**: *byte*, *range*: \[0,4\], *default*: 0  
  - “Controller Number” setting.  
    - 0: Controller 1  
    - 1: Controller 2  
    - 2: Controller 3  
    - 3: Controller 4  
    - **4: Console**  
- **LorR**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Which Controller?” setting.  
    - **0: Joy-Con (L)**  
    - 1: Joy-Con (R)  
- **outDuration**: *float*, *range*: \[0.0,100.0\], *default*: 0.0  
  - “Continue output for How Long?” setting value.  
- **freq**: *int*, *range*: \[40,1280\], *default*: 170  
  - “Frequency” setting value.

##### **createReduceGravityNodon**

**createReduceGravityNodon(*gridX*, *gridY*);**  
Create and place a Reduce Gravity Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.

##### **createSlowTimeNodon**

**createSlowTimeNodon(*gridX*, *gridY*);**  
Create and place a Slow Time Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.

##### **createRetryNodon**

**createRetryNodon(*gridX*, *gridY*, *transition*);**  
Create and place a Retry Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **transition**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Transition Effect” setting.  
    - **0: Default**  
    - 1: Blink  
    - 2: Iris Shot

Notes:

- This Nodon is called “Retry Game” in the menu, but simply “Retry” everywhere else; I stuck with the latter.

##### **createEndGameNodon**

**createEndGameNodon(*gridX*, *gridY*);**  
Create and place a End Game Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.

##### **createSwapGameNodon**

**createSwapGameNodon(*gridX*, *gridY*, *swapType*, *targetKeyword*, *gameKeyword*, *transition*);**  
Create and place a Swap Game Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **swapType**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Swap Type” setting.  
    - **0: Keyword**  
    - 1: Back to previous  
- **targetKeyword**: *String*, *default*: “”  
  - “Swap-Target Keyword” setting.  
- **gameKeyword**: *String*, *default*: “”  
  - “Game Keyword” setting.  
- **transition**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Transition Appearance” setting.  
    - **0: With title**  
    - 1: Without title

##### **createMarkerDisplayNodon**

**createMarkerDisplayNodon(*gridX*, *gridY*);**  
Create and place a Marker Display Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **mode**: *byte*, *range*: \[0,6\], *default*: 0  
  - “Light Up How?” setting.  
    - **0: Move**  
    - 1: Extend  
    - 2: Line  
    - 3: Rotate  
    - 4: Pie Chart  
    - 5: Opacity  
    - 6: Flash  
- **actBullseye**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Activates Bull’s-Eye Nodon?” setting.  
    - **0: Bull’s-eye compatible**  
    - 1: Bull’s-eye incompatible

Notes:

- There is currently no functionality to resize and move Nodons for Marker logic.

##### **create2DMarkerDisplayNodon**

**create2DMarkerDisplayNodon(*gridX*, *gridY*, *DorA*, *lowerRange*, *upperRange*, *markerSize*, *actBullseye*);**  
Create and place a 2D Marker Display Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **DorA**: *boolean*, *range*: \[0,1\], *default*: 1  
  - “Output” setting.  
    - 0: Digital  
    - **1: Analog**  
- **lowerRange**: *float*, *range*: \[0.0,1.0\], *default*: 0.0  
  - Lower “Range” setting value.  
- **upperRange**: *float*, *range*: \[0.0,1.0\], *default*: 1.0  
  - Upper “Range” setting value.  
- **markerSize**: *float*, *range*: \[0.0,1.0\], *default*: 0.1  
  - Upper “Range” setting value.  
- **actBullseye**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Activates Bull’s-Eye Nodon?” setting.  
    - **0: Bull’s-eye compatible**  
    - 1: Bull’s-eye incompatible

Notes:

- There is currently no functionality to resize and move Nodons for Marker logic.

##### **createContinuousMarkerDisplayNodon**

**createContinuousMarkerDisplayNodon(*gridX*, *gridY*, *actBullseye*);**  
Create and place a Continuous Marker Display Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **actBullseye**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Activates Bull’s-Eye Nodon?” setting.  
    - **0: Bull’s-eye compatible**  
    - 1: Bull’s-eye incompatible

Notes:

- There is currently no functionality to resize and move Nodons for Marker logic.

##### **createIRLightNodon**

**createIRLightNodon(*gridX*, *gridY*, *controlNum*, *outDuration*);**  
Create and place an IR Light Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **controlNum**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Controller Number” setting.  
    - **0: Controller 1**  
    - 1: Controller 2  
- **outDuration**: *float*, *range*: \[0.0,100.0\], *default*: 0.0  
  - “Continue output for How Long?” setting value.

#### **Object Nodon Functions**

##### **createPersonNodon**

**createPersonNodon(*gridX*, *gridY*, *visible*, *solid*, *destructibleNormal*, *destructibleFancy*, *destructiveNormal*, *destructiveFancy*, *silent*, *ungrabbable*, *color*, *referenceFrame*, *action*, *movementSpeed*, *jumpStrength*, *turningSpeed*);**  
Create and place a Person Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **visible**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Visible” setting.  
- **solid**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Solid” setting.  
- **destructibleNormal**: *byte*, *range*: \[0, 255\], *default*: 0  
  - Bit array to enable non-Fancy Objects in the “Destructible” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructibleFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 0  
  - Bit array to enable Fancy Objects in the “Destructible” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructiveNormal**: *byte*, *range*: \[0, 63\], *default*: 0  
  - Bit array to enable non-Fancy Objects in the “Destructive” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructiveFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 0  
  - Bit array to enable Fancy Objects in the “Destructive” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **silent**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Play Sound When Hit/Destroyed?” setting.  
    - **0: Play**  
    - 1: Don’t Play  
- **ungrabbable**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Can Be Grabbed by Hand Nodon?” setting.  
    - **0: Can be grabbed**  
    - 1: Can’t be grabbed  
- **color**: *byte*, *range*: \[0,12\], *default*: 0  
  - “Color” setting.  
    - **0: Auto**  
    - 1: Blue  
    - 2: Red  
    - 3: Green  
    - 4: Yellow  
    - 5: Light blue  
    - 6: Pink  
    - 7: Lime green  
    - 8: Orange  
    - 9: Purple  
    - 10: Brown  
    - 11: White  
    - 12: Black  
- **referenceFrame**: *boolean*, *range*: \[0,1\], *default*: 1  
  - “Frame of Reference for Motion” setting.  
    - 0: World  
    - **1: Camera**  
- **action**: *byte*, *range*: \[0,3\], *default*: 0  
  - “Action” setting.  
    - **0: Celebrate**  
    - 1: Punch  
    - 2: Kick  
    - 3: Turn  
- **movementSpeed**: *float*, *range*: \[0.0,2.0\], *default*: 1.0  
  - “Movement Speed” setting value.  
- **jumpStrength**: *float*, *range*: \[0.0,4.0\], *default*: 1.0  
  - “Jump Strength” setting value.  
- **turningSpeed**: *float*, *range*: \[0.0,1.0\], *default*: 0.1  
  - “Turning Speed” setting value.

Notes:

- When calling this Nodon, make sure to be in X/Z view and not X/Y view, as the script was characterized for a square-shaped Person Nodon.

##### **createCarNodon**

**createCarNodon(*gridX*, *gridY*, *visible*, *solid*, *destructibleNormal*, *destructibleFancy*, *destructiveNormal*, *destructiveFancy*, *silent*, *ungrabbable*, *color*, *movementSpeed*, *jumpStrength*);**  
Create and place a Car Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **visible**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Visible” setting.  
- **solid**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Solid” setting.  
- **destructibleNormal**: *byte*, *range*: \[0, 255\], *default*: 0  
  - Bit array to enable non-Fancy Objects in the “Destructible” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructibleFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 0  
  - Bit array to enable Fancy Objects in the “Destructible” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructiveNormal**: *byte*, *range*: \[0, 63\], *default*: 0  
  - Bit array to enable non-Fancy Objects in the “Destructive” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructiveFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 0  
  - Bit array to enable Fancy Objects in the “Destructive” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **silent**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Play Sound When Hit/Destroyed?” setting.  
    - **0: Play**  
    - 1: Don’t Play  
- **ungrabbable**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Can Be Grabbed by Hand Nodon?” setting.  
    - **0: Can be grabbed**  
    - 1: Can’t be grabbed  
- **color**: *byte*, *range*: \[0,12\], *default*: 0  
  - “Color” setting.  
    - **0: Auto**  
    - 1: Blue  
    - 2: Red  
    - 3: Green  
    - 4: Yellow  
    - 5: Light blue  
    - 6: Pink  
    - 7: Lime green  
    - 8: Orange  
    - 9: Purple  
    - 10: Brown  
    - 11: White  
    - 12: Black  
- **movementSpeed**: *float*, *range*: \[0.0,2.0\], *default*: 1.0  
  - “Movement Speed” setting value.  
- **jumpStrength**: *float*, *range*: \[0.0,2.0\], *default*: 1.0  
  - “Jump Strength” setting value.

Notes:

- This Nodon is automatically shrunk to a size of 0.8x0.8x0.8 to fit with the other Nodons on the grid.

##### **createUFONodon**

**createUFONodon(*gridX*, *gridY*, *visible*, *solid*, *destructibleNormal*, *destructibleFancy*, *destructiveNormal*, *destructiveFancy*, *silent*, *ungrabbable*, *color*, *referenceFrame*, *horizontalSpeed*, *verticalSpeed*, *turningSpeed*);**  
Create and place a UFO Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **visible**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Visible” setting.  
- **solid**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Solid” setting.  
- **destructibleNormal**: *byte*, *range*: \[0, 255\], *default*: 0  
  - Bit array to enable non-Fancy Objects in the “Destructible” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructibleFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 0  
  - Bit array to enable Fancy Objects in the “Destructible” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructiveNormal**: *byte*, *range*: \[0, 63\], *default*: 0  
  - Bit array to enable non-Fancy Objects in the “Destructive” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructiveFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 0  
  - Bit array to enable Fancy Objects in the “Destructive” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **silent**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Play Sound When Hit/Destroyed?” setting.  
    - **0: Play**  
    - 1: Don’t Play  
- **ungrabbable**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Can Be Grabbed by Hand Nodon?” setting.  
    - **0: Can be grabbed**  
    - 1: Can’t be grabbed  
- **color**: *byte*, *range*: \[0,12\], *default*: 0  
  - “Color” setting.  
    - **0: Auto**  
    - 1: Blue  
    - 2: Red  
    - 3: Green  
    - 4: Yellow  
    - 5: Light blue  
    - 6: Pink  
    - 7: Lime green  
    - 8: Orange  
    - 9: Purple  
    - 10: Brown  
    - 11: White  
    - 12: Black  
- **referenceFrame**: *boolean*, *range*: \[0,1\], *default*: 1  
  - “Frame of Reference for Motion” setting.  
    - 0: World  
    - **1: Camera**  
- **horizontalSpeed**: *float*, *range*: \[0.0,2.0\], *default*: 1.0  
  - “Movement Speed” setting value.  
- **verticalSpeed**: *float*, *range*: \[0.0,2.0\], *default*: 1.0  
  - “Jump Strength” setting value.  
- **turningSpeed**: *float*, *range*: \[0.0,1.0\], *default*: 0.1  
  - “Turning Speed” setting value.

##### **createObjectNodon**

**createObjectNodon(*gridX*, *gridY*, *shape*, *visible*, *solid*, *movable*, *destructibleNormal*, *destructibleFancy*, *destructiveNormal*, *destructiveFancy*, *silent*, *ungrabbable*, *color*, *material*, *connectionType*, *connectionOwn*, *connectionTarget*);**  
Create and place an Object Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **shape**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Object Shape” setting.  
    - **0: Box**  
    - 1: Cylinder  
    - 2: Sphere  
- **visible**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Visible” setting.  
- **solid**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Solid” setting.  
- **movable**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Movable” setting.  
- **destructibleNormal**: *byte*, *range*: \[0, 255\], *default*: 255  
  - Bit array to enable non-Fancy Objects in the “Destructible” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructibleFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 4294967295  
  - Bit array to enable Fancy Objects in the “Destructible” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructiveNormal**: *byte*, *range*: \[0, 63\], *default*: 63  
  - Bit array to enable non-Fancy Objects in the “Destructive” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructiveFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 4294967295  
  - Bit array to enable Fancy Objects in the “Destructive” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **silent**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Play Sound When Hit/Destroyed?” setting.  
    - **0: Play**  
    - 1: Don’t Play  
- **ungrabbable**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Can Be Grabbed by Hand Nodon?” setting.  
    - **0: Can be grabbed**  
    - 1: Can’t be grabbed  
- **color**: *byte*, *range*: \[0,12\], *default*: 0  
  - “Color” setting.  
    - **0: Auto**  
    - 1: Blue  
    - 2: Red  
    - 3: Green  
    - 4: Yellow  
    - 5: Light blue  
    - 6: Pink  
    - 7: Lime green  
    - 8: Orange  
    - 9: Purple  
    - 10: Brown  
    - 11: White  
    - 12: Black  
- **material**: *byte*, *range*: \[0,4\], *default*: 0  
  - “Material” setting.  
    - **0: Normal**  
    - 1: Bouncy  
    - 2: Slippery  
    - 3: Floaty  
    - 4: Zero gravity  
- **connectionType**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Connection Type” setting.  
    - **0: Normal**  
    - 1: Springy  
    - 2: 180° Rotation  
- **connectionOwn**: *byte*, *range*: \[0,7\], *default*: 3  
  - “Own Connection Point” or “Connection Point” settings.  
    - 0: Center  
    - 1: X-  
    - 2: X+  
    - **3: Y-**  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
    - 7: Auto (Overrides connectionTarget as well)  
- **connectionTarget**: *byte*, *range*: \[0,6\], *default*: 4  
  - “Target Connection Point” setting.  
    - 0: Center  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - **4: Y+**  
    - 5: Z-  
    - 6: Z+

##### 

##### **createFancyObjectNodon**

**createFancyObjectNodon(*gridX*, *gridY*, *visible*, *solid*, *movable*, *destructibleNormal*, *destructibleFancy*, *destructiveNormal*, *destructiveFancy*, *silent*, *ungrabbable*, *color*, *material*, *connectionType*, *connectionOwn*, *connectionTarget*);**  
Create and place a Fancy Object Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **visible**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Visible” setting.  
- **solid**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Solid” setting.  
- **movable**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Movable” setting.  
- **destructibleNormal**: *byte*, *range*: \[0, 255\], *default*: 0  
  - Bit array to enable non-Fancy Objects in the “Destructible” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructibleFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 0  
  - Bit array to enable Fancy Objects in the “Destructible” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructiveNormal**: *byte*, *range*: \[0, 63\], *default*: 0  
  - Bit array to enable non-Fancy Objects in the “Destructive” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructiveFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 0  
  - Bit array to enable Fancy Objects in the “Destructive” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **silent**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Play Sound When Hit/Destroyed?” setting.  
    - **0: Play**  
    - 1: Don’t Play  
- **ungrabbable**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Can Be Grabbed by Hand Nodon?” setting.  
    - **0: Can be grabbed**  
    - 1: Can’t be grabbed  
- **material**: *byte*, *range*: \[0,4\], *default*: 0  
  - “Material” setting.  
    - **0: Normal**  
    - 1: Bouncy  
    - 2: Slippery  
    - 3: Floaty  
    - 4: Zero gravity  
- **connectionType**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Connection Type” setting.  
    - **0: Normal**  
    - 1: Springy  
    - 2: 180° Rotation  
- **connectionOwn**: *byte*, *range*: \[0,7\], *default*: 3  
  - “Own Connection Point” or “Connection Point” settings.  
    - 0: Center  
    - 1: X-  
    - 2: X+  
    - **3: Y-**  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
    - 7: Auto (Overrides connectionTarget as well)  
- **connectionTarget**: *byte*, *range*: \[0,6\], *default*: 4  
  - “Target Connection Point” setting.  
    - 0: Center  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - **4: Y+**  
    - 5: Z-  
    - 6: Z+

Notes:

- The “Appearance” setting is set to Crate by default; to change this, an [editObject](#editobject) call with the appropriate fancyAppearance parameter is required.

##### **createMovingObjectNodon**

**createMovingObjectNodon(*gridX*, *gridY*, *shape*, *visible*, *solid*, *destructibleNormal*, *destructibleFancy*, *destructiveNormal*, *destructiveFancy*, *silent*, *ungrabbable*, *color*, *material*, *connectionType*, *connectionOwn*, *connectionTarget*, *referenceFrame*, *mode*);**  
Create and place a Moving Object Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **shape**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Object Shape” setting.  
    - **0: Box**  
    - 1: Cylinder  
    - 2: Sphere  
- **visible**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Visible” setting.  
- **solid**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Solid” setting.  
- **destructibleNormal**: *byte*, *range*: \[0, 255\], *default*: 255  
  - Bit array to enable non-Fancy Objects in the “Destructible” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructibleFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 4294967295  
  - Bit array to enable Fancy Objects in the “Destructible” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructiveNormal**: *byte*, *range*: \[0, 63\], *default*: 63  
  - Bit array to enable non-Fancy Objects in the “Destructive” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructiveFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 4294967295  
  - Bit array to enable Fancy Objects in the “Destructive” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **silent**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Play Sound When Hit/Destroyed?” setting.  
    - **0: Play**  
    - 1: Don’t Play  
- **ungrabbable**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Can Be Grabbed by Hand Nodon?” setting.  
    - **0: Can be grabbed**  
    - 1: Can’t be grabbed  
- **color**: *byte*, *range*: \[0,12\], *default*: 0  
  - “Color” setting.  
    - **0: Auto**  
    - 1: Blue  
    - 2: Red  
    - 3: Green  
    - 4: Yellow  
    - 5: Light blue  
    - 6: Pink  
    - 7: Lime green  
    - 8: Orange  
    - 9: Purple  
    - 10: Brown  
    - 11: White  
    - 12: Black  
- **material**: *byte*, *range*: \[0,4\], *default*: 0  
  - “Material” setting.  
    - **0: Normal**  
    - 1: Bouncy  
    - 2: Slippery  
    - 3: Floaty  
    - 4: Zero gravity  
- **connectionType**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Connection Type” setting.  
    - **0: Normal**  
    - 1: Springy  
    - 2: 180° Rotation  
- **connectionOwn**: *byte*, *range*: \[0,7\], *default*: 3  
  - “Own Connection Point” or “Connection Point” settings.  
    - 0: Center  
    - 1: X-  
    - 2: X+  
    - **3: Y-**  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
    - 7: Auto (Overrides connectionTarget as well)  
- **connectionTarget**: *byte*, *range*: \[0,6\], *default*: 4  
  - “Target Connection Point” setting.  
    - 0: Center  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - **4: Y+**  
    - 5: Z-  
    - 6: Z+  
- **referenceFrame**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Frame of Reference for Motion” setting.  
    - **0: World**  
    - 1: Local  
    - 2: Camera  
- **mode**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Mode” setting.  
    - **0: Acceleration**  
    - 1: Speed

##### **createRotatingObjectNodon**

**createRotatingObjectNodon(*gridX*, *gridY*, *shape*, *visible*, *solid*, *destructibleNormal*, *destructibleFancy*, *destructiveNormal*, *destructiveFancy*, *silent*, *ungrabbable*, *color*, *material*, *connectionType*, *connectionOwn*, *connectionTarget*, *referenceFrame*);**  
Create and place a Rotating Object Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **shape**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Object Shape” setting.  
    - **0: Box**  
    - 1: Cylinder  
    - 2: Sphere  
- **visible**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Visible” setting.  
- **solid**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Solid” setting.  
- **destructibleNormal**: *byte*, *range*: \[0, 255\], *default*: 255  
  - Bit array to enable non-Fancy Objects in the “Destructible” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructibleFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 4294967295  
  - Bit array to enable Fancy Objects in the “Destructible” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructiveNormal**: *byte*, *range*: \[0, 63\], *default*: 63  
  - Bit array to enable non-Fancy Objects in the “Destructive” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructiveFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 4294967295  
  - Bit array to enable Fancy Objects in the “Destructive” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **silent**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Play Sound When Hit/Destroyed?” setting.  
    - **0: Play**  
    - 1: Don’t Play  
- **ungrabbable**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Can Be Grabbed by Hand Nodon?” setting.  
    - **0: Can be grabbed**  
    - 1: Can’t be grabbed  
- **color**: *byte*, *range*: \[0,12\], *default*: 0  
  - “Color” setting.  
    - **0: Auto**  
    - 1: Blue  
    - 2: Red  
    - 3: Green  
    - 4: Yellow  
    - 5: Light blue  
    - 6: Pink  
    - 7: Lime green  
    - 8: Orange  
    - 9: Purple  
    - 10: Brown  
    - 11: White  
    - 12: Black  
- **material**: *byte*, *range*: \[0,4\], *default*: 0  
  - “Material” setting.  
    - **0: Normal**  
    - 1: Bouncy  
    - 2: Slippery  
    - 3: Floaty  
    - 4: Zero gravity  
- **connectionType**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Connection Type” setting.  
    - **0: Normal**  
    - 1: Springy  
    - 2: 180° Rotation  
- **connectionOwn**: *byte*, *range*: \[0,7\], *default*: 3  
  - “Own Connection Point” or “Connection Point” settings.  
    - 0: Center  
    - 1: X-  
    - 2: X+  
    - **3: Y-**  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
    - 7: Auto (Overrides connectionTarget as well)  
- **connectionTarget**: *byte*, *range*: \[0,6\], *default*: 4  
  - “Target Connection Point” setting.  
    - 0: Center  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - **4: Y+**  
    - 5: Z-  
    - 6: Z+  
- **referenceFrame**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Frame of Reference for Motion” setting.  
    - **0: World**  
    - 1: Local  
    - 2: Camera

##### **createExtendingObjectNodon**

**createExtendingObjectNodon(*gridX*, *gridY*, *shape*, *ungrabbable*, *color*, *connectionOwn*, *connectionTarget*);**  
Create and place an Extending Object Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **shape**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Object Shape” setting.  
    - **0: Box**  
    - 1: Cylinder  
    - 2: Sphere  
- **ungrabbable**: *boolean*, *range*: \[0,1\], *default*: 1  
  - “Can Be Grabbed by Hand Nodon?” setting.  
    - 0: Can be grabbed  
    - **1: Can’t be grabbed**  
- **color**: *byte*, *range*: \[0,11\], *default*: 0  
  - “Color” setting.  
    - **0: Blue**  
    - 1: Red  
    - 2: Green  
    - 3: Yellow  
    - 4: Light blue  
    - 5: Pink  
    - 6: Lime green  
    - 7: Orange  
    - 8: Purple  
    - 9: Brown  
    - 10: White  
    - 11: Black  
- **connectionOwn**: *byte*, *range*: \[0,7\], *default*: 3  
  - “Own Connection Point” or “Connection Point” settings.  
    - 0: Center  
    - 1: X-  
    - 2: X+  
    - **3: Y-**  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
    - 7: Auto (Overrides connectionTarget as well)  
- **connectionTarget**: *byte*, *range*: \[0,6\], *default*: 4  
  - “Target Connection Point” setting.  
    - 0: Center  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - **4: Y+**  
    - 5: Z-  
    - 6: Z+

Notes:

- Unlike every other Nodon with the “Can Be Grabbed by Hand Nodon?” setting, the default for the Extending Object is 1 instead of 0\.  
- For the “Color” setting, this Nodon does not have an “Auto” option, so this setting is slightly different from other Nodons’.

##### **createEffectNodon**

**createEffectNodon(*gridX*, *gridY*, *appearance*, *effectTiming*, *effectLocation*, *visible*, *ungrabbable*, *connectionOwn*, *connectionTarget*);**  
Create and place an Effect Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **appearance**: *byte*, *range*: \[0,8\], *default*: 0  
  - “Appearance” setting.  
    - **0: Fireworks**  
    - 1: Explosion  
    - 2: Bubbles  
    - 3: Smoke  
    - 4: Party Popper  
    - 5: Damage  
    - 6: Countdown  
    - 7: Failure  
    - 8: Light  
- **effectTiming**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Effect Timing” setting.  
    - **0: On change from 0**  
    - 1: While not 0  
- **effectLocation**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Effect Location” setting.  
    - **0: Camera**  
    - 1: World  
- **visible**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Visible” setting.  
- **ungrabbable**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Can Be Grabbed by Hand Nodon?” setting.  
    - **0: Can be grabbed**  
    - 1: Can’t be grabbed  
- **connectionOwn**: *byte*, *range*: \[0,7\], *default*: 0  
  - “Own Connection Point” or “Connection Point” settings.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
    - 7: Auto (Overrides connectionTarget as well)  
- **connectionTarget**: *byte*, *range*: \[0,6\], *default*: 0  
  - “Target Connection Point” setting.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+

##### **createTextObjectNodon**

**createTextObjectNodon(*gridX*, *gridY*, *displayText*, *visible*, *solid*, *movable*, *destructibleNormal*, *destructibleFancy*, *destructiveNormal*, *destructiveFancy*, *silent*, *ungrabbable*, *color*, text*Color*, *material*, *connectionType*, *connectionOwn*, *connectionTarget*, *displaySide*);**  
Create and place a Text Object Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **displaytext**: *String*, *default*: “Text Object”  
  - “Display Text” setting.  
- **visible**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Visible” setting.  
- **solid**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Solid” setting.  
- **movable**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Movable” setting.  
- **destructibleNormal**: *byte*, *range*: \[0, 255\], *default*: 255  
  - Bit array to enable non-Fancy Objects in the “Destructible” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructibleFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 4294967295  
  - Bit array to enable Fancy Objects in the “Destructible” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructiveNormal**: *byte*, *range*: \[0, 63\], *default*: 63  
  - Bit array to enable non-Fancy Objects in the “Destructive” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructiveFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 4294967295  
  - Bit array to enable Fancy Objects in the “Destructive” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **silent**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Play Sound When Hit/Destroyed?” setting.  
    - **0: Play**  
    - 1: Don’t Play  
- **ungrabbable**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Can Be Grabbed by Hand Nodon?” setting.  
    - **0: Can be grabbed**  
    - 1: Can’t be grabbed  
- **color**: *byte*, *range*: \[0,12\], *default*: 0  
  - “Color” setting.  
    - **0: Auto**  
    - 1: Blue  
    - 2: Red  
    - 3: Green  
    - 4: Yellow  
    - 5: Light blue  
    - 6: Pink  
    - 7: Lime green  
    - 8: Orange  
    - 9: Purple  
    - 10: Brown  
    - 11: White  
    - 12: Black  
- **textColor**: *byte*, *range*: \[0,11\], *default*: 11  
  - “Color” setting.  
    - 0: Blue  
    - 1: Red  
    - 2: Green  
    - 3: Yellow  
    - 4: Light blue  
    - 5: Pink  
    - 6: Lime green  
    - 7: Orange  
    - 8: Purple  
    - 9: Brown  
    - 10: White  
    - **11: Black**  
- **material**: *byte*, *range*: \[0,4\], *default*: 0  
  - “Material” setting.  
    - **0: Normal**  
    - 1: Bouncy  
    - 2: Slippery  
    - 3: Floaty  
    - 4: Zero gravity  
- **connectionType**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Connection Type” setting.  
    - **0: Normal**  
    - 1: Springy  
    - 2: 180° Rotation  
- **connectionOwn**: *byte*, *range*: \[0,7\], *default*: 3  
  - “Own Connection Point” or “Connection Point” settings.  
    - 0: Center  
    - 1: X-  
    - 2: X+  
    - **3: Y-**  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
    - 7: Auto (Overrides connectionTarget as well)  
- **connectionTarget**: *byte*, *range*: \[0,6\], *default*: 4  
  - “Target Connection Point” setting.  
    - 0: Center  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - **4: Y+**  
    - 5: Z-  
    - 6: Z+  
- **displaySide**: *byte*, *range*: \[0,5\], *default*: 5  
  - “Text Display Side” setting.  
    - 0: X+  
    - 1: Y+  
    - 2: Z+  
    - 3: X-  
    - 4: Y-  
    - **5: Z-**

##### **createNumberObjectNodon**

**createNumberObjectNodon(*gridX*, *gridY*, *visible*, *solid*, *movable*, *destructibleNormal*, *destructibleFancy*, *destructiveNormal*, *destructiveFancy*, *silent*, *ungrabbable*, *color*, text*Color*, *material*, *connectionType*, *connectionOwn*, *connectionTarget*, *displaySide*, *wholeDigits*, *decimalDigits*);**  
Create and place a Number Object Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **visible**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Visible” setting.  
- **solid**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Solid” setting.  
- **movable**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Movable” setting.  
- **destructibleNormal**: *byte*, *range*: \[0, 255\], *default*: 255  
  - Bit array to enable non-Fancy Objects in the “Destructible” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructibleFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 4294967295  
  - Bit array to enable Fancy Objects in the “Destructible” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructiveNormal**: *byte*, *range*: \[0, 63\], *default*: 63  
  - Bit array to enable non-Fancy Objects in the “Destructive” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructiveFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 4294967295  
  - Bit array to enable Fancy Objects in the “Destructive” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **silent**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Play Sound When Hit/Destroyed?” setting.  
    - **0: Play**  
    - 1: Don’t Play  
- **ungrabbable**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Can Be Grabbed by Hand Nodon?” setting.  
    - **0: Can be grabbed**  
    - 1: Can’t be grabbed  
- **color**: *byte*, *range*: \[0,12\], *default*: 0  
  - “Color” setting.  
    - **0: Auto**  
    - 1: Blue  
    - 2: Red  
    - 3: Green  
    - 4: Yellow  
    - 5: Light blue  
    - 6: Pink  
    - 7: Lime green  
    - 8: Orange  
    - 9: Purple  
    - 10: Brown  
    - 11: White  
    - 12: Black  
- **textColor**: *byte*, *range*: \[0,11\], *default*: 11  
  - “Color” setting.  
    - 0: Blue  
    - 1: Red  
    - 2: Green  
    - 3: Yellow  
    - 4: Light blue  
    - 5: Pink  
    - 6: Lime green  
    - 7: Orange  
    - 8: Purple  
    - 9: Brown  
    - 10: White  
    - **11: Black**  
- **material**: *byte*, *range*: \[0,4\], *default*: 0  
  - “Material” setting.  
    - **0: Normal**  
    - 1: Bouncy  
    - 2: Slippery  
    - 3: Floaty  
    - 4: Zero gravity  
- **connectionType**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Connection Type” setting.  
    - **0: Normal**  
    - 1: Springy  
    - 2: 180° Rotation  
- **connectionOwn**: *byte*, *range*: \[0,7\], *default*: 3  
  - “Own Connection Point” or “Connection Point” settings.  
    - 0: Center  
    - 1: X-  
    - 2: X+  
    - **3: Y-**  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
    - 7: Auto (Overrides connectionTarget as well)  
- **connectionTarget**: *byte*, *range*: \[0,6\], *default*: 4  
  - “Target Connection Point” setting.  
    - 0: Center  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - **4: Y+**  
    - 5: Z-  
    - 6: Z+  
- **displaySide**: *byte*, *range*: \[0,5\], *default*: 5  
  - “Text Display Side” setting.  
    - 0: X+  
    - 1: Y+  
    - 2: Z+  
    - 3: X-  
    - 4: Y-  
    - **5: Z-**  
- **wholeDigits**: *byte*, *range*: \[1,5\], *default*: 2  
  - “Whole Number Digits” setting value.  
- **decimalDigits**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Decimal Digits” setting value.

##### **createTextureNodon**

**createTextureNodon(*gridX*, *gridY*, *faceX*, *faceY*, *faceZ*, *mainColor*, *subColor*);**  
Create and place a Texture Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **faceX**: *byte*, *range*: \[0, 7\], *default*: 3  
  - Bit array to enable X-axis options in the “Texture Face” setting.  
    - 0: None  
    - 1: X-  
    - 2: X+  
    - **3: X-, X+**  
    - 4: X Center  
    - 5: X-, X Center  
    - 6: X+, X Center  
    - 7: X+, X-, X Center  
- **faceY**: *byte*, *range*: \[0, 7\], *default*: 3  
  - Bit array to enable Y-axis options in the “Texture Face” setting.  
    - 0: None  
    - 1: Y-  
    - 2: Y+  
    - **3: Y-, Y+**  
    - 4: Y Center  
    - 5: Y-, Y Center  
    - 6: Y+, Y Center  
    - 7: Y+, Y-, Y Center  
- **faceZ**: *byte*, *range*: \[0, 7\], *default*: 3  
  - Bit array to enable Z-axis options in the “Texture Face” setting.  
    - 0: None  
    - 1: Z-  
    - 2: Z+  
    - **3: Z-, Z+**  
    - 4: Z Center  
    - 5: Z-, Z Center  
    - 6: Z+, Z Center  
    - 7: Z+, Z-, Z Center  
- **mainColor**: *byte*, *range*: \[0, 13\], *default*: 13  
  - Color group to fill the canvas with.  
    - 0: Monochrome  
    - 1: Purple  
    - 2: Light Blue  
    - 3: Lime Green  
    - 4: Red  
    - 5: Magenta  
    - 6: Blue  
    - 7: Green  
    - 8: Orange  
    - 9: Pink  
    - 10: Dark Blue  
    - 11: Cyan  
    - 12: Yellow  
    - **13: Transparent**  
- **subColor**: *byte*, *range*: \[0, 8\], *default*: 3  
  - Shade in the 3x3 color group to fill the canvas with.  
    - 0: Top-left  
    - 1: Top-middle  
    - 2: Top-right  
    - 3: Middle-left  
    - 4: Middle  
    - 5: Middle-right  
    - 6: Bottom-left  
    - 7: Bottom-middle  
    - 8: Bottom-right

Notes:

- The script currently does not have functionality to fully draw textures due to memory limitations. There is only an option to fill textures with a specific color using mainColor and subColor for easier differentiation.

##### **createTouchSensorNodon**

**createTouchSensorNodon(*gridX*, *gridY*, *shape*, *visible*, *ungrabbable*, *timing*, *connectionOwn*, *connectionTarget*, *senseNormal*, *senseFancy*);**  
Create and place a Touch Sensor Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **shape**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Sensor Shape” setting.  
    - **0: Box**  
    - 1: Cylinder  
    - 2: Sphere  
- **visible**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Visible” setting.  
- **ungrabbable**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Can Be Grabbed by Hand Nodon?” setting.  
    - **0: Can be grabbed**  
    - 1: Can’t be grabbed  
- **timing**: *boolean*, *range*: \[0,1\], *default*: 1  
  - “Output Timing” setting.  
    - 0: On touch  
    - **1: While touched**  
- **connectionOwn**: *byte*, *range*: \[0,7\], *default*: 0  
  - “Own Connection Point” or “Connection Point” settings.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
    - 7: Auto (Overrides connectionTarget as well)  
- **connectionTarget**: *byte*, *range*: \[0,6\], *default*: 0  
  - “Target Connection Point” setting.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
- **senseNormal**: *byte*, *range*: \[0, 255\], *default*: 14  
  - Bit array to enable non-Fancy Objects in the “Check What?” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **senseFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 0  
  - Bit array to enable Fancy Objects in the “Check What?” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details

##### **createDestroyingSensorNodon**

**createDestroyingSensorNodon(*gridX*, *gridY*, *shape*, *visible*, *ungrabbable*, *connectionOwn*, *connectionTarget*);**  
Create and place a Destroying Sensor Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **shape**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Sensor Shape” setting.  
    - **0: Box**  
    - 1: Cylinder  
    - 2: Sphere  
- **visible**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Visible” setting.  
- **ungrabbable**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Can Be Grabbed by Hand Nodon?” setting.  
    - **0: Can be grabbed**  
    - 1: Can’t be grabbed  
- **connectionOwn**: *byte*, *range*: \[0,7\], *default*: 0  
  - “Own Connection Point” or “Connection Point” settings.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
    - 7: Auto (Overrides connectionTarget as well)  
- **connectionTarget**: *byte*, *range*: \[0,6\], *default*: 0  
  - “Target Connection Point” setting.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+

##### **createDestroyedSensorNodon**

**createDestroyedSensorNodon(*gridX*, *gridY*, *shape*, *visible,* *ungrabbable*, *connectionOwn*, *connectionTarget*);**  
Create and place a Destroyed Sensor Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **shape**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Sensor Shape” setting.  
    - **0: Box**  
    - 1: Cylinder  
    - 2: Sphere  
- **visible**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Visible” setting.  
- **ungrabbable**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Can Be Grabbed by Hand Nodon?” setting.  
    - **0: Can be grabbed**  
    - 1: Can’t be grabbed  
- **connectionOwn**: *byte*, *range*: \[0,7\], *default*: 0  
  - “Own Connection Point” or “Connection Point” settings.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
    - 7: Auto (Overrides connectionTarget as well)  
- **connectionTarget**: *byte*, *range*: \[0,6\], *default*: 0  
  - “Target Connection Point” setting.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+

##### **createGrabbedSensorNodon**

**createGrabbedSensorNodon(*gridX*, *gridY*, *shape*, *visible*, *ungrabbable*, *timing*, *connectionOwn*, *connectionTarget*);**  
Create and place a Grabbed Sensor Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **shape**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Sensor Shape” setting.  
    - **0: Box**  
    - 1: Cylinder  
    - 2: Sphere  
- **visible**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Visible” setting.  
- **ungrabbable**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Can Be Grabbed by Hand Nodon?” setting.  
    - **0: Can be grabbed**  
    - 1: Can’t be grabbed  
- **timing**: *boolean*, *range*: \[0,1\], *default*: 1  
  - “Output Timing” setting.  
    - 0: On grip  
    - **1: While gripped**  
- **connectionOwn**: *byte*, *range*: \[0,7\], *default*: 0  
  - “Own Connection Point” or “Connection Point” settings.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
    - 7: Auto (Overrides connectionTarget as well)  
- **connectionTarget**: *byte*, *range*: \[0,6\], *default*: 0  
  - “Target Connection Point” setting.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+

##### **createLocationSensorNodon**

**createLocationSensorNodon(*gridX*, *gridY*, *shape*, *visible*, *ungrabbable*, *connectionOwn*, *connectionTarget*, *referenceFrame*);**  
Create and place a Location Sensor Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **shape**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Sensor Shape” setting.  
    - **0: Box**  
    - 1: Cylinder  
    - 2: Sphere  
- **visible**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Visible” setting.  
- **ungrabbable**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Can Be Grabbed by Hand Nodon?” setting.  
    - **0: Can be grabbed**  
    - 1: Can’t be grabbed  
- **connectionOwn**: *byte*, *range*: \[0,7\], *default*: 0  
  - “Own Connection Point” or “Connection Point” settings.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
    - 7: Auto (Overrides connectionTarget as well)  
- **connectionTarget**: *byte*, *range*: \[0,6\], *default*: 0  
  - “Target Connection Point” setting.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
- **referenceFrame**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Frame of Reference” setting.  
    - **0: World**  
    - 1: Initial Position  
    - 2: Camera

##### **createSpeedSensorNodon**

**createSpeedSensorNodon(*gridX*, *gridY*, *shape*, *visible*, *ungrabbable*, *connectionOwn*, *connectionTarget*, *referenceFrame*);**  
Create and place a Speed Sensor Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **shape**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Sensor Shape” setting.  
    - **0: Box**  
    - 1: Cylinder  
    - 2: Sphere  
- **visible**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Visible” setting.  
- **ungrabbable**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Can Be Grabbed by Hand Nodon?” setting.  
    - **0: Can be grabbed**  
    - 1: Can’t be grabbed  
- **connectionOwn**: *byte*, *range*: \[0,7\], *default*: 0  
  - “Own Connection Point” or “Connection Point” settings.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
    - 7: Auto (Overrides connectionTarget as well)  
- **connectionTarget**: *byte*, *range*: \[0,6\], *default*: 0  
  - “Target Connection Point” setting.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
- **referenceFrame**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Frame of Reference” setting.  
    - **0: World**  
    - 1: Local  
    - 2: Camera

##### **createAccelerationSensorNodon**

**createAccelerationSensorNodon(*gridX*, *gridY*, *shape*, *visible*, *ungrabbable*, *connectionOwn*, *connectionTarget*, *referenceFrame*);**  
Create and place an Acceleration Sensor Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **shape**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Sensor Shape” setting.  
    - **0: Box**  
    - 1: Cylinder  
    - 2: Sphere  
- **visible**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Visible” setting.  
- **ungrabbable**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Can Be Grabbed by Hand Nodon?” setting.  
    - **0: Can be grabbed**  
    - 1: Can’t be grabbed  
- **connectionOwn**: *byte*, *range*: \[0,7\], *default*: 0  
  - “Own Connection Point” or “Connection Point” settings.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
    - 7: Auto (Overrides connectionTarget as well)  
- **connectionTarget**: *byte*, *range*: \[0,6\], *default*: 0  
  - “Target Connection Point” setting.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
- **referenceFrame**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Frame of Reference” setting.  
    - **0: World**  
    - 1: Local  
    - 2: Camera

##### **createAngleSensorNodon**

**createAngleSensorNodon(*gridX*, *gridY*, *shape*, *visible*, *ungrabbable*, *connectionOwn*, *connectionTarget*, *referenceFrame*);**  
Create and place an Angle Sensor Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **shape**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Sensor Shape” setting.  
    - **0: Box**  
    - 1: Cylinder  
    - 2: Sphere  
- **visible**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Visible” setting.  
- **ungrabbable**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Can Be Grabbed by Hand Nodon?” setting.  
    - **0: Can be grabbed**  
    - 1: Can’t be grabbed  
- **connectionOwn**: *byte*, *range*: \[0,7\], *default*: 0  
  - “Own Connection Point” or “Connection Point” settings.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
    - 7: Auto (Overrides connectionTarget as well)  
- **connectionTarget**: *byte*, *range*: \[0,6\], *default*: 0  
  - “Target Connection Point” setting.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
- **referenceFrame**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Frame of Reference” setting.  
    - **0: World**  
    - 1: Initial Angle  
    - 2: Camera

##### **createRotationSpeedSensorNodon**

**createSensorNodon(*gridX*, *gridY*, *shape*, *visible*, *ungrabbable*, *connectionOwn*, *connectionTarget*, *referenceFrame*);**  
Create and place a Rotation-Speed Sensor Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **shape**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Sensor Shape” setting.  
    - **0: Box**  
    - 1: Cylinder  
    - 2: Sphere  
- **visible**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Visible” setting.  
- **ungrabbable**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Can Be Grabbed by Hand Nodon?” setting.  
    - **0: Can be grabbed**  
    - 1: Can’t be grabbed  
- **connectionOwn**: *byte*, *range*: \[0,7\], *default*: 0  
  - “Own Connection Point” or “Connection Point” settings.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
    - 7: Auto (Overrides connectionTarget as well)  
- **connectionTarget**: *byte*, *range*: \[0,6\], *default*: 0  
  - “Target Connection Point” setting.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
- **referenceFrame**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Frame of Reference” setting.  
    - **0: World**  
    - 1: Local  
    - 2: Camera

##### **createSlideConnectorNodon**

**createSlideConnectorNodon(*gridX*, *gridY*, *axis*, *lowerRange*, *upperRange*);**  
Create and place a Slide Connector Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **axis**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Slide Axis” setting.  
    - **0: X**  
    - 1: Y  
    - 2: Z  
- **lowerRange**: *float*, *range*: \[-100.0,100.0\], *default*: \-100.0  
  - Lower “Range” setting value.  
- **upperRange**: *float*, *range*: \[-100.0,100.0\], *default*: 100.0  
  - Upper “Range” setting value.

##### **createFreeSlideConnectorNodon**

**createFreeSlideConnectorNodon(*gridX*, *gridY*, *enX*, *enY*, *enZ*);**  
Create and place a Free Slide Connector Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **enX**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the X “Slide Motion Input” setting.  
- **enY**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the Y “Slide Motion Input” setting.  
- **enZ**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the Z “Slide Motion Input” setting.

##### **createHingeConnectorNodon**

**createHingeConnectorNodon(*gridX*, *gridY*, *axis*, *lowerRange*, *upperRange*);**  
Create and place a Hinge Connector Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **axis**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Slide Axis” setting.  
    - **0: X**  
    - 1: Y  
    - 2: Z  
- **lowerRange**: *float*, *range*: \[-180.0,180.0\], *default*: \-180.0  
  - Lower “Range” setting value.  
- **upperRange**: *float*, *range*: \[-180.0,180.0\], *default*: 180.0  
  - Upper “Range” setting value.

##### **createStringConnectorNodon**

**createStringConnectorNodon(*gridX*, *gridY*, *visible*, *solid*, *destructibleNormal*, *destructibleFancy*, *destructiveNormal*, *destructiveFancy*, *strStiffness*, *strLength*);**  
Create and place a String Connector Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **visible**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Visible” setting.  
- **solid**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Solid” setting.  
- **destructibleNormal**: *byte*, *range*: \[0, 255\], *default*: 0  
  - Bit array to enable non-Fancy Objects in the “Destructible” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructibleFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 0  
  - Bit array to enable Fancy Objects in the “Destructible” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructiveNormal**: *byte*, *range*: \[0, 63\], *default*: 0  
  - Bit array to enable non-Fancy Objects in the “Destructive” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructiveFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 0  
  - Bit array to enable Fancy Objects in the “Destructive” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **strStiffness**: *float*, *range*: \[0.0,1.0\], *default*: 0.5  
  - “String Stiffness” setting value.  
- **strLength**: *float*, *range*: \[0.1,10.0\], *default*: 5.0  
  - “String Length” setting value.

##### **createLaunchObjectNodon**

**createLaunchObjectNodon(*gridX*, *gridY*, *launchLimit*, *shape*, *visible*, *solid*, *movable*, *destructibleNormal*, *destructibleFancy*, *destructiveNormal*, *destructiveFancy*, *silent*, *ungrabbable*, *color*, *material*, *connectionOwn*, *connectionTarget*, *launchDirection*, *launchSpeed*, *launchInterval*);**  
Create and place a Launch Object (1), Launch Object (10), or Launch Object (100) Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **launchLimit**: *byte*, *range*: \[0,2\], *default*: 0  
  - Selects which type of Launch Object Nodon will be created.  
    - **0: Launch Object (1)**  
    - 1: Launch Object (10)  
    - 2: Launch Object (100)  
- **shape**: *byte*, *range*: \[0,2\], *default*: 2  
  - “Object Shape” setting.  
    - 0: Box  
    - 1: Cylinder  
    - **2: Sphere**  
- **visible**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Visible” setting.  
- **solid**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Solid” setting.  
- **movable**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Movable” setting.  
- **destructibleNormal**: *byte*, *range*: \[0, 255\], *default*: 255  
  - Bit array to enable non-Fancy Objects in the “Destructible” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructibleFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 4294967295  
  - Bit array to enable Fancy Objects in the “Destructible” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructiveNormal**: *byte*, *range*: \[0, 63\], *default*: 63  
  - Bit array to enable non-Fancy Objects in the “Destructive” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructiveFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 4294967295  
  - Bit array to enable Fancy Objects in the “Destructive” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **silent**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Play Sound When Hit/Destroyed?” setting.  
    - **0: Play**  
    - 1: Don’t Play  
- **ungrabbable**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Can Be Grabbed by Hand Nodon?” setting.  
    - **0: Can be grabbed**  
    - 1: Can’t be grabbed  
- **color**: *byte*, *range*: \[0,12\], *default*: 0  
  - “Color” setting.  
    - **0: Auto**  
    - 1: Blue  
    - 2: Red  
    - 3: Green  
    - 4: Yellow  
    - 5: Light blue  
    - 6: Pink  
    - 7: Lime green  
    - 8: Orange  
    - 9: Purple  
    - 10: Brown  
    - 11: White  
    - 12: Black  
- **material**: *byte*, *range*: \[0,4\], *default*: 0  
  - “Material” setting.  
    - **0: Normal**  
    - 1: Bouncy  
    - 2: Slippery  
    - 3: Floaty  
    - 4: Zero gravity  
- **connectionOwn**: *byte*, *range*: \[0,7\], *default*: 3  
  - “Own Connection Point” or “Connection Point” settings.  
    - 0: Center  
    - 1: X-  
    - 2: X+  
    - **3: Y-**  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
    - 7: Auto (Overrides connectionTarget as well)  
- **connectionTarget**: *byte*, *range*: \[0,6\], *default*: 4  
  - “Target Connection Point” setting.  
    - 0: Center  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - **4: Y+**  
    - 5: Z-  
    - 6: Z+  
- **launchDirection**: *byte*, *range*: \[0,5\], *default*: 2  
  - “Launch Direction” setting.  
    - 0: X+  
    - 1: Y+  
    - **2: Z+**  
    - 3: X-  
    - 4: Y-  
    - 5: Z-  
- **launchSpeed**: *float*, *range*: \[0.0,100.0\], *default*: 10.0  
  - “Launch Speed” setting value.  
- **launchInterval**: *float*, *range*: \[0.1,100.0\], *default*: 1.0  
  - “Launch Interval” setting value.

##### **createDestroyObjectNodon**

**createDestroyObjectNodon(*gridX*, *gridY*, *shape*, *visible*, *ungrabbable*, *connectionOwn*, *connectionTarget*, *destroyNormal*, *destroyFancy*);**  
Create and place a Destroy Object Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **shape**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Object Shape” setting.  
    - **0: Box**  
    - 1: Cylinder  
    - 2: Sphere  
- **visible**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Visible” setting.  
- **ungrabbable**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Can Be Grabbed by Hand Nodon?” setting.  
    - **0: Can be grabbed**  
    - 1: Can’t be grabbed  
- **connectionOwn**: *byte*, *range*: \[0,7\], *default*: 0  
  - “Own Connection Point” or “Connection Point” settings.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
    - 7: Auto (Overrides connectionTarget as well)  
- **connectionTarget**: *byte*, *range*: \[0,6\], *default*: 0  
  - “Target Connection Point” setting.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
- **destroyNormal**: *byte*, *range*: \[0, 63\], *default*: 7  
  - Bit array to enable non-Fancy Objects in the “Destroy What?” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destroyFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 0  
  - Bit array to enable Fancy Objects in the “Destroy What?” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details

##### **createTeleportObjectEntranceNodon**

**createTeleportObjectEntranceNodon(*gridX*, *gridY*, *teleportID*, *shape*, *visible*, *ungrabbable*, *connectionOwn*, *connectionTarget*, *teleportNormal*, *teleportFancy*);**  
Create and place a Teleport Object Entrance Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **teleportID**: *byte*, *range*: \[0,7\], *default*: 0  
  - “Teleport ID” setting.  
    - **0: A**  
    - 1: B  
    - 2: C  
    - 3: D  
    - 4: E  
    - 5: F  
    - 6: G  
    - 7: H  
- **shape**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Object Shape” setting.  
    - **0: Box**  
    - 1: Cylinder  
    - 2: Sphere  
- **visible**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Visible” setting.  
- **ungrabbable**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Can Be Grabbed by Hand Nodon?” setting.  
    - **0: Can be grabbed**  
    - 1: Can’t be grabbed  
- **connectionOwn**: *byte*, *range*: \[0,7\], *default*: 0  
  - “Own Connection Point” or “Connection Point” settings.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
    - 7: Auto (Overrides connectionTarget as well)  
- **connectionTarget**: *byte*, *range*: \[0,6\], *default*: 0  
  - “Target Connection Point” setting.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
- **teleportNormal**: *byte*, *range*: \[0, 63\], *default*: 7  
  - Bit array to enable non-Fancy Objects in the “Teleport What?” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **teleportFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 0  
  - Bit array to enable Fancy Objects in the “Teleport What?” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details

##### **createTeleportObjectExitNodon**

**createTeleportObjectExitNodon(*gridX*, *gridY*, *teleportID*, *shape*, *visible*, *ungrabbable*, *connectionOwn*, *connectionTarget*, *teleportPhysics*, *launchSpeed*, *launchDirection*);**  
Create and place a Teleport Object Exit Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **teleportID**: *byte*, *range*: \[0,7\], *default*: 0  
  - “Teleport ID” setting.  
    - **0: A**  
    - 1: B  
    - 2: C  
    - 3: D  
    - 4: E  
    - 5: F  
    - 6: G  
    - 7: H  
- **shape**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Object Shape” setting.  
    - **0: Box**  
    - 1: Cylinder  
    - 2: Sphere  
- **visible**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Visible” setting.  
- **ungrabbable**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Can Be Grabbed by Hand Nodon?” setting.  
    - **0: Can be grabbed**  
    - 1: Can’t be grabbed  
- **connectionOwn**: *byte*, *range*: \[0,7\], *default*: 0  
  - “Own Connection Point” or “Connection Point” settings.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
    - 7: Auto (Overrides connectionTarget as well)  
- **connectionTarget**: *byte*, *range*: \[0,6\], *default*: 0  
  - “Target Connection Point” setting.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
- **teleportPhysics**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Teleport Physics” setting.  
    - **0: Preserve**  
    - 1: Reset  
- **launchSpeed**: *float*, *range*: \[0.0,100.0\], *default*: 0.0  
  - “Launch Speed” setting value.  
- **launchDirection**: *byte*, *range*: \[0,5\], *default*: 1  
  - “Launch Direction” setting.  
    - 0: X+  
    - **1: Y+**  
    - 2: Z+  
    - 3: X-  
    - 4: Y-  
    - 5: Z-

##### **createAttractObjectNodon**

**createAttractObjectNodon(*gridX*, *gridY*, *shape*, *visible*, *ungrabbable*, *connectionOwn*, *connectionTarget*, *attractCenter*, *attractNormal*, *attractFancy*);**  
Create and place an Attract Object Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **shape**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Object Shape” setting.  
    - **0: Box**  
    - 1: Cylinder  
    - 2: Sphere  
- **visible**: *boolean*, *range*: \[0,1\], *default*: 1  
  - Enables the “Visible” setting.  
- **ungrabbable**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Can Be Grabbed by Hand Nodon?” setting.  
    - **0: Can be grabbed**  
    - 1: Can’t be grabbed  
- **connectionOwn**: *byte*, *range*: \[0,7\], *default*: 0  
  - “Own Connection Point” or “Connection Point” settings.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
    - 7: Auto (Overrides connectionTarget as well)  
- **connectionTarget**: *byte*, *range*: \[0,6\], *default*: 0  
  - “Target Connection Point” setting.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
- **attractCenter**: *byte*, *range*: \[0,6\], *default*: 6  
  - “Center of Attraction” setting.  
    - 0: X+  
    - 1: Y+  
    - 2: Z+  
    - 3: X-  
    - 4: Y-  
    - 5: Z-  
    - **6: Center**  
- **attractNormal**: *byte*, *range*: \[0, 63\], *default*: 7  
  - Bit array to enable non-Fancy Objects in the “Attract Which Objects?” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **attractFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 0  
  - Bit array to enable Fancy Objects in the “Attract Which Objects?” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details

##### **createWorldNodon**

**createWorldNodon(*gridX*, *gridY*, *worldShape*, *worldAppearance*, *worldLighting*, *sunDirection*, *sunHeight*, *worldMaterial*, *objectAppearance*, *destructiveNormal*, *destructiveFancy*, *destructionSpeed*);**  
Create and place a World Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **worldShape**: *byte*, *range*: \[0,5\], *default*: 1  
  - “World Shape” setting.  
    - 0: None  
    - **1: Plane**  
    - 2: Dome  
    - 3: Cuboid  
    - 4: Cylinder  
    - 5: Sphere  
- **worldAppearance**: *byte*, *range*: \[0,4\], *default*: 0  
  - “World Appearance” setting.  
    - **0: Default**  
    - 1: Grass  
    - 2: Tiles  
    - 3: Metal  
    - 4: Sand  
- **worldLighting**: *byte*, *range*: \[0,4\], *default*: 0  
  - “World Lighting” setting.  
    - **0: Noon**  
    - 1: Evening  
    - 2: Night  
    - 3: Pitch black  
    - 4: Outer Space  
- **sunDirection**: *int*, *range*: \[-180,180\], *default*: \-130  
  - “Sun Direction” setting value.  
- **sunHeight**: *int*, *range*: \[-90,90\], *default*: 52  
  - “Sun Height” setting value.  
- **worldMaterial**: *byte*, *range*: \[0,2\], *default*: 0  
  - “World Material” setting.  
    - **0: Normal**  
    - 1: Bouncy  
    - 2: Slippery  
- **objectAppearance**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Object Appearance” setting.  
    - **0: Default**  
    - 1: Metallic  
    - 2: Neon  
- **destructiveNormal**: *byte*, *range*: \[0, 63\], *default*: 0  
  - Bit array to enable non-Fancy Objects in the “Destructive” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructiveFancy**: *unsigned long*, *range*: \[0, 4294967295\], *default*: 0  
  - Bit array to enable Fancy Objects in the “Destructive” setting.  
    - See [Bit array parameters](#bit-array-parameters) section for more details  
- **destructionSpeed**: *float*, *range*: \[0.0,100.0\], *default*: 0.1  
  - “Object-Destruction Speed” setting value.

Notes:

- The sunDirection and sunHeight parameters are especially sensitive to missed inputs due to lag.  
- It is recommended to use editObject on the World Nodon last as changing it may force Objects to be moved prematurely.

##### **createGameScreenNodon**

**createNodon(*gridX*, *gridY*, *horizontalTrack*, *verticalTrack*, *cameraFOV*);**  
Create and place a Game Screen Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **horizontalTrack**: *float*, *range*: \[0.0,1.0\], *default*: 0.2  
  - “Horizontal Tracking Rate” setting value.  
- **verticalTrack**: *float*, *range*: \[0.0,1.0\], *default*: 0.2  
  - “Vertical Tracking Rate” setting value.  
- **cameraFOV**: *float*, *range*: \[10.0,120.0\], *default*: 60.0  
  - “Camera Field of View” setting value.

Notes:

- The “Viewpoint” cannot be changed upon Nodon creation; to change this, an [editObject](#editobject) call with the appropriate screenViewpoint parameter is required.

##### **createCameraNodon**

**createCameraNodon(*gridX*, *gridY*, *horizontalTrack*, *verticalTrack*, *cameraFOV*, *trackRotation*);**  
Create and place a Camera Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **horizontalTrack**: *float*, *range*: \[0.0,1.0\], *default*: 0.2  
  - “Horizontal Tracking Rate” setting value.  
- **verticalTrack**: *float*, *range*: \[0.0,1.0\], *default*: 0.2  
  - “Vertical Tracking Rate” setting value.  
- **cameraFOV**: *float*, *range*: \[10.0,120.0\], *default*: 90.0  
  - “Camera Field of View” setting value.  
- **trackRotation**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Track Character’s Y Rotation” setting.  
    - **0: Disable**  
    - 1: Enable

##### **createCameraPositionNodon**

**createCameraPositionNodon(*gridX*, *gridY*, *horizontalTrack*, *verticalTrack*, *connectionOwn*, *connectionTarget*);**  
Create and place a Camera Position Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **horizontalTrack**: *float*, *range*: \[0.0,1.0\], *default*: 0.5  
  - “Horizontal Tracking Rate” setting value.  
- **verticalTrack**: *float*, *range*: \[0.0,1.0\], *default*: 0.5  
  - “Vertical Tracking Rate” setting value.  
- **connectionOwn**: *byte*, *range*: \[0,7\], *default*: 0  
  - “Own Connection Point” or “Connection Point” settings.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
    - 7: Auto (Overrides connectionTarget as well)  
- **connectionTarget**: *byte*, *range*: \[0,6\], *default*: 0  
  - “Target Connection Point” setting.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+

##### **createCameraTargetNodon**

**createCameraTargetNodon(*gridX*, *gridY*, *horizontalTrack*, *verticalTrack*, *connectionOwn*, *connectionTarget*);**  
Create and place a Camera Target Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **horizontalTrack**: *float*, *range*: \[0.0,1.0\], *default*: 0.5  
  - “Horizontal Tracking Rate” setting value.  
- **verticalTrack**: *float*, *range*: \[0.0,1.0\], *default*: 0.5  
  - “Vertical Tracking Rate” setting value.  
- **connectionOwn**: *byte*, *range*: \[0,7\], *default*: 0  
  - “Own Connection Point” or “Connection Point” settings.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+  
    - 7: Auto (Overrides connectionTarget as well)  
- **connectionTarget**: *byte*, *range*: \[0,6\], *default*: 0  
  - “Target Connection Point” setting.  
    - **0: Center**  
    - 1: X-  
    - 2: X+  
    - 3: Y-  
    - 4: Y+  
    - 5: Z-  
    - 6: Z+

##### **createCameraDirectionNodon**

**createCameraDirectionNodon(*gridX*, *gridY*);**  
Create and place a Camera Direction Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.

##### **createCameraAngleNodon**

**createCameraAngleNodon(*gridX*, *gridY*, *cameraFOV*);**  
Create and place a Camera Angle Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **cameraFOV**: *float*, *range*: \[10.0,120.0\], *default*: 90.0  
  - “Camera Field of View” setting value.

##### **createHeadNodon**

**createHeadNodon(*gridX*, *gridY*);**  
Create and place a Head Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.

##### **createHandNodon**

**createHandNodon(*gridX*, *gridY*);**  
Create and place a Digitize Nodon on the grid.  
Parameters:

- **gridX**: *byte*, *range*: \[0,18\]  
  - Grid X position to move Nodon to.  
- **gridY**: *byte*, *range*: \[0,10\]  
  - Grid Y position to move Nodon to.  
- **controlNum**: *byte*, *range*: \[0,4\], *default*: 0  
  - “Controller Number” setting.  
    - 0: Controller 1  
    - 1: Controller 2  
    - 2: Controller 3  
    - 3: Controller 4  
    - **4: Auto**  
- **LorR**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Which Controller?” setting.  
    - **0: Joy-Con (L)**  
    - 1: Joy-Con (R)  
- **mode**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Mode” setting.  
    - **0: Hold**  
    - 1: Toggle  
- **carryingStyle**: *boolean*, *range*: \[0,1\], *default*: 0  
  - “Carrying Style” setting.  
    - **0: Precise**  
    - 1: Snappy  
- **snapDistance**: *float*, *range*: \[0.0,100.0\], *default*: 0.0  
  - “Snap Distance” setting value.  
- **rotationCenter**: *byte*, *range*: \[0,2\], *default*: 0  
  - “Center of Rotation” setting.  
    - **0: Wrist**  
    - 1: Elbow  
    - 2: Shoulder  
- **launchSpeed**: *float*, *range*: \[0.0,100.0\], *default*: 0.0  
  - “Launch Speed” setting value.

#### **Custom Nodon Functions**

##### **TBA**

#### **Appendix**

##### **Bit array parameters** {#bit-array-parameters}

Some Nodon settings allow you to individually toggle up to 40 different objects. Instead of adding up to 40 different parameters for each time this is required, these were instead condensed into two bit field parameters typically named “*setting*Normal” and “*setting*Fancy”. (e.g. destructibleNormal and destructibleFancy)  
Values inputted into these parameters are converted to binary, and then each bit of the number from right to left is interpreted as the enable for each setting. (i.e. b0 is the rightmost bit)

For example, a value of “23” when converted to binary is “10111”, and will only enable the settings for b0, b1, b2, and b4.  
One may also write values in terms of their binary equivalent by appending “0b” to the front of it. For instance, writing “0b10111” is the same as writing “23”.

*setting*Fancy:  
For “*setting*Fancy” parameters, they are 32-bit arrays which always map to the following list:

- b0: Crate  
- b1: Shipping Container  
- b2: Dice  
- b3: Panel  
- b4: Treasure Chest  
- b5: Television  
- b6: Joy-Con (R)  
- b7: Joy-Con (L)  
- b8: Soccer Ball  
- b9: Golf Ball  
- b10: Balloon  
- b11: Apple  
- b12: Turnip  
- b13: Fish  
- b14: Fluffball  
- b15: Alien  
- b16: Traveler  
- b17: Cheerleader  
- b18: Diver  
- b19: Mermaid  
- b20: Robot  
- b21: Sorceress  
- b22: Yeti  
- b23: Sumo Wrestler  
- b24: Hoop  
- b25: Arrow  
- b26: Rocket  
- b27: Pencil  
- b28: Tuna  
- b29: Chick  
- b30: Hippo  
- b31: Bear

*setting*Normal:  
For “*setting*Normal” parameters, they are 8-bit arrays, but map to slightly different lists depending on the setting:  
For “destructiveNormal” (most Object Nodons),  
“checkNormal” (Object Break Nodon),  
“destroyNormal” (Destroy Object Nodon),  
“teleportNormal” (Teleport Object Entrance Nodon), and  
“attractNormal”(Attract Object Nodon):

- b0: Box  
- b1: Cylinder  
- b2: Sphere  
- b3: Person  
- b4: Car  
- b5: UFO

For “destructibleNormal” (most Object Nodons):

- b0: World  
- b1: Box  
- b2: Cylinder  
- b3: Sphere  
- b4: Person  
- b5: Car  
- b6: UFO  
- b7: Destroy Object

For “senseNormal” (Touch Sensor Nodon):

- b0: World  
- b1: Box  
- b2: Cylinder  
- b3: Sphere  
- b4: Person  
- b5: Car  
- b6: UFO  
- b7: Head/Hands

Notes:

- The reason why these parameters did not just use a singular 40-bit array is because the largest datatype that the Arduino Leonardo can use only has 32 bits.  
- To enable all settings, a value of “4294967295” is required for “*setting*Fancy” parameters and a value of “255” can be used for any “*setting*Normal” parameter (even if “255” is not listed within their range in this document).  
  - Because of how underflow works, putting a value of “-1” into both settings will also enable all the settings.

##### **Characterization of createConnection** {#characterization-of-createconnection}

At zoom=4, the following are the Y coordinates where a connection is guaranteed to connect correctly for a Nodon at row 0:

| Input Count | Top Input | Middle Input |  | Bottom Input |
| :---- | :---: | :---: | :---: | :---: |
| One Input | 86 to 120 |  |  |  |
| Two Inputs | 79 to 95 |  | 96 to 121 |  |
| Three Inputs | 75 to 86 | 87 to 99 |  | 100 to 121 |
| Four Inputs | 73 to 82 | 83 to 92 | 93 to 101 | 102 to 121 |

The port parameter was characterized to place the mouse at Y coordinates 89.5, 80.5, 100.5, and 111 for port values 0, 1,  2, and 3 respectively to guarantee the following placements within 1 pixel of error:

| Input Count | inPort \== 0 | inPort \== 1 | inPort \== 2 | inPort \== 3 |
| :---- | :---: | :---: | :---: | :---: |
| One Input | Middle | ??? | Middle | Middle |
| Two Inputs | Top | Top | Bottom | Bottom |
| Three Inputs | Middle | Top | Bottom | Bottom |
| Four Inputs | Upper Middle | Top | Lower Middle | Bottom |

This configuration was chosen specifically to cover all inputs for 4-input Nodons while not needing inPort=3 for 3-input Nodons.  
For each following row, the mouse Y coordinate is offset by 49.818 pixels which achieves a maximum error of ±0.6 pixels.

At zoom=4, the following are the Y coordinates where a connection is guaranteed to be grabbed correctly from a Nodon at row 0:

| Output Count | Top Output | Middle Output |  | Bottom Output |
| :---- | :---: | :---: | :---: | :---: |
| One Output | 70 to 103 |  |  |  |
| Two Outputs | 66 to 92 |  | 93 to 110 |  |
| Three Outputs | 66 to 88 | 89 to 100 |  | 101 to 111 |

The port parameter was characterized to place the mouse at Y coordinates 90.5, 77, and 105.5 for port values 0, 1, and 2 respectively to guarantee the following placements within 1 pixel of error:

| Output Count | outPort \== 0 | outPort \== 1 | outPort \== 2 |
| :---- | :---: | :---: | :---: |
| One Output | Middle | ??? | ??? |
| Two Outputs | Top | Top | Bottom |
| Three Outputs | Middle | Top | Bottom |

This configuration was chosen specifically for outPort=0 to connect to Middle for 1 & 3 outputs, and Top for 2 outputs.  
For each following row, the mouse Y coordinate is offset by 49.846 pixels which achieves a maximum error of ±0.6 pixels.

The X coordinate for grabbing connections is defined as 106.5, offset by 62.25 pixels per column.  
This was characterized to be at the middle of 101 and 112, which is the range where a connection is guaranteed to be created, and not drag the Nodon or grab a nearby existing connection instead.

The X coordinate for terminating connections is defined as 88, offset by 62.25 pixels per column.  
This is based off of the definition used for grabbing, and offset to guarantee that the connection can only connect to a Nodon at the specified X grid position.

