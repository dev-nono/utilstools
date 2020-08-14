 /*
 * utils.c
 *
 *  Created on: 10 juil. 2020
 *      Author: bruno
 */

#include <fcntl.h> /* Définition des constantes AT_* */
#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <libgen.h>
#include <stdint.h>

#include <fcntl.h>           /* Pour les constantes O_* */
#include <sys/stat.h>        /* Pour les constantes des modes */
#include <mqueue.h>
#include <errno.h>
#include "time.h"

#include <utilstools.h>

//          1         2         3
// 1234567890123456789012345678901234567890
//




//****************************************************
//*
//*
//****************************************************
int getFifoname(char* a_Fifoname)
{
    int             result = 0;
    char vProcessname[NAME_MAX];

    result = getProcessname(vProcessname);

    int long vTID  = syscall(SYS_gettid);

    snprintf(a_Fifoname,PATH_MAX-1,"/tmp/%s.%ld",vProcessname,vTID);

    return result;
}

//****************************************************
//* /tmp/process1.srv1.123456789
//*
//****************************************************
int getUniqname(    const char *a_Path,           // in
                    const char *a_Svcname,          // in
                    char        a_ClientFilename[NAME_MAX])   // out
{
    int         result                  = 0;
    char        vProcessname[NAME_MAX]  = {0};
    struct timespec Time_ts = {0,0};

    result = getProcessname(vProcessname);

    if( 0 == result)
    {
        result = clock_gettime(CLOCK_MONOTONIC_RAW, &Time_ts);
    }
    if( 0 == result)
    {
        snprintf(a_ClientFilename,NAME_MAX-1,
                "%.100s/%.50s.%.50s.%ld",a_Path,vProcessname,a_Svcname,Time_ts.tv_nsec);
    }

    return result;
}
//****************************************************
//*
//*
//****************************************************
int getProcessname(char* a_Processname)
{
    int             result = 0;
    char vLinkname[PATH_MAX];
    char *pBasename = 0;


    result = readlink("/proc/self/exe", vLinkname, PATH_MAX-1);

    pBasename = basename(vLinkname);

    strncpy(a_Processname,pBasename,NAME_MAX-1);

    return (result > 0) ? 0 : -1;
}





