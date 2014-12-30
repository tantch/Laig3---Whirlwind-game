#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>	// for memcpy()...
#include <stdlib.h>	// for atoi()...
#include <unistd.h>	// for gethostname()...
#include <ctype.h>	// for tolower()...
#include <iostream>

#define IPADDRESS "127.0.0.1"
#define PORT 60070
#define BUFS	1024


using namespace std;
int sock;
struct sockaddr_in server;
struct hostent *hp;
char buf[BUFS];

bool socketConnect() {
	/* Create socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		{
		perror("Opening stream socket");
		exit(1);
		}

	/* Connect socket using server name indicated in the command line */
	server.sin_family = AF_INET;
	hp = gethostbyname(IPADDRESS);
	if (hp == NULL)
		{
		perror("Trying to get host by name");
		exit(2);
		}
	memcpy((char *)&server.sin_addr, (char *)hp->h_addr, hp->h_length);
	server.sin_port = htons(PORT);

	if (connect(sock, (struct sockaddr *)&server, sizeof server) < 0)
		{
		perror("Connecting stream socket");
		exit(1);
		}

    // Send and receive data.
	printf("Connected\n");
	return true;
}

void envia(char *s, int len) {
	if (write (sock, s, len) < 0)
			perror("Writing on stream socket");
}

void recebe(char *ans) {
	read(sock,ans, sizeof (ans));
	cout << "prolog answered: " << ans << endl;
}

void quit() {

	cout << "Asking prolog to quit" << endl;
	char buff[] = "quit.\n";
	envia(buff, 6);
	char ans[128];
	recebe(ans);
}
/*
int main() {
	socketConnect();
	char *s = "comando(1, 2).\n";
	envia(s, strlen(s));
	char ans[128];
	recebe(ans);
	quit();
	getchar();
	close(sock);
	return 0;
}*/
