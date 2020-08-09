/*
 * utilstools_msgqueue.h
 *
 *  Created on: 9 août 2020
 *      Author: bruno
 */

#ifndef INC_UTILSTOOLS_MSGQUEUE_H_
#define INC_UTILSTOOLS_MSGQUEUE_H_

#include <limits.h>

#include "utilstools.h"

int fushMessageQueue(int a_Fd);

int getMqClientname(  const char* a_ID,           // in
                const char *a_Svcname,      // in
                char        a_MqFilename[NAME_MAX]);   // out


#endif /* INC_UTILSTOOLS_MSGQUEUE_H_ */
