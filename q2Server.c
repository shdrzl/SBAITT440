#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>

int PORT = 8484;

int main()
{
    printf("This is SERVER.\n");
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };
  
    // create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    else
        printf("Socket successfully created");
  
    // binding socket to port 8484
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    else
        printf("\nSocket binded to %d", PORT);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
  
    // forcefully attaching socket to the port 8484
    if (bind(server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    else
        printf("\nSocket is listening...");
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen))
        < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    else
        printf("\nGot connection from Client");
   
    char message[100];
    int random_num;
    srand(time(NULL));  // seed the random number generator with the current time

    // generate a random number between 0 and 899, then add 100 to shift the range to 100 to 999
    random_num = rand() % 900 + 100;

    printf("\nRandom number: %d\n", random_num);
    
    sprintf(message, "%d", random_num);   
    send(new_socket, message, strlen(message), 0); //send string to Client
    printf("Message sent to Client\n");
    
    // closing the connected socket
    close(new_socket);
    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
    return 0;
}
