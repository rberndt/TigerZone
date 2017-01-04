//first start the server
//then the client
//./server.o 20001
//./client.o 127.0.0.1 20001 tournamentPassword teamUserName teamPassword

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <vector>
#include "Shuffle.cpp"

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;

     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }

     // create a socket
     // socket(int domain, int type, int protocol)
     sockfd =  socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");

     // clear address structure
     bzero((char *) &serv_addr, sizeof(serv_addr));

     portno = atoi(argv[1]);

     /* setup the host_addr structure for use in bind call */
     // server byte order
     serv_addr.sin_family = AF_INET;  

     // automatically be filled with current host's IP address
     serv_addr.sin_addr.s_addr = INADDR_ANY;  

     // convert short integer value for port must be converted into network byte order
     serv_addr.sin_port = htons(portno);

     // bind(int fd, struct sockaddr *local_addr, socklen_t addr_length)
     // bind() passes file descriptor, the address structure, 
     // and the length of the address structure
     // This bind() call will bind  the socket to the current IP address on port, portno
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");

     // This listen() call tells the socket to listen to the incoming connections.
     // The listen() function places all incoming connection into a backlog queue
     // until accept() call accepts the connection.
     // Here, we set the maximum size for the backlog queue to 5.
     listen(sockfd,5);

     // The accept() call actually accepts an incoming connection
     clilen = sizeof(cli_addr);

     // This accept() function will write the connecting client's address info 
     // into the the address structure and the size of that structure is clilen.
     // The accept() returns a new socket file descriptor for the accepted connection.
     // So, the original socket file descriptor can continue to be used 
     // for accepting new connections while the new socker file descriptor is used for
     // communicating with the connected client.
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");

     printf("server: got connection\n" /* from %s port %d\n",
            inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port) */ );


     std::string message;
     std::string cliMessage;
     char mesg[1024];
     //while(1)
     //{
       message = "THIS IS SPARTA!\r\n";
       strncpy(mesg, message.c_str(), sizeof(mesg));
       mesg[sizeof(mesg) - 1] = 0;
       send(newsockfd, mesg, strlen(mesg), 0);

       n = read(newsockfd,buffer,255);
       if (n < 0) error("ERROR reading from socket");
       printf("Here is the message: %s\n",buffer);
       cliMessage = std::string(buffer);
       if(cliMessage.compare("JOIN tp\r\n") != 0)
       {
         printf("Join message not correct\n");
       }

       message = "HELLO!\r\n";
       strncpy(mesg, message.c_str(), sizeof(mesg));
       mesg[sizeof(mesg) - 1] = 0;
       send(newsockfd, mesg, strlen(mesg), 0);

       bzero(buffer,256);
       n = read(newsockfd,buffer,255);
       if (n < 0) error("ERROR reading from socket");
       printf("Here is the message: %s\n",buffer);
 
       message = "WELCOME blue PLEASE WAIT FOR THE NEXT CHALLENGE\r\n";
       strncpy(mesg, message.c_str(), sizeof(mesg));
       mesg[sizeof(mesg) - 1] = 0;
       send(newsockfd, mesg, strlen(mesg), 0);
//       sleep(1);

       message = "NEW CHALLENGE 1 YOU WILL PLAY 1 MATCH(ES)\r\n";
       strncpy(mesg, message.c_str(), sizeof(mesg));
       mesg[sizeof(mesg) - 1] = 0;
       send(newsockfd, mesg, strlen(mesg), 0);
//       sleep(1);

       message = "BEGIN ROUND 1 of 1\r\n";
       strncpy(mesg, message.c_str(), sizeof(mesg));
       mesg[sizeof(mesg) - 1] = 0;
       send(newsockfd, mesg, strlen(mesg), 0);
//       sleep(1);

       message = "YOUR OPPONENT IS PLAYER red\r\n";
       strncpy(mesg, message.c_str(), sizeof(mesg));
       mesg[sizeof(mesg) - 1] = 0;
       send(newsockfd, mesg, strlen(mesg), 0);
//       sleep(1);

       message = "STARTING TILE IS TLTJ- AT 0 0 0\r\n";
       strncpy(mesg, message.c_str(), sizeof(mesg));
       mesg[sizeof(mesg) - 1] = 0;
       send(newsockfd, mesg, strlen(mesg), 0);
//       sleep(1);

       vector<std::string> tiles = shuffleTiles();
//       vector<std::string> tiles2 = shuffleTiles();
 
       message = "THE REMAINING 76 TILES ARE [ ";
       for(int j = 1; j < tiles.size(); j++)
       {
         message.append(tiles[j] + " ");
       }
       message.append("]\r\n");
       strncpy(mesg, message.c_str(), sizeof(mesg));
       mesg[sizeof(mesg) - 1] = 0;
       send(newsockfd, mesg, strlen(mesg), 0);
//       sleep(1);

       message = "MATCH BEGINS IN 10 SECONDS\r\n";
       strncpy(mesg, message.c_str(), sizeof(mesg));
       mesg[sizeof(mesg) - 1] = 0;
       send(newsockfd, mesg, strlen(mesg), 0);
//       sleep(1);

//       vector<std::string> tiles = shuffleTiles();
//       vector<std::string> tiles2 = shuffleTiles();
       for(int k = 1; k < tiles.size(); k++)
       {

       message = "MAKE YOUR MOVE IN GAME A WITHIN 1 SECOND(S): MOVE <#> PLACE " + tiles[k] + "\r\n";
       strncpy(mesg, message.c_str(), sizeof(mesg));
       mesg[sizeof(mesg) - 1] = 0;
       send(newsockfd, mesg, strlen(mesg), 0);

       bzero(buffer,256);
       n = read(newsockfd,buffer,255);
       if (n < 0) error("ERROR reading from socket");
       printf("Here is the message: %s\n",buffer);

/*
       message = "GAME A MOVE <#> PLAYER <pid> (<move> or FORFEITED:)\r\n";
       strncpy(mesg, message.c_str(), sizeof(mesg));
       mesg[sizeof(mesg) - 1] = 0;
       send(newsockfd, mesg, strlen(mesg), 0);
//       sleep(1);

       message = "MAKE YOUR MOVE IN GAME B WITHIN 1 SECOND(S): MOVE <#> PLACE " + tiles[k] + "\r\n";
       strncpy(mesg, message.c_str(), sizeof(mesg));
       mesg[sizeof(mesg) - 1] = 0;
       send(newsockfd, mesg, strlen(mesg), 0);

       bzero(buffer,256);
       n = read(newsockfd,buffer,255);
       if (n < 0) error("ERROR reading from socket");
       printf("Here is the message: %s\n",buffer);

       message = "GAME B MOVE <#> PLAYER <pid> (<move> or FORFEITED:)\r\n";
       strncpy(mesg, message.c_str(), sizeof(mesg));
       mesg[sizeof(mesg) - 1] = 0;
       send(newsockfd, mesg, strlen(mesg), 0);
*/
       }

       message = "GAME A OVER PLAYER <pid> <score> PLAYER <pid> <score>\r\n";
       strncpy(mesg, message.c_str(), sizeof(mesg));
       mesg[sizeof(mesg) - 1] = 0;
       send(newsockfd, mesg, strlen(mesg), 0);
//       sleep(1);

       message = "END OF ROUND 1 OF 1 (PLEASE WAIT FOR THE NEXT MATCH)\r\n";
       strncpy(mesg, message.c_str(), sizeof(mesg));
       mesg[sizeof(mesg) - 1] = 0;
       send(newsockfd, mesg, strlen(mesg), 0);
//       sleep(1);

       message = "PLEASE WAIT FOR THE NEXT CHALLENGE TO BEGIN\r\n";
       strncpy(mesg, message.c_str(), sizeof(mesg));
       mesg[sizeof(mesg) - 1] = 0;
       send(newsockfd, mesg, strlen(mesg), 0);
//       sleep(1);

       message = "END OF CHALLENGES\r\n";
       strncpy(mesg, message.c_str(), sizeof(mesg));
       mesg[sizeof(mesg) - 1] = 0;
       send(newsockfd, mesg, strlen(mesg), 0);
//       sleep(1);

       message = "THANK YOU FOR PLAYING! GOODBYE\r\n";
       strncpy(mesg, message.c_str(), sizeof(mesg));
       mesg[sizeof(mesg) - 1] = 0;
       send(newsockfd, mesg, strlen(mesg), 0);
//       sleep(1);

/*       WRITE MESSAGE TO CLIENT
       message = "WELCOME <pid> PLEASE WAIT FOR THE NEXT CHALLENGE\r\n";
       strncpy(mesg, message.c_str(), sizeof(mesg));
       mesg[sizeof(mesg) - 1] = 0;
       send(newsockfd, mesg, strlen(mesg), 0);
*/

/*       READ MESSAGE FROM CLIENT
       bzero(buffer,256);
       n = read(newsockfd,buffer,255);
       if (n < 0) error("ERROR reading from socket");
       printf("Here is the message: %s\n",buffer);
*/
     //}

     close(newsockfd);
     close(sockfd);
     return 0; 

}
