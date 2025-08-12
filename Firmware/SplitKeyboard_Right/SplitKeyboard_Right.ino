#include "HID-Project.h"
#include <Encoder.h>
#include "KeyMapping.h"

#define KEYBORD_ROWS_COUNT 4
#define KEYBORD_COLS_COUNT 6

#define BUTTONS_DEBUNCE_TIME 30
#define MAIN_LOOP_CYCLIC_TIME_MS  1
#define KEY_HOLD_UPDATE_PERIOD_MS 40
#define BUTTON_HOLD_DEBUNCE_TIME 500

#define LAYER_SHIFT_TOGGLE_ENABLED LAYER_SHIFT_TOGGLE
// Arduino Micro => Adafruit itsybitsy m0
// 5 => A4, 6 => A2, 8 => A3
// 16 => 11, 14 => 12. 15 => 13

int rowPins[KEYBORD_ROWS_COUNT] = {SDA,A3,9,10}; // Arduino row pins
int colPins[KEYBORD_COLS_COUNT] = {2,3,4,A4,A2,7}; // Arduino column pins
int sumbPins[4] = {13,12,11,A5};
#define LED_1_PIN A0
#define LED_2_PIN A1

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

strButtonStatus keyMatrixButtonsStatus[KEYBORD_ROWS_COUNT][KEYBORD_COLS_COUNT]; 
strButtonStatus sumbButtonsStatus[4] = {{RELEASED, RELEASED, RELEASED, RELEASED, 0, 0, 0, BUTTON_HOLD_DEBUNCE_TIME, false, false, false},
                                      {RELEASED, RELEASED, RELEASED, RELEASED, 0, 0, 0, BUTTON_HOLD_DEBUNCE_TIME, false, false, false},
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
}

byte dataOut[30];
byte dataIn[10];

unsigned long responceWaitTimer = 0;
bool isAckReceived = false;
bool isGamingModeActive = false;
void loop() {
 
  // Serial.println("Data");
  if(Serial1.available())
  {
    // digitalWrite(2, HIGH);
    Serial1.setTimeout(100);
    // int readLength = Serial1.readBytes(datain,3);
    int readLength = Serial1.readBytesUntil('\n',dataIn,10);
    if( dataIn[0] == 0x0C )
    { 
      ReadKeyboardMatrix();  
      for(int buttonIndex=0 ; buttonIndex<4 ; buttonIndex++)
      {
        GetButtonStatus(&sumbButtonsStatus[buttonIndex], sumbPins[buttonIndex]);
      } 
      int index = 0;
      for (int row = 0; row < KEYBORD_ROWS_COUNT; row++) 
      {
        for (int col = 0; col < KEYBORD_COLS_COUNT; col++) 
        {
          dataOut[index] = keyMatrixButtonsStatus[row][col].button_curr_state;
          dataOut[index] |= keyMatrixButtonsStatus[row][col].is_updated << 4 ;
          index++;
          // Serial.print(dataOut[index]);
          // Serial.print(" , ");
        }
      }
      for(int buttonIndex=0 ; buttonIndex<4 ; buttonIndex++)
      {
        dataOut[index] = sumbButtonsStatus[buttonIndex].button_curr_state;
        dataOut[index] |= sumbButtonsStatus[buttonIndex].is_updated << 4 ;
        index++;
        // Serial.print(dataOut[index]);
        // Serial.print(" , ");
      } 
      dataOut[28] =  0x0C;
      dataOut[29] = '\n';
      Serial1.write(dataOut, 30);
    }
    else if( dataIn[0] == 0x0D )
    { 
      if(dataIn[1] == 2)
      {
        digitalWrite(LED_1_PIN, HIGH) ;
      }
      else 
      {
        digitalWrite(LED_1_PIN, LOW) ;
      }
    }
    else if( dataIn[0] == 0x0B )
    { 
      digitalWrite(LED_2_PIN, dataIn[1]) ;
    }
    /*
    else if( dataIn[0] == 0x0F )
    { 
      isGamingModeActive = (bool) dataIn[1];
      isAckReceived= true;
      for(int i=0 ; i<KEYBORD_ROWS_COUNT ; i++)
      { 
        int index = 1;
        dataOut[0] = 0x0F;
        for(int k=0 ; k<3 ; k++)
        { 
          if( isGamingModeActive == false)
          {
            dataOut[index] = (byte) thumbMapingLeftPress_Normal[i].LayerMap[k].Keycode; 
            dataOut[index+1] = (byte) thumbMapingLeftPress_Normal[i].LayerMap[k].isShifted;
            dataOut[index+2] = (byte) thumbMapingLeftPress_Normal[i].LayerMap[k].isAMacro;
            dataOut[index+3] = (byte) thumbMapingLeftPress_Normal[i].LayerMap[k].MacroKey1;
            dataOut[index+4] = (byte) thumbMapingLeftPress_Normal[i].LayerMap[k].MacroKey2;
            dataOut[index+5] = (byte) thumbMapingLeftPress_Normal[i].LayerMap[k].MacroKey3; 
          }
          else
          {
            dataOut[index] = (byte) thumbMapingLeftPress_Gaming[i].LayerMap[k].Keycode; 
            dataOut[index+1] = (byte) thumbMapingLeftPress_Gaming[i].LayerMap[k].isShifted;
            dataOut[index+2] = (byte) thumbMapingLeftPress_Gaming[i].LayerMap[k].isAMacro;
            dataOut[index+3] = (byte) thumbMapingLeftPress_Gaming[i].LayerMap[k].MacroKey1;
            dataOut[index+4] = (byte) thumbMapingLeftPress_Gaming[i].LayerMap[k].MacroKey2;
            dataOut[index+5] = (byte) thumbMapingLeftPress_Gaming[i].LayerMap[k].MacroKey3; 
          }
          index = index + 6;
        }
        // index = 18
        dataOut[19] = 0xFF;
        // Serial1.flush();
        Serial1.write(dataOut, 20);

        for(int n=0 ; n<19 ; n++)
        {
          Serial.print(dataOut[n]);
          Serial.print("   ");
        }
        Serial.println("");
        // delay(50);
        if( i <=1 )
        {
        responceWaitTimer = millis();
        while ( Serial1.available()==0 && ((millis() - responceWaitTimer)<=500) ) {}

        if( ((millis() - responceWaitTimer)>=500) )
        {
          Serial.println("Error 0x0F Ack not recevied"); 
        }
        else
        {
          int readLength = Serial1.readBytesUntil('\n',dataIn,3);
          Serial1.flush();
          if( dataIn[0] == 0x0F)
          {
            isAckReceived = true;
          }
          else
          {
            isAckReceived = false;
            Serial.print(i); 
            Serial.println(" Error 0x0F Ack not recevied 2"); 
            break;
          }
        }
        }
      }
    }
    else if( dataIn[0] == 0x0E )
    { 
      isGamingModeActive = (bool) dataIn[1];
      isAckReceived= true;
      for(int i=0 ; i<KEYBORD_ROWS_COUNT ; i++)
      { 
        for(int j=0 ; j<KEYBORD_COLS_COUNT ; j++)
        {
          int index = 1;
          dataOut[0] = 0x0E;
          for(int k=0 ; k<3 ; k++)
          { 
            if( isGamingModeActive == false)
            {
              dataOut[index] = (byte) keyMapingLeftPress_Normal[i][j].LayerMap[k].Keycode; 
              dataOut[index+1] = (byte) keyMapingLeftPress_Normal[i][j].LayerMap[k].isShifted;
              dataOut[index+2] = (byte) keyMapingLeftPress_Normal[i][j].LayerMap[k].isAMacro;
              dataOut[index+3] = (byte) keyMapingLeftPress_Normal[i][j].LayerMap[k].MacroKey1;
              dataOut[index+4] = (byte) keyMapingLeftPress_Normal[i][j].LayerMap[k].MacroKey2;
              dataOut[index+5] = (byte) keyMapingLeftPress_Normal[i][j].LayerMap[k].MacroKey3; 
            }
            else
            {
              dataOut[index] = (byte) keyMapingLeftPress_Gaming[i][j].LayerMap[k].Keycode; 
              dataOut[index+1] = (byte) keyMapingLeftPress_Gaming[i][j].LayerMap[k].isShifted;
              dataOut[index+2] = (byte) keyMapingLeftPress_Gaming[i][j].LayerMap[k].isAMacro;
              dataOut[index+3] = (byte) keyMapingLeftPress_Gaming[i][j].LayerMap[k].MacroKey1;
              dataOut[index+4] = (byte) keyMapingLeftPress_Gaming[i][j].LayerMap[k].MacroKey2;
              dataOut[index+5] = (byte) keyMapingLeftPress_Gaming[i][j].LayerMap[k].MacroKey3; 
            }
            index = index + 6;
          }
          // index = 18
          dataOut[19] = 0xFF;
          // Serial1.flush();
          Serial1.write(dataOut, 20);

           for(int n=0 ; n<19 ; n++)
          {
            Serial.print(dataOut[n]);
            Serial.print("   ");
          }
          Serial.println(""); 

          if( !(i==KEYBORD_ROWS_COUNT-1 && j==KEYBORD_COLS_COUNT-1))
          {
          responceWaitTimer = millis();
          while ( Serial1.available()==0 && ((millis() - responceWaitTimer)<=500) ) {}

          if( ((millis() - responceWaitTimer)>=500) )
          {
            Serial.println("Error 0x0E Ack not recevied"); 
          }
          else
          {
            int readLength = Serial1.readBytesUntil('\n',dataIn,3);
            Serial1.flush();
            if( dataIn[0] == 0x0E)
            {
              isAckReceived = true;
            }
            else
            {
              isAckReceived = false;
              Serial.print(i);
              Serial.print(",");
              Serial.print(j);
              Serial.println(" Error 0x0E Ack not recevied 2"); 
              break;
            }
          }
          }
        }
        if( isAckReceived == false)
        {
          break;
        }
      } 
      // if(isAckReceived == true)
      // {
      //   dataOut[0] = 0x0E;
      //   dataOut[1] = 2;
      //   dataOut[2] = '\n';
      //   Serial1.write(dataOut, 3);
      // }
    }
    */
    // digitalWrite(2, LOW); 
  }

  
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
