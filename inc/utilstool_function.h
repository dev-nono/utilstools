/*
 * utilstool_function.h
 *
 *  Created on: 18 janv. 2021
 *      Author: bruno
 */

#ifndef INC_UTILSTOOL_FUNCTION_H_
#define INC_UTILSTOOL_FUNCTION_H_

#include <limits.h>

//*******************************************************************
//*
//*
//*
//*******************************************************************

int getFifoname(char* a_Fifoname);
int getProcessname(char* a_Processname);
int getClientname(  const char* a_UniqID,           // in
                const char *a_Svcname,          // in
                char       a_ClientFilename[NAME_MAX]);   // out

int getUniqname(    const char* a_Path,           // in
                    const char *a_Svcname,          // in
                    char       a_ClientFilename[NAME_MAX]);   // out


#endif /* INC_UTILSTOOL_FUNCTION_H_ */
