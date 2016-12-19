#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>





int is_symlink(const char *filename)
{
  struct stat p_statbuf;
  if (S_ISLNK(p_statbuf.st_mode) == 1)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}











int valid_path(char *path)
{
  struct stat statbuf;

  stat(path, &statbuf);

  if(S_ISDIR(statbuf.st_mode))
    {
      return 1;
    }
  else
    {
      return 0;
    }
}






int folder_not_there(char *path)
{
  FILE *fp;
  int count=0;
  char name[500];
  fp=fopen("tmp-files-info.lst","r");

  while(!feof(fp))
    {
      fscanf(fp,"%s",name);

      if(strcmp(name,path)==0)
	{

	  count=1;
	}
    }


  return count;
}








int file_not_there(char *path)
{
  FILE *fp;
  int count=0;
  char name[500];
  fp=fopen("files.output","r");

  while(!feof(fp))
    {
      fscanf(fp,"%s",name);

      if(strcmp(name,path)==0)
	{

	  count=1;
	}
    }
  return count;
}

int check(char *path)
{
  struct stat s;
  if( stat(path,&s) == 0 )
    {
      if( s.st_mode & S_IFDIR )
	{
	  return 1;
	}
      else if( s.st_mode & S_IFREG )
	{
	  return 0;
	}
      else
	{
	  return 0;
	}
    }
  else
    {
      return 0;
    }
}



void  separet_file_directory()
{
  FILE *fp,*file,*directory,*temp;
  char name[500];
  fp=fopen("new-files-found.lst","r");
  file=fopen("files.output","a");
  directory=fopen("tmp-files-info.lst","a");
  temp=fopen("recursive_file.txt","a");
  while(!feof(fp))
    {
      fscanf(fp,"%s",name);
      if(valid_path(name) == 0 && is_symlink(name)==0)
	{
	  if(file_not_there(name)==0)
	    {
	      fprintf(file,"%s\n",name);
	    }
	}
      if(valid_path(name) == 1 && check(name)==1)
      {
	 if(folder_not_there(name)==0)
	    {
	      //	      printf("%s\n",name);
	      fprintf(directory,"%s\n",name);
	      //	      fprintf(temp,"%s\n",name);
	    }
	    	}
    }

  fclose(fp);
  fclose(file);
  fclose(directory);
}



int main()
{
  separet_file_directory();
}
