#include "sr.h"



int sr_connect(const char *name)
{
	int fd, size;
	struct sockaddr_un un;
	memset(&un, 0, sizeof(un));
	un.sun_family = AF_UNIX;
	
	if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
		return 0;
	}
	sprintf(un.sun_path, "%s%05d", "tmp", getpid());
	size = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);
	if (bind(fd, (struct sockaddr *)&un, size) < 0) {
		printf("no2\n");
		return 0;
	}
	strcpy(un.sun_path, name);
	size = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);
	if (connect(fd, (struct sockaddr *)&un, size) < 0) {
		printf("no3\n");
		return 0;
	}
	return fd;
}




int send_fd(int sock, int fd, char* data)    
{    
    struct iovec iov[1];    
    iov[0].iov_base = data;    
    iov[0].iov_len  = strlen(data);
  
    int cmsgsize = CMSG_LEN(sizeof(int));    
    struct cmsghdr* cmptr = (struct cmsghdr*)malloc(cmsgsize);    
    if(cmptr == NULL){    
        return -1;    
    }    
    cmptr->cmsg_level = SOL_SOCKET;    
    cmptr->cmsg_type = SCM_RIGHTS; // we are sending fd.    
    cmptr->cmsg_len = cmsgsize;    
    
    struct msghdr msg;    
    msg.msg_iov = iov;    
    msg.msg_iovlen = 1;    
    msg.msg_name = NULL;    
    msg.msg_namelen = 0;    
    msg.msg_control = cmptr;    
    msg.msg_controllen = cmsgsize;    
    *(int *)CMSG_DATA(cmptr) = fd;    
        
    int ret = sendmsg(sock, &msg, 0);    
    free(cmptr);    
    if (ret == -1){    
        return -1;    
    }
    return 0;  
}    
    
int recv_fd(int sock, char* data)    
{   
    int cmsgsize = CMSG_LEN(sizeof(int));    
    struct cmsghdr* cmptr = (struct cmsghdr*)malloc(cmsgsize);    
    if (cmptr == NULL) {  
        return -1;  
    }  
    char buf[33]; // the max buf in msg. 
    memset(buf, 0, 33);  
    struct iovec iov[1];  
    iov[0].iov_base = buf;    
    iov[0].iov_len = sizeof(buf);    
    struct msghdr msg;
    msg.msg_iov = iov;    
    msg.msg_iovlen  = 1;    
    msg.msg_name = NULL;    
    msg.msg_namelen = 0;    
    msg.msg_control = cmptr;    
    msg.msg_controllen = cmsgsize;    
        
    int ret = recvmsg(sock, &msg, 0);  
       
    if (ret == -1) {    
        return -1;   
    }
    int fd = *(int *)CMSG_DATA(cmptr);
    strcpy(data, iov[0].iov_base);
    free(cmptr); 
    return fd;    
}

void close_fd(int fd)
{
    close(fd);
}


// int main()
// {
// 	int lis = serv_listen("/tmp/fjs.sock");
// 	printf("ok\n");
// 	char* hello = "hello fjs";
// 	// ssize_t out = send(lis, (void*)hello, strlen(hello), 0);
// 	send_fd(lis, lis);

// }

