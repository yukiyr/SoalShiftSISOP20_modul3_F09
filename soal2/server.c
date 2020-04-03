#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <wait.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define PORT 8080

pthread_t tid;
void *make_file(void *);

int cfileexists(const char *filename) {
	FILE *file;
	if (file = fopen(filename,"r")) {
		fclose(file);
		return 1;
	}
	return 0;
}

void *make_file(void *arg)
{
	char *argv[3] = {"touch","akun.txt",NULL};
	execv("/usr/bin/touch", argv);

	return NULL;
}

int main(int argc, char const *argv[]) {
    	int server_fd, new_socket, valread, valread2, valread3, valread4, valread5, valread6;
    	struct sockaddr_in address;
    	int opt = 1;
    	int addrlen = sizeof(address);
    	char buffer[1024] = {0};
	char buffer2[1024] = {0};
	char buffer3[1024] = {0};
        char buffer4[1024] = {0};
        char buffer5[1024] = {0};
        char buffer6[1024] = {0};
    	char *hello = "Hello from server";

    	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        	perror("socket failed");
        	exit(EXIT_FAILURE);
    	}

    	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        	perror("setsockopt");
        	exit(EXIT_FAILURE);
    	}

    	address.sin_family = AF_INET;
    	address.sin_addr.s_addr = INADDR_ANY;
    	address.sin_port = htons( PORT );

    	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        	perror("bind failed");
        	exit(EXIT_FAILURE);
    	}

    	if (listen(server_fd, 3) < 0) {
        	perror("listen");
        	exit(EXIT_FAILURE);
    	}

    	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        	perror("accept");
        	exit(EXIT_FAILURE);
    	}

	char *arr[] = {"hai", "hai"};
	char **ptr = arr;
	char *filename = "akun.txt";
	int exist = cfileexists(filename);
	if(exist)
	{
		printf("File exist\n");
	}
	else
	{
		pthread_create(&tid, NULL, make_file, NULL);
		pthread_join(tid,NULL);
		valread = read( new_socket , buffer, 1024);
		valread2 = read( new_socket , buffer2, 1024);
		FILE *fp;
		fp = fopen("akun.txt", "w");
		fwrite(buffer, 1, sizeof(buffer), fp);
		fwrite(buffer2, 1, sizeof(buffer2), fp);
		fclose(fp);
		valread3 = read( new_socket , buffer3, 1024);
		if(strcmp(buffer3, "login") == 0)
		{
			valread4 = read( new_socket , buffer4, 1024);
		}
		else
		{
			valread5 = read( new_socket , buffer5, 1024);
			valread6 = read( new_socket , buffer6, 1024);
			int awal = sizeof(arr)/sizeof(arr[0]);
			int i;
			for(i=0;i<2;i++)
			{
				ptr[awal+1] = buffer5;
				ptr[awal+2] = buffer6;
			}
			for(i=0;i<awal+2;i=i+2)
			{
				printf("%s\t", ptr[i]);
				printf("%s\n", ptr[i+1]);
			}
		}
	}

    return 0;
}
