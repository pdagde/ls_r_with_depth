#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include<math.h>

int file_not_alredy(char *name)
{
  FILE *fp1;
  int lock=0;
  char line[1024];
  fp1=fopen("recursive_file.txt","r");
  while(!feof(fp1))
    {
      fscanf(fp1,"%s",line);
      if(strcmp(name,line)==0)
	{
	  lock=1;
	}
    }
  return lock;
}


void add_if_file_not_in_use_file(char *name)
{
  FILE *fp1;
  int lock=0;
  char line[1024],name1[1024];
  // fp=fopen("tmp-files-info.lst","r");
  fp1=fopen("recursive_file.txt","r");

  strcpy(name1,name); 
 strcat(name1,"--@@--");
 
  while(!feof(fp1))
    {
      fscanf(fp1,"%s",line);
     
      if(strcmp(line,name1)==0)
	{
	  lock=1;
	}
    }
  fclose(fp1);
  
  fp1=fopen("recursive_file.txt","a");
  if(lock==0 && file_not_alredy(name)==0)
    {
      fprintf(fp1,"%s\n",name);
    }
  fclose(fp1);
}

int main()
{
  FILE *fp,*fp1;
  char name[1024];
  fp=fopen("tmp-files-info.lst","r");
 

  while(!feof(fp))
    {
      fscanf(fp,"%s",name);
      add_if_file_not_in_use_file(name);
    }
  
}
