
cdef extern from "sr.h":
	extern int sr_connect(const char *name)
	extern int send_fd(int sock, int fd, char* data)
	extern int recv_fd(int sock, char* data)
	void close_fd(int fd)

cdef extern from "stdlib.h":
	extern void *malloc(unsigned int num_bytes)
	extern void free(void *ptr)


def connect_and_send():
	cdef char* dist = "/tmp/fjs.sock"
	cdef int fd = sr_connect(dist)
	send_fd(fd, fd, "fdsaf");

def fjs_recv_fd(sock):
	cdef int fd = sock
	cdef char* data = <char*>malloc(33)
	fd = recv_fd(fd, data)
	try:
		out_data = data
		return (fd, out_data)
	finally:
		free(data)

def fjs_send_fd(fd1, fd2, data):
	cdef int source = fd1
	cdef int des    = fd2
	return send_fd(source, des, data)

def fjs_close_fd(fd):
	cdef int now_fd = fd
	close_fd(fd)

