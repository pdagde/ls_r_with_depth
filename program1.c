#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

FILE *globptr,*globptr1,*fp;


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







int path_in_range(char *path,int n)
{
  int count=0,i=0;
  while(path[i]!='\0')
    {
      if(path[i]=='/')
	{
	  count++;
	}
      i++;
    }
  if(count<n+1)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}




int alredy_path_not_there(char *path)
{
  FILE *fp;
  char name[1024];
  int lock=0;
  fp=fopen("new-files-found.lst","r");

  while(!feof(fp))
    {
      fscanf(fp,"%s",name);

      if(strcmp(name,path)==0)
	{
	  lock=1;
	}
    }
  return lock;
}











void only_ls_command(char *path,int n)
{
  DIR *dir;
  struct dirent *ent;
  char cdw[1024],temp[500];
  FILE *fp;

  fp=fopen("new-files-found.lst","a");

  if((dir = opendir(path))!=NULL)
    {
      while((ent =readdir(dir))!= NULL)
	{
	  if(strcmp(ent->d_name,".")!=0 && strcmp(ent->d_name,"..")!=0)
	    {
	      strcpy(temp,path);
	      strcat(temp,"/");
	      strcat(temp,ent->d_name);
	      if(path_in_range(path,n)==1 && alredy_path_not_there(temp)==0 && ent->d_name!=NULL)
		{
		  fprintf (fp,"%s\n", temp);
		}

	    }

	}
    }

  closedir (dir);
  fclose(fp);
}



int not_visited_path(char *name)
{
  FILE *pp;
  int lock=0;
  char line[1024];
  pp=fopen("recursive_file.txt","r");

  while(!feof(pp))
    {
      fscanf(pp,"%s",line);
      strcat(line,"--@@--");
	if(strcmp(line,name)==0)
	  {
	    lock=1;
	  }
    }
  
  return lock;
}

int totalpath(char *path)
{
  int i=0,n=0;
  while(path[i]!='\0')
    {
      if(path[i]=='/')
	{
	  n++;
	}
      i++;
    }
  return n;
}


int calculet_depth()
{
  FILE *fp;
  char name[1024],i[2];
  int n=0;
  fp=fopen("dirs2process.lst","r");
  fscanf(fp,"%s",name);
  fscanf(fp,"%s",i);
     n=i[0]-'0';
     n=n + totalpath(name);
  return n;
}

int main()
{
  FILE *fp1,*fp2;
  char name[1024];
  int lock=0,n;
  fp1 = fopen("recursive_file.txt", "r");
  fp2 = fopen("copy.c", "w");
  n=calculet_depth();
  
  while (!feof(fp1))
    {
      fscanf(fp1,"%s\n",name);
      if(not_visited_path(name)==0)
	{
	  if(lock==0 && strstr(name,"--@@--")==NULL)
	    {
	      lock=1;
	      only_ls_command(name,n);
	      strcat(name,"--@@--");
	      fprintf(fp2,"%s\n",name);
	    }
	  else
	    {
	      fprintf(fp2,"%s\n",name);
	    }
	}  
      //else
	    //fprintf(fp2,"%s\n",name);
	
    }

      fclose(fp1);
      fclose(fp2);
      remove("recursive_file.txt");
      rename("copy.c", "recursive_file.txt");
      return 0;
      
}
