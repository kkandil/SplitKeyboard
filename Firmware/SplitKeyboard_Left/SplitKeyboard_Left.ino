#include "BUTTONH.h"
#include "KeyMapping.h"
#include <Encoder.h>

 

typedef enum{
LAYER_SHIFT_STICKY = 0,
LAYER_SHIFT_TOGGLE_HOLD = 1,
LAYER_SHIFT_TOGGLE_RELEASED = 2
}enLayerShiftMode;




byte currentLayer = 0;
byte prevLayer = 0;
byte layerShiftMode = LAYER_SHIFT_STICKY;
bool layerShiftModeToggleEnable = false;
bool isCapsPressed = false;
bool isPressCurActive = false;
bool isLayerChangePressCurActive = false;

bool isGamingModeActive = false;




 

 typedef struct{
  enButton_Status status[KEYBOARD_LAYERS_COUNT];
}strButtonPessStatus;
 
strButtonPessStatus ButtonPessStatus_L [KEYBORD_ROWS_COUNT][KEYBORD_COLS_COUNT];
strButtonPessStatus ButtonPessStatus_R [KEYBORD_ROWS_COUNT][KEYBORD_COLS_COUNT];

strButtonPessStatus ButtonPessStatusSumb_L [4];
strButtonPessStatus ButtonPessStatusSumb_R [4]; 

#define LED_1_PIN 5
#define LED_2_PIN 7
#define ENCODER_PIN_A 9
#define ENCODER_PIN_B 10 

int ecoderPrevState;
volatile int8_t stepAccum = 0;     // accumulates ±1 per valid edge
volatile uint8_t lastState;

// Lookup table for state transitions (Gray-code quadrature)
// index = (lastState << 2) | curState, value = -1, 0, +1
// valid sequences produce ±1; all others (including bounce) yield 0.
const int8_t qtab[16] = {
  0, -1, +1,  0,
  +1,  0,  0, -1,
  -1,  0,  0, +1,
   0, +1, -1,  0
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  BUTTONH_Init();

  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT); 

  pinMode(ENCODER_PIN_A, INPUT_PULLUP);
  pinMode(ENCODER_PIN_B, INPUT_PULLUP);

  for (int row = 0; row < KEYBORD_ROWS_COUNT; row++) 
  {
    for (int col = 0; col < KEYBORD_COLS_COUNT; col++) 
    {
      for (int layer = 0; layer < KEYBOARD_LAYERS_COUNT; layer++) 
      {
        ButtonPessStatus_L[row][col].status[layer] = RELEASED;
        ButtonPessStatus_R[row][col].status[layer] = RELEASED;
      }
    }
  }

  for (int sumIndex = 0; sumIndex < 4; sumIndex++) 
  {
    for (int layer = 0; layer < KEYBOARD_LAYERS_COUNT; layer++) 
    {
      ButtonPessStatusSumb_L[sumIndex].status[layer] = RELEASED;
      ButtonPessStatusSumb_R[sumIndex].status[layer] = RELEASED;
    }
  }
 
  Keyboard.begin();
  Consumer.begin();
  Mouse.begin();

  // uint8_t a = digitalRead(ENCODER_PIN_A);
  // uint8_t b = digitalRead(ENCODER_PIN_B);
  // lastState = (a << 1) | b;
 lastState = readAB();  
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A), encoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_B), encoderISR, CHANGE);

  ecoderPrevState = digitalRead(ENCODER_PIN_A);
}








void loop() { 
 
    
  BUTTONH_UpdateButtonStatus();
  
  if( isGamingModeActive == false)
  {
    SumbButtonsMapingHandler(sumbButtonsStatus, thumbMapingLeftPress, ButtonPessStatusSumb_L);
    SumbButtonsMapingHandler(sumbButtonsStatus_R, thumbMapingRightPress, ButtonPessStatusSumb_R);
  }
  else 
  {
    SumbButtonsMapingHandler(sumbButtonsStatus, thumbMapingLeftPress_Gaming, ButtonPessStatusSumb_L);
    SumbButtonsMapingHandler(sumbButtonsStatus_R, thumbMapingRightPress_Gaming, ButtonPessStatusSumb_R);
  }
  
 
  if( isGamingModeActive == false)
  {
   KeyboardMatrixMapingHandler(keyMatrixButtonsStatus, keyMapingLeftPress, ButtonPessStatus_L);
   KeyboardMatrixMapingHandler(keyMatrixButtonsStatus_R, keyMapingRightPress, ButtonPessStatus_R);
 
  }
  else
  {
    KeyboardMatrixMapingHandler(keyMatrixButtonsStatus, keyMapingLeftPress_Gaming, ButtonPessStatus_L);
    KeyboardMatrixMapingHandler(keyMatrixButtonsStatus_R, keyMapingRightPress_Gaming, ButtonPessStatus_R);
 
  }
  
  if( currentLayer == 1 )//&& isGamingModeActive == false)
  {
    digitalWrite(LED_2_PIN, HIGH);
  }
  else
  {
    digitalWrite(LED_2_PIN, LOW);
  }

  if( isGamingModeActive == true)
  {
    digitalWrite(LED_1_PIN, HIGH);
  }
  else
  {
    digitalWrite(LED_1_PIN, LOW);
  }
  
  EncoderHandler();
  delay(5); 
}



 
   



void KeyboardMatrixMapingHandler(strButtonStatus buttonStatus[][6], strKeyMapping KeyMapingPress[][6], strButtonPessStatus ButtonPessStatus[][6])
{
  for (int row = 0; row < KEYBORD_ROWS_COUNT; row++) 
  {
    for (int col = 0; col < KEYBORD_COLS_COUNT; col++) 
    {
      KeyPressHandler(&buttonStatus[row][col], &KeyMapingPress[row][col], &ButtonPessStatus[row][col]);
    }
  }
}

void  SumbButtonsMapingHandler(strButtonStatus buttonStatus[4], strKeyMapping KeyMapingPress[4], strButtonPessStatus ButtonPessStatusSumb[4])
{
  for(int i=0 ; i<4 ; i++)
  { 
    if( KeyMapingPress[i].LayerMap[currentLayer].Keycode == KEY_LANG1 || KeyMapingPress[i].LayerMap[currentLayer].Keycode == KEY_LANG2)
    {
      LayerHandler(buttonStatus[i].button_curr_state, buttonStatus[i].is_updated, buttonStatus[i].isMultiBotPressed, KeyMapingPress[i].LayerMap[currentLayer].Keycode );
    } 
    else
    {
      KeyPressHandler(&buttonStatus[i], &KeyMapingPress[i], &ButtonPessStatusSumb[i]); 
    }
  }
}

void KeyPressHandler(strButtonStatus *buttonStatus, strKeyMapping *KeyMapingPress, strButtonPessStatus *ButtonPessStatus)
{
  if(buttonStatus->is_updated == true && buttonStatus->button_curr_state == PRESSED && buttonStatus->isMultiBotPressed == false )
  {   
    isPressCurActive = true;
    if( KeyMapingPress->LayerMap[currentLayer].keyType == KeyType_Consumer)
    {
      ConsumerKeyPressHandler(KeyMapingPress->LayerMap[currentLayer].Keycode);
    }
    else if( KeyMapingPress->LayerMap[currentLayer].Keycode == KEY_LANG9 )
    {
      Keyboard.print("kkandil");
      Keyboard.write(KEY_TAB);
      Keyboard.print("2wad@Mywork1"); 
    }
    else if( KeyMapingPress->LayerMap[currentLayer].Keycode == KEY_LANG8 )
    {
      if( layerShiftModeToggleEnable == false)
        layerShiftModeToggleEnable = true;
      else 
        layerShiftModeToggleEnable = false; 
    }
    else if( KeyMapingPress->LayerMap[currentLayer].Keycode == KEY_LANG7 )
    { 
      Mouse.click();
      Mouse.move(0, 82);
      Mouse.click();
      Mouse.move(0, -53);
    }
    else if( KeyMapingPress->LayerMap[currentLayer].keyType == KeyType_String )
    {   
      if(KeyMapingPress->LayerMap[currentLayer].txt == "WoodWall")
      { 
        Keyboard.write(KEY_Q);
        Keyboard.write(KEY_X);
      }
      else if(KeyMapingPress->LayerMap[currentLayer].txt == "StoneWall")
      { 
        Keyboard.write(KEY_W);
        Keyboard.write(KEY_X);
      }
      else if(KeyMapingPress->LayerMap[currentLayer].txt == "Tower")
      { 
        Keyboard.write(KEY_W);
        Keyboard.write(KEY_Z);
      }
      else if(KeyMapingPress->LayerMap[currentLayer].txt == "Keep")
      { 
        Keyboard.write(KEY_E);
        Keyboard.write(KEY_Z);
      }
      else if(KeyMapingPress->LayerMap[currentLayer].txt == "House")
      { 
        Keyboard.write(KEY_Q);
        Keyboard.write(KEY_Q);
      }
      else if(KeyMapingPress->LayerMap[currentLayer].txt == "MinCamp")
      { 
        Keyboard.write(KEY_Q);
        Keyboard.write(KEY_R);
      }
      else if(KeyMapingPress->LayerMap[currentLayer].txt == "LumbCamp")
      { 
        Keyboard.write(KEY_Q);
        Keyboard.write(KEY_E);
      }
      else if(KeyMapingPress->LayerMap[currentLayer].txt == "Mill")
      { 
        Keyboard.write(KEY_Q);
        Keyboard.write(KEY_W);
      }
      else if(KeyMapingPress->LayerMap[currentLayer].txt == "Farm")
      { 
        Keyboard.write(KEY_Q);
        Keyboard.write(KEY_A);
      }
      else if(KeyMapingPress->LayerMap[currentLayer].txt == "ArchRange")
      { 
        Keyboard.write(KEY_W);
        Keyboard.write(KEY_A);
      }
      else if(KeyMapingPress->LayerMap[currentLayer].txt == "Stable")
      { 
        Keyboard.write(KEY_W);
        Keyboard.write(KEY_S);
      }
      else if(KeyMapingPress->LayerMap[currentLayer].txt == "Barak")
      { 
        Keyboard.write(KEY_Q);
        Keyboard.write(KEY_S);
      }
      else if(KeyMapingPress->LayerMap[currentLayer].txt == "Seig")
      { 
        Keyboard.write(KEY_E);
        Keyboard.write(KEY_A);
      }
      else if(KeyMapingPress->LayerMap[currentLayer].txt == "Market")
      { 
        Keyboard.write(KEY_W);
        Keyboard.write(KEY_W);
      }
      else if(KeyMapingPress->LayerMap[currentLayer].txt != "")
      {
        Keyboard.print(KeyMapingPress->LayerMap[currentLayer].txt); 
      } 
    }
    else if( KeyMapingPress->LayerMap[currentLayer].Keycode == KEY_VOLUME_MUTE )
    {  
      Consumer.write(MEDIA_VOLUME_MUTE);
    }
    else if( KeyMapingPress->LayerMap[currentLayer].Keycode == KEY_LANG5 )
    { 
      if( isGamingModeActive == false)
      {
        isGamingModeActive = true; 
      }
      else
      { 
        isGamingModeActive = false;
      } 
    }
    else if( KeyMapingPress->LayerMap[currentLayer].keyType == KeyType_Macro)
    {
      ButtonPessStatus->status[currentLayer] = PRESSED;
      if( KeyMapingPress->LayerMap[currentLayer].MacroKey1 != KEY_RESERVED)
      {
        Keyboard.press(KeyMapingPress->LayerMap[currentLayer].MacroKey1); 
      }
      if( KeyMapingPress->LayerMap[currentLayer].MacroKey2 != KEY_RESERVED)
      {
        Keyboard.press(KeyMapingPress->LayerMap[currentLayer].MacroKey2); 
      }
      if( KeyMapingPress->LayerMap[currentLayer].MacroKey3 != KEY_RESERVED)
      {
        Keyboard.press(KeyMapingPress->LayerMap[currentLayer].MacroKey3); 
      }
    }
    else
    {
      ButtonPessStatus->status[currentLayer] = PRESSED;
      if(KeyMapingPress->LayerMap[currentLayer].isShifted == false)
      {
        Keyboard.press(KeyMapingPress->LayerMap[currentLayer].Keycode); 
      }
      else
      {
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KeyMapingPress->LayerMap[currentLayer].Keycode); 
      } 
      HandleKeyCaps(KeyMapingPress->LayerMap[currentLayer].Keycode); 
    }
  }
  else if( (KeyMapingPress->LayerMap[currentLayer].keyType == KeyType_Normal) && (KeyMapingPress->LayerMap[currentLayer].Keycode != KEY_LEFT_SHIFT)&&(buttonStatus->button_curr_state == HOLD ) && (buttonStatus->isMultiBotPressed == false) && (millis() - buttonStatus->holdKeyPresstickstart) >= KEY_HOLD_UPDATE_PERIOD_MS)
  { 
    if( KeyMapingPress->LayerMap[currentLayer].Keycode != KEY_LANG9  && KeyMapingPress->LayerMap[currentLayer].Keycode != KEY_LANG4 && KeyMapingPress->LayerMap[currentLayer].Keycode != KEY_LANG7)
    {
      ButtonPessStatus->status[currentLayer] = HOLD;
      if(KeyMapingPress->LayerMap[currentLayer].isShifted == false)
      {
        Keyboard.press(KeyMapingPress->LayerMap[currentLayer].Keycode); 
      }
      else
      {
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KeyMapingPress->LayerMap[currentLayer].Keycode); 
      }  
      buttonStatus->holdKeyPresstickstart = millis();
    }
  }
  else if( buttonStatus->button_curr_state == RELEASED && buttonStatus->is_updated == true)
  { 
    ButtonPessStatus->status[currentLayer] = RELEASED;
    isPressCurActive = false;
    ReleasePress(KeyMapingPress); 
  }
}
void ReleasePress (strKeyMapping *KeyMapingPress)
{
 if( KeyMapingPress->LayerMap[currentLayer].keyType == KeyType_Macro )
  {
    if( KeyMapingPress->LayerMap[currentLayer].MacroKey1 != KEY_RESERVED)
    {
      Keyboard.release(KeyMapingPress->LayerMap[currentLayer].MacroKey1); 
    }
    if( KeyMapingPress->LayerMap[currentLayer].MacroKey2 != KEY_RESERVED)
    {
      Keyboard.release(KeyMapingPress->LayerMap[currentLayer].MacroKey2); 
    }
    if( KeyMapingPress->LayerMap[currentLayer].MacroKey3 != KEY_RESERVED)
    {
      Keyboard.release(KeyMapingPress->LayerMap[currentLayer].MacroKey3); 
    }
  }
  else if( (KeyMapingPress->LayerMap[currentLayer].Keycode != KEY_LANG9 && KeyMapingPress->LayerMap[currentLayer].Keycode != KEY_LANG4 && KeyMapingPress->LayerMap[currentLayer].Keycode != KEY_LANG8 && KeyMapingPress->LayerMap[currentLayer].Keycode != KEY_LANG7 ) && KeyMapingPress->LayerMap[currentLayer].keyType == KeyType_Normal)
  {
    if(KeyMapingPress->LayerMap[currentLayer].isShifted == false)
    {
      Keyboard.release(KeyMapingPress->LayerMap[currentLayer].Keycode);
    }
    else
    {
      Keyboard.release(KeyMapingPress->LayerMap[currentLayer].Keycode);
      Keyboard.release(KEY_LEFT_SHIFT);
    }
  }
}

void ReleasePressedButton(byte layerIndex)
{
  for (int row = 0; row < KEYBORD_ROWS_COUNT; row++) 
  {
    for (int col = 0; col < KEYBORD_COLS_COUNT; col++) 
    {  
      if(ButtonPessStatus_L[row][col].status[layerIndex] == PRESSED || ButtonPessStatus_L[row][col].status[layerIndex] == HOLD)
      {
        PrintSerialDebugMsg("-----------------------------------------------------------");
        ReleasePress(&keyMapingLeftPress[row][col]);
        ButtonPessStatus_L[row][col].status[layerIndex] = RELEASED;
      }
      if(ButtonPessStatus_R[row][col].status[layerIndex] == PRESSED || ButtonPessStatus_R[row][col].status[layerIndex] == HOLD)
      {
        PrintSerialDebugMsg("-----------------------------------------------------------");
        ReleasePress(&keyMapingRightPress[row][col]);
        ButtonPessStatus_R[row][col].status[layerIndex] = RELEASED;
      } 
    }
  }

  // for (int sumIndex = 0; sumIndex < 4; sumIndex++) 
  // { 
  //   if(ButtonPessStatus_L[row][col].status[layerIndex] == PRESSED || ButtonPessStatus_L[row][col].status[layerIndex] == HOLD)
  //   {
  //     ButtonPessStatusSumb_L[sumIndex].status[layerIndex] = RELEASED;
  //     ButtonPessStatusSumb_R[sumIndex].status[layerIndex] = RELEASED; 
  // }
}

void LayerHandler(int button_curr_state, bool is_updated, bool isMultiBotPressed, KeyboardKeycode keycode)
{ 
  byte dataOut[3];

  //if( isPressCurActive == false || ((is_updated == true && button_curr_state == HOLD)))
  {
    if( button_curr_state == PRESSED && is_updated == true && isMultiBotPressed == false)
    { 
      ReleasePressedButton(currentLayer);
      prevLayer = currentLayer;
      if( keycode == KEY_LANG1 && currentLayer == 1)
        currentLayer = 0;
      else if( keycode == KEY_LANG2 && currentLayer == 2)
        currentLayer = 0;
      else if( keycode == KEY_LANG1)
        currentLayer = 1;
      else if( keycode == KEY_LANG2)
        currentLayer = 2;
      layerShiftMode = LAYER_SHIFT_STICKY ;
      dataOut[0] = 0x0D;
      // if (isGamingModeActive == false)
      // {
        dataOut[1] = (byte) currentLayer;
      // } 
      // else
      // {
      //   if (currentLayer != 0) 
      //     dataOut[1] = (byte) 2;
      // }
      dataOut[2] = '\n';
      Serial1.write(dataOut, 3);
      PrintSerialDebugMsg("Layer_L PRESS");
      isLayerChangePressCurActive = true;
    } 
    else if(((is_updated == true && button_curr_state == HOLD))&& isMultiBotPressed == false)
    {
      ReleasePressedButton(currentLayer);
      prevLayer = currentLayer;
      layerShiftMode = LAYER_SHIFT_TOGGLE_HOLD ; 
      if( keycode == KEY_LANG1)
        currentLayer = 1;
      else if( keycode == KEY_LANG2)
        currentLayer = 2;
      dataOut[0] = 0x0D;
      // if (isGamingModeActive == false)
      // {
        dataOut[1] = (byte) currentLayer;
      // } 
      // else
      // {
      //   if (currentLayer != 0) 
      //     dataOut[1] = (byte) 2;
      // }
      dataOut[2] = '\n';
      Serial1.write(dataOut, 3);
      PrintSerialDebugMsg("Layer_L HOLD");
    }
    else if(button_curr_state == RELEASED && (layerShiftMode == LAYER_SHIFT_TOGGLE_RELEASED || layerShiftMode == LAYER_SHIFT_TOGGLE_HOLD || layerShiftModeToggleEnable == true) && isMultiBotPressed == false && is_updated == true)
    { 
      ReleasePressedButton(currentLayer);
      prevLayer = currentLayer;
      if(layerShiftMode == LAYER_SHIFT_TOGGLE_HOLD)
        layerShiftMode = LAYER_SHIFT_TOGGLE_RELEASED;
      currentLayer = 0; 
      dataOut[0] = 0x0D;
      dataOut[1] = (byte) currentLayer;
      dataOut[2] = '\n';
      Serial1.write(dataOut, 3); 
      PrintSerialDebugMsg("Layer_L RELEASED");
      isLayerChangePressCurActive = false;
    }
  }
  // else
  // {
  //   if(button_curr_state == RELEASED && (layerShiftMode == LAYER_SHIFT_TOGGLE_HOLD )  && is_updated == true)
  //   {
  //       layerShiftMode = LAYER_SHIFT_TOGGLE_RELEASED;
  //   }
  // }
}
 

void HandleKeyCaps(KeyboardKeycode Keycode)
{
  byte dataOut[3];
  if(Keycode == KEY_CAPS_LOCK && isCapsPressed == false)
  {
    isCapsPressed = true;
    dataOut[0] = 0x0B;
    dataOut[1] = (byte) isCapsPressed;
    dataOut[2] = '\n'; 
    Serial1.write(dataOut, 3);
  }
  else if( Keycode== KEY_CAPS_LOCK && isCapsPressed == true)
  { 
    isCapsPressed = false;
    dataOut[0] = 0x0B;
    dataOut[1] = (byte) isCapsPressed;
    dataOut[2] = '\n'; 
    Serial1.write(dataOut, 3);
  }
}


void EncoderHandler()
{

  noInterrupts();
  int8_t acc = stepAccum;
  // Only report on full detent: 4 edges per quadrature cycle
  if (acc >= +4) 
  { 
    stepAccum = 0; 
    interrupts(); 
    // Serial.println("Clockwise"); 
    if(currentLayer == 2)
    {
      Keyboard.press(KEY_LEFT_ARROW);
      Keyboard.release(KEY_LEFT_ARROW);
    }
    else
    {
      Consumer.write(MEDIA_VOL_DOWN);
    }
  }
  else if (acc <= -4) 
  { 
    stepAccum = 0; 
    interrupts(); 
    // Serial.println("Counter-Clockwise"); 
    if(currentLayer == 2)
    {
      Keyboard.press(KEY_RIGHT_ARROW);
      Keyboard.release(KEY_RIGHT_ARROW);
    }
    else
    {
      Consumer.write(MEDIA_VOL_UP);
    }
    }
  else 
  { 
    interrupts(); 
    }
  // int ecoderCurState = digitalRead(ENCODER_PIN_A);

  // if (ecoderCurState != ecoderPrevState) {
  //   // Only act on falling edge
  //   if (ecoderCurState == LOW) {
  //     if (digitalRead(ENCODER_PIN_B) == LOW) {
  //       // Clockwise
  //       Serial.println("Clockwise");
  //       if(currentLayer == 2)
  //       {
  //         Keyboard.press(KEY_RIGHT_ARROW);
  //         Keyboard.release(KEY_RIGHT_ARROW);
  //       }
  //       else
  //       {
  //         Consumer.write(MEDIA_VOL_UP);
  //       }
        
  //     } 
  //     else 
  //     { 
  //       // Counter-Clockwise
  //       Serial.println("Counter-Clockwise");
  //       if(currentLayer == 2)
  //       {
  //         Keyboard.press(KEY_LEFT_ARROW);
  //         Keyboard.release(KEY_LEFT_ARROW);
  //       }
  //       else
  //       {
  //         Consumer.write(MEDIA_VOL_DOWN);
  //       }
        
  //     } 
      
  //   }
  // } 
  // ecoderPrevState = ecoderCurState;
}

inline uint8_t readAB() {
    uint8_t a = digitalRead(ENCODER_PIN_A);
    uint8_t b = digitalRead(ENCODER_PIN_B);
    return (a << 1) | b;
  }

void encoderISR() {
   uint8_t cur = readAB();
  uint8_t idx = (lastState << 2) | cur;
  int8_t step = qtab[idx];
  lastState = cur;                  // advance state even on invalids

  if (step != 0) {
    stepAccum += step;              // ±1 per valid edge
  }
}

void ConsumerKeyPressHandler(KeyboardKeycode keyCode)
{
  switch(keyCode)
  {
    case Key_CALC:
      Consumer.write(CONSUMER_CALCULATOR);
    break;
  }
}


void PrintSerialDebugMsg(String msg)
{
  if(SERIAL_DEBUGGING_ENABLE == true )
  {
    Serial.println(msg); 
  }
}