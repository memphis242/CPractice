#include <stdio.h>
#include <stdint.h>


#define MAX_NUM_OF_SIGNALS_PER_MESSAGE    10


/******* FOR CHECKING TIMEOUTS OF SIGNALS *******/
enum identifierlist
{
   RM_CAN_KeySwitchState,
   RM_CAN_OpSeatDirctnCF,
   RM_CAN_MachDelaydShutdwnTimer,
   RM_CAN_PilotHydEnblDrvrState,
   NUM_OF_APP_VARS
};

enum statlist
   {
   DATA_GOODDATA = -1,
   DATA_ValidAboveNormal,
   DATA_ValidBelowNormal,
   DATA_ErraticOrInvalid,
   DATA_VoltageAboveNormal,
   DATA_VoltageBelowNormal,
   DATA_CurrentBelowNormal,
   DATA_CurrentAboveNormal,
   DATA_MechanicalOutOfAdjustment,
   DATA_ErraticFrequency,
   DATA_AbnormalUpdateRate,
   DATA_AbnormalRateOfChange,
   DATA_FailureNotIdentified, // illegal var id
   DATA_BadDeviceOrComponent,
   DATA_OutOfCalibration,
   DATA_SpecialInstructions,
   DATA_ValidAboveNormalLeastSevere,
   DATA_ValidAboveNormalModeratelySevere,
   DATA_ValidBelowNormalLeastSevere,
   DATA_ValidBelowNormalModeratelySevere,
   DATA_ReceivedNetworkDataInError,
   // Reserved for SAE assignment 15 - 30
   DATA_NOTAVAILABLE = 31     // data never written after init
   };

typedef struct SYSTEMVARIABLE_S
{
   int value;
   int status;
} SYSTEMVARIABLE_T;

static struct SYSTEMVARIABLE_S _vars[NUM_OF_APP_VARS];


void JD_WriteVar( enum identifierlist var_id, SYSTEMVARIABLE_T * app_var )
{
   _vars[ var_id ].value = app_var->value;
   _vars[ var_id ].status = app_var->status;
}

void JD_ReadVar( enum identifierlist var_id, SYSTEMVARIABLE_T * app_var )
{
   app_var->value = _vars[ var_id ].value;
   app_var->status = _vars [ var_id ].status;
}

void JD_WriteVarStatus( enum identifierlist var_id, int status )
{
   _vars[ var_id ].status = status;
}



static enum ManuallyReceivedSignal_E
{
   ManuallyReceivedSignal_KeySwitchState,
   ManuallyReceivedSignal_OpSeatDirctnCF,
   ManuallyReceivedSignal_MachDelaydShutdwnTimer,
   ManuallyReceivedSignal_PilotHydEnblDrvrState,
   NUMBER_OF_MANUALLY_RECEIVED_SIGNALS
};

// Enum for indexing into message tables
static enum ManuallyReceivedMessage_E
{
   ManuallyReceivedMessage_VCUProp1,
   ManuallyReceivedMessage_eBackhoeVehicleState_EVCCChargeToVehicle,
   NUMBER_OF_MANUALLY_RECEIVED_MESSAGES
};

// For keeping track of how long it's been since a signal was last received WITH valid data
static int ManuallyReceivedMessageTimers[NUMBER_OF_MANUALLY_RECEIVED_MESSAGES];

// How long before we call a message timeout for each message
static const int MANUALLY_RECEIVED_MESSAGE_TIMEOUTS[NUMBER_OF_MANUALLY_RECEIVED_MESSAGES] =
{
   200,
   200
};

// Signal to message mapping
static const enum ManuallyReceivedMessage_E MANUALLY_RECEIVED_SIGNAL_TO_MESSAGE_MAP[NUMBER_OF_MANUALLY_RECEIVED_SIGNALS] =
{
      ManuallyReceivedMessage_VCUProp1,
      ManuallyReceivedMessage_VCUProp1,
      ManuallyReceivedMessage_VCUProp1,
      ManuallyReceivedMessage_VCUProp1
};

// Message to signal mapping
static struct SignalNode_S
{
   const struct SignalNode_S * next;
   const enum ManuallyReceivedSignal_E signal;
};

// Linked list to allow for iterating through signals associated with a message
static const struct SignalNode_S MANUALLY_RECEIVED_SIGNAL_LINKED_LIST[NUMBER_OF_MANUALLY_RECEIVED_SIGNALS] = 
{
   {  &MANUALLY_RECEIVED_SIGNAL_LINKED_LIST[1]     ,     ManuallyReceivedSignal_KeySwitchState           },
   {  &MANUALLY_RECEIVED_SIGNAL_LINKED_LIST[2]     ,     ManuallyReceivedSignal_OpSeatDirctnCF           },
   {  &MANUALLY_RECEIVED_SIGNAL_LINKED_LIST[3]     ,     ManuallyReceivedSignal_MachDelaydShutdwnTimer   },
   {  NULL                                         ,     ManuallyReceivedSignal_PilotHydEnblDrvrState    },
};

// Maps message to associated linked list head
static const struct SignalNode_S * MANUALLY_RECEIVED_MESSAGE_TO_SIGNAL_MAP[NUMBER_OF_MANUALLY_RECEIVED_MESSAGES] =
{
   &MANUALLY_RECEIVED_SIGNAL_LINKED_LIST[0],
   NULL
};

// Signal to app-var mapping
static const enum identifierlist MANUALLY_RECEIVED_SIGNAL_TO_APP_VAR_MAP[NUMBER_OF_MANUALLY_RECEIVED_SIGNALS] =
{
   RM_CAN_KeySwitchState,
   RM_CAN_OpSeatDirctnCF,
   RM_CAN_MachDelaydShutdwnTimer,
   RM_CAN_PilotHydEnblDrvrState
};

void PDU_Manual_Receive_Task(void);


int main ( void )
{
   // Call task several times until timeout
   PDU_Manual_Receive_Task();
   PDU_Manual_Receive_Task();
   // Next call will cause timeouts
   PDU_Manual_Receive_Task();
}




/*!*******************************************************************************
* \fn PDU_Manual_Receive_Task
*
* \brief Checks the message timers and updates status of manually received CAN vars to
*        DATA_NOTAVAILABLE if a timer has surpassed its limit.
*
* \note I believe the CAN Configurable Interface (CCI) is the recommended way to do
*       this but I'm writing my own solution for now for the sake of time (and not have to
*       integrated CCI for the EMUII).
*
* \note Reentrancy: Yes. Static variables accessed inside a critical sections. Reentrant
*                   functions called.
* 
* \note Critical section contains loops.
*
* \return None.
*******************************************************************************/
void PDU_Manual_Receive_Task(void)
{
   int task_rate;

   // Increment timers for each message and check for timeouts
   task_rate = 80;
   for ( int i = 0; i < (sizeof(ManuallyReceivedMessageTimers) / sizeof(int) ); i++ )
   {
      ManuallyReceivedMessageTimers[i] += task_rate;
      // If timer has risen to past the respective timeout of a message, mark signal as unavailable.
      // For the signal's value, keep the last valid value. Discuss?
      if ( ManuallyReceivedMessageTimers[i] > MANUALLY_RECEIVED_MESSAGE_TIMEOUTS[i] )
      {
         // Reset associated signal timers
         int iteration_stop_count = 0;   // Way to ensure while loop ends
         const struct SignalNode_S * current_node = MANUALLY_RECEIVED_MESSAGE_TO_SIGNAL_MAP[i];
         // In case this is a message for which no signals are associated, skip it.
         if ( current_node == NULL )
         {
            continue;
         }
         // Iterate over signals associated with this message
         do
         {
            JD_WriteVarStatus( MANUALLY_RECEIVED_SIGNAL_TO_APP_VAR_MAP[current_node->signal], DATA_NOTAVAILABLE );
            current_node = current_node->next;
            iteration_stop_count++;
         } while ( current_node != NULL && iteration_stop_count < MAX_NUM_OF_SIGNALS_PER_MESSAGE );
      }
   }

}