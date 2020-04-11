#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<dirent.h>

pthread_t tid[500];
char *workDir;
char *tempDir;
int currentInd;
void moveFile(char src[], char dst[]);
char* getFilename(char str[]);
char* getExtension(char str[]);

void* kategoriSatu(void *arg)
{
	pthread_t id=pthread_self();
	int i;
	char *extension;
	char destination[500];
	char path[500];
	extension = getExtension((char *)arg);

	if(extension == NULL)
	{
		strcpy(destination, "Unknown");
	}
	else
	{
		strcpy(destination, extension);
		//mengubah jika extension berhuruf besar diselaraskan ke huruf kecil
		for(i=0;i<strlen(destination);i++)
		{
			//64 = DEC from @
			//91 = DEC from [
			//32 kembali ke alphabet huruf kecil dari a
			if(destination[i]>64 && destination[i]<91)
			{
				destination[i]+=32;
			}
		}
	}

	if(mkdir(destination,0777) == -1);

	snprintf(path,500,"%s/%s/%s",workDir,destination,getFilename((char *)arg));
	moveFile((char *)arg, path);
	return NULL;
}

void* kategoriDua(void *arg)
{
	pthread_t id = pthread_self();
	char *extension;
	char destination[500];
	int i;
	char sourceFolder[500];
	char destinationFolder[500];
	extension = getExtension((char *)arg);

	if(extension == NULL)
	{
		strcpy(destination,"Unknown");
	}
	else
	{
                strcpy(destination, extension);
                //mengubah jika extension berhuruf besar diselaraskan ke huruf kecil
                for(i=0;i<strlen(destination);i++)
                {
                        //64 = DEC from @
                        //91 = DEC from [
                        //32 kembali ke alphabet huruf kecil dari a
                        if(destination[i]>64 && destination[i]<91)
                        {
                                destination[i]+=32;
                        }
                }

	}

	if(mkdir(destination,0777) == -1);

	snprintf(sourceFolder,500,"%s/%s",workDir,(char *)arg);
	snprintf(destinationFolder,500,"%s/%s/%s",workDir,destination,getFilename((char *)arg));
	moveFile(sourceFolder,destinationFolder);
	return NULL;
}

void* kategoriTiga(void *arg)
{
	pthread_t id = pthread_self();
	char *extension;
	char destination[500];
	int i;
	char sourceFolder[500];
	char destinationFolder[500];
	extension = getExtension((char *)arg);

	if(extension == NULL)
	{
		strcpy(destination,"Unknown");
	}
	else
	{
		strcpy(destination,extension);
		for(i=0;i<strlen(destination);i++)
		{
			if(destination[i]>64 && destination[i]<91)
			{
				destination[i]+=32;
			}
		}
	}
	char pathhh[42] = "/home/test/SISOP2/TIGA/PRAKTIKUM/gambar";
	chdir(pathhh);
	if(mkdir(destination,0777) == -1);

	snprintf(sourceFolder,500,"%s/%s",tempDir,(char *)arg);
	snprintf(destinationFolder,500,"%s/%s/%s",pathhh,destination,getFilename((char *)arg));
	moveFile(sourceFolder,destinationFolder);
	return NULL;
}

int main(int argc, char **arg2)
{
	char buffer[500];
	workDir = getcwd(buffer,500);
	int i=2,j,cek;

	if(!strcmp(arg2[1],"-f"))
	{
		while (arg2[i] != NULL)
		{
			cek = pthread_create(&(tid[i-2]),NULL,&kategoriSatu,(void *)arg2[i]);
			if(cek!=0)
			{
				printf(" ");
			}
			i++;
		}
		for(j=0;j<(i-1);j++)
		{
			pthread_join(tid[j],NULL);
		}
	}
	else if (!strcmp(arg2[1],"*"))
	{
		DIR *d;
		struct dirent *direktori;
		struct stat File;
		d = opendir(".");
		if(d)
		{
			while((direktori = readdir(d))!=NULL)
			{
				if(stat(direktori->d_name,&File)<0);
				else if(!S_ISDIR(File.st_mode))
				{
	        	                cek = pthread_create(&(tid[i-2]),NULL,&kategoriDua,(void *)direktori->d_name);
					if(cek!=0)
					{
						printf(" ");
					}
        	        	        i++;
				} 
				else;
			}
                	for(j=0;j<(i-1);j++)
               		{
                        	pthread_join(tid[j],NULL);
                	}
		}
	}
	else if(!strcmp(arg2[1],"-d"))
	{
		chdir(arg2[2]);
		tempDir = getcwd(buffer,500);
		DIR *d;
                struct dirent *direktori;
                struct stat File;
                d = opendir(".");
                if(d)
                {
                        while((direktori = readdir(d))!=NULL)
                        {
                                if(stat(direktori->d_name,&File)<0);
                                else if(!S_ISDIR(File.st_mode))
                                {
                                        cek = pthread_create(&(tid[i-2]),NULL,&kategoriTiga,(void *)direktori->d_name);
					if(cek!=0)
					{
						printf(" ");
					}
                                        i++;
                                }
				else;
                        }
                        for(j=0;j<(i-1);j++)
                        {
                                pthread_join(tid[j],NULL);
                        }
                }
	}
	return 0;
}

void moveFile(char src[], char dst[])
{
	FILE *file1, *file2;
	int charr;

	file1 = fopen(src,"r");
	file2 = fopen(dst,"w");

	if(!file1)
	{
		fclose(file2);
		return ;
	}
	if(!file2)
	{
		return ;
	}
	while((charr=fgetc(file1)) != EOF)
	{
		fputc(charr,file2);
	}

	fclose(file1);
	fclose(file2);

	remove(src);
	return ;
}

char* getFilename(char str[])
{
	char* stop;
	char* final;
	stop = strchr(str,'/');
	if(stop == NULL)
	{
		return str;
	}
	while(stop != NULL)
	{
		final = stop+1;
		stop = strchr(stop+1,'/');
	}
	return final;
}

char* getExtension(char str[])
{
	char* stop = getFilename(str);
	char* final = strchr(stop,'.');
	if(final == NULL)
	{
		return NULL;
	}
	else
	{
		return (final+1);
	}
}
