#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h> 
#define MAX 50

void chatting_function(int clientSocketAccept){
    char buff[MAX]; 
    int n; 
    // infinite loop for chat 
    for (;;) { 
        bzero(buff, MAX);

        
        // read the message from client and copy it in buffer 
        read(clientSocketAccept, buff, sizeof(buff)); 
        // print buffer which contains the client contents 
        printf("From client: %s\t To client : ", buff); 
        bzero(buff, MAX);
        n = 0; 
        // copy server message in the buffer 
        while ((buff[n++] = getchar()) != '\n') ; 
   
        // and send that buffer to client 
        write(clientSocketAccept, buff, sizeof(buff)); 
   
        // if msg contains "Exit" then server exit and chat ended. 
        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        } 
    } 
}

int main(int argc, const char** argv) {

    int servSockD = socket(AF_INET, SOCK_STREAM, 0);
    if (servSockD == -1) { 
        printf("Socket creation failed...\n"); 
        exit(0);
    }
    else {
        printf("Socket succesfully created!\n");
    } 

    struct sockaddr_in servAddr, client;
    bzero(&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(9000); 
    servAddr.sin_addr.s_addr = INADDR_ANY;

    bind(servSockD, (struct sockaddr*)&servAddr, sizeof(servAddr)); 
    listen(servSockD, 1);

    int clientSocket = accept(servSockD, (struct sockaddr*)&client, sizeof(client)); 
    //send(clientSocket, serMsg, sizeof(serMsg), 0); 

    chatting_function(clientSocket);

    close(servSockD);
    return 0;
}