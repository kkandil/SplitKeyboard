
#include "KeyMapping.h"
#include <Encoder.h>

 

typedef enum{
LAYER_SHIFT_STICKY = 0,
LAYER_SHIFT_TOGGLE = 1
}enLayerShiftMode;


byte rowPins[KEYBORD_ROWS_COUNT] = {8,9,10}; // Arduino row pins
byte colPins[KEYBORD_COLS_COUNT] = {2,3,4,5,6,7}; // Arduino column pins
byte sumbPins[3] = {15,14,16};
#define LED_1_PIN A0
#define LED_2_PIN A1 

byte currentLayer = 0;
byte layerShiftMode = LAYER_SHIFT_STICKY;
bool isCapsPressed = false;
bool isPressCurActive = false;
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
strButtonStatus sumbButtonsStatus[3] = {{RELEASED, RELEASED, RELEASED, RELEASED, 0, 0, 0, BUTTON_HOLD_DEBUNCE_TIME, false, false, false},
                                     {RELEASED, RELEASED, RELEASED, RELEASED, 0, 0, 0, 200, false, false, false},
                                     {RELEASED, RELEASED, RELEASED, RELEASED, 0, 0, 0, BUTTON_HOLD_DEBUNCE_TIME, false, false, false}};

strButtonStatus keyMatrixButtonsStatus_R[KEYBORD_ROWS_COUNT][KEYBORD_COLS_COUNT]; 
strButtonStatus sumbButtonsStatus_R[3] = {{RELEASED, RELEASED, RELEASED, RELEASED, 0, 0, 0, BUTTON_HOLD_DEBUNCE_TIME, false, false, false},
                                     {RELEASED, RELEASED, RELEASED, RELEASED, 0, 0, 0, 200, false, false, false},
                                     {RELEASED, RELEASED, RELEASED, RELEASED, 0, 0, 0, BUTTON_HOLD_DEBUNCE_TIME, false, false, false}};



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);

  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT); 
  
  for (int row = 0; row < KEYBORD_ROWS_COUNT; row++) 
  {
    pinMode(rowPins[row], OUTPUT); // Set rows as input with pull-ups
    digitalWrite(rowPins[row], HIGH); // Ensure columns are high by default
  }
  for (int col = 0; col < KEYBORD_COLS_COUNT; col++) 
  {
      pinMode(colPins[col], INPUT_PULLUP); 
  }
  for( int sumIndex=0;sumIndex<3;sumIndex++)
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
}








void loop() { 
 
  ReadKeyboardMatrix();  
  for(int buttonIndex=0 ; buttonIndex<3 ; buttonIndex++)
  {
   GetButtonStatus(&sumbButtonsStatus[buttonIndex],sumbPins[buttonIndex]);
  }
  GetRightKeyboardButtonsStatus();
  
  // if( isGamingModeActive == true)
  // {
  //   SumbButtonsMapingHandler(sumbButtonsStatus, thumbMapingLeftPress_, thumbMapingLeftPress_);
  // }
  // else
  // {
    SumbButtonsMapingHandler(sumbButtonsStatus, thumbMapingLeftPress, thumbMapingLeftPress);
  // }
  SumbButtonsMapingHandler(sumbButtonsStatus_R, thumbMapingRightPress, thumbMapingRightPress);
  // if( isGamingModeActive == true)
  // {
  //   KeyboardMatrixMapingHandler(keyMatrixButtonsStatus, keyMapingLeftPress_, keyMapingLeftPress_);
  // }
  // else
  // {
    KeyboardMatrixMapingHandler(keyMatrixButtonsStatus, keyMapingLeftPress, keyMapingLeftPress);
  // }
  KeyboardMatrixMapingHandler(keyMatrixButtonsStatus_R, keyMapingRightPress, keyMapingRightPress);
 
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
          
        // Serial.print(buttonPin );
        // Serial.print(" ");
        // Serial.println("PRESS"); 
      }
      else if( buttonStatus->button_curr_read == RELEASED ) 
      {
        buttonStatus->button_curr_state = RELEASED;
        buttonStatus->is_updated = true;
        buttonStatus->isMultiBotPressed = false;
        // Serial.print(buttonPin );
        // Serial.print(" ");
        // Serial.println("RELEASED");
      }
      buttonStatus->isDebunceInProgress = false;
  }

  if ( buttonStatus->button_curr_state == PRESSED &&  (millis() - buttonStatus->button_holdtickstart) > buttonStatus->buttonHoldDebounceTime)
  {
    buttonStatus->button_prev_state = buttonStatus->button_curr_state;
    buttonStatus->button_curr_state = HOLD;
    buttonStatus->is_updated = true;
    buttonStatus->holdKeyPresstickstart = millis() + KEY_HOLD_UPDATE_PERIOD_MS;
    // Serial.print(buttonPin );
    // Serial.print(" ");
    // Serial.println("HOLD");
  }

  buttonStatus->button_prev_read = buttonStatus->button_curr_read; 
}

void GetRightKeyboardButtonsStatus(void)
{ 
  byte datain[25];
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
    int readLength = Serial1.readBytesUntil('\n',datain,25);
    
    if( datain[21] == 0x0C)
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
      for(int buttonIndex=0 ; buttonIndex<3 ; buttonIndex++)
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

void  SumbButtonsMapingHandler(strButtonStatus buttonStatus[3], strKeyMapping KeyMapingPress[3], strKeyMapping KeyMapingHold[3])
{
  for(int i=0 ; i<3 ; i++)
  { 
    if( KeyMapingPress[i].LayerMap[currentLayer].Keycode == KEY_LANG1 || KeyMapingPress[i].LayerMap[currentLayer].Keycode == KEY_LANG2)
    {
      LayerHandlerLeft(buttonStatus[i].button_curr_state, buttonStatus[i].is_updated, buttonStatus[i].isMultiBotPressed, KeyMapingPress[i].LayerMap[currentLayer].Keycode );
    }
    // else if( KeyMapingPress[i].LayerMap[currentLayer].Keycode == KEY_LANG2)
    // {
    //   LayerHandlerRight(buttonStatus[i].button_curr_state, buttonStatus[i].is_updated, buttonStatus[i].isMultiBotPressed);
    // }
    else
    {
      KeyPressHandler(&buttonStatus[i], &KeyMapingPress[i], &KeyMapingHold[i]);
      // if( (buttonStatus[i].button_curr_state == PRESSED || buttonStatus[i].button_curr_state == HOLD ) && (buttonStatus[i].isMultiBotPressed == false) && buttonStatus[i].is_updated == true)
      // {  
      //   Keyboard.press( KeyMaping[i].LayerMap[currentLayer].Keycode);  
      // }  
      // else if( (buttonStatus[i].button_curr_state == RELEASED && buttonStatus[i].is_updated == true) && (buttonStatus[i].isMultiBotPressed == false)  && buttonStatus[i].is_updated == true)
      // { 
      //   Keyboard.release( KeyMaping[i].LayerMap[currentLayer].Keycode); 
      // }

    }
  }
}

void KeyPressHandler(strButtonStatus *buttonStatus, strKeyMapping *KeyMapingPress, strKeyMapping *KeyMapingHold)
{
  if(buttonStatus->is_updated == true && buttonStatus->button_curr_state == PRESSED && buttonStatus->isMultiBotPressed == false )
  {   
    isPressCurActive = true;
    if( KeyMapingPress->LayerMap[currentLayer].Keycode == KEY_LANG3 )
    {
      Keyboard.print("kkandil");
      Keyboard.write(KEY_TAB);
      Keyboard.print("2wad@Mywork1"); 
    }
    else if( KeyMapingPress->LayerMap[currentLayer].Keycode == KEY_LANG4 )
    {   
      Keyboard.print("2wad@Mywork1"); 
    }
    else if( KeyMapingPress->LayerMap[currentLayer].Keycode == KEY_LANG5 )
    { 
      if( isGamingModeActive == false)
      {
        thumbMapingRightPress[1].LayerMap[0].Keycode = KEY_LANG2;  
        thumbMapingRightPress[1].LayerMap[1].Keycode = KEY_LANG2; 
        thumbMapingRightPress[1].LayerMap[2].Keycode = KEY_LANG2; 
        isGamingModeActive = true; 
      }
      else
      {
        thumbMapingRightPress[1].LayerMap[0].Keycode = KEY_LANG2;  
        thumbMapingRightPress[1].LayerMap[1].Keycode = KEY_LANG2; 
        thumbMapingRightPress[1].LayerMap[2].Keycode = KEY_LANG2; 
        isGamingModeActive = false;
      }
      GetKeyMapingData(isGamingModeActive); 
      Serial.println("isGamingModeActive"); 
    }
    else if( KeyMapingPress->LayerMap[currentLayer].isAMacro == true)
    {
      if( KeyMapingPress->LayerMap[currentLayer].MacroKey1 != NULL)
      {
        Keyboard.press(KeyMapingPress->LayerMap[currentLayer].MacroKey1); 
      }
      if( KeyMapingPress->LayerMap[currentLayer].MacroKey2 != NULL)
      {
        Keyboard.press(KeyMapingPress->LayerMap[currentLayer].MacroKey2); 
      }
      if( KeyMapingPress->LayerMap[currentLayer].MacroKey3 != NULL)
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
  else if( (KeyMapingPress->LayerMap[currentLayer].isAMacro == false) && (KeyMapingPress->LayerMap[currentLayer].Keycode != KEY_LEFT_SHIFT)&&(buttonStatus->button_curr_state == HOLD ) && (buttonStatus->isMultiBotPressed == false) && (millis() - buttonStatus->holdKeyPresstickstart) >= KEY_HOLD_UPDATE_PERIOD_MS)
  { 
    if( KeyMapingPress->LayerMap[currentLayer].Keycode != KEY_LANG3  && KeyMapingPress->LayerMap[currentLayer].Keycode != KEY_LANG4)
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
    if( KeyMapingPress->LayerMap[currentLayer].isAMacro == true )
    {
      if( KeyMapingPress->LayerMap[currentLayer].MacroKey1 != NULL)
      {
        Keyboard.release(KeyMapingPress->LayerMap[currentLayer].MacroKey1); 
      }
      if( KeyMapingPress->LayerMap[currentLayer].MacroKey2 != NULL)
      {
        Keyboard.release(KeyMapingPress->LayerMap[currentLayer].MacroKey2); 
      }
      if( KeyMapingPress->LayerMap[currentLayer].MacroKey3 != NULL)
      {
        Keyboard.release(KeyMapingPress->LayerMap[currentLayer].MacroKey3); 
      }
    }
    else if( KeyMapingPress->LayerMap[currentLayer].Keycode != KEY_LANG3 && KeyMapingPress->LayerMap[currentLayer].Keycode != KEY_LANG4)
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
}

void LayerHandlerLeft(int button_curr_state, bool is_updated, bool isMultiBotPressed, KeyboardKeycode keycode)
{ 
  byte dataOut[3];

  if( isPressCurActive == false)
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
    // Serial.println("Layer_L PRESS");
  } 
  else if(((is_updated == true && button_curr_state == HOLD))&& isMultiBotPressed == false)
  {
    layerShiftMode = LAYER_SHIFT_TOGGLE ; 
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
    // Serial.println("Layer_L HOLD");
  }
  else if(button_curr_state == RELEASED && layerShiftMode == LAYER_SHIFT_TOGGLE && isMultiBotPressed == false && is_updated == true)
  { 
    currentLayer = 0; 
    dataOut[0] = 0x0D;
    dataOut[1] = (byte) currentLayer;
    dataOut[2] = '\n';
    Serial1.write(dataOut, 3);
    // Serial.println("Layer_L RELEASED");
  }
  }
}

void LayerHandlerRight(int button_curr_state, bool is_updated, bool isMultiBotPressed)
{ 
  byte dataOut[3];
  if( isPressCurActive == false)
  {
  if( button_curr_state == PRESSED && is_updated == true && isMultiBotPressed == false)
  {
    // Serial.println("LayerChange");
    if( currentLayer == 1)
      currentLayer = 0;
    else
      currentLayer = 1;
    layerShiftMode = LAYER_SHIFT_STICKY ;
    // Serial.println("Layer_R PRESS");

    dataOut[0] = 0x0D;
    dataOut[1] = (byte) currentLayer;
    dataOut[2] = '\n';
    Serial1.write(dataOut, 3);
  } 
  else if(((is_updated == true && button_curr_state == HOLD))&& isMultiBotPressed == false)
  {
    layerShiftMode = LAYER_SHIFT_TOGGLE ; 
    currentLayer = 1; 
    // Serial.println("Layer_R HOLD");
    dataOut[0] = 0x0D;
    dataOut[1] = (byte) currentLayer;
    dataOut[2] = '\n';
    Serial1.write(dataOut, 3);
  }
  else if(button_curr_state == RELEASED && layerShiftMode == LAYER_SHIFT_TOGGLE && isMultiBotPressed == false && is_updated == true)
  { 
    currentLayer = 0; 
    dataOut[0] = 0x0D;
    dataOut[1] = (byte) currentLayer;
    dataOut[2] = '\n';
    Serial1.write(dataOut, 3);
    // Serial.println("Layer_R RELEASED");
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

void GetKeyMapingData(bool isGamingModeActive)
{
  // strKeyMapping keyMaping[KEYBORD_ROWS_COUNT][KEYBORD_COLS_COUNT] = {0};
  // strKeyMapping thumbMaping[KEYBORD_ROWS_COUNT] = {0};
  byte datain[25];
  byte dataOut[3]; 
  bool isDataReceived = false;

  for(int i=0 ; i<KEYBORD_ROWS_COUNT ; i++)
  { 
    for(int j=0 ; j<KEYBORD_COLS_COUNT ; j++)
    { 
      responceWaitTimer = millis();
      dataOut[0] = 0x0E;
      dataOut[1] = (byte) isGamingModeActive;
      dataOut[2] = '\n';
      Serial1.write(dataOut, 3);
      responceWaitTimer = millis(); 
      while ( Serial1.available()==0 && ((millis() - responceWaitTimer)<=500) ) {}
      if( ((millis() - responceWaitTimer)>=500) )
      {
        Serial.println("Error KeyMaping data not recevied"); 
      }
      else
      {
        int readLength = Serial1.readBytesUntil(0xFF,datain,20); 
        if( datain[0] == 0x0E )
        { 
          isDataReceived = true;
          int index=1;
          for(int k=0 ; k<3 ; k++)
          { 
            keyMapingLeftPress[i][j].LayerMap[k].Keycode = datain[index];
            keyMapingLeftPress[i][j].LayerMap[k].isShifted = datain[index+1];
            keyMapingLeftPress[i][j].LayerMap[k].isAMacro = datain[index+2];
            keyMapingLeftPress[i][j].LayerMap[k].MacroKey1 = datain[index+3];
            keyMapingLeftPress[i][j].LayerMap[k].MacroKey2 = datain[index+4];
            keyMapingLeftPress[i][j].LayerMap[k].MacroKey3 = datain[index+5];
            index = index + 6;
          }
          Serial.print(readLength);
          Serial.print(", ");
          for(int k=0 ; k<readLength ; k++)
          {
            Serial.print(datain[k]);
            Serial.print("   ");
          }
          Serial.println("");
        }
        else
        {
          isDataReceived = false;
          Serial.print(datain[0]);
          Serial.println(" Error KeyMaping data not valid"); 
          break;
        }
      }
    }
    if( isDataReceived == false)
    {
      break;
    }
  }
  // if( isDataReceived == true)
  // {
  //   for(int i=0 ; i<KEYBORD_ROWS_COUNT ; i++)
  //   { 
  //     for(int j=0 ; j<KEYBORD_COLS_COUNT ; j++)
  //     { 
  //       for(int k=0 ; k<3 ; k++)
  //       { 
          
  //         keyMapingLeftPress[i][j].LayerMap[k].Keycode = keyMaping[i][j].LayerMap[k].Keycode;
  //         keyMapingLeftPress[i][j].LayerMap[k].isShifted = keyMaping[i][j].LayerMap[k].isShifted;
  //         keyMapingLeftPress[i][j].LayerMap[k].isAMacro = keyMaping[i][j].LayerMap[k].isAMacro;
  //         keyMapingLeftPress[i][j].LayerMap[k].MacroKey1 = keyMaping[i][j].LayerMap[k].MacroKey1;
  //         keyMapingLeftPress[i][j].LayerMap[k].MacroKey2 = keyMaping[i][j].LayerMap[k].MacroKey2;
  //         keyMapingLeftPress[i][j].LayerMap[k].MacroKey3 = keyMaping[i][j].LayerMap[k].MacroKey3;
  //       }
  //     }
  //   } 
  //   Serial.println("keyMaping Updated");
  // }
  delay(100);
  isDataReceived = false; 
  for(int i=0 ; i<KEYBORD_ROWS_COUNT ; i++)
  { 
    responceWaitTimer = millis();
    dataOut[0] = 0x0F;
    dataOut[1] = (byte) isGamingModeActive;
    dataOut[2] = '\n';
    Serial1.write(dataOut, 3);
    responceWaitTimer = millis(); 
    while ( Serial1.available()==0 && ((millis() - responceWaitTimer)<=500) ) {}
    if( ((millis() - responceWaitTimer)>=500) )
    {
      Serial.println("Error thumbMaping data not recevied"); 
    }
    else
    {
      int readLength = Serial1.readBytesUntil(0xFF,datain,20); 
      if( datain[0] == 0x0F )
      { 
        isDataReceived = true;
        int index=1;
        for(int k=0 ; k<3 ; k++)
        { 
          thumbMapingLeftPress[i].LayerMap[k].Keycode = datain[index];
          thumbMapingLeftPress[i].LayerMap[k].isShifted = datain[index+1];
          thumbMapingLeftPress[i].LayerMap[k].isAMacro = datain[index+2];
          thumbMapingLeftPress[i].LayerMap[k].MacroKey1 = datain[index+3];
          thumbMapingLeftPress[i].LayerMap[k].MacroKey2 = datain[index+4];
          thumbMapingLeftPress[i].LayerMap[k].MacroKey3 = datain[index+5];
          index = index + 6;
        }
        Serial.print(readLength);
        Serial.print(", ");
        for(int k=0 ; k<readLength ; k++)
        { 
          Serial.print(datain[k]);
          Serial.print("   ");
        }
        Serial.println("");
      }
      else
      {
        isDataReceived = false; 
        Serial.println("Error thumbMaping data not valid"); 
        break;
      }
    }
  }
  // if( isDataReceived == true)
  // {
  //   for(int i=0 ; i<KEYBORD_ROWS_COUNT ; i++)
  //   { 
  //     for(int k=0 ; k<3 ; k++)
  //     { 
        
  //       thumbMapingLeftPress[i].LayerMap[k].Keycode = thumbMaping[i].LayerMap[k].Keycode;
  //       thumbMapingLeftPress[i].LayerMap[k].isShifted = thumbMaping[i].LayerMap[k].isShifted;
  //       thumbMapingLeftPress[i].LayerMap[k].isAMacro = thumbMaping[i].LayerMap[k].isAMacro;
  //       thumbMapingLeftPress[i].LayerMap[k].MacroKey1 = thumbMaping[i].LayerMap[k].MacroKey1;
  //       thumbMapingLeftPress[i].LayerMap[k].MacroKey2 = thumbMaping[i].LayerMap[k].MacroKey2;
  //       thumbMapingLeftPress[i].LayerMap[k].MacroKey3 = thumbMaping[i].LayerMap[k].MacroKey3;
  //     }
  //   } 
  //   Serial.println("thumbMaping Updated");
  // }

}
