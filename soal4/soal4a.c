#include <stdio.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int matrix1[10][10];
int matrix2[10][10];
int (*hasil)[10];
int baris1=4;
int kolom1=2;
int baris2=2;
int kolom2=5;
int status;

pthread_t tid1, tid2, tid3;

void *multiply_matrix(void *);
void *fill_matrix1(void *);
void *fill_matrix2(void *);

void *fill_matrix1(void *arg)
{
	status=0;
        matrix1[0][0]=1;
        matrix1[0][1]=1;
        matrix1[1][0]=1;
        matrix1[1][1]=1;
        matrix1[2][0]=1;
        matrix1[2][1]=1;
        matrix1[3][0]=1;
        matrix1[3][1]=1;

	status=1;
	return NULL;
}

void *fill_matrix2(void *arg)
{
	while(status!=1)
	{

	}
        matrix2[0][0]=1;
        matrix2[0][1]=1;
        matrix2[0][2]=1;
        matrix2[0][3]=1;
        matrix2[0][4]=1;
        matrix2[1][0]=1;
        matrix2[1][1]=1;
        matrix2[1][2]=1;
        matrix2[1][3]=1;
        matrix2[1][4]=1;

	status=2;
	return NULL;
}

void *multiply_matrix(void *arg)
{
	while(status!=2)
	{

	}
	int i, j, k;
	for(i=0;i<baris1;i++)
	{
		for(j=0;j<kolom2;j++)
		{
			for(k=0;k<kolom1;k++)
			{
				hasil[i][j]+=matrix1[i][k] * matrix2[k][j];
			}
		}
	}
	return NULL;
}

int main()
{
	int i, j;
	key_t key = 1234;
        int shmid = shmget(key, sizeof(int[10][10]), IPC_CREAT | 0666);
        hasil = shmat(shmid, 0, 0);

	pthread_create(&tid1, NULL, fill_matrix1, NULL);
	pthread_join(tid1,NULL);

	pthread_create(&tid2, NULL, fill_matrix2, NULL);
	pthread_join(tid2,NULL);

	for(i=0;i<baris1;i++)
	{
		for(j=0;j<kolom2;j++)
		{
			hasil[i][j]=0;
		}
		pthread_create(&tid3, NULL, multiply_matrix, NULL);
		pthread_join(tid3,NULL);
	}

	printf("Hasil Perkalian\n");
	for(i=0;i<baris1;i++)
	{
		for(j=0;j<kolom2;j++)
		{
			printf("%d\t", hasil[i][j]);
		}
		printf("\n");
	}

	return 0;
}
