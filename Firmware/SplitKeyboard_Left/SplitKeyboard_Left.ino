
#include "KeyMapping.h"
#include <Encoder.h>

 

typedef enum{
LAYER_SHIFT_STICKY = 0,
LAYER_SHIFT_TOGGLE_HOLD = 1,
LAYER_SHIFT_TOGGLE_RELEASED = 2
}enLayerShiftMode;


int rowPins[KEYBORD_ROWS_COUNT] = {2,SCK,MOSI,MISO}; // Arduino row pins
int colPins[KEYBORD_COLS_COUNT] = {A0,A1,A2,A3,A4,A5}; // Arduino column pins
byte sumbPins[4] = {SCL,3,4,SDA};
#define LED_1_PIN 5
#define LED_2_PIN 7 

#define ENCODER_PIN_A 9
#define ENCODER_PIN_B 10 

byte currentLayer = 0;
byte layerShiftMode = LAYER_SHIFT_STICKY;
bool layerShiftModeToggleEnable = false;
bool isCapsPressed = false;
bool isPressCurActive = false;
bool isLayerChangePressCurActive = false;
unsigned long responceWaitTimer = 0;
bool isGamingModeActive = false;

typedef enum{
  PRESSED = 0,
  RELEASED = 1,
  HOLD = 2,
  PRESSHOLD = 3
}enButton_Status;

typedef struct{
  byte button_curr_read ;
  byte button_prev_read ;
  byte button_curr_state;
  byte button_prev_state;
  unsigned long button_tickstart;
  unsigned long button_holdtickstart;
  unsigned long holdKeyPresstickstart;
  int buttonHoldDebounceTime;
  bool is_updated;
  bool isMultiBotPressed;
  bool isDebunceInProgress;
}strButtonStatus;
 
 
strButtonStatus keyMatrixButtonsStatus[KEYBORD_ROWS_COUNT][KEYBORD_COLS_COUNT]; 
strButtonStatus sumbButtonsStatus[4] = {{RELEASED, RELEASED, RELEASED, RELEASED, 0, 0, 0, BUTTON_HOLD_DEBUNCE_TIME, false, false, false},
                                      {RELEASED, RELEASED, RELEASED, RELEASED, 0, 0, 0, BUTTON_HOLD_DEBUNCE_TIME, false, false, false},
                                     {RELEASED, RELEASED, RELEASED, RELEASED, 0, 0, 0, 200, false, false, false},
                                     {RELEASED, RELEASED, RELEASED, RELEASED, 0, 0, 0, BUTTON_HOLD_DEBUNCE_TIME, false, false, false}};

strButtonStatus keyMatrixButtonsStatus_R[KEYBORD_ROWS_COUNT][KEYBORD_COLS_COUNT]; 
strButtonStatus sumbButtonsStatus_R[4] = {{RELEASED, RELEASED, RELEASED, RELEASED, 0, 0, 0, BUTTON_HOLD_DEBUNCE_TIME, false, false, false},
                                      {RELEASED, RELEASED, RELEASED, RELEASED, 0, 0, 0, 200, false, false, false},
                                     {RELEASED, RELEASED, RELEASED, RELEASED, 0, 0, 0, BUTTON_HOLD_DEBUNCE_TIME, false, false, false},
                                     {RELEASED, RELEASED, RELEASED, RELEASED, 0, 0, 0, BUTTON_HOLD_DEBUNCE_TIME, false, false, false}};


int ecoderPrevState;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);

  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT); 

  pinMode(ENCODER_PIN_A, INPUT_PULLUP);
  pinMode(ENCODER_PIN_B, INPUT_PULLUP);
  for (int row = 0; row < KEYBORD_ROWS_COUNT; row++) 
  {
    pinMode(rowPins[row], OUTPUT); // Set rows as input with pull-ups
    digitalWrite(rowPins[row], HIGH); // Ensure columns are high by default
  }
  for (int col = 0; col < KEYBORD_COLS_COUNT; col++) 
  {
      pinMode(colPins[col], INPUT_PULLUP); 
  }
  for( int sumIndex=0;sumIndex<4;sumIndex++)
  {
     pinMode(sumbPins[sumIndex], INPUT_PULLUP); 
  }
  
  for (int row = 0; row < KEYBORD_ROWS_COUNT; row++) 
  {
    for (int col = 0; col < KEYBORD_COLS_COUNT; col++) 
    {
      keyMatrixButtonsStatus[row][col].button_curr_read = RELEASED;
      keyMatrixButtonsStatus[row][col].button_prev_read = RELEASED;
      keyMatrixButtonsStatus[row][col].button_curr_state = RELEASED;
      keyMatrixButtonsStatus[row][col].button_prev_state = RELEASED;
      keyMatrixButtonsStatus[row][col].button_tickstart = 0;
      keyMatrixButtonsStatus[row][col].button_holdtickstart = 0;
      keyMatrixButtonsStatus[row][col].holdKeyPresstickstart = 0;
      keyMatrixButtonsStatus[row][col].buttonHoldDebounceTime = BUTTON_HOLD_DEBUNCE_TIME;
      keyMatrixButtonsStatus[row][col].is_updated = false;
      keyMatrixButtonsStatus[row][col].isMultiBotPressed = false;
      keyMatrixButtonsStatus[row][col].isDebunceInProgress = false;
    }
  }

  for (int row = 0; row < KEYBORD_ROWS_COUNT; row++) 
  {
    for (int col = 0; col < KEYBORD_COLS_COUNT; col++) 
    {
      keyMatrixButtonsStatus_R[row][col].button_curr_read = RELEASED;
      keyMatrixButtonsStatus_R[row][col].button_prev_read = RELEASED;
      keyMatrixButtonsStatus_R[row][col].button_curr_state = RELEASED;
      keyMatrixButtonsStatus_R[row][col].button_prev_state = RELEASED;
      keyMatrixButtonsStatus_R[row][col].button_tickstart = 0;
      keyMatrixButtonsStatus_R[row][col].button_holdtickstart = 0;
      keyMatrixButtonsStatus_R[row][col].holdKeyPresstickstart = 0;
      keyMatrixButtonsStatus_R[row][col].buttonHoldDebounceTime = BUTTON_HOLD_DEBUNCE_TIME;
      keyMatrixButtonsStatus_R[row][col].is_updated = false;
      keyMatrixButtonsStatus_R[row][col].isMultiBotPressed = false;
      keyMatrixButtonsStatus_R[row][col].isDebunceInProgress = false;
    }
  }
  
 
  Keyboard.begin();
  Consumer.begin();

  ecoderPrevState = digitalRead(ENCODER_PIN_A);
}








void loop() { 
 
    
  for(int buttonIndex=0 ; buttonIndex<4 ; buttonIndex++)
  {
   GetButtonStatus(&sumbButtonsStatus[buttonIndex],sumbPins[buttonIndex]);
  }
  ReadKeyboardMatrix();
  GetRightKeyboardButtonsStatus();
  
  if( isGamingModeActive == false)
  {
    SumbButtonsMapingHandler(sumbButtonsStatus, thumbMapingLeftPress, thumbMapingLeftPress);
    SumbButtonsMapingHandler(sumbButtonsStatus_R, thumbMapingRightPress, thumbMapingRightPress);
  }
  else 
  {
    SumbButtonsMapingHandler(sumbButtonsStatus, thumbMapingLeftPress_Gaming, thumbMapingLeftPress_Gaming);
    SumbButtonsMapingHandler(sumbButtonsStatus_R, thumbMapingRightPress_Gaming, thumbMapingRightPress);
  }
  
 
  if( isGamingModeActive == false)
  {
   KeyboardMatrixMapingHandler(keyMatrixButtonsStatus, keyMapingLeftPress, keyMapingLeftPress);
   KeyboardMatrixMapingHandler(keyMatrixButtonsStatus_R, keyMapingRightPress, keyMapingRightPress);
 
  }
  else
  {
    KeyboardMatrixMapingHandler(keyMatrixButtonsStatus, keyMapingLeftPress_Gaming, keyMapingLeftPress_Gaming);
    KeyboardMatrixMapingHandler(keyMatrixButtonsStatus_R, keyMapingRightPress_Gaming, keyMapingRightPress_Gaming);
 
  }
  
  if( currentLayer == 1 && isGamingModeActive == false)
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


void ReadKeyboardMatrix(void)
{ 
  for (int row = 0; row < KEYBORD_ROWS_COUNT; row++) 
  {
    digitalWrite(rowPins[row], LOW); // Activate the column
    for(int col=0 ; col<KEYBORD_COLS_COUNT ; col++)
    {  
      GetButtonStatus(&keyMatrixButtonsStatus[row][col], colPins[col]); 
    }
    digitalWrite(rowPins[row], HIGH); // Deactivate the column
  }
}
 
   
void GetButtonStatus(strButtonStatus *buttonStatus, int buttonPin)
{
  if (buttonStatus->is_updated == true )
  {
    Serial.print(buttonPin );
      Serial.print(" ");
      Serial.println("Updated");
  }
  buttonStatus->is_updated = false;
  buttonStatus->button_curr_read = digitalRead(buttonPin) ;

  if (buttonStatus->button_curr_read != buttonStatus->button_prev_read) {
    buttonStatus->button_tickstart = millis();
    buttonStatus->isDebunceInProgress = true;
  }


  if (((millis() - buttonStatus->button_tickstart) > BUTTONS_DEBUNCE_TIME) && (buttonStatus->isDebunceInProgress == true )) 
  {
      buttonStatus->button_prev_state = buttonStatus->button_curr_state;
      if( buttonStatus->button_curr_read == PRESSED && buttonStatus->button_curr_state == RELEASED )
      {
        buttonStatus->button_curr_state = PRESSED;
        buttonStatus->button_holdtickstart = millis();
        buttonStatus->is_updated = true;
          
        Serial.print(buttonPin );
        Serial.print(" ");
        Serial.println("PRESS"); 
      }
      else if( buttonStatus->button_curr_read == RELEASED ) 
      {
        buttonStatus->button_curr_state = RELEASED;
        buttonStatus->is_updated = true;
        buttonStatus->isMultiBotPressed = false;
        Serial.print(buttonPin );
        Serial.print(" ");
        Serial.println("RELEASED");
      }
      buttonStatus->isDebunceInProgress = false;
  }

  if ( buttonStatus->button_curr_state == PRESSED &&  (millis() - buttonStatus->button_holdtickstart) > buttonStatus->buttonHoldDebounceTime)
  {
    buttonStatus->button_prev_state = buttonStatus->button_curr_state;
    buttonStatus->button_curr_state = HOLD;
    buttonStatus->is_updated = true;
    buttonStatus->holdKeyPresstickstart = millis() + KEY_HOLD_UPDATE_PERIOD_MS;
    Serial.print(buttonPin );
    Serial.print(" ");
    Serial.println("HOLD");
  }

  buttonStatus->button_prev_read = buttonStatus->button_curr_read; 
}

void GetRightKeyboardButtonsStatus(void)
{ 
  byte datain[31];
  byte dataOut[3];

  responceWaitTimer = millis();
  dataOut[0] = 0x0C;
  dataOut[1] = '\n';
  Serial1.write(dataOut, 2);
  responceWaitTimer = millis();
  while ( Serial1.available()==0 && ((millis() - responceWaitTimer)<=100) ) {}

  if( ((millis() - responceWaitTimer)>=100) )
  {
    // Serial.println("Error data not recevied"); 
  }
  else
  {
    int readLength = Serial1.readBytesUntil('\n',datain,31);
    
    if( datain[28] == 0x0C)
    {
      int index = 0;
      for (int row = 0; row < KEYBORD_ROWS_COUNT; row++) 
      {
        for (int col = 0; col < KEYBORD_COLS_COUNT; col++) 
        {
          keyMatrixButtonsStatus_R[row][col].button_curr_state = (datain[index] & 0x0F);
          keyMatrixButtonsStatus_R[row][col].is_updated = (datain[index] & 0xF0 )>>4; 
          index++;
        }
      }
      for(int buttonIndex=0 ; buttonIndex<4 ; buttonIndex++)
      {
        sumbButtonsStatus_R[buttonIndex].button_curr_state = (datain[index] & 0x0F);
        sumbButtonsStatus_R[buttonIndex].is_updated = (datain[index] & 0xF0 )>>4; 
        index++;
      }
    }
    else
    {
      // Serial.println("Data Error");
    }
  }
 
}

// typedef struct {
//     String text;
//     int col;
//     int row;
// } strKeyText;
// strKeyText textKeysLeft[2] = {
//   {"2wad@Mywork1", },{}
// };

void KeyboardMatrixMapingHandler(strButtonStatus buttonStatus[][6], strKeyMapping KeyMapingPress[][6], strKeyMapping KeyMapingHold[][6])
{
  for (int row = 0; row < KEYBORD_ROWS_COUNT; row++) 
  {
    for (int col = 0; col < KEYBORD_COLS_COUNT; col++) 
    {
      KeyPressHandler(&buttonStatus[row][col], &KeyMapingPress[row][col], &KeyMapingHold[row][col]);
    }
  }
}

void  SumbButtonsMapingHandler(strButtonStatus buttonStatus[4], strKeyMapping KeyMapingPress[4], strKeyMapping KeyMapingHold[4])
{
  for(int i=0 ; i<4 ; i++)
  { 
    if( KeyMapingPress[i].LayerMap[currentLayer].Keycode == KEY_LANG1 || KeyMapingPress[i].LayerMap[currentLayer].Keycode == KEY_LANG2)
    {
      LayerHandler(buttonStatus[i].button_curr_state, buttonStatus[i].is_updated, buttonStatus[i].isMultiBotPressed, KeyMapingPress[i].LayerMap[currentLayer].Keycode );
    } 
    else
    {
      KeyPressHandler(&buttonStatus[i], &KeyMapingPress[i], &KeyMapingHold[i]); 
    }
  }
}

void KeyPressHandler(strButtonStatus *buttonStatus, strKeyMapping *KeyMapingPress, strKeyMapping *KeyMapingHold)
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
    else if( KeyMapingPress->LayerMap[currentLayer].keyType == KeyType_String )
    {   
      if(KeyMapingPress->LayerMap[currentLayer].txt != "")
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
      //GetKeyMapingData(isGamingModeActive); 
      // Serial.println("isGamingModeActive"); 
    }
    else if( KeyMapingPress->LayerMap[currentLayer].keyType == KeyType_Macro)
    {
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
    if( KeyMapingPress->LayerMap[currentLayer].Keycode != KEY_LANG9  && KeyMapingPress->LayerMap[currentLayer].Keycode != KEY_LANG4)
    {
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
    
    isPressCurActive = false;
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
    else if( (KeyMapingPress->LayerMap[currentLayer].Keycode != KEY_LANG9 && KeyMapingPress->LayerMap[currentLayer].Keycode != KEY_LANG4 && KeyMapingPress->LayerMap[currentLayer].Keycode != KEY_LANG8 ) && KeyMapingPress->LayerMap[currentLayer].keyType == KeyType_Normal)
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
    if(isLayerChangePressCurActive==true && (layerShiftMode == LAYER_SHIFT_TOGGLE_RELEASED || layerShiftModeToggleEnable == true) )
    {
       byte dataOut[3];
    currentLayer = 0; 
      dataOut[0] = 0x0D;
      dataOut[1] = (byte) currentLayer;
      dataOut[2] = '\n';
      Serial1.write(dataOut, 3);
      Serial.println("Layer_L RELEASED");
      isLayerChangePressCurActive = false;
    }
  }
}

void LayerHandler(int button_curr_state, bool is_updated, bool isMultiBotPressed, KeyboardKeycode keycode)
{ 
  byte dataOut[3];

  if( isPressCurActive == false || ((is_updated == true && button_curr_state == HOLD)))
  {
    if( button_curr_state == PRESSED && is_updated == true && isMultiBotPressed == false)
    {
      // Serial.println("LayerChange");
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
      if (isGamingModeActive == false)
      {
        dataOut[1] = (byte) currentLayer;
      } 
      else
      {
        if (currentLayer != 0) 
          dataOut[1] = (byte) 2;
      }
      dataOut[2] = '\n';
      Serial1.write(dataOut, 3);
      Serial.println("Layer_L PRESS");
      isLayerChangePressCurActive = true;
    } 
    else if(((is_updated == true && button_curr_state == HOLD))&& isMultiBotPressed == false)
    {
      layerShiftMode = LAYER_SHIFT_TOGGLE_HOLD ; 
      if( keycode == KEY_LANG1)
        currentLayer = 1;
      else if( keycode == KEY_LANG2)
        currentLayer = 2;
      dataOut[0] = 0x0D;
      if (isGamingModeActive == false)
      {
        dataOut[1] = (byte) currentLayer;
      } 
      else
      {
        if (currentLayer != 0) 
          dataOut[1] = (byte) 2;
      }
      dataOut[2] = '\n';
      Serial1.write(dataOut, 3);
      Serial.println("Layer_L HOLD");
    }
    else if(button_curr_state == RELEASED && (layerShiftMode == LAYER_SHIFT_TOGGLE_RELEASED || layerShiftMode == LAYER_SHIFT_TOGGLE_HOLD || layerShiftModeToggleEnable == true) && isMultiBotPressed == false && is_updated == true)
    { 
      if(layerShiftMode == LAYER_SHIFT_TOGGLE_HOLD)
        layerShiftMode = LAYER_SHIFT_TOGGLE_RELEASED;
      currentLayer = 0; 
      dataOut[0] = 0x0D;
      dataOut[1] = (byte) currentLayer;
      dataOut[2] = '\n';
      Serial1.write(dataOut, 3);
      Serial.println("Layer_L RELEASED");
      isLayerChangePressCurActive = false;
    }
  }
  else
  {
    if(button_curr_state == RELEASED && (layerShiftMode == LAYER_SHIFT_TOGGLE_HOLD )  && is_updated == true)
    {
        layerShiftMode = LAYER_SHIFT_TOGGLE_RELEASED;
    }
  }
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
  int ecoderCurState = digitalRead(ENCODER_PIN_A);

  if (ecoderCurState != ecoderPrevState) {
    // Only act on falling edge
    if (ecoderCurState == LOW) {
      if (digitalRead(ENCODER_PIN_B) == LOW) {
        //Serial.println("Counter-Clockwise");  // ✅ flipped!
        if(currentLayer == 2)
        {
          Keyboard.press(KEY_RIGHT_ARROW);
          Keyboard.release(KEY_RIGHT_ARROW);
        }
        else
        {
          Consumer.write(MEDIA_VOL_UP);
        }
        
      } else {
        //Serial.println("Clockwise");
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
      
    }
  } 
  ecoderPrevState = ecoderCurState;
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
