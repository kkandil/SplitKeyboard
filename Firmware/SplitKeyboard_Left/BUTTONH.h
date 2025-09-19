#include "SplitKeyboard_Cfg.h"
#include <Arduino.h>
//========================================================================================================
//========================================================================================================
// Macros
 
  
//========================================================================================================
//========================================================================================================
// Global Variables
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

extern strButtonStatus keyMatrixButtonsStatus[KEYBORD_ROWS_COUNT][KEYBORD_COLS_COUNT];
extern strButtonStatus sumbButtonsStatus[4];
extern strButtonStatus keyMatrixButtonsStatus_R[KEYBORD_ROWS_COUNT][KEYBORD_COLS_COUNT]; 
extern strButtonStatus sumbButtonsStatus_R[4];
//========================================================================================================
//========================================================================================================
// Locak Variables

//========================================================================================================
//========================================================================================================
// Global Functions
void BUTTONH_Init(void);
void BUTTONH_UpdateButtonStatus(void); 
//========================================================================================================
//========================================================================================================
// Local Functions