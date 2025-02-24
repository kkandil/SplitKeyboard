
#include "KeyMapping.h"
#include <Encoder.h>

typedef enum{
BUTTON_R1_C1   =0 ,
BUTTON_R1_C2   =1 ,
BUTTON_R1_C3   =2 ,
BUTTON_R1_C4   =3 ,
BUTTON_R2_C1   =4 ,
BUTTON_R2_C2   =5 ,
BUTTON_R2_C3   =6 ,
BUTTON_R2_C4   =7 ,
BUTTON_R3_C1   =8 ,
BUTTON_R3_C2   =9 ,
BUTTON_R3_C3   =10,
BUTTON_SUMB_1  =11,
BUTTON_SUMB_2  =12,
BUTTON_PINK    =13
}enButtons;

typedef enum{
LAYER_SHIFT_STICKY = 0,
LAYER_SHIFT_TOGGLE = 1
}enLayerShiftMode;





int rowPins[KEYBORD_ROWS_COUNT] = {8,9,10}; // Arduino row pins
int colPins[KEYBORD_COLS_COUNT] = {2,3,4,5,6,7}; // Arduino column pins
int sumbPins[3] = {15,14,16};
#define LED_1_PIN A0
#define LED_2_PIN A1

int currentLayer = 0;
int layerShiftMode = LAYER_SHIFT_STICKY;
bool isCapsPressed = false;

typedef enum{
  PRESSED = 0,
  RELEASED = 1,
  HOLD = 2,
  PRESSHOLD = 3
}enButton_Status;

typedef struct{
  int button_curr_read ;
  int button_prev_read ;
  int button_curr_state;
  int button_prev_state;
  unsigned long button_tickstart;
  unsigned long button_holdtickstart;
  unsigned long holdKeyPresstickstart;
  int buttonHoldDebounceTime;
  bool is_updated;
  bool isMultiBotPressed;
  bool isDebunceInProgress;
}strButtonStatus;
 
//  typedef struct{
//   KeyboardKeycode Keycode; 
//   bool isShifted;
// }strKeyCode;

// typedef struct{
//   strKeyCode LayerMap[3]; 
// }strKeyMapping;

strButtonStatus keyMatrixButtonsStatus[KEYBORD_ROWS_COUNT][KEYBORD_COLS_COUNT]; 
strButtonStatus sumbButtonsStatus[3] = {{RELEASED, RELEASED, RELEASED, RELEASED, 0, 0, 0, BUTTON_HOLD_DEBUNCE_TIME, false, false, false},
                                     {RELEASED, RELEASED, RELEASED, RELEASED, 0, 0, 0, BUTTON_HOLD_DEBUNCE_TIME, false, false, false},
                                     {RELEASED, RELEASED, RELEASED, RELEASED, 0, 0, 0, BUTTON_HOLD_DEBUNCE_TIME, false, false, false}};

strButtonStatus keyMatrixButtonsStatus_R[KEYBORD_ROWS_COUNT][KEYBORD_COLS_COUNT]; 
strButtonStatus sumbButtonsStatus_R[3] = {{RELEASED, RELEASED, RELEASED, RELEASED, 0, 0, 0, BUTTON_HOLD_DEBUNCE_TIME, false, false, false},
                                     {RELEASED, RELEASED, RELEASED, RELEASED, 0, 0, 0, BUTTON_HOLD_DEBUNCE_TIME, false, false, false},
                                     {RELEASED, RELEASED, RELEASED, RELEASED, 0, 0, 0, BUTTON_HOLD_DEBUNCE_TIME, false, false, false}};


// strKeyMapping keyMapingLeft[KEYBORD_ROWS_COUNT][KEYBORD_COLS_COUNT] =   {  
//   {
//         {{{KEY_ESC,false}, {KEY_TAB,false}, {KEY_TILDE,false}}},
//         {{{KEY_Q,false}, {KEY_1,true}, {KEY_F1,false}}},
//         {{{KEY_W,false}, {KEY_2,true}, {KEY_F2,false}}},
//         {{{KEY_E,false}, {KEY_3,true}, {KEY_F3,false}}},
//         {{{KEY_R,false}, {KEY_4,true}, {KEY_F4,false}}},
//         {{{KEY_T,false}, {KEY_5,true}, {KEY_F5,false}}},
//   },
//   {
//         {{{KEY_LEFT_SHIFT,false}, {KEY_LEFT_SHIFT,false}, {KEY_CAPS_LOCK,false}}},
//         {{{KEY_A,false}, {KEY_A,false}, {KEY_F6,false}}},
//         {{{KEY_S,false}, {KEY_S,false}, {KEY_F7,false}}},
//         {{{KEY_D,false}, {KEY_D,false}, {KEY_F8,false}}},
//         {{{KEY_F,false}, {KEY_F,false}, {KEY_F9,false}}},
//         {{{KEY_G,false}, {KEY_G,false}, {KEY_F10,false}}},
//   },
//   {
//         {{{KEY_LEFT_WINDOWS,false}, {KEY_LEFT_WINDOWS,false}, {KEY_LEFT_ALT,false}}},
//         {{{KEY_Z,false}, {KEY_Z,false}, {KEY_F11,false}}},
//         {{{KEY_X,false}, {KEY_X,false}, {KEY_F12,false}}},
//         {{{KEY_C,false}, {KEY_C,false}, {KEY_C,false}}},
//         {{{KEY_V,false}, {KEY_V,false}, {KEY_V,false}}},
//         {{{KEY_B,false}, {KEY_B,false}, {KEY_B,false}}},
//   }
// };
// strKeyMapping keyMapingRight[KEYBORD_ROWS_COUNT][KEYBORD_COLS_COUNT] =   {  
//   {
//         {{{KEY_Y,false}, {KEY_6,true}, {KEY_6,true}}},
//         {{{KEY_U,false}, {KEY_7,true}, {KEYPAD_7,false}}},
//         {{{KEY_I,false}, {KEY_8,true}, {KEYPAD_8,false}}},
//         {{{KEY_O,false}, {KEY_9,true}, {KEYPAD_9,false}}},
//         {{{KEY_P,false}, {KEY_0,true}, {KEYPAD_SUBTRACT,false}}},
//         {{{KEY_BACKSPACE,false}, {KEY_DELETE,false}, {KEY_BACKSPACE,false}}},
//   },
//   {
//         {{{KEY_H,false}, {KEY_H,false}, {KEY_H,false}}},
//         {{{KEY_J,false}, {KEY_MINUS,false}, {KEYPAD_4,false}}},
//         {{{KEY_K,false}, {KEY_UP_ARROW,false}, {KEYPAD_5,false}}},
//         {{{KEY_L,false}, {KEY_LEFT_BRACE,false}, {KEYPAD_6,false}}},
//         {{{KEY_SEMICOLON,false}, {KEY_RIGHT_BRACE,false}, {KEYPAD_ADD,false}}},
//         {{{KEY_HOME,false}, {KEY_HOME,false}, {KEYPAD_MULTIPLY,false}}},
//   },
//   {
//         {{{KEY_N,false}, {KEY_N,false}, {KEY_5,true}}},
//         {{{KEY_M,false}, {KEY_LEFT_ARROW,false}, {KEYPAD_1,false}}},
//         {{{KEY_COMMA,false}, {KEY_DOWN_ARROW,false}, {KEYPAD_2,false}}},
//         {{{KEY_PERIOD,false}, {KEY_RIGHT_ARROW,false}, {KEYPAD_3,false}}},
//         {{{KEY_QUOTE,false}, {KEY_SLASH,false}, {KEY_EQUAL,false}}},
//         {{{KEY_END,false}, {KEY_END,false}, {KEYPAD_DIVIDE,false}}},
//   },
// };
  
// strKeyMapping sumbMapingLeft[3] =   {  
//   {{{KEY_LEFT_CTRL,false}, {KEY_LEFT_CTRL,false}, {KEY_LEFT_CTRL,false}}},
//   {{{KEY_LANG1,false}, {KEY_LANG1,false}, {KEY_LANG1,false}}},
//   {{{KEY_SPACE,false}, {KEY_SPACE,false}, {KEY_SPACE,false}}},
// };

// strKeyMapping sumbMapingRight[3] =   {  
//   {{{KEY_RETURN,false}, {KEY_RETURN,false}, {KEY_RETURN,false}}},
//   {{{KEY_LANG2,false}, {KEY_LANG2,false}, {KEY_LANG2,false}}},
//   {{{KEY_BACKSPACE,false}, {KEY_BACKSPACE,false}, {KEYPAD_0,false}}},
// };

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

byte datain[50];
byte dataOut[10];

unsigned long responceWaitTimer = 0;



void loop() { 
 
  ReadKeyboardMatrix();  
  for(int buttonIndex=0 ; buttonIndex<3 ; buttonIndex++)
  {
   GetButtonStatus(&sumbButtonsStatus[buttonIndex],sumbPins[buttonIndex]);
  }
  GetRightKeyboardButtonsStatus();
  
  SumbButtonsMapingHandler(sumbButtonsStatus, thumbMapingLeftPress, thumbMapingLeftPress);
  SumbButtonsMapingHandler(sumbButtonsStatus_R, thumbMapingRightPress, thumbMapingRightPress);
  KeyboardMatrixMapingHandler(keyMatrixButtonsStatus, keyMapingLeftPress, keyMapingLeftPress);
  KeyboardMatrixMapingHandler(keyMatrixButtonsStatus_R, keyMapingRightPress, keyMapingRightPress);


  if( currentLayer == 2)
  {
    digitalWrite(LED_2_PIN, HIGH);
  }
  else
  {
    digitalWrite(LED_2_PIN, LOW);
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
          
        Serial.print(buttonPin );
        Serial.print(" ");
        Serial.println("PRESS");
        // Serial.println("PRESSHOLD");
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
  responceWaitTimer = millis();
  dataOut[0] = 0x0C;
  dataOut[1] = '\n';
  Serial1.write(dataOut, 2);
  responceWaitTimer = millis();
  while ( Serial1.available()==0 && ((millis() - responceWaitTimer)<=100) ) {}

  if( ((millis() - responceWaitTimer)>=100) )
  {
    Serial.println("Error data not recevied"); 
  }
  else
  {
    int readLength = Serial1.readBytesUntil('\n',datain,50);
    
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
      Serial.println("Data Error");
    }
  }
 
}


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
    if( KeyMapingPress[i].LayerMap[currentLayer].Keycode == KEY_LANG1)
    {
      LayerHandlerLeft(buttonStatus[i].button_curr_state, buttonStatus[i].is_updated, buttonStatus[i].isMultiBotPressed);
    }
    else if( KeyMapingPress[i].LayerMap[currentLayer].Keycode == KEY_LANG2)
    {
      LayerHandlerRight(buttonStatus[i].button_curr_state, buttonStatus[i].is_updated, buttonStatus[i].isMultiBotPressed);
    }
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
  else if( (KeyMapingPress->LayerMap[currentLayer].Keycode != KEY_LEFT_SHIFT)&&(buttonStatus->button_curr_state == HOLD ) && (buttonStatus->isMultiBotPressed == false) && (millis() - buttonStatus->holdKeyPresstickstart) >= KEY_HOLD_UPDATE_PERIOD_MS)
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
  else if( buttonStatus->button_curr_state == RELEASED && buttonStatus->is_updated == true)
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

void LayerHandlerLeft(int button_curr_state, bool is_updated, bool isMultiBotPressed)
{ 
  if( button_curr_state == PRESSED && is_updated == true && isMultiBotPressed == false)
  {
    // Serial.println("LayerChange");
    if( currentLayer == 2)
      currentLayer = 0;
    else
      currentLayer = 2;
    layerShiftMode = LAYER_SHIFT_STICKY ;
    Serial.println("Layer_L PRESS");
  } 
  else if(((is_updated == true && button_curr_state == HOLD))&& isMultiBotPressed == false)
  {
    layerShiftMode = LAYER_SHIFT_TOGGLE ; 
    currentLayer = 2; 
    Serial.println("Layer_L HOLD");
  }
  else if(button_curr_state == RELEASED && layerShiftMode == LAYER_SHIFT_TOGGLE && isMultiBotPressed == false && is_updated == true)
  { 
    currentLayer = 0; 
    Serial.println("Layer_L RELEASED");
  }
  
}

void LayerHandlerRight(int button_curr_state, bool is_updated, bool isMultiBotPressed)
{ 
  if( button_curr_state == PRESSED && is_updated == true && isMultiBotPressed == false)
  {
    // Serial.println("LayerChange");
    if( currentLayer == 1)
      currentLayer = 0;
    else
      currentLayer = 1;
    layerShiftMode = LAYER_SHIFT_STICKY ;
    Serial.println("Layer_R PRESS");

    dataOut[0] = 0x0D;
    dataOut[1] = (byte) currentLayer;
    dataOut[2] = '\n';
    Serial1.write(dataOut, 3);
  } 
  else if(((is_updated == true && button_curr_state == HOLD))&& isMultiBotPressed == false)
  {
    layerShiftMode = LAYER_SHIFT_TOGGLE ; 
    currentLayer = 1; 
    Serial.println("Layer_R HOLD");
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
    Serial.println("Layer_R RELEASED");
  }
}

void HandleKeyCaps(KeyboardKeycode Keycode)
{
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
