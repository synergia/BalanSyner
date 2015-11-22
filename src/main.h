#ifndef MAIN_H_
#define MAIN_H_

//-----------------------Includes-------------------------------------//

//-----------------------Public typedefs------------------------------//

//-----------------------Public defines-------------------------------//

//-----------------------Public macros--------------------------------//

//-----------------------Public variables-----------------------------//
const float DT = 0.032f; /*! extern float DT; if needed */

//-----------------------Public prototypes----------------------------//
inline void MainTask16ms();
inline void MainTask128ms();

#endif
