#include <stdio.h>
#include "setting.h"


extern int ROW;
extern int COL;
extern point_t map2[MAXSIZE][MAXSIZE];
point_t *search();
void hop_check(point_t *node,int hop);



void dijkstra(point_t *start,int not_done){
  point_t *tmp1 = start;
  for(/*引数の値そのまま*/;not_done>0;not_done--){
    tmp1->done=1;
    if(tmp1->left!=NULL){
      hop_check(tmp1->left,tmp1->hop);
    }
    if(tmp1->right!=NULL){
      hop_check(tmp1->right,tmp1->hop);
    }
    if(tmp1->up!=NULL){
      hop_check(tmp1->up,tmp1->hop);
    }
    if(tmp1->down!=NULL){
      hop_check(tmp1->down,tmp1->hop);
    }
    tmp1=search();
  }
}

point_t *search(){
  int min=ROW*COL;
  int i,j;
   point_t *ret;

  for(i=0;i<ROW;i++){
    for(j=0;j<COL;j++){
      if(map2[i][j].hop<min&&map2[i][j].done!=1){
	min=map2[i][j].hop;
	ret = &map2[i][j];
      }
    }
  }

  return ret;
}



void hop_check(point_t *node,int hop){
    /*hop+1した値のほうが現在の値(距離)より小さいなら
     hop+1をその場所の距離とする*/
    if(node->hop>hop+1)
      node->hop=hop+1;
}


void initialize_hop(){
  int i,j;
   for(i=0;i<ROW;i++){
    for(j=0;j<COL;j++){
      map2[i][j].hop=ROW*COL;
      map2[i][j].done=0;
    }
   }
}
