#define ROW 12
#define COL 13

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
