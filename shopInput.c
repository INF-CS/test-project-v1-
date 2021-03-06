#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "setting.h"
#define MAXCHARS 50
#define MAXCHARSFILENAME 10

extern int map[MAXSIZE][MAXSIZE];
extern int ROW;
extern int COL;
char *GetShopName();
int selected_shop;
char shop[100][MAXCHARS];
char figure[100][MAXCHARS];
int shopInput(){
  char filename[MAXCHARSFILENAME],line[MAXCHARS];
  int i,j;
  char *tmp,temp[10];
  int num;
  FILE *fp;
  char *ret;
  int shop_cnt;
  

  shop_cnt=0;
  /*店リスト取得*/
  strcpy(filename,"shoplist.txt");
  fp=(FILE*)fopen(filename,"r");
  if(fp!=NULL){
    ret= fgets(line,MAXCHARS,fp);
    while(ret!=NULL){
      tmp= strtok(line,":");  
      strcpy(shop[shop_cnt],tmp);
      tmp=strtok(NULL,":");
      strcpy(figure[shop_cnt],tmp);
     
      ret= fgets(line,MAXCHARS,fp);
      if(figure[shop_cnt][strlen(figure[shop_cnt])-1]=='\n')
	figure[shop_cnt][strlen(figure[shop_cnt])-1]='\0';
       shop_cnt++;
    }
   }else{
     fprintf(stderr,"shoplist.txtがありません\n");
fprintf(stderr,"(例)\n店1:店1の構造図を記述したファイル名\n店2:店2の構造図を記述したファイル名\n");  
     return -1;
   }
   fclose(fp);
 if(shop_cnt==0){
    fprintf(stderr,"店情報が登録されていません\n");
  }
 for(i=0;i<shop_cnt;i++){
    fprintf(stderr,"(%d)%s : %s\n",i,shop[i],figure[i]);
  }

  /*行く店を決める*/
 selected_shop=-1;
 char buf[10];
 
 while(selected_shop ==-1){
fprintf(stderr,"shop番号(0~%d)を入力してください \n",shop_cnt-1);
   fgets( buf, 10, stdin );


    for(i=0;i<10;i++){
       if(buf[i]==10)
         break;
       if(buf[i]<'0'||buf[i]>'9')
          buf[0]=10;
   }

   
   if(buf[0]!=10){
     selected_shop = atoi(buf);
   }else{
     continue;
   }
 
   if(selected_shop >= shop_cnt){
     fprintf(stderr,"shopは 0 ~ %d です\n",shop_cnt-1);
       selected_shop = -1;
   }
 }
 fprintf(stderr,"%s を選択しました\n",shop[selected_shop]);
 
 strcpy(filename,figure[selected_shop]);
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
    fprintf(stderr,"指定された店の構造図 '%s' NOT FOUND.\n",figure[selected_shop]);
    return -1;
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

  fprintf(stderr,"店構造図を読込ました。\n");
  return 0;
}

char *GetShopName(){
  return &(shop[selected_shop][0]);
}
