#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>

unsigned long long factorial[10][10];
int baris=4, kolom=5;
void *factorial_matrix(void *);

void *factorial_matrix(void *arg)
{
        key_t key = 1234;
        int (*hasil)[10];

        int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
        hasil = shmat(shmid, 0, 0);

	int i,j,k,angka;
	unsigned long long fact=1;
	for(i=0;i<baris;i++)
	{
		for(j=0;j<kolom;j++)
		{
			angka=hasil[i][j];
			//printf("%d\n", angka);
			for(k=1;k<=angka;++k)
			{
				fact*=k;
				factorial[i][j]=fact;
			}
			fact=1;
		}
	}
}

void main()
{
        key_t key = 1234;
        int (*hasil)[10];
	int i,j;

        int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
        hasil = shmat(shmid, 0, 0);

	printf("Hasil Perkalian\n");
	for(i=0;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
			printf("%d\t", hasil[i][j]);
		}
		printf("\n");
	}

        //shmdt(value);
        //shmctl(shmid, IPC_RMID, NULL);

	pthread_t tid;

	pthread_create(&tid, NULL, factorial_matrix, NULL);
	pthread_join(tid,NULL);

	printf("Hasil Faktorial\n");
	for(i=0;i<baris;i++)
	{
		for(j=0;j<kolom;j++)
		{
			printf("%llu\t", factorial[i][j]);
		}
		printf("\n");
	}
}
