/*
 * sockt.h
 *
 *  Created on: Jan 2, 2015
 *      Author: pim
 */

#ifndef SRC_SOCKT_H_
#define SRC_SOCKT_H_
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <string.h>	// for memcpy()...
#include <stdlib.h>	// for atoi()...
#include <unistd.h>	// for gethostname()...
#include <ctype.h>	// for tolower()...
#include <iostream>
bool socketConnect();


void envia(char *s, int len);

int recebe(char *ans);
void quit();




#endif /* SRC_SOCKT_H_ */
