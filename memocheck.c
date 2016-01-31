
#include "setting.h"

#define MAXCHARSIZE 400


/*買う品物(メモの内容)をしまっておく配列*/
char menu[MENUSIZE][MAXCHARSIZE];

/*店にある商品とその商品の棚を一致させるために製作 商品名と棚番号*/
typedef struct {
  char item[MAXCHARSIZE];
  int itemnum;
} SHOPITEMLIST;

SHOPITEMLIST shopitem[SHOPITEMSIZE];
int itemcount = 0;

/*メモに書いてあった品物で商品の位置番号しまっている*/
int position[MENUSIZE];

/*読み込んだ品物の数*/
int maxmenucount = 0;

void tokenAdd(char *);
void initshopitemlist();
void addshopitemlist();
void initposition();
/*品物名から場所の値を探す関数*/
int whereitem(char *);

/*
  int main() {
*/
int memocheck() {
  FILE *fp;
  char line[MAXCHARSIZE];
  char *ret;
  int i;

  /*メモしてあるファイルは memo.txt として読み込む*/
  fp = fopen("memo.txt","r");

  if(fp==NULL){/*memo.txtが見つからなかった*/
  fprintf(stderr,"ERROR! : memo.txtを作成し、商品名を入力してください\n");
  return -1;
}
  do {
    ret = fgets(line,MAXCHARSIZE,fp);
    if( ret != NULL ) {
      tokenAdd(line);
    }
  } while( ret != NULL );
  fclose(fp);

  initshopitemlist();
  addshopitemlist();
  initposition();
  for(i = 0; i < maxmenucount; i++) {
    position[i] = whereitem(menu[i]);

    printf("-----Memo Result-----\n");
    if(position[i] == -1) {
      printf("「%s」 は売ってないか見つかりませんでした.\n",menu[i]);
    } else {
      printf("menu[%d] = %s  position = %3d\n",i,menu[i],position[i]);
    }
    printf("---------------------\n");
  }
  
    return 0;
  
}


void tokenAdd(char *data) {
  /*"スペース" "," "改行コード"で分割*/
  char str[] = " ,\n";
  char *token[MAXCHARSIZE];
  int tokencount = 0;
  int i;

  token[tokencount] = strtok(data,str);
  do {
    token[++tokencount] = strtok(NULL,str);
  } while( token[tokencount] != NULL );

  for( i = 0; i < tokencount; i++ ) {
    if( maxmenucount >= MENUSIZE ) {
      fprintf(stderr,"Table is full!\n");
      exit(1);
    }
    /*読み込んだ品物をmenuにコピーする*/
    strcpy(menu[maxmenucount++],token[i]);
  }
}


void initshopitemlist() {
  int i;
  for(i = 0; i < SHOPITEMSIZE; i++) {
    strcpy(shopitem[i].item, "未登録");
    shopitem[i].itemnum = -1;
  }
}


void addshopitemlist() {
  int num, i = 0;
  /*
    10　パン
    20　お惣菜
    30　魚介
    40　乳製品
    50　肉類
    60　野菜
    70　豆腐
    80　インスタント類
    90　調味料
    110　酒類
    110　飲料
    120　お菓子類
    130　卵
  */
  /*
    copy use
    strcpy(shopitem[i].item, "");
    shopitem[i++].itemnum = num;
  */
  num = 10;
  strcpy(shopitem[i].item, "パン");
  shopitem[i++].itemnum = num;

  num = 20;
  strcpy(shopitem[i].item, "お惣菜");
  shopitem[i++].itemnum = num;

  num = 30;
  strcpy(shopitem[i].item, "魚");
  shopitem[i++].itemnum = num;
  strcpy(shopitem[i].item, "寿司");
  shopitem[i++].itemnum = num;

  num = 40;
  strcpy(shopitem[i].item, "牛乳");
  shopitem[i++].itemnum = num;
  strcpy(shopitem[i].item, "チーズ");
  shopitem[i++].itemnum = num;

  num = 50;
  strcpy(shopitem[i].item, "鶏肉");
  shopitem[i++].itemnum = num;
  strcpy(shopitem[i].item, "豚肉");
  shopitem[i++].itemnum = num;
  strcpy(shopitem[i].item, "牛肉");
  shopitem[i++].itemnum = num;
  strcpy(shopitem[i].item, "挽き肉");
  shopitem[i++].itemnum = num;
  strcpy(shopitem[i].item, "ソーセージ");
  shopitem[i++].itemnum = num;

  num = 60;
  strcpy(shopitem[i].item, "玉ねぎ");
  shopitem[i++].itemnum = num;
  strcpy(shopitem[i].item, "じゃがいも");
  shopitem[i++].itemnum = num;
  strcpy(shopitem[i].item, "白菜");
  shopitem[i++].itemnum = num;
  strcpy(shopitem[i].item, "もやし");
  shopitem[i++].itemnum = num;
  strcpy(shopitem[i].item, "キャベツ");
  shopitem[i++].itemnum = num;
  strcpy(shopitem[i].item, "レタス");
  shopitem[i++].itemnum = num;
  strcpy(shopitem[i].item, "小松菜");
  shopitem[i++].itemnum = num;
 
  num = 70;
  strcpy(shopitem[i].item, "豆腐");
  shopitem[i++].itemnum = num;

  num = 80;
  strcpy(shopitem[i].item, "カップ麺");
  shopitem[i++].itemnum = num;
  strcpy(shopitem[i].item, "パスタ");
  shopitem[i++].itemnum = num;
  strcpy(shopitem[i].item, "パスタソース");
  shopitem[i++].itemnum = num;

  num = 90;
  strcpy(shopitem[i].item, "しょうゆ");
  shopitem[i++].itemnum = num;
  strcpy(shopitem[i].item, "ソース");
  shopitem[i++].itemnum = num;
  strcpy(shopitem[i].item, "塩");
  shopitem[i++].itemnum = num;
  strcpy(shopitem[i].item, "こしょう");
  shopitem[i++].itemnum = num;
  strcpy(shopitem[i].item, "砂糖");
  shopitem[i++].itemnum = num;
  strcpy(shopitem[i].item, "ドレッシング");
  shopitem[i++].itemnum = num;

  num = 100;
  strcpy(shopitem[i].item, "お酒");
  shopitem[i++].itemnum = num;

  num = 110;
  strcpy(shopitem[i].item, "ジュース");
  shopitem[i++].itemnum = num;
  strcpy(shopitem[i].item, "コーラ");
  shopitem[i++].itemnum = num;
  strcpy(shopitem[i].item, "ソーダ");
  shopitem[i++].itemnum = num;

  num = 120;
  strcpy(shopitem[i].item, "お菓子");
  shopitem[i++].itemnum = num;

  num = 130;
  strcpy(shopitem[i].item, "たまご");
  shopitem[i++].itemnum = num;
  strcpy(shopitem[i].item, "卵");
  shopitem[i++].itemnum = num;

  itemcount = i;
}

void initposition() {
  int i;
  for(i = 0; i < MENUSIZE; i++) {
    position[i] = -1;
  }
}

int whereitem(char *data) {
  int i;

  for(i = 0; i < itemcount; i++) {
    /*見つかった*/
    if( strcmp(data,shopitem[i].item) == 0 ) {
      return shopitem[i].itemnum;
    }
  }
  /*見つからなかった*/
  return -1;
}


/* memo */
/*
  0　通り道
  1　通行不可
  2　入り口
  3
  4
  5　レジ
  6
  7
  8
  9
*/
