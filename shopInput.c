#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "setting.h"
#define MAXCHARS 50
#define MAXCHARSFILENAME 10

extern int map[MAXSIZE][MAXSIZE];
extern int ROW;
extern int COL;

int shopInput(){
  char filename[MAXCHARSFILENAME],line[MAXCHARS];
  int i,j;
  char *tmp,temp[10];
  int num;
  FILE *fp;
  char *ret;
  strcpy(filename,"map1.txt\0");
  /* strcat(temp,filename);*/
  
  fp=(FILE*)fopen(filename,"r");
  
  num=1;
  /*map初期化*/
  for(i=0;i<MAXSIZE;i++){
    for(j=0;j<MAXSIZE;j++){
      map[i][j]=1;
    }
  }
  
  if(fp!=NULL){
    fprintf(stderr,"Load file:%s\n",filename);
    ret= fgets(line,MAXCHARS,fp);
    i=0;
    while(ret!=NULL){
     
      tmp= strtok(line,",");
      j=0;
      while(tmp!=NULL){
	 
	strcpy(temp,tmp);
	num = atoi(temp);


	map[i][j]=num;
#ifdef DEBUG
	fprintf(stderr,"[%d,%d]%d,",i,j,num);
#endif
	tmp=strtok(NULL,",");
	j++;

      }
#ifdef DEBUG
      fprintf(stderr,"\n");
#endif
      ret= fgets(line,MAXCHARS,fp);
      i++;
    }
    fclose(fp);
    
  }else{
    fprintf(stderr,"FILE NOT FOUND.\n");
  }

  
  ROW=i;
  COL=j;
  
  fprintf(stderr,"-----\n");
  for(i=0;i<ROW;i++){
    for(j=0;j<COL;j++){
      fprintf(stderr,"%3d ",map[i][j]);
    }
    fprintf(stderr,"\n");
  }

  fprintf(stderr,"店構造図を読み込みしました。\n");
  return 0;
}
