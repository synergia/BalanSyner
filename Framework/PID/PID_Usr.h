/*
 * PID_Usr.h
 *
 *  Created on: Nov 20, 2015
 *      Author: Kuba
 */

#ifndef PID_Usr_H_
#define PID_Usr_H_

//-----------------------Includes-------------------------------------//

//-----------------------Public defines-------------------------------//
#define AngleOffset        0.1f /*! Because the fact that center of the mass of the robot is not
                                     straight above wheels axis, default angle should not be 0 */

#define MinPwmToReact      50.0f /*! Below this value wheels don't turn */

//-----------------------Public macros--------------------------------//

//-----------------------Public typedefs------------------------------//

//-----------------------Public variables-----------------------------//

//-----------------------Public prototypes----------------------------//
float PID_AngleAdjust( float Angle );

#endif /* PID_Usr_H_ */
