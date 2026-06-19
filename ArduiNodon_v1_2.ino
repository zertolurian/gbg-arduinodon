/* -----------------------------------------------------------------------------------------
  ArduiNodon Importer
  v1.2
  Made for Arduino Leonardo by Zert
  Adapted from AGTD: Automatic GBG Texture Drawing by Borri & Scrubz

  IMPORTANT DEPENDENCIES:
  Libraries Dependency:    HID-Project by NicoHood https://github.com/NicoHood/HID/
  You can download libraries dependencies under Arduino Official IDE [Tools]/[Manage Libraries]
  ------------------------------------------------------------------------------------------*/
//               --Scroll down to line 200 to paste all your Nodon code!--
/*------------------------------------------------------------------------------------------
                                           CONFIG
/*------------------------------------------------------------------------------------------
  SLOW MODE - For projects with a lot of nodon a delay has to be added to astatic void lag induced
  miss-clicks on the GBG Program screen. Recommended values are:

  Recommended option for new GBG projects (Programming screen with minimal lag):
     int delay_mouse = 10;  (for Switch 1 users)
     int delay_mouse = 0;   (for Switch 2 users)

  Recommended option for existing GBG projects (Programming screen with medium-high lag):
     int delay_mouse = 20;  (for Switch 1 users)
     int delay_mouse = 10;  (for Switch 2 users)

  Adjust "delay_mouse" value if you still encounter problems.
  ------------------------------------------------------------------------------------------*/
int delay_mouse = 20;
/*------------------------------------------------------------------------------------------
  CODE COORDINATES
  Set the location where you want the script to build the code here.
  Make sure to set it where there's lots of space to reduce lag or mishaps!
  By default, it will be placed at [0,4].
  ------------------------------------------------------------------------------------------*/
float codeX    = 0;
float codeYorZ = 4;
/*------------------------------------------------------------------------------------------
  OVERWRITE MODE
  If you want the script to delete Nodons that are already in the spots where you want the
  Nodons to be placed, set this value to 1. Note that this will make the script slightly slower.
  Warning: Enabling may break for Game Screen, and any Nodon whose pos/rot/size have been changed.
  ------------------------------------------------------------------------------------------*/
boolean overwriteMode = 0;
/*------------------------------------------------------------------------------------------
  NO_BUTTON
  If don't have a button, or a wire to simulate it, you can un-comment both lines below to make
  the script run automatically. NO_BUTTON_DELAY sets delay (in seconds) before program start.
  ------------------------------------------------------------------------------------------*/
//  #define NO_BUTTON
//  #define NO_BUTTON_DELAY   30
/*------------------------------------------------------------------------------------------
  If button/Wire is present, define the Arduino input board PIN
  By default, pins 8, 9, 10, 11, 12, and 13 are enabled.
  ------------------------------------------------------------------------------------------*/
#define BUTTON_PIN    8
#define BUTTON_PIN2   9
#define BUTTON_PIN3   10
#define BUTTON_PIN4   11
#define BUTTON_PIN5   12
#define BUTTON_PIN6   13
/*------------------------------------------------------------------------------------------*/
#include "HID-Project.h"    // Remember to add this library from Tools/Manage Libraries!
/*------------------------------------------------------------------------------------------
                                        OTHER NOTES
  ------------------------------------------------------------------------------------------
  DOCUMENTATION
  If you want to know all the details and parameters for all the functions in this library, follow this link!
  https://docs.google.com/document/d/1k3etjDgX5qatUks1V0ngDcBNUjBsl_w2PmdcXI4GaDw/
  ------------------------------------------------------------------------------------------
  VERSION HISTORY
  v1.0 - Official release!
  v1.1 - Official release (for realzies now with UI and a lot of bug fixes)!
  v1.2 - Fixed rare misinputs after editObject, optimized sketch size
  ------------------------------------------------------------------------------------------
  PLANNED FEATURES
  Functionality to move and resize Nodons for Marker-based code.
  Custom Nodon functions that come up.
  ------------------------------------------------------------------------------------------*/
//               --Scroll down to line 200 to paste all your Nodon code!--
/*------------------------------------------------------------------------------------------
                                 FUNCTION FORWARD DECLARATIONS
  ------------------------------------------------------------------------------------------*/
static void resetScreen(float posX=0, float posZ=0, byte zoom=4);
static void createConnection(byte gridX1, byte gridY1, byte gridX2, byte gridY2, byte inPort=0, byte outPort=0);
static void createObjectConnection(byte gridX1, byte gridY1, byte gridX2, byte gridY2);
static void editObject (byte gridX, byte gridY, float sizeX=0, float sizeY=0, float sizeZ=0, float rotX=0, float rotY=0, float rotZ=0, float posX=404, float posY=404, float posZ=404, byte fancyAppearance=0, byte screenViewpoint=0);
static void createConstantNodon(byte gridX, byte gridY, float value=1);
static void createButtonNodon(byte gridX, byte gridY, boolean timing=1, byte controlNum=5, boolean enA=1, boolean enB=0, boolean enX=0, boolean enY=0, boolean enRight=0, boolean enDown=0, boolean enUp=0, boolean enLeft=0, boolean enL=0, boolean enR=0, boolean enZL=0, boolean enZR=0, boolean enL3=0, boolean enR3=0, boolean enSLL=0, boolean enSRL=0, boolean enSLR=0, boolean enSRR=0);
static void createStickNodon(byte gridX, byte gridY, byte controlNum=5, boolean DorA=1, float lowerIn=0.1, float upperIn=1, byte dirResponse=5, boolean LorR=0);
static void createIfTouchedNodon(byte gridX, byte gridY, boolean timing=1, boolean touchWhere=1);
static void createTouchPositionNodon(byte gridX, byte gridY);
static void createShakeNodon(byte gridX, byte gridY, byte checkWhat=0, byte controlNum=0, boolean DorA=1, float lowerIn=0.1, float upperIn=1, byte dirResponse=6);
static void createTiltNodon(byte gridX, byte gridY, byte checkWhat=0, byte controlNum=0, boolean DorA=1, float lowerIn=0, float upperIn=1, byte axisRotation=2, boolean mode=0);
static void createIfFaceUpNodon(byte gridX, byte gridY, byte checkWhat=0, byte controlNum=0, boolean DorA=1, float lowerIn=0.5, float upperIn=1, byte whichSide=1);
static void createRotationSpeedNodon(byte gridX, byte gridY, byte checkWhat=0, byte controlNum=0, boolean DorA=1, float lowerIn=0.1, float upperIn=1, byte axisRotation=2, byte dirResponse=2);
static void createIRMotionCameraNodon(byte gridX, byte gridY, byte controlNum=0, byte disRecognize=2, boolean mirrored=0);
static void createObjectBreakNodon(byte gridX, byte gridY, byte checkNormal=0b111, unsigned long checkFancy=0);
static void createOnStartNodon(byte gridX, byte gridY);
static void createCalculatorNodon(byte gridX, byte gridY, byte calcMethod=0);
static void createMapNodon(byte gridX, byte gridY, float lowerIn=0, float upperIn=1, float lowerOut=-1, float upperOut=1, bool invert=0, bool limitless=1);
static void createDigitizeNodon(byte gridX, byte gridY, byte stages=2);
static void createSquareRootNodon(byte gridX, byte gridY);
static void createAbsoluteValueNodon(byte gridX, byte gridY);
static void createInversionNodon(byte gridX, byte gridY);
static void createTriggerFrom0Nodon(byte gridX, byte gridY);
static void createPositionToAngleNodon(byte gridX, byte gridY);
static void createAngleToPositionNodon(byte gridX, byte gridY);
static void createAngleDifferenceNodon(byte gridX, byte gridY);
static void createComparisonNodon(byte gridX, byte gridY, byte method=0);
static void createANDNodon(byte gridX, byte gridY);
static void createNOTNodon(byte gridX, byte gridY);
static void createFlagNodon(byte gridX, byte gridY);
static void createCounterNodon(byte gridX, byte gridY, int startVal=0, byte mode=0, int lowerRange=0, int upperRange=1000, bool timing=1);
static void createRandomNodon(byte gridX, byte gridY, bool timing=0, int outputRange=10);
static void createTimerNodon(byte gridX, byte gridY, float outDelay=1, float outDuration=0);
static void createBullseyeNodon(byte gridX, byte gridY, boolean DorA=1, float lowerRange=0, float upperRange=1, boolean eyeShape=0);
static void createWormholeEntranceNodon(byte gridX, byte gridY, byte id=0);
static void createWormholeExitNodon(byte gridX, byte gridY, byte id=0);
static void createCommentNodon(byte gridX, byte gridY, String comment="Comment");
static void createPlaySoundNodon(byte gridX, byte gridY, byte category=11, byte subColumn=0, byte subRow=0);
static void createBackgroundMusicNodon(byte gridX, byte gridY, byte theme=6, byte melody=0, byte mainAcc=0, byte subAcc=0, byte rhythm=0);
static void createVibrationNodon(byte gridX, byte gridY, byte controlNum=0, boolean LorR=0, float outDuration=0, int freq=170);
static void createReduceGravityNodon(byte gridX, byte gridY);
static void createSlowTimeNodon(byte gridX, byte gridY);
static void createRetryNodon(byte gridX, byte gridY, byte transition=0);
static void createEndGameNodon(byte gridX, byte gridY);
static void createSwapGameNodon(byte gridX, byte gridY, boolean swapType=0, String targetKeyword="", String gameKeyword="", boolean transition=0);
static void createMarkerDisplayNodon(byte gridX, byte gridY, byte mode=0, boolean actBullseye=0);
static void create2DMarkerDisplayNodon(byte gridX, byte gridY, boolean DorA=1, float lowerRange=0, float upperRange=1, float markerSize=0.1, boolean actBullseye=0);
static void createContinuousMarkerDisplayNodon(byte gridX, byte gridY, boolean actBullseye=0);
static void createIRLightNodon(byte gridX, byte gridY, boolean controlNum=0, float outDuration=0);
static void createPersonNodon(byte gridX, byte gridY, boolean visible=1, boolean solid=1, byte destructibleNormal=0, unsigned long destructibleFancy=0, byte destructiveNormal=0, unsigned long destructiveFancy=0, boolean silent=0, boolean ungrabbable=0, byte color=0, boolean referenceFrame=1, byte action=0, float movementSpeed=1, float jumpStrength=1, float turningSpeed=0.1);
static void createCarNodon(byte gridX, byte gridY, boolean visible=1, boolean solid=1, byte destructibleNormal=0, unsigned long destructibleFancy=0, byte destructiveNormal=0, unsigned long destructiveFancy=0, boolean silent=0, boolean ungrabbable=0, byte color=0, float movementSpeed=1, float jumpStrength=1);
static void createUFONodon(byte gridX, byte gridY, boolean visible=1, boolean solid=1, byte destructibleNormal=0, unsigned long destructibleFancy=0, byte destructiveNormal=0, unsigned long destructiveFancy=0, boolean silent=0, boolean ungrabbable=0, byte color=0, boolean referenceFrame=1, float horizontalSpeed=1, float verticalSpeed=1, float turningSpeed=0.1);
static void createObjectNodon(byte gridX, byte gridY, byte shape=0, boolean visible=1, boolean solid=1, boolean movable=1, byte destructibleNormal=0b11111111, unsigned long destructibleFancy=0b11111111111111111111111111111111, byte destructiveNormal=0b11111111, unsigned long destructiveFancy=0b11111111111111111111111111111111, boolean silent=0, boolean ungrabbable=0, byte color=0, byte material=0, byte connectionType=0, byte connectionOwn=3, byte connectionTarget=4);
static void createFancyObjectNodon(byte gridX, byte gridY, boolean visible=1, boolean solid=1, boolean movable=1, byte destructibleNormal=0, unsigned long destructibleFancy=0, byte destructiveNormal=0, unsigned long destructiveFancy=0, boolean silent=0, boolean ungrabbable=0, byte material=0, byte connectionType=0, byte connectionOwn=3, byte connectionTarget=4);
static void createMovingObjectNodon(byte gridX, byte gridY, byte shape=0, boolean visible=1, boolean solid=1, byte destructibleNormal=0b11111111, unsigned long destructibleFancy=0b11111111111111111111111111111111, byte destructiveNormal=0b11111111, unsigned long destructiveFancy=0b11111111111111111111111111111111, boolean silent=0, boolean ungrabbable=0, byte color=0, byte material=0, byte connectionType=0, byte connectionOwn=3, byte connectionTarget=4, byte referenceFrame=0, boolean mode=0);
static void createRotatingObjectNodon(byte gridX, byte gridY, byte shape=0, boolean visible=1, boolean solid=1, byte destructibleNormal=0b11111111, unsigned long destructibleFancy=0b11111111111111111111111111111111, byte destructiveNormal=0b11111111, unsigned long destructiveFancy=0b11111111111111111111111111111111, boolean silent=0, boolean ungrabbable=0, byte color=0, byte material=0, byte connectionType=0, byte connectionOwn=3, byte connectionTarget=4, byte referenceFrame=0);
static void createExtendingObjectNodon(byte gridX, byte gridY, byte shape=0, boolean ungrabbable=1, byte color=0, byte connectionOwn=3, byte connectionTarget=4);
static void createEffectNodon(byte gridX, byte gridY, byte appearance=0, boolean effectTiming=0, boolean effectLocation=0, boolean visible=1, boolean ungrabbable=0, byte connectionOwn=0, byte connectionTarget=0);
static void createTextObjectNodon(byte gridX, byte gridY, String displayText="Text Object", boolean visible=1, boolean solid=1, boolean movable=1, byte destructibleNormal=0b11111111, unsigned long destructibleFancy=0b11111111111111111111111111111111, byte destructiveNormal=0b11111111, unsigned long destructiveFancy=0b11111111111111111111111111111111, boolean silent=0, boolean ungrabbable=0, byte color=0, byte textColor=11, byte material=0, byte connectionType=0, byte connectionOwn=3, byte connectionTarget=4, byte displaySide=5);
static void createNumberObjectNodon(byte gridX, byte gridY, boolean visible=1, boolean solid=1, boolean movable=1, byte destructibleNormal=0b11111111, unsigned long destructibleFancy=0b11111111111111111111111111111111, byte destructiveNormal=0b11111111, unsigned long destructiveFancy=0b11111111111111111111111111111111, boolean silent=0, boolean ungrabbable=0, byte color=0, byte textColor=11, byte material=0, byte connectionType=0, byte connectionOwn=3, byte connectionTarget=4, byte displaySide=5, byte wholeDigits=2, byte decimalDigits=0);
static void createTextureNodon(byte gridX, byte gridY, byte faceX=3, byte faceY=3, byte faceZ=3, byte mainColor=13, byte subColor=3);
static void createTouchSensorNodon(byte gridX, byte gridY, byte shape=0, boolean visible=1, boolean ungrabbable=0, boolean timing=1, byte connectionOwn=0, byte connectionTarget=0, byte senseNormal=0b1110, unsigned long senseFancy=0);
static void createDestroyingSensorNodon(byte gridX, byte gridY, byte shape=0, boolean visible=1, boolean ungrabbable=0, byte connectionOwn=0, byte connectionTarget=0);
static void createDestroyedSensorNodon(byte gridX, byte gridY, byte shape=0, boolean visible=1, boolean ungrabbable=0, byte connectionOwn=0, byte connectionTarget=0);
static void createGrabbedSensorNodon(byte gridX, byte gridY, byte shape=0, boolean visible=1, boolean ungrabbable=0, boolean timing=1, byte connectionOwn=0, byte connectionTarget=0);
static void createLocationSensorNodon(byte gridX, byte gridY, byte shape=0, boolean visible=1, boolean ungrabbable=0, byte connectionOwn=0, byte connectionTarget=0, byte referenceFrame=0);
static void createSpeedSensorNodon(byte gridX, byte gridY, byte shape=0, boolean visible=1, boolean ungrabbable=0, byte connectionOwn=0, byte connectionTarget=0, byte referenceFrame=0);
static void createAccelerationSensorNodon(byte gridX, byte gridY, byte shape=0, boolean visible=1, boolean ungrabbable=0, byte connectionOwn=0, byte connectionTarget=0, byte referenceFrame=0);
static void createAngleSensorNodon(byte gridX, byte gridY, byte shape=0, boolean visible=1, boolean ungrabbable=0, byte connectionOwn=0, byte connectionTarget=0, byte referenceFrame=0);
static void createRotationSpeedSensorNodon(byte gridX, byte gridY, byte shape=0, boolean visible=1, boolean ungrabbable=0, byte connectionOwn=0, byte connectionTarget=0, byte referenceFrame=0);
static void createSlideConnectorNodon(byte gridX, byte gridY, byte axis=0, float lowerRange=-100, float upperRange=100);
static void createFreeSlideConnectorNodon(byte gridX, byte gridY, boolean enX=1, boolean enY=1, boolean enZ=1);
static void createHingeConnectorNodon(byte gridX, byte gridY, byte axis=0, float lowerRange=-180, float upperRange=180);
static void createStringConnectorNodon(byte gridX, byte gridY, boolean visible=1, boolean solid=1, byte destructibleNormal=0, unsigned long destructibleFancy=0, byte destructiveNormal=0, unsigned long destructiveFancy=0, float strStiffness=0.5, float strLength=5);
static void createLaunchObjectNodon(byte gridX, byte gridY, byte launchLimit=0, byte shape=2, boolean visible=1, boolean solid=1, boolean movable=1, byte destructibleNormal=0b11111111, unsigned long destructibleFancy=0b11111111111111111111111111111111, byte destructiveNormal=0b11111111, unsigned long destructiveFancy=0b11111111111111111111111111111111, boolean silent=0, boolean ungrabbable=0, byte color=0, byte material=0, byte connectionOwn=0, byte connectionTarget=0, byte launchDirection=2, float launchSpeed=10, float launchInterval=1);
static void createDestroyObjectNodon(byte gridX, byte gridY, byte shape=0, boolean visible=1, boolean ungrabbable=0, byte connectionOwn=0, byte connectionTarget=0, byte destroyNormal=0b111, unsigned long destroyFancy=0);
static void createTeleportObjectEntranceNodon(byte gridX, byte gridY, byte teleportID=0, byte shape=0, boolean visible=1, boolean ungrabbable=0, byte connectionOwn=0, byte connectionTarget=0, byte teleportNormal=0b111, unsigned long teleportFancy=0);
static void createTeleportObjectExitNodon(byte gridX, byte gridY, byte teleportID=0, byte shape=0, boolean visible=1, boolean ungrabbable=0, byte connectionOwn=0, byte connectionTarget=0, boolean teleportPhysics=0, float launchSpeed=0, byte launchDirection=1);
static void createAttractObjectNodon(byte gridX, byte gridY, byte shape=0, boolean visible=1, boolean ungrabbable=0, byte connectionOwn=0, byte connectionTarget=0, byte attractCenter=6, byte attractNormal=0b111, unsigned long attractFancy=0);
static void createWorldNodon(byte gridX, byte gridY, byte worldShape=1, byte worldAppearance=0, byte worldLighting=0, int sunDirection=-130, int sunHeight=52, byte worldMaterial=0, byte objectAppearance=0, byte destructiveNormal=0, unsigned long destructiveFancy=0, float destructionSpeed=0.1);
static void createGameScreenNodon(byte gridX, byte gridY, float horizontalTrack=0.2, float verticalTrack=0.2, float cameraFOV=60);
static void createCameraNodon(byte gridX, byte gridY, float horizontalTrack=0.2, float verticalTrack=0.2, float cameraFOV=90, boolean trackRotation=0, float offsetX=0, float offsetY=0, float offsetZ=0);
static void createCameraPositionNodon(byte gridX, byte gridY, float horizontalTrack=0.5, float verticalTrack=0.5, byte connectionOwn=0, byte connectionTarget=0, float offsetX=0, float offsetY=0, float offsetZ=0);
static void createCameraTargetNodon(byte gridX, byte gridY, float horizontalTrack=0.5, float verticalTrack=0.5, byte connectionOwn=0, byte connectionTarget=0, float offsetX=0, float offsetY=0, float offsetZ=0);
static void createCameraDirectionNodon(byte gridX, byte gridY);
static void createCameraAngleNodon(byte gridX, byte gridY, float cameraFOV=90);
static void createHeadNodon(byte gridX, byte gridY);
static void createHandNodon(byte gridX, byte gridY, byte controlNum=4, boolean LorR=0, boolean mode=0, boolean carryingStyle=0, float snapDistance=0, byte rotationCenter=0, float launchSpeed=0);
void setup(void) {
  BootKeyboard.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PIN2, INPUT_PULLUP);
  pinMode(BUTTON_PIN3, INPUT_PULLUP);
  pinMode(BUTTON_PIN4, INPUT_PULLUP);
  pinMode(BUTTON_PIN5, INPUT_PULLUP);
  pinMode(BUTTON_PIN6, INPUT_PULLUP);
#if defined(NO_BUTTON)
  delay(NO_BUTTON_DELAY * 1000);
#endif
}
void loop() {
#ifndef NO_BUTTON
  while (digitalRead(BUTTON_PIN)*digitalRead(BUTTON_PIN2)*digitalRead(BUTTON_PIN3)*digitalRead(BUTTON_PIN4)*digitalRead(BUTTON_PIN5)*digitalRead(BUTTON_PIN6) == HIGH) delay(100);
#endif
resetScreen(codeX,codeYorZ);  //moves programming screen and sets correct zoom
/*  ------------------------------------------------------------------------------------------
                                 NODON CODE SPACE - START
                              - PASTE HERE YOUR NODON CODE -
    ------------------------------------------------------------------------------------------*/
//Note: If your Nodon code has a Person Nodon, use top-down view or else the code will break!
//PASTE YOUR NODON CODE HERE
//PASTE YOUR NODON CODE HERE
//PASTE YOUR NODON CODE HERE
//PASTE YOUR NODON CODE HERE
//PASTE YOUR NODON CODE HERE
//PASTE YOUR NODON CODE HERE
//PASTE YOUR NODON CODE HERE
//PASTE YOUR NODON CODE HERE
//PASTE YOUR NODON CODE HERE
//PASTE YOUR NODON CODE HERE
//PASTE YOUR NODON CODE HERE
//PASTE YOUR NODON CODE HERE
//PASTE YOUR NODON CODE HERE
//PASTE YOUR NODON CODE HERE
//PASTE YOUR NODON CODE HERE
//PASTE YOUR NODON CODE HERE
//PASTE YOUR NODON CODE HERE
//PASTE YOUR NODON CODE HERE
//PASTE YOUR NODON CODE HERE
//PASTE YOUR NODON CODE HERE
/* -----------------------------------------------------------------------------------------
                                 NODON CODE SPACE - END
   ------------------------------------------------------------------------------------------*/
}
/*------------------------------------------------------------------------------------------
                                   FUNCTION DEFINITIONS
  ------------------------------------------------------------------------------------------*/
int mouseX = 0;
int mouseY = 0;
byte nodonGrid[19][11];
boolean connectedGrid[19][11];
boolean compactMode = 0;
int nodonStretchX = 0;
int nodonStretchY = 0;
boolean justPlacedNodon = 0;

static void clickMouse() {
  delay(40 + delay_mouse);
  Mouse.press(MOUSE_LEFT);
  delay(30 + delay_mouse);
  Mouse.release(MOUSE_LEFT);
}

static void moveMouseTo (int targetX, int targetY) {
  int moveX, moveY;
  while ((targetX - mouseX) || (targetY - mouseY)) {
    moveX = min(max(targetX - mouseX, -127), 127);
    moveY = min(max(targetY - mouseY, -127), 127);
    Mouse.move(moveX,moveY);
    mouseX = mouseX + moveX;
    mouseY = mouseY + moveY;
  }
}

static void clickMouseAt (int targetX, int targetY) {
  moveMouseTo(targetX, targetY);
  clickMouse();
}

static void resetMouse() {
  for (int i = 0; i < 20; i++) {
    Mouse.move(-127,-127);
  }
  mouseX = 0;
  mouseY = 0;
}

static void dragMouseAcross (int x1, int y1, int x2, int y2) {
  int moveX, moveY;
  moveMouseTo(x1, y1);
  delay(40 + delay_mouse);
  Mouse.press(MOUSE_LEFT); 
  delay(40 + delay_mouse);
  moveMouseTo(x2, y2);
  delay(40 + delay_mouse);
  Mouse.release(MOUSE_LEFT); 
}

/*------------------------------------------------------------------------------------------
                                       AUX NODON FUNCTIONS
  ------------------------------------------------------------------------------------------*/

static void callNodon (byte category, byte column1, byte column2=0, byte column3=0) {
  clickMouseAt(30+category*100, 690);      //Input/Middle/Output/Objects
  clickMouseAt(30+category*100, 690-column1*60);      //First Column
  if (column2) clickMouseAt(350+category*100, 690-column2*60);      //Second Column
  if (column3) clickMouseAt(670+category*100, 690-column3*60);      //Third Column
  delay(100 + delay_mouse);    //Wait for Nodon creation
}

static void deleteNodon (byte gridX, byte gridY) {
  clickMouseAt(round(99+62.25*gridX),round(86+49.846*gridY)); //select Nodon
  clickMouseAt(round(106+62.25*gridX),round(162+49.846*gridY)); //delete
}

static void editNodon () {
  clickMouseAt(562, 458);
}

static void closeNodon () {
  clickMouseAt(1240, 40);
}

static void dragNodonToGrid (int gridX, int gridY, byte nodonID=0) {
  if (overwriteMode) {
    deleteNodon(gridX, gridY);
    clickMouseAt(639, 337);
  }
  dragMouseAcross(639, 404, round(80+62.11*gridX), 129+50*gridY);
  nodonGrid[gridX][gridY] = nodonID;
  justPlacedNodon = 1;
}

static void inputNumber(char n) {
  switch (n) {
    case '0':
      clickMouseAt(560, 550);
    break;
    case '1':
      clickMouseAt(480, 470);
    break;
    case '2':
      clickMouseAt(560, 470);
    break;
    case '3':
      clickMouseAt(640, 470);
    break;
    case '4':
      clickMouseAt(480, 400);
    break;
    case '5':
      clickMouseAt(560, 400);
    break;
    case '6':
      clickMouseAt(640, 400);
    break;
    case '7':
      clickMouseAt(480, 320);
    break;
    case '8':
      clickMouseAt(560, 320);
    break;
    case '9':
      clickMouseAt(640, 320);
    break;
    case '-':
      clickMouseAt(480, 550);
    break;
    case '.':
      clickMouseAt(640, 550);
    break;
    default:
      clickMouseAt(760, 550);
    break;
  }
}

static void inputCalculator(int offsetX, int offsetY, float n) {
  float nFloatInt = floor(abs(n));
  float nFloatDec = abs(n)-nFloatInt;
  unsigned long nInt = round(nFloatInt);
  unsigned long nDec;
  if (nInt>=100) {
    nDec = round(nFloatDec*10000)*1000;
  } else if (nInt>=10) {
    nDec = round(nFloatDec*100000)*100;
  } else if (nInt>=1) {
    nDec = round(nFloatDec*1000000)*10;
  } else {
    nDec = round(nFloatDec*10000000);
  }
  if (nDec>=10000000) {
    nDec = 0;
    nInt++;
  }
  String nString = String(nInt);
  byte nLength = nString.length();
  clickMouseAt(offsetX, offsetY);  //Open menu
  if (n<0) inputNumber('-');  //Negative sign
  if (nInt || !nDec) { //Integer part
    for (byte i=0; i < nLength; i++) inputNumber(nString[i]);
  }
  if (nDec) { //Decimal part
    nDec = nDec + 10000000; //Induce leading 0's
    while (nDec%10 == 0) nDec = nDec/10;
    nString = String(nDec);
    nString[0] = '.';       //Replace leading 1 with decimal point
    nLength = nString.length();
    for (byte i=0; i < nLength; i++) inputNumber(nString[i]);
  }
  inputNumber(12);  //OK
}

static void inputKeyboard(int offsetX, int offsetY, String inputText) {
  clickMouseAt(offsetX, offsetY);  //Open menu
  delay(1500);
  for (int i=0; i<11; i++) {  //Remove "Comment"
    BootKeyboard.press(KEY_BACKSPACE);
    delay(34);
    BootKeyboard.release(KEY_BACKSPACE);
    delay(34);
  }
  for (int i=0; i<inputText.length(); i++) {  //Type code
    BootKeyboard.press(inputText[i]);
    delay(34);
    BootKeyboard.release(inputText[i]);
    delay(34);
  }
  BootKeyboard.press(KEY_RIGHT_SHIFT);
  BootKeyboard.press(KEY_RETURN);
  delay(34);
  BootKeyboard.release(KEY_RETURN);
  BootKeyboard.release(KEY_RIGHT_SHIFT);
  delay(1500);
}

static void objectList(int offsetX, int offsetY, unsigned long normalObjects, unsigned long fancyObjects=0) {
  unsigned long longBuffer;
  boolean bitBuffer;
  byte count;
  clickMouseAt(offsetX, offsetY);  //Open menu
  longBuffer = normalObjects;
  for (count=0; count<40; count++) {
    if (count==8) longBuffer = fancyObjects;
    bitBuffer = longBuffer & 1;
    if (bitBuffer) clickMouseAt(170+(count/8)*208, 140+(count%8)*64);
    longBuffer = longBuffer>>1;
  }
  closeNodon();    //Close menu
}

static void objectProperties(int offsetY, boolean visible=0, boolean solid=0, boolean movable=0, byte destructibleNormal=0, unsigned long destructibleFancy=0, byte destructiveNormal=0, unsigned long destructiveFancy=0, boolean silent=0, boolean ungrabbable=0) {
  if (visible) clickMouseAt(150, offsetY);      //Visible
  if (solid) clickMouseAt(360, offsetY);      //Solid
  if (movable) clickMouseAt(570, offsetY);      //Movable
  if (destructibleNormal || destructibleFancy) {
    if (destructibleNormal==0b11111111 && destructibleFancy==0b11111111111111111111111111111111) {
      clickMouseAt(150, offsetY+65);  //Destructible
    } else {
      objectList(235, offsetY+65, destructibleNormal, destructibleFancy); //...
    }
  }
  if (destructiveNormal || destructiveFancy) {
    if (destructiveNormal==0b11111111 && destructiveFancy==0b11111111111111111111111111111111) {
      clickMouseAt(360, offsetY+65);  //Destructive
    } else {
      objectList(445, offsetY+65, destructiveNormal&0b111111, destructiveFancy); //...
    }
  }
  if (silent || ungrabbable) {
    clickMouseAt(570, offsetY+65);    //Other
    if (silent) clickMouseAt(390, 160);    //Play Sound...?; Don't Play
    if (ungrabbable) clickMouseAt(390, 260);    //Can Be Grabbed...?; Can't be grabbed
    closeNodon();    //Close Other settings
  }
}

static void objectMenu(int offsetX, int offsetY, byte selX=0, byte selY=0) {
  clickMouseAt(offsetX, offsetY);  //Open menu
  clickMouseAt(90+selX*208, 140+selY*64);    //Select option
}

static void objectConnectionPoint(int offsetX, int offsetY, byte connectionOwn=0, byte connectionTarget=0, byte connectionOwnDefault=0, byte connectionTargetDefault=0) {
  clickMouseAt(offsetX, offsetY);  //Open menu
  if (connectionOwn>6 || connectionTarget>6) {
    clickMouseAt(170, 140);    //Auto
  } else {
    if (connectionOwn!=connectionOwnDefault) clickMouseAt(110+75*connectionOwn, 240);      //Own Connection Point
    if (connectionTarget!=connectionTargetDefault) clickMouseAt(110+75*connectionTarget, 320);      //Target Connection Point
  }
  closeNodon();    //Close menu
}

static void objectTriple(int offsetX, int offsetY, float inTop, float inMid, float inBot, float inDefault=0) {
  if (inTop!=inDefault) inputCalculator(offsetX,offsetY,inTop);
  //delay(40 + delay_mouse);
  if (inMid!=inDefault) inputCalculator(offsetX,offsetY+60,inMid);
  //delay(40 + delay_mouse);
  if (inBot!=inDefault) inputCalculator(offsetX,offsetY+120,inBot);
  //delay(40 + delay_mouse);
}

static void objectNonuple(int offsetY, float inTop1=0, float inMid1=0, float inBot1=0, float inTop2=404, float inMid2=404, float inBot2=404, float inTop3=0, float inMid3=0, float inBot3=0) {
  objectTriple(870,offsetY,inTop1,inMid1,inBot1);
  objectTriple(870+244,offsetY,inTop2,inMid2,inBot2,404);
  objectTriple(870,offsetY+210,inTop3,inMid3,inBot3);
}

/*------------------------------------------------------------------------------------------
                                       GENERAL USER FUNCTIONS
  ------------------------------------------------------------------------------------------*/

static void resetScreen(float posX, float posZ, byte zoom) {
  resetMouse();
  for (byte i = 0; i < 80; i++) Mouse.move(0, 0, 1);  //Zoom fully in
  float roundedX = round(posX/0.2)*0.2;  //Round coordinates to 0.2 grid
  float roundedZ = round(posZ/0.2)*0.2;  //Z or Y to work for either view
  callNodon(3,5,6);      //Location Sensor
  delay(100+delay_mouse);
  clickMouseAt(550, 560);      //Edit gear icon, @ full zoom
  objectTriple(1120, 250, roundedX, roundedZ, roundedZ, 404);
  closeNodon();      //Close Nodon
  clickMouseAt(710, 690);      //Undo
  for (byte i = 0; i < 20; i++) Mouse.move(0, 0, 1);  //Zoom fully in
  clickMouseAt(760, 690);      //Redo
  for (byte i = 0; i < 80; i++) Mouse.move(0, 0, -1);  //Zoom fully out
  clickMouseAt(670, 440);      //Delete Nodon
  moveMouseTo(950, 690);                               //Zoom to setting
  for (byte i = 0; i < zoom; i++) {
    clickMouse();
    delay(20+delay_mouse);
  }
}

static void createConnection(byte gridX1, byte gridY1, byte gridX2, byte gridY2, byte inPort, byte outPort) {
  if (justPlacedNodon) {
    clickMouseAt(640,719);
    justPlacedNodon = 0;
  }
  float inOffset = 89.5;
  if (inPort==1) inOffset=80.5;
  if (inPort==2) inOffset=100.5;
  if (inPort==3) inOffset=111;
  float outOffset = 90.5;
  if (outPort==1) outOffset=77;
  if (outPort==2) outOffset=105.5;
  dragMouseAcross(round(93.5+62.25*gridX1), round(outOffset+(49.846*gridY1)), round(75+62.25*gridX2), round(inOffset+(49.818*gridY2)));
}

static void createObjectConnection(byte gridX1, byte gridY1, byte gridX2, byte gridY2) {
  if (justPlacedNodon) {
    clickMouseAt(640,719);
    justPlacedNodon = 0;
  }
  if (!connectedGrid[gridX1][gridY1]) {
    dragMouseAcross(round(64+62.25*gridX1), round(104+(49.846*gridY1)), round(64+62.25*gridX2), round(80+(49.818*gridY2)));
    connectedGrid[gridX1][gridY1] = 1;
  } else {  //additional connections to Texture need to be connected from top->bottom
    clickMouseAt(round(99+62.25*gridX2),round(86+49.846*gridY2)); //select Nodon
    dragMouseAcross(round(48+62.25*gridX2), round(56+(49.818*gridY2)), round(64+62.25*gridX1), round(104+(49.846*gridY1))); //reverse
  }
  
  
  
}

static void editObject (byte gridX, byte gridY, float sizeX, float sizeY, float sizeZ, float rotX, float rotY, float rotZ, float posX, float posY, float posZ, byte fancyAppearance, byte screenViewpoint) {
  clickMouseAt(round(99+62.25*gridX),round(86+49.846*gridY)); //select Nodon
  if (nodonGrid[gridX][gridY]!=9) {
    clickMouseAt(round(158+62.25*gridX),round(162+49.846*gridY)); //lock
    clickMouseAt(round(2+62.25*gridX),round(162+49.846*gridY));   //edit
    if (fancyAppearance) objectMenu(150, 150, fancyAppearance/8, fancyAppearance%8); //Appearance
    if (nodonGrid[gridX][gridY]==1) objectNonuple(370,sizeX,sizeY,sizeZ,posX,posY,posZ,rotY);
    if (nodonGrid[gridX][gridY]==2) objectNonuple(263,sizeX,sizeY,sizeZ,posX,posY,posZ,rotY);
    if (nodonGrid[gridX][gridY]==3) objectNonuple(263,sizeX,sizeY,sizeZ,posX,posY,posZ,rotX,rotY,rotZ);
    if (nodonGrid[gridX][gridY]==4) objectNonuple(150,sizeX,sizeY,sizeZ,posX,posY,posZ,rotX,rotY,rotZ);
    if (nodonGrid[gridX][gridY]==5) objectNonuple(360,sizeX,sizeY,sizeZ,posX,posY,posZ,rotX,rotY,rotZ);
    if (nodonGrid[gridX][gridY]==6) {
      objectTriple(150,250,sizeX,sizeY,0);
      objectTriple(150,400,posX,posY,posZ,404);
      if (rotX) inputCalculator(150,610,rotX);
    }
    if (nodonGrid[gridX][gridY]==7) objectNonuple(315,sizeX,sizeY,sizeZ,posX,posY,posZ,rotX,rotY,rotZ);
    if (nodonGrid[gridX][gridY]==8) objectTriple(960,150,posX,posY,posZ,404);
    if (nodonGrid[gridX][gridY]==10) {
      objectTriple(630,150,posX,posY,posZ,404);
      objectTriple(870,150,sizeX,sizeY,sizeZ,404);
      if (rotX) inputCalculator(630,490,rotX);
      if (rotY) inputCalculator(870,490,rotY);
    }
  } else {  //Game Screen
    clickMouseAt(round(200+62.25*gridX),round(162+49.846*gridY));
    clickMouseAt(round(15+62.25*gridX),round(162+49.846*gridY));
    if (screenViewpoint==1) clickMouseAt(630,150);
    if (screenViewpoint==2) clickMouseAt(840,150);
    objectTriple(630,250,sizeX,sizeY,0);
    objectTriple(870,250,posX,posY,posZ,404);
  }
  closeNodon();
  clickMouseAt(640,719);
}

/*------------------------------------------------------------------------------------------
                                       INPUT NODON FUNCTIONS
  ------------------------------------------------------------------------------------------*/

static void createConstantNodon(byte gridX, byte gridY, float value) {
  callNodon(0,6);
  if (value!=1) {
    editNodon();      //Edit gear icon
    inputCalculator(670, 150, value); //Value
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createButtonNodon(byte gridX, byte gridY, boolean timing, byte controlNum, boolean enA, boolean enB, boolean enX, boolean enY, boolean enRight, boolean enDown, boolean enUp, boolean enLeft, boolean enL, boolean enR, boolean enZL, boolean enZR, boolean enL3, boolean enR3, boolean enSLL, boolean enSRL, boolean enSLR, boolean enSRR) {
  callNodon(0,5,9); //(A)
  if (!timing || controlNum!=5 || !enA || enB || enX || enY || enRight || enDown || enUp || enLeft || enL || enR || enZL || enZR || enL3 || enR3 || enSLL || enSRL || enSLR || enSRR) {
    editNodon();      //Edit gear icon
    if (!timing) clickMouseAt(160, 150);  //On press
    if (controlNum!=5) clickMouseAt(90+83*controlNum, 250);  //Controller number
    if (!enA) clickMouseAt(1100, 340);     //Unselect A
    if (enB) clickMouseAt(1060, 390);      //B
    if (enX) clickMouseAt(1060, 290);      //X
    if (enY) clickMouseAt(1010, 340);      //Y
    if (enRight) clickMouseAt(740, 430);      //>
    if (enDown) clickMouseAt(700, 480);      //v
    if (enUp) clickMouseAt(700, 380);      //^
    if (enLeft) clickMouseAt(640, 430);      //<
    if (enL) clickMouseAt(670, 150);      //L
    if (enR) clickMouseAt(1080, 150);      //R
    if (enZL) clickMouseAt(590, 190);      //ZL
    if (enZR) clickMouseAt(1160, 190);     //ZR
    if (enL3) clickMouseAt(700, 300);      //L3
    if (enR3) clickMouseAt(1060, 470);      //R3
    if (enSLL) clickMouseAt(820, 300);      //SLL
    if (enSLR) clickMouseAt(930, 470);      //SLR
    if (enSRL) clickMouseAt(820, 470);      //SRL
    if (enSRR) clickMouseAt(930, 300);      //SRR
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createStickNodon(byte gridX, byte gridY, byte controlNum, boolean DorA, float lowerIn, float upperIn, byte dirResponse, boolean LorR) {
  callNodon(0,4,4-LorR,4-LorR-(dirResponse==6)); //(L)
  if (controlNum!=5 || !DorA || lowerIn!=0.1 || upperIn!=1 || dirResponse<5 || LorR) {
    editNodon();      //Edit gear icon
    if (controlNum!=5) clickMouseAt(90+controlNum*83, 150); //Controller Number
    if (!DorA) clickMouseAt(150, 310);  //Output; Digital
    if (lowerIn!=0.1) inputCalculator(260, 380, lowerIn); //Range; left
    if (upperIn!=1) inputCalculator(400, 380, upperIn); //Range; right
    if (dirResponse<5) clickMouseAt(600+dirResponse*128, 150);  //Direction of Response
    if (LorR) clickMouseAt(840, 310);  //Which Stick?; Right Stick
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createIfTouchedNodon(byte gridX, byte gridY, boolean timing, boolean touchWhere) {
  callNodon(0,3,3);
  if (!timing || !touchWhere) {
    editNodon();      //Edit gear icon
    if (!timing) clickMouseAt(150, 150);  //Output Timing; On touch
    if (!touchWhere) clickMouseAt(150, 250);  //Touch Where to Output?; This Nodon
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createTouchPositionNodon(byte gridX, byte gridY) {
  callNodon(0,3,2); //Touch Position
  dragNodonToGrid(gridX,gridY);
}

static void createShakeNodon(byte gridX, byte gridY, byte checkWhat, byte controlNum, boolean DorA, float lowerIn, float upperIn, byte dirResponse) {
  callNodon(0,2,6,7-checkWhat); //Auto
  if (controlNum || !DorA || lowerIn!=0.1 || upperIn!=1 || dirResponse!=6) {
    editNodon();      //Edit gear icon
    if (controlNum) clickMouseAt(100+controlNum*100, 310); //Controller Number
    if (!DorA) clickMouseAt(150, 410);  //Output; Digital
    if (lowerIn!=0.1) inputCalculator(260, 480, lowerIn); //Range; left
    if (upperIn!=1) inputCalculator(400, 480, upperIn); //Range; right
    if (dirResponse==0) clickMouseAt(600, 250);  //Direction of Response; X-
    if (dirResponse==1) clickMouseAt(930, 410);  //X+
    if (dirResponse==2) clickMouseAt(770, 470);  //Y-
    if (dirResponse==3) clickMouseAt(770, 200);  //Y+
    if (dirResponse==4) clickMouseAt(650, 440);  //Z-
    if (dirResponse==5) clickMouseAt(880, 220);  //Z+
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createTiltNodon(byte gridX, byte gridY, byte checkWhat, byte controlNum, boolean DorA, float lowerIn, float upperIn, byte axisRotation, boolean mode) {
  callNodon(0,2,5,6-checkWhat); //Auto
  if (controlNum || !DorA || lowerIn!=0 || upperIn!=1 || axisRotation!=2 || mode) {
    editNodon();      //Edit gear icon
    if (controlNum) clickMouseAt(100+controlNum*100, 310); //Controller Number
    if (!DorA) clickMouseAt(150, 410);  //Output; Digital
    if (lowerIn!=0) inputCalculator(260, 480, lowerIn); //Range; left
    if (upperIn!=1) inputCalculator(400, 480, upperIn); //Range; right
    if (axisRotation==0) clickMouseAt(930, 380);  //Axis of Rotation; X
    if (axisRotation==1) clickMouseAt(770, 170);  //Y
    if (mode) clickMouseAt(840, 520);  //Mode; Angle of rotation
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createIfFaceUpNodon(byte gridX, byte gridY, byte checkWhat, byte controlNum, boolean DorA, float lowerIn, float upperIn, byte whichSide) {
  callNodon(0,2,4,5-checkWhat); //Auto
  if (controlNum || !DorA || lowerIn!=0.5 || upperIn!=1 || whichSide!=1) {
    editNodon();      //Edit gear icon
    if (controlNum) clickMouseAt(100+controlNum*100, 310); //Controller Number
    if (!DorA) clickMouseAt(150, 410);  //Output; Digital
    if (lowerIn!=0.5) inputCalculator(260, 480, lowerIn); //Range; left
    if (upperIn!=1) inputCalculator(400, 480, upperIn); //Range; right
    if (whichSide!=1) clickMouseAt(620+(whichSide%3)*200, 230+(whichSide/3)*220);  //Which Side Should Face Up?
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createRotationSpeedNodon(byte gridX, byte gridY, byte checkWhat, byte controlNum, boolean DorA, float lowerIn, float upperIn, byte axisRotation, byte dirResponse) {
  callNodon(0,2,3,4-checkWhat); //Auto
  if (controlNum || !DorA || lowerIn!=0.1 || upperIn!=1 || axisRotation!=2 || dirResponse!=2) {
    editNodon();      //Edit gear icon
    if (controlNum) clickMouseAt(100+controlNum*100, 310); //Controller Number
    if (!DorA) clickMouseAt(150, 410);  //Output; Digital
    if (lowerIn!=0.1) inputCalculator(260, 480, lowerIn); //Range; left
    if (upperIn!=1) inputCalculator(400, 480, upperIn); //Range; right
    if (axisRotation==0) clickMouseAt(930, 380);  //Axis of Rotation; X
    if (axisRotation==1) clickMouseAt(770, 170);  //Y
    if (axisRotation==3) clickMouseAt(1040, 390);  //Any
    if (dirResponse!=2) clickMouseAt(590+dirResponse*110, 550);  //Mode; Angle of rotation
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createIRMotionCameraNodon(byte gridX, byte gridY, byte controlNum, byte disRecognize, boolean mirrored) {
  callNodon(0,2,2);
  if (controlNum || disRecognize!=2 || mirrored) {
    editNodon();      //Edit gear icon
    if (controlNum) clickMouseAt(360, 150); //Check What?
    if (disRecognize!=2) clickMouseAt(610+disRecognize*155, 150); //Distance to Recognize
    if (mirrored) clickMouseAt(910, 410);  //<->
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createObjectBreakNodon(byte gridX, byte gridY, byte checkNormal, unsigned long checkFancy) {
  callNodon(0,1,2);
  if (checkNormal!=0b111 || checkFancy) {
    editNodon();      //Edit gear icon
    objectList(260, 180, (checkNormal^0b111)&0b111111, checkFancy);
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createOnStartNodon(byte gridX, byte gridY) {
  callNodon(0,1,1);
  dragNodonToGrid(gridX,gridY);
}

/*------------------------------------------------------------------------------------------
                                       MIDDLE NODON FUNCTIONS
  ------------------------------------------------------------------------------------------*/

static void createCalculatorNodon(byte gridX, byte gridY, byte calcMethod) {
  callNodon(1,9,9-calcMethod);
  dragNodonToGrid(gridX,gridY);
}

static void createMapNodon(byte gridX, byte gridY, float lowerIn, float upperIn, float lowerOut, float upperOut, bool invert, bool limitless) {
  callNodon(1,8,10);
  if (lowerIn!=0 || upperIn!=1 || lowerOut!= -1 || upperOut!=1 || invert || !limitless) {
    editNodon();      //Edit gear icon
    if (lowerIn>1) {  //If upper should be inputted first
      if (upperIn!=1) inputCalculator(710, 120, upperIn); //Upper input
      if (lowerIn!=0) inputCalculator(560, 120, lowerIn); //Lower input
    } else {
      if (lowerIn!=0) inputCalculator(560, 120, lowerIn); //Lower input
      if (upperIn!=1) inputCalculator(710, 120, upperIn); //Upper input
    }
    if (lowerOut>1) { //If upper should be inputted first
      if (upperOut!=1) inputCalculator(710, 270, upperOut);  //Upper output
      if (lowerOut!=-1) inputCalculator(560, 270, lowerOut);  //Lower output
    } else {
      if (lowerOut!=-1) inputCalculator(560, 270, lowerOut);  //Lower output
      if (upperOut!=1) inputCalculator(710, 270, upperOut);  //Upper output
    }
    if (invert) clickMouseAt(860, 350);  //Invert
    if (!limitless) clickMouseAt(150, 460);   //Limit range
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createDigitizeNodon(byte gridX, byte gridY, byte stages) {
  callNodon(1,8,9);
  if (stages!=2) {
    editNodon();      //Edit gear icon   
    inputCalculator(400, 120, stages);  //Stages
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createSquareRootNodon(byte gridX, byte gridY) {
  callNodon(1,8,8);
  dragNodonToGrid(gridX,gridY);
}

static void createAbsoluteValueNodon(byte gridX, byte gridY) {
  callNodon(1,8,7);
  dragNodonToGrid(gridX,gridY);
}

static void createInversionNodon(byte gridX, byte gridY) {
  callNodon(1,8,6);
  dragNodonToGrid(gridX,gridY);
}

static void createTriggerFrom0Nodon(byte gridX, byte gridY) {
  callNodon(1,8,5);
  dragNodonToGrid(gridX,gridY);
}

static void createPositionToAngleNodon(byte gridX, byte gridY) {
  callNodon(1,7,7);
  dragNodonToGrid(gridX,gridY);
}

static void createAngleToPositionNodon(byte gridX, byte gridY) {
  callNodon(1,7,6);
  dragNodonToGrid(gridX,gridY);
}

static void createAngleDifferenceNodon(byte gridX, byte gridY) {
  callNodon(1,7,5);
  dragNodonToGrid(gridX,gridY);
}

static void createComparisonNodon(byte gridX, byte gridY, byte method) {
  if (method==1) callNodon(1,6,4);
  if (method==2) callNodon(1,6,5);
  if (method==0 || method>2) callNodon(1,6,6);
  if (method>2) {
    editNodon();      //Edit gear icon
    clickMouseAt(150+method*210, 150);  //Comparison method
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createANDNodon(byte gridX, byte gridY) {
  callNodon(1,5,5);
  dragNodonToGrid(gridX,gridY);
}

static void createNOTNodon(byte gridX, byte gridY) {
  callNodon(1,5,4);
  dragNodonToGrid(gridX,gridY);
}

static void createFlagNodon(byte gridX, byte gridY) {
  callNodon(1,4,5);
  dragNodonToGrid(gridX,gridY);
}

static void createCounterNodon(byte gridX, byte gridY, int startVal, byte mode, int lowerRange, int upperRange, bool timing) {
  callNodon(1,4,4);
  if (startVal!=0 || !timing || mode) {
    editNodon();      //Edit gear icon
    if (startVal!=0) inputCalculator(670, 120, startVal);  //Starting Value
    if (mode) {
      clickMouseAt(160+mode*210, 300);      //Mode
      if (lowerRange!=0) inputCalculator(530, 370, lowerRange);  //Lower range     
      if (upperRange!=1000) inputCalculator(670, 370, upperRange);  //Upper range 
    }
    if (!timing) clickMouseAt(160, 550);  //On change from 0
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createRandomNodon(byte gridX, byte gridY, bool timing, int outputRange) {
  callNodon(1,4,3);
  if (timing || outputRange!=10) {
    editNodon();      //Edit gear icon
    if (timing) clickMouseAt(360, 150);  //While not 0
    if (outputRange!=10) inputCalculator(675, 215, outputRange); //Output Range
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createTimerNodon(byte gridX, byte gridY, float outDelay, float outDuration) {
  callNodon(1,3);
  if (outDelay!=1 || outDuration!=0) {
    editNodon();      //Edit gear icon
    if (outDelay!=1) inputCalculator(400, 150, outDelay);  //Output after How Many Seconds?
    if (outDuration!=0) inputCalculator(400, 335, outDuration); //Continue Output for How Long?
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createBullseyeNodon(byte gridX, byte gridY, boolean DorA, float lowerRange, float upperRange, boolean eyeShape) {
  callNodon(1,2);
  if (!DorA || lowerRange!=0 || upperRange !=1 || eyeShape) {
    editNodon();      //Edit gear icon
    if (!DorA) clickMouseAt(150, 150);      //Digital
    if (lowerRange!=0) inputCalculator(260, 220, lowerRange);  //Lower range
    if (upperRange!=1) inputCalculator(400, 220, upperRange);  //Upper range
    if (eyeShape) clickMouseAt(360, 470);      //Rectangle
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createWormholeEntranceNodon(byte gridX, byte gridY, byte id) {
  callNodon(1,1,3);
  if (id) {
    editNodon();      //Edit gear icon
    clickMouseAt(100+(id%8)*104, 150+(id/8)*64);      //Wormhole ID
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createWormholeExitNodon(byte gridX, byte gridY, byte id) {
  callNodon(1,1,2);
  if (id) {
    editNodon();      //Edit gear icon
    clickMouseAt(100+(id%8)*104, 150+(id/8)*64);      //Wormhole ID
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createCommentNodon(byte gridX, byte gridY, String comment) {
  callNodon(1,1,1);
  if (comment!="Comment") {
    editNodon();      //Edit gear icon
    inputKeyboard(150, 180, comment);
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

/*------------------------------------------------------------------------------------------
                                       OUTPUT NODON FUNCTIONS
  ------------------------------------------------------------------------------------------*/

static void createPlaySoundNodon(byte gridX, byte gridY, byte category, byte subColumn, byte subRow) {
  callNodon(2,6,6); //Play Instrument
  if (category != 11 || subColumn) {
    editNodon();      //Edit gear icon
    if (category<11) {
      clickMouseAt(150+(category%5)*208, 270+(category/5)*64);      //Effects
      if (subColumn || subRow) {
        clickMouseAt(170+(subColumn)*208, 180+(subRow)*64);      //Sound
      }
    } else {
      clickMouseAt(150+((category-11)%5)*208, 500+((category-11)/5)*64);      //Instruments
      if (subColumn==12) {
        clickMouseAt(630, 190);                      //High C
      } else if (subColumn>4) {
        clickMouseAt(340+(subColumn-5)*35, 190);      //F to B        
      } else {
        clickMouseAt(120+(subColumn)*35, 190);      //C# to E
      }
    }
    closeNodon();      //Close menu
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createBackgroundMusicNodon(byte gridX, byte gridY, byte theme, byte melody, byte mainAcc, byte subAcc, byte rhythm) {
  callNodon(2,5);
  if (theme!=6 || melody || mainAcc || subAcc || rhythm) {
    editNodon();      //Edit gear icon
    if (theme!=6) objectMenu(150, 150, theme/5, theme%5); //Theme
    if (melody) clickMouseAt(150, 250+melody*64);  //Melody
    if (mainAcc) clickMouseAt(358, 250+mainAcc*64);  //Main Accompaniment
    if (subAcc) clickMouseAt(566, 250+subAcc*64);  //Sub Accompaniment
    if (rhythm) clickMouseAt(774, 250+rhythm*64);  //Rhythm
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createVibrationNodon(byte gridX, byte gridY, byte controlNum, boolean LorR, float outDuration, int freq) {
  callNodon(2,4,4-LorR); //Joy-Con (L)
  if (controlNum || outDuration!=0 || freq!=170) {
    editNodon();      //Edit gear icon
    if (controlNum) clickMouseAt(90+controlNum*83, 150);  //Controller Number
    if (outDuration!=0) inputCalculator(400, 350, outDuration); //Continue Output for How Long?
    if (freq!=170) inputCalculator(1150, 120, freq); //Frequency
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createReduceGravityNodon(byte gridX, byte gridY) {
  callNodon(2,3,3);
  dragNodonToGrid(gridX,gridY);
}

static void createSlowTimeNodon(byte gridX, byte gridY) {
  callNodon(2,3,2);
  dragNodonToGrid(gridX,gridY);
}

static void createRetryNodon(byte gridX, byte gridY, byte transition) {
  callNodon(2,2,4);
  if (transition) {
    editNodon();      //Edit gear icon
    clickMouseAt(150+transition*208, 150);  //Transition Effect
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createEndGameNodon(byte gridX, byte gridY) {
  callNodon(2,2,3);
  dragNodonToGrid(gridX,gridY);
}

static void createSwapGameNodon(byte gridX, byte gridY, boolean swapType, String targetKeyword, String gameKeyword, boolean transition) {
  callNodon(2,2,2);
  if (swapType || targetKeyword!="" || gameKeyword!="" || transition) {
    editNodon();      //Edit gear icon
    if (swapType) clickMouseAt(360, 150);      //Swap Type
    if (targetKeyword!="") inputKeyboard(150, 270, targetKeyword);
    if (gameKeyword!="") inputKeyboard(150, 400, gameKeyword);
    if (transition) clickMouseAt(360, 500);    //Transition Appearance
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createMarkerDisplayNodon(byte gridX, byte gridY, byte mode, boolean actBullseye) {
  callNodon(2,1,2,10-mode);
  if (actBullseye) {
    editNodon();      //Edit gear icon
    clickMouseAt(370, 310);      //Disable Bullseye
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void create2DMarkerDisplayNodon(byte gridX, byte gridY, boolean DorA, float lowerRange, float upperRange, float markerSize, boolean actBullseye) {
  callNodon(2,1,2,3);
  if (!DorA || lowerRange!=0 || upperRange !=1 || markerSize!=0.1 || actBullseye) {
    editNodon();      //Edit gear icon
    if (!DorA) clickMouseAt(150, 150);      //Digital
    if (lowerRange!=0) inputCalculator(260, 220, lowerRange);  //Lower range
    if (upperRange!=1) inputCalculator(400, 220, upperRange);  //Upper range
    if (markerSize!=0.1) inputCalculator(1150, 120, markerSize); //Size
    if (actBullseye) clickMouseAt(850, 300);      //Disable Bullseye
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createContinuousMarkerDisplayNodon(byte gridX, byte gridY, boolean actBullseye) {
  callNodon(2,1,2,2);
  if (actBullseye) {
    editNodon();      //Edit gear icon
    clickMouseAt(360, 150);      //Activates Bull's-Eye Nodon?; Bull's-eye incompatible
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createIRLightNodon(byte gridX, byte gridY, boolean controlNum, float outDuration) {
  callNodon(2,1,1);
  if (controlNum || outDuration!=0) {
    editNodon();      //Edit gear icon
    if (controlNum) clickMouseAt(360, 150);  //Controller Number; 2
    if (outDuration!=0) inputCalculator(400, 250, outDuration); //Continue Output for How Long?
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

/*------------------------------------------------------------------------------------------
                                       OBJECT NODON FUNCTIONS
  ------------------------------------------------------------------------------------------*/

static void createPersonNodon(byte gridX, byte gridY, boolean visible, boolean solid, byte destructibleNormal, unsigned long destructibleFancy, byte destructiveNormal, unsigned long destructiveFancy, boolean silent, boolean ungrabbable, byte color, boolean referenceFrame, byte action, float movementSpeed, float jumpStrength, float turningSpeed) {
  callNodon(3,9,9);
  if (!visible || !solid || destructibleNormal || destructibleFancy || destructiveNormal || destructiveFancy || silent || ungrabbable || color || !referenceFrame || action || movementSpeed!=1 || jumpStrength!=1 || turningSpeed!=0.1) {
    editNodon();      //Edit gear icon
    objectProperties(150, !visible, !solid, 0, destructibleNormal, destructibleFancy, destructiveNormal, destructiveFancy, silent, ungrabbable); //Object Properties
    if (color) objectMenu(150, 310, (color-1)%4, (color+3)/4);      //Color
    if (!referenceFrame) objectMenu(870, 180);  //Frame of Reference for Motion
    if (action) objectMenu(1120, 180, action);  //Action
    if (movementSpeed!=1) inputCalculator(870, 280, movementSpeed); //Movement Speed
    if (jumpStrength!=1) inputCalculator(1120, 280, jumpStrength);  //Jump Strength
    if (turningSpeed!=0.1) inputCalculator(1120, 580, turningSpeed);  //Jump Strength
    closeNodon();      //Close Nodon
  } 
  dragNodonToGrid(gridX,gridY,1);
}

static void createCarNodon(byte gridX, byte gridY, boolean visible, boolean solid, byte destructibleNormal, unsigned long destructibleFancy, byte destructiveNormal, unsigned long destructiveFancy, boolean silent, boolean ungrabbable, byte color, float movementSpeed, float jumpStrength) {
  callNodon(3,9,8);
  dragMouseAcross(710, 430, 685, 405);  //Shrink Car to grid size
  if (!visible || !solid || destructibleNormal || destructibleFancy || destructiveNormal || destructiveFancy || silent || ungrabbable || color || movementSpeed!=1 || jumpStrength!=1) {
    editNodon();      //Edit gear icon
    objectProperties(150, !visible, !solid, 0, destructibleNormal, destructibleFancy, destructiveNormal, destructiveFancy, silent, ungrabbable); //Object Properties
    if (color) objectMenu(150, 310, (color-1)%4, (color+3)/4);      //Color
    if (movementSpeed!=1) inputCalculator(870, 150, movementSpeed); //Movement Speed
    if (jumpStrength!=1) inputCalculator(1120, 150, jumpStrength);  //Jump Strength
    closeNodon();      //Close Nodon
  } 
  dragNodonToGrid(gridX,gridY,2);
}

static void createUFONodon(byte gridX, byte gridY, boolean visible, boolean solid, byte destructibleNormal, unsigned long destructibleFancy, byte destructiveNormal, unsigned long destructiveFancy, boolean silent, boolean ungrabbable, byte color, boolean referenceFrame, float horizontalSpeed, float verticalSpeed, float turningSpeed) {
  callNodon(3,9,7);
  if (!visible || !solid || destructibleNormal || destructibleFancy || destructiveNormal || destructiveFancy || silent || ungrabbable || color || !referenceFrame || horizontalSpeed!=1 || verticalSpeed!=1 || turningSpeed!=0.1) {
    editNodon();      //Edit gear icon
    objectProperties(150, !visible, !solid, 0, destructibleNormal, destructibleFancy, destructiveNormal, destructiveFancy, silent, ungrabbable); //Object Properties
    if (color) objectMenu(150, 310, (color-1)%4, (color+3)/4);      //Color
    if (!referenceFrame) objectMenu(870, 180);  //Frame of Reference for Motion
    if (horizontalSpeed!=1) inputCalculator(870, 280, horizontalSpeed); //Movement Speed
    if (verticalSpeed!=1) inputCalculator(1120, 280, verticalSpeed);  //Jump Strength
    if (turningSpeed!=0.1) inputCalculator(1120, 580, turningSpeed);  //Jump Strength
    closeNodon();      //Close Nodon
  } 
  dragNodonToGrid(gridX,gridY,1);
}

static void createObjectNodon(byte gridX, byte gridY, byte shape, boolean visible, boolean solid, boolean movable, byte destructibleNormal, unsigned long destructibleFancy, byte destructiveNormal, unsigned long destructiveFancy, boolean silent, boolean ungrabbable, byte color, byte material, byte connectionType, byte connectionOwn, byte connectionTarget) {
  callNodon(3,8,8-shape);
  if (!visible || !solid || !movable || destructibleNormal!=0b11111111 || destructibleFancy!=0b11111111111111111111111111111111 || destructiveNormal!=0b11111111 || destructiveFancy!=0b11111111111111111111111111111111 || silent || ungrabbable || color || material || connectionType || connectionOwn!=3 || connectionTarget!=4) {
    editNodon();      //Edit gear icon
    objectProperties(250, !visible, !solid, !movable, ~destructibleNormal, ~destructibleFancy, ~destructiveNormal, ~destructiveFancy, silent, ungrabbable); //Object Properties
    if (color) objectMenu(150, 410, (color-1)%4, (color+3)/4);      //Color
    if (material) objectMenu(360, 410, material); //Material
    if (connectionType) objectMenu(150, 510, connectionType);
    if (connectionOwn!=3 || connectionTarget!=4) objectConnectionPoint(360, 510, connectionOwn, connectionTarget, 3, 4);
    closeNodon();      //Close Nodon
  } 
  dragNodonToGrid(gridX,gridY,4);
}

static void createFancyObjectNodon(byte gridX, byte gridY, boolean visible, boolean solid, boolean movable, byte destructibleNormal, unsigned long destructibleFancy, byte destructiveNormal, unsigned long destructiveFancy, boolean silent, boolean ungrabbable, byte material, byte connectionType, byte connectionOwn, byte connectionTarget) {
  callNodon(3,7,8,9);
  if (!visible || !solid || !movable || destructibleNormal || destructibleFancy || destructiveNormal || destructiveFancy || silent || ungrabbable || material || connectionType || connectionOwn!=3 || connectionTarget!=4) {
    editNodon();      //Edit gear icon
    objectProperties(250, !visible, !solid, !movable, destructibleNormal, destructibleFancy, destructiveNormal, destructiveFancy, silent, ungrabbable); //Object Properties
    if (material) objectMenu(150, 410, material); //Material
    if (connectionType) objectMenu(150, 510, connectionType); //Connection Type
    if (connectionOwn!=3 || connectionTarget!=4) objectConnectionPoint(360, 510, connectionOwn, connectionTarget, 3, 4);  //Connection Point
    closeNodon();      //Close Nodon
  } 
  dragNodonToGrid(gridX,gridY,4);
}

static void createMovingObjectNodon(byte gridX, byte gridY, byte shape, boolean visible, boolean solid, byte destructibleNormal, unsigned long destructibleFancy, byte destructiveNormal, unsigned long destructiveFancy, boolean silent, boolean ungrabbable, byte color, byte material, byte connectionType, byte connectionOwn, byte connectionTarget, byte referenceFrame, boolean mode) {
  callNodon(3,6,8,8-shape);
  if (!visible || !solid || destructibleNormal!=0b11111111 || destructibleFancy!=0b11111111111111111111111111111111 || destructiveNormal!=0b11111111 || destructiveFancy!=0b11111111111111111111111111111111 || silent || ungrabbable || color || material || connectionType || connectionOwn!=3 || connectionTarget!=4 || referenceFrame || mode) {
    editNodon();      //Edit gear icon
    objectProperties(250, !visible, !solid, 0, ~destructibleNormal, ~destructibleFancy, ~destructiveNormal, ~destructiveFancy, silent, ungrabbable); //Object Properties
    if (color) objectMenu(150, 410, (color-1)%4, (color+3)/4);      //Color
    if (material) objectMenu(360, 410, material); //Material
    if (connectionType) objectMenu(150, 510, connectionType);
    if (connectionOwn!=3 || connectionTarget!=4) objectConnectionPoint(360, 510, connectionOwn, connectionTarget, 3, 4);
    if (referenceFrame) objectMenu(870, 180, referenceFrame);  //Frame of Reference for Motion
    if (mode) objectMenu(1120, 150, mode);  //Mode
    closeNodon();      //Close Nodon
  } 
  dragNodonToGrid(gridX,gridY,3);
}

static void createRotatingObjectNodon(byte gridX, byte gridY, byte shape, boolean visible, boolean solid, byte destructibleNormal, unsigned long destructibleFancy, byte destructiveNormal, unsigned long destructiveFancy, boolean silent, boolean ungrabbable, byte color, byte material, byte connectionType, byte connectionOwn, byte connectionTarget, byte referenceFrame) {
  callNodon(3,6,7,7-shape);
  if (!visible || !solid || destructibleNormal!=0b11111111 || destructibleFancy!=0b11111111111111111111111111111111 || destructiveNormal!=0b11111111 || destructiveFancy!=0b11111111111111111111111111111111 || silent || ungrabbable || color || material || connectionType || connectionOwn!=3 || connectionTarget!=4 || referenceFrame) {
    editNodon();      //Edit gear icon
    objectProperties(250, !visible, !solid, 0, ~destructibleNormal, ~destructibleFancy, ~destructiveNormal, ~destructiveFancy, silent, ungrabbable); //Object Properties
    if (color) objectMenu(150, 410, (color-1)%4, (color+3)/4);      //Color
    if (material) objectMenu(360, 410, material); //Material
    if (connectionType) objectMenu(150, 510, connectionType);
    if (connectionOwn!=3 || connectionTarget!=4) objectConnectionPoint(360, 510, connectionOwn, connectionTarget, 3, 4);
    if (referenceFrame) objectMenu(870, 150, referenceFrame);  //Frame of Reference for Motion
    closeNodon();      //Close Nodon
  } 
  dragNodonToGrid(gridX,gridY,3);
}

static void createExtendingObjectNodon(byte gridX, byte gridY, byte shape, boolean ungrabbable, byte color, byte connectionOwn, byte connectionTarget) {
  callNodon(3,6,6,6-shape);
  if (!ungrabbable || color || connectionOwn!=3 || connectionTarget!=4) {
    editNodon();      //Edit gear icon
    objectProperties(250, 0, 0, 0, 0, 0, 0, 0, 0, !ungrabbable); //Object Properties
    if (color) objectMenu(150, 410, (color)%4, (color)/4);      //Color
    if (connectionOwn!=3 || connectionTarget!=4) objectConnectionPoint(150, 510, connectionOwn, connectionTarget, 3, 4);
    closeNodon();      //Close Nodon
  } 
  dragNodonToGrid(gridX,gridY,4);
}

static void createEffectNodon(byte gridX, byte gridY, byte appearance, boolean effectTiming, boolean effectLocation, boolean visible, boolean ungrabbable, byte connectionOwn, byte connectionTarget) {
  callNodon(3,6,5,10-appearance);
  if (effectTiming || effectLocation) {
    editNodon();      //Edit gear icon
    if (effectTiming) clickMouseAt(360, 250); //Effect Timing; While not 0
    if (effectLocation) clickMouseAt(360, 350); //Effect Location; World
    objectProperties(450, !visible, 0, 0, 0, 0, 0, 0, 0, ungrabbable); //Object Properties
    if (connectionOwn || connectionTarget) objectConnectionPoint(150, 610, connectionOwn, connectionTarget, 0, 0);  //Connection Point
    closeNodon();      //Close Nodon
  } 
  dragNodonToGrid(gridX,gridY,4);
}

static void createTextObjectNodon(byte gridX, byte gridY, String displayText, boolean visible, boolean solid, boolean movable, byte destructibleNormal, unsigned long destructibleFancy, byte destructiveNormal, unsigned long destructiveFancy, boolean silent, boolean ungrabbable, byte color, byte textColor, byte material, byte connectionType, byte connectionOwn, byte connectionTarget, byte displaySide) {
  callNodon(3,6,4);
  if (displayText!="TextObject" || !visible || !solid || !movable || destructibleNormal!=0b11111111 || destructibleFancy!=0b11111111111111111111111111111111 || destructiveNormal!=0b11111111 || destructiveFancy!=0b11111111111111111111111111111111 || silent || ungrabbable || color || textColor!=11 || material || connectionType || connectionOwn!=3 || connectionTarget!=4 || displaySide!=5) {
    editNodon();      //Edit gear icon
    if (displayText!="TextObject") inputKeyboard(150, 180, displayText);  //Display Text
    objectProperties(380, !visible, !solid, !movable, ~destructibleNormal, ~destructibleFancy, ~destructiveNormal, ~destructiveFancy, silent, ungrabbable); //Object Properties
    if (color) objectMenu(150, 540, (color-1)%4, (color+3)/4);      //Color
    if (textColor!=11) objectMenu(360, 540, textColor%4, textColor/4);  //Text Color
    if (material) objectMenu(570, 540, material); //Material
    if (connectionType) objectMenu(150, 640, connectionType); //Connection Type
    if (connectionOwn!=3 || connectionTarget!=4) objectConnectionPoint(360, 640, connectionOwn, connectionTarget, 3, 4);  //Connection Point
    if (displaySide!=5) objectMenu(870, 270, displaySide%3, (displaySide/3)*3);  //Text Display Side
    closeNodon();      //Close Nodon
  } 
  dragNodonToGrid(gridX,gridY,5);
}

static void createNumberObjectNodon(byte gridX, byte gridY, boolean visible, boolean solid, boolean movable, byte destructibleNormal, unsigned long destructibleFancy, byte destructiveNormal, unsigned long destructiveFancy, boolean silent, boolean ungrabbable, byte color, byte textColor, byte material, byte connectionType, byte connectionOwn, byte connectionTarget, byte displaySide, byte wholeDigits, byte decimalDigits) {
  callNodon(3,6,3);
  if (!visible || !solid || !movable || destructibleNormal!=0b11111111 || destructibleFancy!=0b11111111111111111111111111111111 || destructiveNormal!=0b11111111 || destructiveFancy!=0b11111111111111111111111111111111 || silent || ungrabbable || color || textColor!=11 || material || connectionType || connectionOwn!=3 || connectionTarget!=4 || displaySide!=5 || wholeDigits!=2 || decimalDigits) {
    editNodon();      //Edit gear icon
    objectProperties(250, !visible, !solid, !movable, ~destructibleNormal, ~destructibleFancy, ~destructiveNormal, ~destructiveFancy, silent, ungrabbable); //Object Properties
    if (color) objectMenu(150, 410, (color-1)%4, (color+3)/4);      //Color
    if (textColor!=11) objectMenu(360, 410, textColor%4, textColor/4);  //Text Color
    if (material) objectMenu(570, 410, material); //Material
    if (connectionType) objectMenu(150, 510, connectionType);
    if (connectionOwn!=3 || connectionTarget!=4) objectConnectionPoint(360, 510, connectionOwn, connectionTarget, 3, 4);
    if (displaySide!=5) objectMenu(870, 270, displaySide%3, (displaySide/3)*3);  //Text Display Side
    if (wholeDigits!=2) inputCalculator(1120, 150, wholeDigits);  //Whole Number Digits
    if (decimalDigits) inputCalculator(1120, 250, decimalDigits);  //Decimal Digits
    closeNodon();      //Close Nodon
  } 
  dragNodonToGrid(gridX,gridY,5);
}

static void createTextureNodon(byte gridX, byte gridY, byte faceX, byte faceY, byte faceZ, byte mainColor, byte subColor) {
  callNodon(3,6,2);
  if (faceX!=3 || faceY!=3 || faceZ!=3 || mainColor!=13) {
    editNodon();      //Edit gear icon
    objectList(150, 150, faceX^0b11, (faceY^0b11)+((faceZ^0b11)<<8)); //Texture Face
    if (mainColor<13) {
      clickMouseAt(1185, 540);
      if (mainColor==0) clickMouseAt(85+(subColor%3)*50, 175+(subColor/3)*50);
      if (mainColor>0) clickMouseAt(245+((mainColor-1)%4)*160+(subColor%3)*50, 175+((mainColor-1)/4)*160+(subColor/3)*50);
      closeNodon();
      clickMouseAt(960, 260);
      clickMouseAt(600, 400);
    }
    closeNodon();      //Close Nodon
  } 
  dragNodonToGrid(gridX,gridY,6);
}

static void createTouchSensorNodon(byte gridX, byte gridY, byte shape, boolean visible, boolean ungrabbable, boolean timing, byte connectionOwn, byte connectionTarget, byte senseNormal, unsigned long senseFancy) {
  callNodon(3,5,10);
  if (shape || !visible || ungrabbable || !timing || connectionOwn || connectionTarget || senseNormal!=0b1110 || senseFancy) {
    editNodon();      //Edit gear icon
    if (shape) clickMouseAt(150+210*shape, 150);      //Sensor Shape
    objectProperties(250, !visible, 0, 0, 0, 0, 0, 0, 0, ungrabbable); //Object Properties
    if (!timing) clickMouseAt(150, 410);      //Output Timing
    if (connectionOwn || connectionTarget) objectConnectionPoint(150, 510, connectionOwn, connectionTarget);  //Connection Point
    if (senseNormal!=0b1110 || senseFancy) objectList(990, 180, senseNormal^0b1110, senseFancy);
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY,7);
}

static void createDestroyingSensorNodon(byte gridX, byte gridY, byte shape, boolean visible, boolean ungrabbable, byte connectionOwn, byte connectionTarget) {
  callNodon(3,5,9);
  if (shape || !visible || ungrabbable || connectionOwn || connectionTarget) {
    editNodon();      //Edit gear icon
    if (shape) clickMouseAt(150+210*shape, 150);      //Sensor Shape
    objectProperties(250, !visible, 0, 0, 0, 0, 0, 0, 0, ungrabbable); //Object Properties
    if (connectionOwn || connectionTarget) objectConnectionPoint(150, 410, connectionOwn, connectionTarget);  //Connection Point
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY,4);
}

static void createDestroyedSensorNodon(byte gridX, byte gridY, byte shape, boolean visible, boolean ungrabbable, byte connectionOwn, byte connectionTarget) {
  callNodon(3,5,8);
  if (shape || !visible || ungrabbable || connectionOwn || connectionTarget) {
    editNodon();      //Edit gear icon
    if (shape) clickMouseAt(150+210*shape, 150);      //Sensor Shape
    objectProperties(250, !visible, 0, 0, 0, 0, 0, 0, 0, ungrabbable); //Object Properties
    if (connectionOwn || connectionTarget) objectConnectionPoint(150, 410, connectionOwn, connectionTarget);  //Connection Point
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY,4);
}

static void createGrabbedSensorNodon(byte gridX, byte gridY, byte shape, boolean visible, boolean ungrabbable, boolean timing, byte connectionOwn, byte connectionTarget) {
  callNodon(3,5,7);
  if (shape || !visible || ungrabbable || !timing || connectionOwn || connectionTarget) {
    editNodon();      //Edit gear icon
    if (shape) clickMouseAt(150+210*shape, 150);      //Sensor Shape
    objectProperties(250, !visible, 0, 0, 0, 0, 0, 0, 0, ungrabbable); //Object Properties
    if (!timing) clickMouseAt(150, 410);      //Output Timing
    if (connectionOwn || connectionTarget) objectConnectionPoint(150, 510, connectionOwn, connectionTarget);  //Connection Point
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY,4);
}

static void createLocationSensorNodon(byte gridX, byte gridY, byte shape, boolean visible, boolean ungrabbable, byte connectionOwn, byte connectionTarget, byte referenceFrame) {
  callNodon(3,5,6);
  if (shape || visible==0 || ungrabbable || connectionOwn || connectionTarget || referenceFrame) {
    editNodon();      //Edit gear icon
    if (shape) clickMouseAt(150+210*shape, 150);      //Sensor Shape
    objectProperties(250, !visible, 0, 0, 0, 0, 0, 0, 0, ungrabbable); //Object Properties
    if (connectionOwn || connectionTarget) objectConnectionPoint(150, 410, connectionOwn, connectionTarget);  //Connection Point
    if (referenceFrame) objectMenu(880, 150, referenceFrame);
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY,3);
}

static void createSpeedSensorNodon(byte gridX, byte gridY, byte shape, boolean visible, boolean ungrabbable, byte connectionOwn, byte connectionTarget, byte referenceFrame) {
  callNodon(3,5,5);
  if (shape || visible==0 || ungrabbable || connectionOwn || connectionTarget || referenceFrame) {
    editNodon();      //Edit gear icon
    if (shape) clickMouseAt(150+210*shape, 150);      //Sensor Shape
    objectProperties(250, !visible, 0, 0, 0, 0, 0, 0, 0, ungrabbable); //Object Properties
    if (connectionOwn || connectionTarget) objectConnectionPoint(150, 410, connectionOwn, connectionTarget);  //Connection Point
    if (referenceFrame) objectMenu(880, 150, referenceFrame);
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY,3);
}

static void createAccelerationSensorNodon(byte gridX, byte gridY, byte shape, boolean visible, boolean ungrabbable, byte connectionOwn, byte connectionTarget, byte referenceFrame) {
  callNodon(3,5,4);
  if (shape || visible==0 || ungrabbable || connectionOwn || connectionTarget || referenceFrame) {
    editNodon();      //Edit gear icon
    if (shape) clickMouseAt(150+210*shape, 150);      //Sensor Shape
    objectProperties(250, !visible, 0, 0, 0, 0, 0, 0, 0, ungrabbable); //Object Properties
    if (connectionOwn || connectionTarget) objectConnectionPoint(150, 410, connectionOwn, connectionTarget);  //Connection Point
    if (referenceFrame) objectMenu(880, 150, referenceFrame);
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY,3);
}

static void createAngleSensorNodon(byte gridX, byte gridY, byte shape, boolean visible, boolean ungrabbable, byte connectionOwn, byte connectionTarget, byte referenceFrame) {
  callNodon(3,5,3);
  if (shape || visible==0 || ungrabbable || connectionOwn || connectionTarget || referenceFrame) {
    editNodon();      //Edit gear icon
    if (shape) clickMouseAt(150+210*shape, 150);      //Sensor Shape
    objectProperties(250, !visible, 0, 0, 0, 0, 0, 0, 0, ungrabbable); //Object Properties
    if (connectionOwn || connectionTarget) objectConnectionPoint(150, 410, connectionOwn, connectionTarget);  //Connection Point
    if (referenceFrame) objectMenu(880, 150, referenceFrame);
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY,3);
}

static void createRotationSpeedSensorNodon(byte gridX, byte gridY, byte shape, boolean visible, boolean ungrabbable, byte connectionOwn, byte connectionTarget, byte referenceFrame) {
  callNodon(3,5,2);
  if (shape || visible==0 || ungrabbable || connectionOwn || connectionTarget || referenceFrame) {
    editNodon();      //Edit gear icon
    if (shape) clickMouseAt(150+210*shape, 150);      //Sensor Shape
    objectProperties(250, !visible, 0, 0, 0, 0, 0, 0, 0, ungrabbable); //Object Properties
    if (connectionOwn || connectionTarget) objectConnectionPoint(150, 410, connectionOwn, connectionTarget);  //Connection Point
    if (referenceFrame) objectMenu(880, 150, referenceFrame);
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY,3);
}

static void createSlideConnectorNodon(byte gridX, byte gridY, byte axis, float lowerRange, float upperRange) {
  callNodon(3,4,7,7-axis); //X Slide
  if (lowerRange!=-100 || upperRange!=100) {
    editNodon();      //Edit gear icon
    if (lowerRange!=-100) inputCalculator(560, 220, lowerRange);  //Lower range  
    if (upperRange!=100) inputCalculator(710, 220, upperRange);  //Upper range
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY,8);
}

static void createFreeSlideConnectorNodon(byte gridX, byte gridY, boolean enX, boolean enY, boolean enZ) {
  callNodon(3,4,6);
  if (!enX || !enY || !enZ) {
    editNodon();      //Edit gear icon
    if (!enX) clickMouseAt(150, 150);
    if (!enY) clickMouseAt(360, 150);
    if (!enZ) clickMouseAt(570, 150);
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY,8);
}

static void createHingeConnectorNodon(byte gridX, byte gridY, byte axis, float lowerRange, float upperRange) {
  callNodon(3,4,5,5-axis);
  if (lowerRange!=-180 || upperRange!=180) {
    editNodon();      //Edit gear icon
    if (lowerRange!=-180) inputCalculator(560, 220, lowerRange);  //Lower range      
    if (upperRange!=180) inputCalculator(710, 220, upperRange);  //Upper range
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY,8);
}

static void createStringConnectorNodon(byte gridX, byte gridY, boolean visible, boolean solid, byte destructibleNormal, unsigned long destructibleFancy, byte destructiveNormal, unsigned long destructiveFancy, float strStiffness, float strLength) {
  callNodon(3,4,4);
  if (!visible || !solid || destructibleNormal || destructibleFancy || destructiveNormal || destructiveFancy || strStiffness!=0.5 || strLength!=5) {
    editNodon();      //Edit gear icon
    objectProperties(150, !visible, !solid, 0, destructibleNormal, destructibleFancy, destructiveNormal, destructiveFancy); //Object Properties
    if (strStiffness!=0.5) inputCalculator(1120, 120, strStiffness);  //String Stiffness
    if (strLength!=5) inputCalculator(1120, 270, strLength);  //String Length
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createLaunchObjectNodon(byte gridX, byte gridY, byte launchLimit, byte shape, boolean visible, boolean solid, boolean movable, byte destructibleNormal, unsigned long destructibleFancy, byte destructiveNormal, unsigned long destructiveFancy, boolean silent, boolean ungrabbable, byte color, byte material, byte connectionOwn, byte connectionTarget, byte launchDirection, float launchSpeed, float launchInterval) {
  callNodon(3,3,6,6-launchLimit);
  if (shape!=2 || !visible || !solid || !movable || destructibleNormal!=0b11111111 || destructibleFancy!=0b11111111111111111111111111111111 || destructiveNormal!=0b11111111 || destructiveFancy!=0b11111111111111111111111111111111 || silent || ungrabbable || color || material || connectionOwn || connectionTarget || launchDirection!=2 || launchSpeed!=10 || launchInterval!=1) {
    editNodon();      //Edit gear icon
    if (shape!=2) clickMouseAt(150+210*shape, 150);      //Object Shape
    objectProperties(250, !visible, !solid, !movable, ~destructibleNormal, ~destructibleFancy, ~destructiveNormal, ~destructiveFancy, silent, ungrabbable); //Object Properties
    if (color) objectMenu(150, 410, (color-1)%4, (color+3)/4);      //Color
    if (material) objectMenu(360, 410, material); //Material
    if (connectionOwn || connectionTarget) objectConnectionPoint(150, 510, connectionOwn, connectionTarget);
    if (launchDirection!=2) objectMenu(870, 270, launchDirection%3, (launchDirection/3)*3);  //Launch Direction
    if (launchSpeed!=10) inputCalculator(1120, 150, launchSpeed);  //Launch Speed
    if (launchInterval!=1) inputCalculator(1120, 250, launchInterval);  //Launch Interval
    closeNodon();      //Close Nodon
  } 
  dragNodonToGrid(gridX,gridY,5);
}

static void createDestroyObjectNodon(byte gridX, byte gridY, byte shape, boolean visible, boolean ungrabbable, byte connectionOwn, byte connectionTarget, byte destroyNormal, unsigned long destroyFancy) {
  callNodon(3,3,5);
  if (shape || !visible || ungrabbable || connectionOwn || connectionTarget || destroyNormal!=0b111 || destroyFancy) {
    editNodon();      //Edit gear icon
    if (shape) clickMouseAt(150+210*shape, 150);      //Sensor Shape
    objectProperties(250, !visible, 0, 0, 0, 0, 0, 0, 0, ungrabbable); //Object Properties
    if (connectionOwn || connectionTarget) objectConnectionPoint(150, 410, connectionOwn, connectionTarget);  //Connection Point
    if (destroyNormal!=0b111 || destroyFancy) objectList(990, 180, (destroyNormal^0b111)&0b111111, destroyFancy);  //Destroy What?
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY,7);
}

static void createTeleportObjectEntranceNodon(byte gridX, byte gridY, byte teleportID, byte shape, boolean visible, boolean ungrabbable, byte connectionOwn, byte connectionTarget, byte teleportNormal, unsigned long teleportFancy) {
  callNodon(3,3,4,4);
  if (teleportID || shape || !visible || ungrabbable || connectionOwn || connectionTarget || teleportNormal!=0b111 || teleportFancy) {
    editNodon();      //Edit gear icon
    if (teleportID) clickMouseAt(90+78*teleportID, 150);      //Teleport ID
    if (shape) clickMouseAt(150+210*shape, 250);      //Sensor Shape
    objectProperties(350, !visible, 0, 0, 0, 0, 0, 0, 0, ungrabbable); //Object Properties
    if (connectionOwn || connectionTarget) objectConnectionPoint(150, 510, connectionOwn, connectionTarget);  //Connection Point
    if (teleportNormal!=0b111 || teleportFancy) objectList(990, 180, (teleportNormal^0b111)&0b111111, teleportFancy);  //Teleport What?
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY,7);
}

static void createTeleportObjectExitNodon(byte gridX, byte gridY, byte teleportID, byte shape, boolean visible, boolean ungrabbable, byte connectionOwn, byte connectionTarget, boolean teleportPhysics, float launchSpeed, byte launchDirection) {
  callNodon(3,3,4,3);
  if (teleportID || shape || !visible || ungrabbable || connectionOwn || connectionTarget || teleportPhysics) {
    editNodon();      //Edit gear icon
    if (teleportID) clickMouseAt(90+78*teleportID, 150);      //Teleport ID
    if (shape) clickMouseAt(150+210*shape, 250);      //Sensor Shape
    objectProperties(350, !visible, 0, 0, 0, 0, 0, 0, 0, ungrabbable); //Object Properties
    if (connectionOwn || connectionTarget) objectConnectionPoint(150, 510, connectionOwn, connectionTarget);  //Connection Point
    if (teleportPhysics) {
      objectMenu(870, 150, teleportPhysics);
      if (launchSpeed!=0) inputCalculator(870, 250, launchSpeed); //Launch Speed
      if (launchDirection!=1) objectMenu(1120, 270, launchDirection%3, (launchDirection/3)*3); //Launch Direction
    }
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY,5);
}

static void createAttractObjectNodon(byte gridX, byte gridY, byte shape, boolean visible, boolean ungrabbable, byte connectionOwn, byte connectionTarget, byte attractCenter, byte attractNormal, unsigned long attractFancy) {
  callNodon(3,3,3);
  if (shape || !visible || ungrabbable || connectionOwn || connectionTarget || attractCenter!=6 || attractNormal!=0b111 || attractFancy) {
    editNodon();      //Edit gear icon
    if (shape) clickMouseAt(150+210*shape, 150);      //Sensor Shape
    objectProperties(250, !visible, 0, 0, 0, 0, 0, 0, 0, ungrabbable); //Object Properties
    if (connectionOwn || connectionTarget) objectConnectionPoint(150, 410, connectionOwn, connectionTarget);  //Connection Point
    if (attractCenter!=6) objectMenu(870, 270, attractCenter%3, (attractCenter/3)*3);      //Center of Attraction
    if (attractNormal!=0b111 || attractFancy) objectList(1120, 180, (attractNormal^0b111)&0b111111, attractFancy);  //Attract Which Objects?
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY,5);
}

static void createWorldNodon(byte gridX, byte gridY, byte worldShape, byte worldAppearance, byte worldLighting, int sunDirection, int sunHeight, byte worldMaterial, byte objectAppearance, byte destructiveNormal, unsigned long destructiveFancy, float destructionSpeed) {
  callNodon(3,2);
  if (worldShape!=1 || worldAppearance || worldLighting || sunDirection!=-130 || sunHeight!=52 || worldMaterial || objectAppearance || destructiveNormal || destructiveFancy || destructionSpeed!=0.1) {
    editNodon();      //Edit gear icon
    if (worldShape!=1) clickMouseAt(150+(worldShape%3)*210, 150+(worldShape/3)*64);      //World Shape
    if (worldAppearance) objectMenu(150, 310, worldAppearance);
    if (worldLighting || sunDirection!=-130 || sunHeight!=52) {
      clickMouseAt(360, 310); //World Lighting
      if (worldLighting) clickMouseAt(90+worldLighting*208, 140);    //Select option
      if (sunDirection!=-130) dragMouseAcross(150, 280, sunDirection+280, 280); //Sun Direction
      if (sunHeight!=52) dragMouseAcross(835, 280, 2*(sunHeight-52)+835, 280); //Sun Height
      closeNodon();      //Close World Lighting
    }
    if (worldMaterial) objectMenu(570, 310, worldMaterial);
    if (objectAppearance) objectMenu(150, 410, objectAppearance);
    objectProperties(445, 0, 0, 0, 0, 0, destructiveNormal, destructiveFancy, 0, 0); //Destructive
    if (destructionSpeed!=0.1) inputCalculator(1120, 360, destructionSpeed);  //Launch Interval
    closeNodon();      //Close Nodon
  } 
  dragNodonToGrid(gridX,gridY,4);
}

static void createGameScreenNodon(byte gridX, byte gridY, float horizontalTrack, float verticalTrack, float cameraFOV) {
  callNodon(3,1,4);
  dragMouseAcross(870, 500, 705, 405);  //Shrink to grid size
  if (horizontalTrack!=0.2 || verticalTrack!=0.2 || cameraFOV!=60) {
    editNodon();      //Edit gear icon
    if (horizontalTrack!=0.2) inputCalculator(400, 120, horizontalTrack); //Horizontal Tracking Rate
    if (verticalTrack!=0.2) inputCalculator(400, 270, verticalTrack); //Vertical Tracking Rate
    if (cameraFOV!=90) inputCalculator(400, 420, cameraFOV); //Camera Field of View
    closeNodon();      //Close Nodon
  }
  dragMouseAcross(639, 404, round(104+62.25*gridX), 129+50*gridY);  //Drag Nodon to grid
  nodonGrid[gridX][gridY] = 9;
  justPlacedNodon = 1;
}

static void createCameraNodon(byte gridX, byte gridY, float horizontalTrack, float verticalTrack, float cameraFOV, boolean trackRotation, float offsetX, float offsetY, float offsetZ) {
  callNodon(3,1,3); //Camera
  if (horizontalTrack!=0.2 || verticalTrack!=0.2 || cameraFOV!=90 || trackRotation || offsetX!=0 || offsetY!=0 || offsetZ!=0) {
    editNodon();      //Edit gear icon
    if (horizontalTrack!=0.2) inputCalculator(400, 120, horizontalTrack); //Horizontal Tracking Rate
    if (verticalTrack!=0.2) inputCalculator(400, 270, verticalTrack); //Vertical Tracking Rate
    if (cameraFOV!=90) inputCalculator(400, 420, cameraFOV); //Camera Field of View
    if (trackRotation) clickMouseAt(360, 600);  //Track Character's Y Rotation
    objectTriple(870, 150, offsetX, offsetY, offsetZ);
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY,10);
}

static void createCameraPositionNodon(byte gridX, byte gridY, float horizontalTrack, float verticalTrack, byte connectionOwn, byte connectionTarget, float offsetX, float offsetY, float offsetZ) {
  callNodon(3,1,2,5); //Camera Position
  if (horizontalTrack!=0.5 || verticalTrack!=0.5 || connectionOwn || connectionTarget || offsetX!=0 || offsetY!=0 || offsetZ!=0) {
    editNodon();      //Edit gear icon
    if (horizontalTrack!=0.5) inputCalculator(400, 120, horizontalTrack); //Horizontal Tracking Rate
    if (verticalTrack!=0.5) inputCalculator(400, 270, verticalTrack); //Vertical Tracking Rate
    if (connectionOwn || connectionTarget) objectConnectionPoint(150, 450, connectionOwn, connectionTarget);  //Connection Point
    objectTriple(870, 150, offsetX, offsetY, offsetZ);
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY,10);
}

static void createCameraTargetNodon(byte gridX, byte gridY, float horizontalTrack, float verticalTrack, byte connectionOwn, byte connectionTarget, float offsetX, float offsetY, float offsetZ) {
  callNodon(3,1,2,4); //Camera Target
  if (horizontalTrack!=0.5 || verticalTrack!=0.5 || connectionOwn || connectionTarget || offsetX!=0 || offsetY!=0 || offsetZ!=0) {
    editNodon();      //Edit gear icon
    if (horizontalTrack!=0.5) inputCalculator(400, 120, horizontalTrack); //Horizontal Tracking Rate
    if (verticalTrack!=0.5) inputCalculator(400, 270, verticalTrack); //Vertical Tracking Rate
    if (connectionOwn || connectionTarget) objectConnectionPoint(150, 450, connectionOwn, connectionTarget);  //Connection Point
    objectTriple(870, 150, offsetX, offsetY, offsetZ);
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY,10);
}

static void createCameraDirectionNodon(byte gridX, byte gridY) {
  callNodon(3,1,2,3); //Camera Direction
  dragNodonToGrid(gridX,gridY);
}

static void createCameraAngleNodon(byte gridX, byte gridY, float cameraFOV) {
  callNodon(3,1,2,2); //Camera Angle
  if (cameraFOV!=90) {
    editNodon();      //Edit gear icon
    inputCalculator(400, 120, cameraFOV); //Camera Angle
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

static void createHeadNodon(byte gridX, byte gridY) {
  callNodon(3,1,1,3); //Head
  dragNodonToGrid(gridX,gridY);
}

static void createHandNodon(byte gridX, byte gridY, byte controlNum, boolean LorR, boolean mode, boolean carryingStyle, float snapDistance, byte rotationCenter, float launchSpeed) {
  callNodon(3,1,1,1+LorR);
  if (controlNum!=4 || mode || carryingStyle || snapDistance!=0 || rotationCenter || launchSpeed!=0) {
    editNodon();      //Edit gear icon
    if (controlNum!=4) clickMouseAt(100+controlNum*105, 150);  //Controller Number
    if (mode) clickMouseAt(360, 410);  //Mode; Toggle
    if (carryingStyle) objectMenu(150, 510, carryingStyle);  //Carrying Style
    if (snapDistance!=0) inputCalculator(360, 510, snapDistance);  //Snap Distance
    if (rotationCenter) objectMenu(150, 610, rotationCenter);  //Center of Rotation
    if (launchSpeed!=0) inputCalculator(360, 610, launchSpeed); //Launch Speed
    closeNodon();      //Close Nodon
  }
  dragNodonToGrid(gridX,gridY);
}

/*------------------------------------------------------------------------------------------
                                       CUSTOM NODON FUNCTIONS
  ------------------------------------------------------------------------------------------*/
//TBA





// ----------------------------------------------------------------------------------------------------
