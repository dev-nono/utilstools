/*
 ============================================================================
 Name        : utilstools.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utiltools_inc.h"



int main(int argc, char* argv[])
{
	int vResult = 0;

	if( argc  >1 )
	{
		if( (strcmp(argv[1],"time")))
		{
			vResult = test_time(argc, argv);
		}
		else if( (strcmp(argv[1],"pthread")))
		{
			vResult = test_pthread(argc, argv);
		}
		else if( (strcmp(argv[1],"net")))
		{
			vResult = test_network(argc, argv);
		}
		else if( (strcmp(argv[1],"msqq")))
		{
			vResult = test_msqueue(argc, argv);
		}
		else
		{
			printf("\n syntaxe : %s [CMD]  [PARAMS]\n", argv[0]);
			printf("\t cmd : time pthread net msgq \n");
		}

	}
	return vResult;
}
