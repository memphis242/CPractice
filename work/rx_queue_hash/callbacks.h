//
// Created by abdullah on 05/05/22.
//

#ifndef RX_QUEUE_HASH_CALLBACKS_H

/*******************************************************************
 *
 * FILE: External_Master_Callbacks.h
 *
 * Description: Includes declarations of all callback functions to be used
 *              with the reception of 11-bit CAN messages for the External
 *              Master.
 *
 * COPYRIGHT:
 *  Copyright (c) Deere Company, as an unpublished work.
 *  THIS SOFTWARE AND/OR MATERIAL IS THE PROPERTY OF DEERE COMPANY.
 *  ALL USE, DISCLOSURE, AND/OR REPRODUCTION NOT SPECIFICALLY
 *  AUTHORIZED BY DEERE COMPANY IS PROHIBITED.
 *
 *******************************************************************/


/** Include Files **/
#include "std_can_ds.h"

//extern struct Std_CAN_Queue_Item_S;

/** Definitions **/

/** Enumerations **/

/** Type Definitions **/

/** Structure Declarations **/

/** Data Declarations **/

/** Function Declarations **/
void CellVoltage_Callback(struct Std_CAN_Queue_Item_S * item);

void DynamicMaxCurrentLimit_Callback(struct Std_CAN_Queue_Item_S * item);

void PackVoltageCurrent_Callback(struct Std_CAN_Queue_Item_S * item);

void StressEstimator_Callback(struct Std_CAN_Queue_Item_S * item);

void CellTemp_Callback(struct Std_CAN_Queue_Item_S * item);

void SOC_Callback(struct Std_CAN_Queue_Item_S * item);

void BMSContactorState_Callback(struct Std_CAN_Queue_Item_S * item);

void IsolationStatus_Callback(struct Std_CAN_Queue_Item_S * item);


/** End of File Copyright *********************************************************
 *                                                                                *
 *  Copyright (c) Deere Company, as an unpublished work.                          *
 *  THIS SOFTWARE AND/OR MATERIAL IS THE PROPERTY OF DEERE COMPANY.               *
 *  ALL USE, DISCLOSURE, AND/OR REPRODUCTION NOT SPECIFICALLY                     *
 *  AUTHORIZED BY DEERE COMPANY IS PROHIBITED.                                    *
 *                                                                                *
 **********************************************************************************/


#define RX_QUEUE_HASH_CALLBACKS_H

#endif //RX_QUEUE_HASH_CALLBACKS_H
