#include <sys/socket.h> 
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>

int serv_listen(const char *name);
int send_fd(int sock, int fd, char* data);
int recv_fd(int sock, char *data);  
void close_fd(int fd);


