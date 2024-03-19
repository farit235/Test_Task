#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h> 
#define MAX 50

void chatting_function(int clientSocket){
    char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        printf("Enter the string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n');
        write(clientSocket, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(clientSocket, buff, sizeof(buff));
        printf("From Server : %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}

int main(int argc, const char** argv) {
    
    // определение сокета клиента и адреса, который будет на этом сокете 
    int sockD = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(9000); 
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // подключение к сокету с указанием структуры адреса, назначаемого на данный сокет
    int connectStatus = connect(sockD, (struct sockaddr*)&servAddr, sizeof(servAddr));  
    if (connectStatus == -1) { 
        printf("Error...\n"); 
        exit(0);
    } 
    
    chatting_function(sockD);

    // закрытие сокета
    close(sockD);
    return 0;
}