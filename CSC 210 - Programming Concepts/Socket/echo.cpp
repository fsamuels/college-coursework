#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

int main() {

	int mySocket;
	struct sockaddr_in myAddress;
	
	mySocket = socket(AF_INET, SOCK_STREAM, 0);
	
	if (mySocket < 0) {		
		printf("error");
		exit(-1);
	}
	
	myAddress.sin_family      = AF_INET;
	myAddress.sin_port        = htons(7);
	myAddress.sin_addr.s_addr = htonl(INADDR_ANY);

	bind( mySocket, (struct sockaddr *) &myAddress, sizeof(myAddress) );

	listen( mySocket, 5);

return 1;	
}
	

	
