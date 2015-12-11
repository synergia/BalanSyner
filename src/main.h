#ifndef MAIN_H_
#define MAIN_H_

//-----------------------Includes-------------------------------------//

//-----------------------Public typedefs------------------------------//

//-----------------------Public defines-------------------------------//

//-----------------------Public macros--------------------------------//

//-----------------------Public variables-----------------------------//
const float DT_fast = 0.008f; /*! extern float DT_fast; if needed. Angle regulator */
const float DT_slow = 0.032f; /*! extern float DT_slow; if needed. Omega regulator */

//-----------------------Public prototypes----------------------------//
void MainTask8ms();
void MainTask32ms();
void MainTask128ms();

#endif
