#include <iostream.h>
#include <sys/types.h>
#include <unistd.h>          
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>?/* specify how a program handles signals while it executes.*/ 
#include <sys/socket.h>/* use to gain access to the data arrays in the ancillary data associated with a message header*/
#include <sys/un.h>
#include <netinet/in.h>/* defines the IN6ADDR_ANY_INIT macro and initialize initialize a variable of type struct in6_addr to the IPv6 wildcard address.*/
using namespace std;
#define SIM_LENGTH 10
#define IP_ADDRESS "10.161.175.121" 
#define PORT 5353 

int  main(void)

{
  int sock; 
  struct sockaddr_in cli_name;
  int value;

  cout<<"Client is alive and establishing socket connection.\n";
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    { perror ("Error opening channel");
      close(sock);
      exit(1);
    }
    bzero(&cli_name, sizeof(cli_name)); 
  cli_name.sin_family = AF_INET;
  cli_name.sin_addr.s_addr = inet_addr(IP_ADDRESS); 
  cli_name.sin_port = htons(PORT); 
  if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0)
    { 
	perror ("Error establishing communications");
      close(sock);
      exit(1);
    }
    int count=1;
    do{
    	if(count<=SIM_LENGTH)
    	break;
    	count++;
    	read(sock,&value,4);
    	cout<<"client has recieved %d from socket.\n"<<value;
	}
	while(true);
  cout<<"Exiting now.\n";

  close(sock); 
  exit(0); 
}

