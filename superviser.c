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


int is_recursive_file_empty()
{
  FILE *fp,*fp1;
  fp=fopen("recursive_file.txt","r");
  
  if(fp==NULL)
    {
      return 0;
    }
  else
    {
      return 1;
    }
}


void coppy_content()
{
  FILE *fp,*fp1;
  char name[1024];
  printf("\n !!       Error 001 : program1 must be run first\n");
  fp=fopen("dirs2process.lst","r");
  fp1=fopen("recursive_file.txt","w");
  fscanf(fp,"%s",name);
  fprintf(fp1,"%s",name);
  fclose(fp);
  fclose(fp1);
}

/* int all_path_are_visited() */
/* { */
/*   FILE *fp; */
/*   char name[1024]; */
/*   int n=1; */
/*   fp=fopen("recursive_file.txt","r"); */
/*   if(fp!=NULL) */
/*     { */
/*       while(!feof(fp)) */
/* 	{ */
/* 	  fscanf(fp,"%s",name); */
/* 	  if(strstr(name,"--@@--")==NULL) */
/* 	    { */
/* 	      n=0; */
/* 	    } */
/* 	} */
/*       fclose(fp); */
/*       return n; */
/*     } */
/*   else */
/*     { */
/*       return 0; */
/*     } */
/* } */





/* int folder_not_there(char *path) */
/* { */
/*   FILE *fp; */
/*   int count=0; */
/*   char name[500]; */
/*   fp=fopen("recursive_file.txt","r"); */
/*   if(fp!=NULL) */
/*     { */
/*       while(!feof(fp)) */
/* 	{ */
/* 	  fscanf(fp,"%s",name); */
	  
/* 	  if(strcmp(name,path)==0) */
/* 	    { */
	      
/* 	      count=1; */
/* 	    } */
/* 	} */
/*       fclose(fp); */
/*     } */
/*   return count; */
/* } */

/*   int all_path_send_in_recursive() */
/*   { */
/*     FILE *fp; */
/*     char name[1021]; */
/*     int n=1; */
    
/*     fp=fopen("tmp-files-info.lst","r"); */
/*     if(fp!=NULL) */
/*       { */
/* 	while(!feof(fp)) */
/* 	  { */
/* 	    fscanf(fp,"%s",name); */
	    
/* 	    strcat(name,"--@@--"); */
/* 	    if(folder_not_there(name)==1) */
/* 	    { */
/* 	      n=0; */
/* 	    } */
/* 	  } */
	
/* 	fclose(fp); */
/* 	return n; */
/*       } */
/*     else */
/*       { */
/* 	return 0; */
/*       } */
/*   } */

void fill_path_depth()
{
  FILE *fp;
  DIR *dir;
  struct dirent *ent;
  char cdw[1024],*chardepth;
  int depth;
  depth=rand()%10;
  
  fp=fopen("dirs2process.lst","w");
  fprintf(fp,"%s",getcwd(cdw,sizeof(cdw)));
  fprintf(fp," %d",depth);
  fclose(fp);
  
}


int main()

{

  int number,lock=0;
  
  if(is_recursive_file_empty()==0)
    {
      fill_path_depth();
      coppy_content();   
    }

  system("gcc program1.c -o program1");
  system("gcc program2.c -o program2");
  system("gcc program3_recursion.c -o program3_recursion");

  while(1)
    {
      number=rand()%200;
                            //printf("\n%d\n",number%3);
                            //      if(all_path_are_visited()==1 && all_path_send_in_recursive()==1)
                            //	{
                            //  printf("\nWE ARE ALMOST COMPLET WORK YOU MAY TERMINET PROGRAM\n");
                            //	}
      if(number%3==0)
      	{
      	  	  printf("\nPlease wait PROGRAM1 is working ! , I am writing all file and directory in new-files-found.lst file !!\n");
      	  system("./program1");
      	  sleep(1);
      	}
      if(number%3==1)
      	{
      	   printf("\nPlease wait PROGRAM2 is working !, I am separeting file and folder\n");
      	  system("./program2");
      	  lock=1;
      	  sleep(1);
      	}
      if(number%3==2)
      	{
      	  if(lock==1)
      	    {
      	        printf("\nPlease wait PROGRAM3 is working ! , I am going recursivly \n");
      	      system("./program3_recursion");
      	    }
      	  else
      	    {
      	      printf(" \n !!       Error 002 : program 2 must start befor prgram3\n");
      	    }
      	  sleep(1);
      	}
    }
  
  
}
