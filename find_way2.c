#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "setting.h"

extern void dijkstra(point_t *,int);
extern point_t *search();
extern void hop_check(point_t*,int);
extern void initialize_hop();
extern int shopInput();

/*合わせ用*/
extern int position[];
extern int memocheck();

int map[MAXSIZE][MAXSIZE];/*店構造図*/
int ROW;
int COL;

point_t map2[MAXSIZE][MAXSIZE];

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
void print_hop(RC *from);/*ある地点からの距離*/

/*経路指示*/
void print_way(RC *from);


int main(int argc,char **argv){
  int i,j;
  /*入り口の座標を入れる変数*/
  RC *start;
  
  shopInput();
  
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

    }
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
#ifdef DEBUG
  print_shelfDist(2);
#endif
  
  /*買いたい品物初期化*/
  for(i=0;i<SHELF_MAX;i++)
    items[i]=0;

  /*買いたい品物登録*/
/*
  items[23]=1;
  items[84]=1;
  items[54]=1;
  items[43]=1;
  items[32]=1;
*/
int err;
  /*ここでmemocheckと合わせる*/
  err = memocheck();
  if(err!=0){
    return -1;
  }
 
  
  for(i = 0; i < MENUSIZE;i++) {
    if(position[i] != -1) {
      items[ position[i] ] = 1;
    }
  }
  
  /*マップ表示*/
   for(i=0;i<ROW;i++){
    for(j=0;j<COL;j++){
      printf("%3d ",map[i][j]);
    }printf("\n");
   }

  /*回る順番指示*/
  int cur_shelf=2;
  int nex_shelf=INIT_MAX;
  int total_dist=0;
  char buf[256];
 

  RC cur1,cur2;
  cur1.r=start->r;
  cur1.c=start->c;
  while(1){
    nex_shelf = next(cur_shelf);
    if(nex_shelf>=INIT_MAX)
      break;
    
    /*総距離計算*/
    total_dist+=shelf_dist[cur_shelf][nex_shelf];
    
    printf("Next is: %d \n",nex_shelf);
    cur_shelf=nex_shelf;
    
    /*行き方を指示*/
    
    
    initialize_hop();/*順番注意<*/
    map2[cur1.r][cur1.c].hop=0;/*順番注意<*/
    tmp1=&map2[cur1.r][cur1.c];
    /*
      node_from.r=i;
      node_from.c=j;
    */
    
    dijkstra(tmp1,not_done_node);
    
    for(i=0;i<ROW;i++){
      for(j=0;j<COL;j++){
	if(map[i][j]==nex_shelf){
	  cur2.r=i;
	  cur2.c=j;
	  break;
	}
      }
    }
    print_way(&cur2);
    /*行き方を指示(終)*/
    fprintf(stderr, "(?)購入できましたか? [press Enter]");
    fgets( buf, 256, stdin );
    cur1.r=cur2.r;
    cur1.c=cur1.c;
  }

  /*最後はレジ*/
  /*総距離計算*/
  total_dist+=shelf_dist[cur_shelf][5];
  
  printf("Next is 5(casher)\n");
  
  /*最も近いレジを探す*/
  

  /*総距離出力*/
  printf("total:%d\n",total_dist);
  

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
#ifdef DEBUG
      if(map2[i][j].hop!=ROW*COL){
	printf("%2d ",map2[i][j].hop);
      }else{
	printf("...");
      }
#endif
    }
#ifdef DEBUG
    printf("\n");
#endif
  }

}

void print_way(RC *from){
  int i,j;
  int min;
  RC min_rc;

  /*
  for(i=0;i<ROW;i++){
    for(j=0;j<COL;j++){
	fprintf(stderr,"%3d ",map2[i][j].hop);
    }
    fprintf(stderr,"\n");
    }*/

  i=from->r;
  j=from->c;
  #ifdef DEBUG
  fprintf(stderr,"[%d][%d] %d.%d\n",i,j,map2[i][j].hop,map[i][j]);
#endif
  while(map2[i][j].hop>0){
    min=999;
   
    if(map2[i+1][j].hop>=0&&map2[i+1][j].hop<min){
      min=map2[i+1][j].hop;
      min_rc.r=i+1;
      min_rc.c=j;
    }
    if(map2[i-1][j].hop>=0&&map2[i-1][j].hop<min){
      min=map2[i-1][j].hop;
      min_rc.r=i-1;
      min_rc.c=j;
    }
    if(map2[i][j+1].hop>=0&&map2[i][j+1].hop<min){
      min=map2[i][j+1].hop;
      min_rc.r=i;
      min_rc.c=j+1;
    }
    if(map2[i][j-1].hop>=0&&map2[i][j-1].hop<min){
      min=map2[i][j-1].hop;
      min_rc.r=i;
      min_rc.c=j-1;
    }
#ifdef DEBUG
    fprintf(stderr,"[%d][%d] %d.%d\n",min_rc.r,min_rc.c,map2[min_rc.r][min_rc.c].hop,map[min_rc.r][min_rc.c]);
#endif
     map2[i][j].hop=-999;
    i=min_rc.r;
    j=min_rc.c;
  }
   
  fprintf(stderr,"S現在地 G目的地 *経路 \n");
  for(i=0;i<ROW;i++){
    for(j=0;j<COL;j++){
      
      if(i==from->r&&j==from->c){
	fprintf(stderr," G ");
      }else if(map2[i][j].hop==-999){
	fprintf(stderr," * ");
      }else if(map2[i][j].hop==0){
	fprintf(stderr," S ");
      }else if(map[i][j]==5){
	fprintf(stderr," ¥ ");	
      }else if(map[i][j]>2){
	fprintf(stderr," | ");
      }else if(map[i][j]==0){
	fprintf(stderr,"   ");
      }else{
	fprintf(stderr," . ");
	}
      /*
      fprintf(stderr,"%3d ",map2[i][j].hop);
      */
    }
    fprintf(stderr,"\n");
  }
}

 void init_shelfDist(){
   int i,j;
   for(i=0;i<SHELF_MAX;i++){
     for(j=0;j<SHELF_MAX;j++){
       shelf_dist[i][j]=INIT_MAX;
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
#ifdef DEBUG
      printf("%d > %d(%d)",min,shelf_dist[from][i],i);
#endif
      min = shelf_dist[from][i];
      next_shelf=i;
    }
  }
  printf("\n");
 
  if(next_shelf!=INIT_MAX)items[next_shelf]=0;
  return next_shelf;
}
