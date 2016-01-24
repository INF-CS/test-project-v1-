#include <stdlib.h>
#include <stdio.h>
#include "setting.h"

#define SHELF_MAX 100
#define  INIT_MAX 999999
extern void dijkstra(point_t *,int);
extern point_t *search();
extern void hop_check(point_t*,int);
extern void initialize_hop();
int map[ROW][COL]=
  { {1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 },
    {1 ,50,51,52,53,54,55,60,61,62,63,1 },
    {1 ,42,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,64,1 },
    {1 ,41,0 ,43,44,0 ,0 ,0 ,0 ,0 ,65,1 },
    {1 ,40,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,66,1 },
    {1 ,35,0 ,0 ,0 ,1,83 ,85,1 ,0 ,20,1 },
    {1 ,34,0 ,0 ,0 ,1,82 ,84,1 ,0 ,21,1 },
    {1 ,33,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,22,1 },
    {1 ,32,1 ,1 ,5 ,1 ,5 ,1 ,0 ,0 ,23,1 },
    {1 ,1 ,0 ,0 ,0 ,0 ,0 ,81,0 ,0 ,24,1 },
    {1 ,1 ,1 ,1 ,1 ,1 ,1 ,2 ,27,26,25,1 },
    {1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 }};


point_t map2[ROW][COL];

/*買いたい商品のある棚*/
int items[SHELF_MAX];

/*ある場所からある場所への最短距離*/
int shelf_dist[SHELF_MAX][SHELF_MAX];
/*その表示*/
void print_shelfDist(int);
/*その初期化*/
void init_shelfDist();

/*ダイクストラ 未処理ノード数*/
int not_done_node=0;

point_t *search();
void print_hop();/*ある地点からの距離*/

int main(int argc,char **argv){
  int i,j;
  /*入り口の座標を入れる変数*/
  RC *start;

  for(i=0;i<ROW;i++){
    for(j=0;j<COL;j++){
      if(map[i][j]==2){
	start = (RC *)malloc(sizeof(RC));
	start->r=i;
	start->c=j;
      }
      
      map2[i][j].hop=ROW*COL;
      map2[i][j].done=0;
      if(i>0&&i<ROW-1&&j>0&&j<COL-1){
	not_done_node+=1;
	if(map[i+1][j]==0||map[i+1][j]>1){
	  map2[i][j].down=&map2[i+1][j];
	}else{
	  map2[i][j].down=NULL;
	}
	if(map[i-1][j]==0||map[i-1][j]>1){
	   map2[i][j].up=&map2[i-1][j];
	}else{
	   map2[i][j].up=NULL;
	}
	if(map[i][j+1]==0||map[i][j+1]>1){
	  map2[i][j].right=&map2[i][j+1];
	}else{
	  map2[i][j].right=NULL;
	}
	if(map[i][j-1]==0||map[i][j-1]>1){
	  map2[i][j].left=&map2[i][j-1];
	}else{
	  map2[i][j].left=NULL;
	} 
	
      }

      printf("%2d ",map[i][j]);
    }
    printf("\n");
  }

  /*棚間の距離初期化*/
  init_shelfDist();
  
  /*ダイクストラによる各地点から各地点への最短距離計算*/
  point_t *tmp1;
  RC node_from;
  int not_done_tmp;

 
  for(i=1;i<ROW-1;i++){
    for(j=1;j<COL-1;j++){
      if(map[i][j]>1){
	initialize_hop();/*順番注意<*/
	map2[i][j].hop=0;/*順番注意<*/
	tmp1=&map2[i][j];
	node_from.r=i;
	node_from.c=j;
    
	dijkstra(tmp1,not_done_node);
	print_hop(&node_from);

      }
    }
  }
  sleep(1);
  print_shelfDist(2);
  
  /*買いたい品物初期化*/
  for(i=0;i<SHELF_MAX;i++)
    items[i]=0;

  
  
  /*買いたい品物登録*/
  items[23]=1;
  items[84]=1;
  items[54]=1;
  items[43]=1;
  items[32]=1;

  
  int cur_shelf=2;
  int nex_shelf=INIT_MAX;
  int total_dist=0;
  printf("2 ");
  while(1){
    nex_shelf = next(cur_shelf);
    if(nex_shelf>=INIT_MAX)
      break;
    
    /*総距離計算*/
    total_dist+=shelf_dist[cur_shelf][nex_shelf];
    printf("-> %d ",nex_shelf);
    cur_shelf=nex_shelf;
  }

  /*最後はレジ*/
  /*総距離計算*/
  total_dist+=shelf_dist[cur_shelf][5];
  
  printf("-> 5\n");

  /*総距離出力*/
  printf("total:%d\n",total_dist);

  /*マップ表示*/
   for(i=0;i<ROW;i++){
    for(j=0;j<COL;j++){
      printf("%2d ",map[i][j]);
    }printf("\n");
   }
}

void print_shelfDist(int from){
  int i;
  for(i=0;i<SHELF_MAX;i++){
   printf("[%d => %d] %d\n",from,i,shelf_dist[from][i]);
  }
}

/*距離記録*/
void print_hop(RC *from){
  int i,j=0;
  for(i=0;i<ROW;i++){
    for(j=0;j<COL;j++){
      /*記録*/
      if(map[from->r][from->c]!=1){
	shelf_dist[map[from->r][from->c]][map[i][j]]=map2[i][j].hop;
      }
      /*出力(DEBUG)*/
      if(map2[i][j].hop!=ROW*COL){
	printf("%2d ",map2[i][j].hop);
      }else{
	printf("...");
      }
    }
    printf("\n");
  }

}

void init_shelfDist(){
  int i,j;
  for(i=0;i<SHELF_MAX;i++){
    for(j=0;j<SHELF_MAX;j++){
      shelf_dist[i][j]=SHELF_MAX*SHELF_MAX;
    }
  }
}

/*現在から回っていない最小の棚を探す*/
int next(int from){
  int i;
  int min=INIT_MAX;
  int next_shelf=INIT_MAX;
  for(i=0;i<SHELF_MAX;i++){
    if(shelf_dist[from][i]<min&&items[i]==1){
      printf("%d > %d(%d)",min,shelf_dist[from][i],i);
      min = shelf_dist[from][i];
      next_shelf=i;
    }
  }
  printf("\n");
 
  if(next_shelf!=INIT_MAX)items[next_shelf]=0;
  return next_shelf;
}
