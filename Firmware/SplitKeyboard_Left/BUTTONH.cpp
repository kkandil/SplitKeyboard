#include "BUTTONH.h"  
 
//========================================================================================================
//========================================================================================================
// Macros 

//========================================================================================================
//========================================================================================================
// Global Variables 
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
//========================================================================================================
//========================================================================================================
// Locak Variables 
unsigned long responceWaitTimer = 0;

int rowPins[KEYBORD_ROWS_COUNT] = {2,SCK,MOSI,MISO}; // Arduino row pins
int colPins[KEYBORD_COLS_COUNT] = {A0,A1,A2,A3,A4,A5}; // Arduino column pins
byte sumbPins[4] = {SCL,3,4,SDA};
 
void ReadLeftKeyboardMatrix(void);
void GetButtonStatus(strButtonStatus *buttonStatus, int buttonPin);
void GetRightKeyboardButtonsStatus(void);
void BUTTONH_PrintSerialDebugMsg(String msg);
//========================================================================================================
//========================================================================================================
// Global Functions

void BUTTONH_Init(void)
{
  Serial1.begin(115200);

  

  // pinMode(ENCODER_PIN_A, INPUT_PULLUP);
  // pinMode(ENCODER_PIN_B, INPUT_PULLUP);
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

  
}


void BUTTONH_UpdateButtonStatus(void)
{
  for(int buttonIndex=0 ; buttonIndex<4 ; buttonIndex++)
  {
   GetButtonStatus(&sumbButtonsStatus[buttonIndex],sumbPins[buttonIndex]);
  }
  ReadLeftKeyboardMatrix();
  GetRightKeyboardButtonsStatus();
}

//========================================================================================================
//========================================================================================================
// Local Functions

void ReadLeftKeyboardMatrix(void)
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
    BUTTONH_PrintSerialDebugMsg("Button# " + String(buttonPin) + " - Updated");
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
        BUTTONH_PrintSerialDebugMsg("Button# " + String(buttonPin) + " - PRESS");
      }
      else if( buttonStatus->button_curr_read == RELEASED ) 
      {
        buttonStatus->button_curr_state = RELEASED;
        buttonStatus->is_updated = true;
        buttonStatus->isMultiBotPressed = false; 
        BUTTONH_PrintSerialDebugMsg("Button# " + String(buttonPin) + " - RELEASED");
      }
      buttonStatus->isDebunceInProgress = false;
  }

  if ( buttonStatus->button_curr_state == PRESSED &&  (millis() - buttonStatus->button_holdtickstart) > buttonStatus->buttonHoldDebounceTime)
  {
    buttonStatus->button_prev_state = buttonStatus->button_curr_state;
    buttonStatus->button_curr_state = HOLD;
    buttonStatus->is_updated = true;
    buttonStatus->holdKeyPresstickstart = millis() + KEY_HOLD_UPDATE_PERIOD_MS; 
    BUTTONH_PrintSerialDebugMsg("Button# " + String(buttonPin) + " - HOLD");
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
     BUTTONH_PrintSerialDebugMsg("Error data not recevied"); 
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
      BUTTONH_PrintSerialDebugMsg("Data Error");
    }
  }
 
}

void BUTTONH_PrintSerialDebugMsg(String msg)
{
  if(SERIAL_DEBUGGING_ENABLE == true )
  {
    Serial.println(msg); 
  }
}