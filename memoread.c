#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHARSIZE 400
#define MENUSIZE 20

/*買う品物をしまっておく配列*/
char menu[MENUSIZE][MAXCHARSIZE];

/*読み込んだ品物の数*/
int maxmenucount = 0;

void tokenAdd(char *);

int main() {
  FILE *fp;
  char line[MAXCHARSIZE];
  char *ret;

  /*メモしてあるファイルは memo.txt として読み込む*/
  fp = fopen("memo.txt","r");
  do {
    ret = fgets(line,MAXCHARSIZE,fp);
    if( ret != NULL ) {
      tokenAdd(line);
    }
  } while( ret != NULL );
  fclose(fp);

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
    strcpy(menu[maxmenucount],token[i]);
    maxmenucount++;
    /*For debug*/
    /*デバッグ用に用意しただけです.*/
    printf("menu[%d] = %s\n", maxmenucount-1, menu[maxmenucount-1]);
  }
}

