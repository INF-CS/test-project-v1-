#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100
/*棚の最大番号*/
#define SHELF_MAX 500
#define  INIT_MAX 999999
/*メモの最大メニュー数*/
#define MENUSIZE 100
#define SHOPITEMSIZE 130
typedef struct{
  int r;
  int c;
}RC;

typedef struct point{
  struct point *left;
  struct point *right;
  struct point *up;
  struct point *down;
  int hop;
  int done;
}point_t;
