/*
 * PID.h
 *
 *  Created on: Nov 20, 2015
 *      Author: Kuba
 */

#ifndef PID_H_
#define PID_H_

//-----------------------Includes-------------------------------------//

//-----------------------Public defines-------------------------------//
typedef struct
{
   float Kp;      /*! Proportional gain */
   float Ki;      /*! Proportional gain */
   float Kd;      /*! Proportional gain */

   float e;             /*! Current error */
   float e_sum;         /*! Summarized error */
   float e_last;        /*! Last error */
   float OutSignal;     /*! Output signal */
   float DstValue;      /*! Value to be reached by regulator */
}PID_Parameters_T;

typedef struct
{
   PID_Parameters_T Parameters;   /*! Structure with gains */

   void ( *ApplyPid )( PID_Parameters_T *PID, float ReadValue );

   void ( *SetDstValue )( PID_Parameters_T *PID, float NewValue );
   float ( *GetDstValue )( PID_Parameters_T *PID );

   void ( *SetKp )( PID_Parameters_T *pkThis, float NewValue );
   void ( *SetKi )( PID_Parameters_T *pkThis, float NewValue );
   void ( *SetKd )( PID_Parameters_T *pkThis, float NewValue );
   float ( *GetKp )( PID_Parameters_T *pkThis );
   float ( *GetKi )( PID_Parameters_T *pkThis );
   float ( *GetKd )( PID_Parameters_T *pkThis );
}PID_Struct_C;

//-----------------------Public macros--------------------------------//

//-----------------------Public typedefs------------------------------//

//-----------------------Public variables-----------------------------//

//-----------------------Public prototypes----------------------------//
void PID_Initialize( PID_Struct_C *PID );

#endif /* PID_H_ */
