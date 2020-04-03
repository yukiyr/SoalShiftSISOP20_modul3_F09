#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080

int main(int argc, char const *argv[]) {
	struct sockaddr_in address;
	int sock = 0, valread;
    	struct sockaddr_in serv_addr;
    	char *hello = "Auth Success";
	char *hello2 = "Auth Failed";
    	char buffer[1024] = {0};
	char input1[10];
	char input2[10];
	char *username;
	char *password;
	char *usernamebenar = "hai";
	char *passwordbenar = "hai";
	char *login = "login";
	char *registerr = "register";
    	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        	printf("\n Socket creation error \n");
        	return -1;
    	}

    	memset(&serv_addr, '0', sizeof(serv_addr));

    	serv_addr.sin_family = AF_INET;
    	serv_addr.sin_port = htons(PORT);

    	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        	printf("\nInvalid address/ Address not supported \n");
       		return -1;
    	}

    	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        	printf("\nConnection Failed \n");
        	return -1;
    	}
	system("clear");
	while(1)
	{
	        send(sock , usernamebenar , strlen(usernamebenar) , 0 );
	        send(sock , passwordbenar , strlen(passwordbenar) , 0 );
		printf("1. Login\n");
		printf("2. Register\n");
		printf("Choices : ");
		scanf("%s", input1);
		if(strcmp(input1,"Login")==0)
		{
			send(sock , login , strlen(login) , 0 );
			printf("Username: ");
			scanf("%s", username);
			printf("password: ");
			scanf("%s", password);
			if(strcmp(username,"hai")==0 && strcmp(password,"hai")==0)
			{
				send(sock , hello , strlen(hello) , 0 );
				printf("Login Success\n");
			}
			else
			{
				send(sock , hello2 , strlen(hello2) , 0 );
				printf("Login Failed\n");
			}
		}
		else
		{
			send(sock , registerr , strlen(registerr) , 0 );
			printf("Username: ");
                	scanf("%s", username);
			send(sock , username , strlen(username) , 0 );
                	printf("password: ");
                	scanf("%s", password);
                        send(sock , password , strlen(password) , 0 );
			printf("Register Success\n");
		}
		sleep(1);
		system("clear");
        	printf("\n1. Find Match\n");
        	printf("2. Logout\n");
        	printf("Choices : ");
        	scanf("%s", input2);
		if (strcmp(input2, "Logout")==0)
		{
			sleep(1);
			system("clear");
		}
		else
		{
			int i=0;
			while(1)
			{
				printf("Waiting for player ...\n");
				//valread = read( sock, buffer, 1024);
				//if(strcmp(buffer,"ayo")==0)
				i++;
				if(i==2)
				{
					break;
				}
			}
			printf("Game dimulai silahkan tap tap secepat mungkin !!\n");
			int healthA=100;
			int c;
			while(getchar() == 32)
			{
				printf("hit!!\n");
			}
		}
		//sleep(1);
		//system("clear");
	}
  
    	return 0;
}
