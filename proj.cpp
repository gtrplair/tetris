//utiliser tableau d'indices pour affichage blocs qu'on peut choisir

#include <iostream>

using namespace std;

struct bloc{

  int ** mat;
  int haut;
  int larg;
  int x;
  int y;
  int valide;
  int type;
};
typedef struct bloc bloc;

struct game{

  int ** board;
  int ** slide_board;
  int haut;
  int larg;
  int score;
  int type_board;
  bloc * tabl_bloc;
  int nb_bloc;
  int * indices;
  int choosing;
};
typedef struct game game;

// On suppose a<b
int rand_a_b(int a, int b){
    return rand()%(b-a) +a;
}

game * g;
bloc * current_b;



int can_move(bloc * b, game * g, int m, int n){

  int i, j;

  for(i=0 ; i<b->haut ; i++){
    for(j=0 ; j<b->larg ; j++){
      if(b->mat[i][j] && (i+b->y+m<0 || i+b->y+m>=g->haut || j+b->x+n<0 || j+b->x+n>=g->larg)){
	return 0;
      }
      if(b->mat[i][j] && (g->board[i+b->y+m][j+b->x+n] != 1)){
	return 0;
      }
    }
  }
  return 1;
}

int can_left(bloc * b, game * g){
  return can_move(b,g,0,-1);
}

int can_right(bloc * b, game * g){
    return can_move(b,g,0,1);
}

int can_top(bloc * b, game * g){
    return can_move(b,g,-1,0);
}

int can_bot(bloc * b, game * g){
    return can_move(b,g,1,0);
}



void left(bloc * b){
    b->x += -1;
    b->y += 0;
}
void right(bloc * b){
    b->x += 1;
    b->y += 0;
}
void top(bloc * b){
    b->x += 0;
    b->y += -1;
}
void bot(bloc * b){
    b->x += 0;
    b->y += 1;
}

void placement_bloc(bloc * b){

  int i, j;

  for(i=0 ; i<b->haut ; i++){
    for(j=0 ; j<b->larg ; j++){
      if(b->mat[i][j]){
	g->board[i+b->y][j+b->x] = 2;
      }
    }
  }
  g->choosing = 1;
}


int row_is_full(int l){

  int i = 0;
  while(!(g->board[l][i])){
    ++i;
  }
  while(g->board[l][i]){
    if(g->board[l][i] == 1){
      return 0;
    }
    ++i;
  }
  return 1;
}

int column_full(int c){

  int i = 0;
  while(!(g->board[i][c])){
    ++i;
  }
  while(g->board[i][c]){
    if(g->board[i][c] == 1){
      return 0;
    }
    ++i;
  }
  return 1;
}

void delete_col(int c){

  int i;

  for(i=0 ; i<g->haut ; i++){
    if(g->board[i][c]==2){
      g->board[i][c] = 1;
    }
  }
}

/*
void free_bloc(){

  int i;

  for(i=0 ; i<b->larg ; i++){
    free(b->mat[i]);
  }
  free(b->mat);
}


void free_board(){

  int i;

  for(i=0 ; i<g->haut ; i++){
    free(g->board[i]);
  }
  free(g->board);
}
*/

void alloc_bloc(bloc * b, int val){

  int i, j;

  b->mat = (int**) malloc(b->haut * sizeof(*(b->mat)));
  for(i=0 ; i<b->haut ; i++){
    b->mat[i] = (int*) malloc(b->larg * sizeof(int));
  }
  for(i=0 ; i<b->haut ; i++){
    for(j=0 ; j<b->larg ; j++){
      b->mat[i][j] = val;
    }
  }
}

void bloc1(bloc * b, int type){
  /* 0
     0 0
  */
  b->haut = 2;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b,1);
  b->mat[0][1] = 0;
  /**********************/
  b->y = 0;
  b->x = g->larg/2;
}

void bloc2(bloc * b, int type){
  /*   0
     0 0
  */
  b->haut = 2;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b,1);
  b->mat[0][0] = 0;
  /**********************/
  b->y = 0;
  b->x = g->larg/2-1;
}

void bloc3(bloc * b, int type){
  /* 0
     0 0 0
  */
  b->haut = 2;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b,1);
  b->mat[0][1] = 0;
  b->mat[0][2] = 0;
  /**********************/
  g->type_board==1 ? b->y=0 : b->y=1;
  b->x = g->larg/2-1;
}

void bloc4(bloc * b, int type){
  /* 0 0
       0
       0
  */
  b->haut = 3;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b,1);
  b->mat[1][0] = 0;
  b->mat[2][0] = 0;
  /**********************/
  g->type_board==1 ? b->y=0 : b->y=1;
  b->x = g->larg/2-1;
}

void bloc5(bloc * b, int type){
  /* 0
     0 0 
     0
  */
  b->haut = 3;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b,1);
  b->mat[0][1] = 0;
  b->mat[2][1] = 0;
  /**********************/
  b->y = 0;
  b->x = g->larg/2;
}

void bloc6(bloc * b, int type){
  /*   0
     0 0 0
  */
  b->haut = 2;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b,1);
  b->mat[0][0] = 0;
  b->mat[0][2] = 0;
  /**********************/
  b->y = 0;
  b->x = g->larg/2-1;
}

void bloc7(bloc * b, int type){
  /* 0 0
       0 0
  */
  b->haut = 2;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b,1);
  b->mat[0][2] = 0;
  b->mat[1][0] = 0;
  /**********************/
  g->type_board==1 ? (b->y=0, b->x=g->larg/2-1) : (b->y=1, b->x=g->larg/2);
}

void bloc8(bloc * b, int type){
  /* 0 
     0 0
       0
  */
  b->haut = 3;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b,1);
  b->mat[0][1] = 0;
  b->mat[2][0] = 0;
  /**********************/
  b->y = 0;
  b->x = g->larg/2;
}

void bloc9(bloc * b, int type){
  /* 0 
     0
     0
     0
  */
  b->haut = 4;
  b->larg = 1;
  b->type = type;
  alloc_bloc(b,1);
  /**********************/
  b->y = 0;
  b->x = g->larg/2;
}

void bloc10(bloc * b, int type){
  /* 0 0 
     0 0
  */
  b->haut = 2;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b,1);
  /**********************/
  g->type_board==1 ? b->y=0 : b->y=1;
  b->x=g->larg/2;
}

void bloc11(bloc * b, int type){
  /* 0 0
       0
  */
  b->haut = 2;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b,1);
  b->mat[1][0] = 0;
  /**********************/
  g->type_board==1 ? b->y=0 : b->y=1;
  b->x=g->larg/2;
}

void bloc12(bloc * b, int type){
  /* 0 0
     0
  */
  b->haut = 2;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b,1);
  b->mat[1][1] = 0;
  /**********************/
  g->type_board==1 ? b->y=0 : b->y=1;
  b->x=g->larg/2;
}

void bloc13(bloc * b, int type){
  /*     0
     0 0 0
  */
  b->haut = 2;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b,1);
  b->mat[0][0] = 0;
  b->mat[0][1] = 0;
  /**********************/
  g->type_board==1 ? b->y=0 : b->y=1;
  b->x = g->larg/2-1;
}

void bloc14(bloc * b, int type){
  /* 0
     0
     0 0
  */
  b->haut = 3;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b,1);
  b->mat[0][1] = 0;
  b->mat[1][1] = 0;
  /**********************/
  b->y = 0;
  b->x = g->larg/2;
}

void bloc15(bloc * b, int type){
  /*   0
     0 0
       0
  */
  b->haut = 3;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b,1);
  b->mat[0][0] = 0;
  b->mat[2][0] = 0;
  /**********************/
  b->y = 0;
  b->x = g->larg/2-1;
}

void bloc16(bloc * b, int type){
  /* 0 0 0
       0
  */
  b->haut = 2;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b,1);
  b->mat[1][0] = 0;
  b->mat[1][2] = 0;
  /**********************/
  g->type_board==1 ? (b->y=0, b->x=g->larg/2-1) : (b->y=1, b->x=g->larg/2-1);
}


void bloc17(bloc * b, int type){
  /*   0 0
     0 0
  */
  b->haut = 2;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b,1);
  b->mat[0][0] = 0;
  b->mat[1][2] = 0;
  /**********************/
  g->type_board==1 ? (b->y=0, b->x=g->larg/2-1) : (b->y=1, b->x=g->larg/2-2);
}

void bloc18(bloc * b, int type){
  /*   0
     0 0
     0
  */
  b->haut = 3;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b,1);
  b->mat[0][0] = 0;
  b->mat[2][1] = 0;
  /**********************/
  b->y=0;
  b->x=g->larg/2-1;
}

void bloc19(bloc * b, int type){
  /*  0 0 0 0
  */
  b->haut = 1;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b,1);
  /**********************/
  g->type_board==1 ? (b->y=0, b->x=g->larg/2-1) : (b->y=2, b->x=g->larg/2-1);
}

void bloc20(bloc * b, int type){
  /*  0
  */
  b->haut = 1;
  b->larg = 1;
  b->type = type;
  alloc_bloc(b,1);
  /**********************/
  b->y=0;
  b->x=g->larg/2;
}

void blocC1(bloc * b, int type){
  /*  0 0 0 0
      0 0 0 0
      0 0 0 0
      0 0 0 0
  */
  b->haut = 4;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b,1);
  /**********************/
  b->y=0;
  b->x=g->larg/2-1;
}

void blocC2(bloc * b, int type){
  /*    0 0 
      0 0 0 0
      0 0 0 0
        0 0 
  */
  b->haut = 4;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b,1);
  b->mat[0][0] = 0;
  b->mat[0][3] = 0;
  b->mat[3][0] = 0;
  b->mat[3][3] = 0;
  /**********************/
  b->y=0;
  b->x=g->larg/2-1;
}

void blocC3(bloc * b, int type){
  /*  0     0
      0     0
      0     0
      0 0 0 0
  */
  int i, j;
  b->haut = 4;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b,1);
  for(i=0 ; i<3 ; i++){
    for(j=1 ; j<3 ; j++){
      b->mat[i][j] = 0;
    }
  }
  /**********************/
  b->y=0;
  b->x=g->larg/2-1;
}

void blocC4(bloc * b, int type){
  /*  0 0 0 0
            0
            0
            0
  */
  int i, j;
  b->haut = 4;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b,1);
  for(i=1 ; i<4 ; i++){
    for(j=0 ; j<3 ; j++){
      b->mat[i][j] = 0;
    }
  }
  /**********************/
  b->y=0;
  b->x=g->larg/2-1;
}

void blocC5(bloc * b, int type){
  /*  0 0 0 0
      0 0 0 
  */
  b->haut = 2;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b,1);
  b->mat[1][3] = 0;
  /**********************/
  b->y=0;
  b->x=g->larg/2-1;
}

void blocC6(bloc * b, int type){
  /*  0 0 0
          0
          0
      0 0 0
  */
  int i, j;
  b->haut = 4;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b,1);
  for(i=1 ; i<3 ; i++){
    for(j=0 ; j<2 ; j++){
      b->mat[i][j] = 0;
    }
  }
  /**********************/
  b->y=0;
  b->x=g->larg/2-1;
}

void blocC7(bloc * b, int type){
  /*  0 0 
      0 0
      0 0   
      0 0
  */
  b->haut = 4;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b,1);
  /**********************/
  b->y=0;
  b->x=g->larg/2-1;
}

void blocC8(bloc * b, int type){
  /*  0 0 0 0 
      0 0 0 0
  */
  b->haut = 2;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b,1);
  b->y=0;
  b->x=g->larg/2-1;
}

void blocC9(bloc * b, int type){
  /*  0
      0
      0
      0
      0
  */
  b->haut = 5;
  b->larg = 1;
  b->type = type;
  alloc_bloc(b,1);
  /**********************/
  b->y=0;
  b->x=g->larg/2;
}

void blocC10(bloc * b, int type){
  /*  0 0 0 0 0 
      0       0
  */
  int i;
  b->haut = 2;
  b->larg = 5;
  b->type = type;
  alloc_bloc(b,1);
  for(i=1 ; i<4 ; i++){
    b->mat[1][i] = 0;
  }
  /**********************/
  b->y=0;
  b->x=g->larg/2-2;
}

void blocC11(bloc * b, int type){
  /*  0 0 0 0 0
  */
  b->haut = 1;
  b->larg = 5;
  b->type = type;
  alloc_bloc(b,1);
  /**********************/
  b->y=0;
  b->x=g->larg/2-2;
}

void blocC12(bloc * b, int type){
  /*  0     
      0     
      0     0
      0 0 0 0
  */
  int i, j;
  b->haut = 4;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b,1);
  for(i=0 ; i<3 ; i++){
    for(j=1 ; j<3 ; j++){
      b->mat[i][j] = 0;
    }
  }
  b->mat[0][3] = 0;
  b->mat[1][3] = 0;
  /**********************/
  b->y=0;
  b->x=g->larg/2-1;
}

void blocL1(bloc * b, int type){
  /*      0 0 
        0 0    
      0 0
      0 
  */
  int i, j;
  b->haut = 4;
  b->larg = 4;
  b->type = type;
  cout << "EEE" << endl;
  alloc_bloc(b,0);
  cout << "EEE" << endl;
  for(i=0 ; i<4 ; i++){
    for(j=3-i ; j>1-i && j>=0 ; j--){
      b->mat[i][j] = 1;
    }
  }
  /**********************/
  b->y=1;
  b->x=g->larg/2-3;
}

void blocL2(bloc * b, int type){
  /*  0 0 
        0 0    
          0 0
            0
  */
  int i, j;
  b->haut = 4;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b,0);
  for(i=0 ; i<4 ; i++){
    for(j=i ; j<2+i && j<4 ; j++){
      b->mat[i][j] = 1;
    }
  }
  /**********************/
  b->y=1;
  b->x=g->larg/2;
}

void blocL3(bloc * b, int type){
  /*  0 0 0 0
        0 0
        0 0
        0 0
  */
  int i, j;
  b->haut = 4;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b,1);
  for(i=1 ; i<4 ; i++){
    b->mat[i][0] = 0;
  }
  for(i=1 ; i<4 ; i++){
    b->mat[i][3] = 0;
  }
  /**********************/
  b->y=2;
  b->x=g->larg/2-1;
}

void blocL4(bloc * b, int type){
  /*  0     0
        0 0
        0 0
      0     0
  */
  int i, j;
  b->haut = 4;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b,0);
  for(i=0, j=0 ; i<4 ; i++, j++){
    b->mat[i][j] = 1;
    b->mat[i][3-j] = 1;
  }
  /**********************/
  b->y=2;
  b->x=g->larg/2-1;
}

void blocL5(bloc * b, int type){
  /*  0 0 0 0 0
        0 0 0
	  0
  */
  int i, j;
  b->haut = 3;
  b->larg = 5;
  b->type = type;
  alloc_bloc(b,0);
  for(i=0 ; i<3 ; i++){
    for(j=i ; j<5-i ; j++){
      b->mat[i][j] = 1;
    }
  }
  /**********************/
  b->y=2;
  b->x=g->larg/2-2;
}

void blocL6(bloc * b, int type){
  /*  0 0 0 0
      0 0 0 0
      0 0 0 0
      0 0 0 0
  */
  int i, j;
  b->haut = 4;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b,1);
  /**********************/
  b->y=2;
  b->x=g->larg/2-1;
}

void blocL7(bloc * b, int type){
  /*  0 
      0 0
        0 0
          0 0
  */
  int i, j;
  b->haut = 4;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b,0);
  for(i=0 ; i<4 ; i++){
    for(j=i ; j<i+2 && j<4 ; j++){
      b->mat[j][i] = 1;
    }
  }
  /**********************/
  b->y=0;
  b->x=g->larg/2;
}

void blocL8(bloc * b, int type){
  /*       0
         0 0
       0 0
     0 0
  */
  int i, j;
  b->haut = 4;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b,0);
  for(i=3 ; i>=0 ; i--){
    for(j=3-i ; j<5-i && j<4 ; j++){
      b->mat[j][i] = 1;
    }
  }
  /**********************/
  b->y=0;
  b->x=g->larg/2-3;
}

void blocL9(bloc * b, int type){
  /* 0
     0
     0
     0 
     0
  */
  int i, j;
  b->haut = 5;
  b->larg = 1;
  b->type = type;
  alloc_bloc(b,1);
  /**********************/
  b->y=0;
  b->x=g->larg/2;
}

void blocL10(bloc * b, int type){
  /*       0
     0 0 0 0
           0
  */
  int i;
  b->haut = 3;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b,1);
  for(i=0 ; i<3 ; i++){
    b->mat[0][i] = 0;
    b->mat[2][i] = 0;
  }
  /**********************/
  b->y=2;
  b->x=g->larg/2-2;
}

void blocL11(bloc * b, int type){
  /*  0 0 0 0 0
  */
  b->haut = 1;
  b->larg = 5;
  b->type = type;
  alloc_bloc(b,1);
  /**********************/
  b->y=2;
  b->x=g->larg/2-2;
}

void blocL12(bloc * b, int type){
  /*  0 0 0 0
            0
  */
  int i;
  b->haut = 2;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b,1);
  for(i=0 ; i<3 ; i++){
    b->mat[1][i] = 0;
  }
  /**********************/
  b->y=2;
  b->x=g->larg/2-1;
}

void blocL13(bloc * b, int type){
  /*  0 0
        0
	0
	0
  */
  int i;
  b->haut = 4;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b,1);
  for(i=1 ; i<4 ; i++){
    b->mat[i][0] = 0;
  }
  /**********************/
  b->y=1;
  b->x=g->larg/2;
}

void blocL14(bloc * b, int type){
  /*  0
      0
      0
      0 0
  */
  int i;
  b->haut = 4;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b,1);
  for(i=0 ; i<3 ; i++){
    b->mat[i][1] = 0;
  }
  /**********************/
  b->y=0;
  b->x=g->larg/2;
}

void blocT1(bloc * b, int type){
  /*  0
      0 0 0
          0
  */
  int i;
  b->haut = 3;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b,1);
  for(i=0 ; i<2 ; i++){
    b->mat[0][i+1] = 0;
    b->mat[2][i] = 0;
  }
  /**********************/
  b->y=1;
  b->x=g->larg/2-1;
}

void blocT2(bloc * b, int type){
  /*  0 0
        0 
        0 0
  */
  int i;
  b->haut = 3;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b,1);
  for(i=0 ; i<2 ; i++){
    b->mat[i+1][0] = 0;
    b->mat[i][2] = 0;
  }
  /**********************/
  b->y=1;
  b->x=g->larg/2-1;
}

void blocT3(bloc * b, int type){
  /*      0
      0 0 0
      0
  */
  int i;
  b->haut = 3;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b,1);
  for(i=0 ; i<2 ; i++){
    b->mat[0][i] = 0;
    b->mat[2][i+1] = 0;
  }
  /**********************/
  b->y=1;
  b->x=g->larg/2-1;
}

void blocT4(bloc * b, int type){
  /*    0 0
        0 
      0 0
  */
  int i;
  b->haut = 3;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b,1);
  for(i=0 ; i<2 ; i++){
    b->mat[i][0] = 0;
    b->mat[i+1][2] = 0;
  }
  /**********************/
  b->y=1;
  b->x=g->larg/2-1;
}

void blocT5(bloc * b, int type){
  /*      0
        0 
      0 
  */
  int i;
  b->haut = 3;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b,0);
  for(i=0 ; i<3 ; i++){
    b->mat[2-i][0+i] = 1;
  }
  /**********************/
  b->y=0;
  b->x=g->larg/2-2;
}

void blocT6(bloc * b, int type){
  /*  0
        0 
          0
  */
  int i;
  b->haut = 3;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b,0);
  for(i=0 ; i<3 ; i++){
    b->mat[i][i] = 1;
  }
  /**********************/
  b->y=0;
  b->x=g->larg/2;
}

void blocT7(bloc * b, int type){
  /*  0
      0 
      0
  */
  int i;
  b->haut = 3;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b,0);
  for(i=0 ; i<3 ; i++){
    b->mat[i][1] = 1;
  }
  /**********************/
  b->y=0;
  b->x=g->larg/2;
}

void blocT8(bloc * b, int type){
  /* 
     0 0 0
  */
  int i;
  b->haut = 3;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b,0);
  for(i=0 ; i<3 ; i++){
    b->mat[1][i] = 1;
  }
  /**********************/
  b->y=1;
  b->x=g->larg/2-1;
}

void blocT9(bloc * b, int type){
  /* 
     0
     0
  */
  int i;
  b->haut = 2;
  b->larg = 1;
  b->type = type;
  alloc_bloc(b,1);
  /**********************/
  b->y=0;
  b->x=g->larg/2;
}

void blocT10(bloc * b, int type){
  /*   0
     0 0 0
       0
  */
  int i;
  b->haut = 3;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b,0);
  for(i=0 ; i<3 ; i++){
    b->mat[i][1] = 1;
    b->mat[1][i] = 1;
  }
  /**********************/
  b->y=0;
  b->x=g->larg/2-1;
}

void blocT11(bloc * b, int type){
  /* 
      0 0
  */
  int i, j;
  b->haut = 1;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b,1);
  /**********************/
  b->y=1;
  b->x=g->larg/2;
}


void alloc_board(int m, int n){

  int i;
  g = (game*) malloc(sizeof(*g));
  g->larg = n;
  g->haut = m;
  g->score = 0;
  g->choosing = 0;
  g->board = (int**) malloc(m * sizeof(*(g->board)));
  g->slide_board = (int**) malloc(m * sizeof(*(g->board)));

  for(i=0 ; i<m ; i++){
    g->board[i] = (int*) malloc(n * sizeof(int));
    g->slide_board[i] = (int*) malloc(n * sizeof(int));
  }
}

void init_board(int val){

  int i, j;

  for(j=0 ; j<g->haut ; j++){
    for(i=0 ; i<g->larg ; i++){
      g->board[j][i] = val;
      g->slide_board[j][i] = val;
    }
  }
}

void display_board(){

  int i, j;

  for(j=0 ; j<g->haut ; j++){
    for(i=0 ; i<g->larg ; i++){
      cout << g->board[j][i] << "  ";
    }
    cout << endl ;
  }
}


void create_bloc(bloc * b, int type){

  cout << "C" << endl << endl;

  switch(type){
  case 1:
    bloc1(b,type);
    break;
  case 2:
    bloc2(b,type);
    break;
  case 3:
    bloc3(b,type);
    break;
  case 4:
    bloc4(b,type);
    break;
  case 5:
    bloc5(b,type);
    break;
  case 6:
    bloc6(b,type);
    break;
  case 7:
    bloc7(b,type);
    break;
  case 8:
    bloc8(b,type);
    break;
  case 9:
    bloc9(b,type);
    break;
  case 10:
    bloc10(b,type);
    break;
  case 11:
    bloc11(b,type);
    break;
  case 12:
    bloc12(b,type);
    break;
  case 13:
    bloc13(b,type);
    break;
  case 14:
    bloc14(b,type);
    break;
  case 15:
    bloc15(b,type);
    break;
  case 16:
    bloc16(b,type);
    break;
  case 17:
    bloc17(b,type);
    break;
  case 18:
    bloc18(b,type);
    break;
  case 19:
    bloc19(b,type);
    break;
  case 20:
    bloc20(b,type);
    break;
  case 21:
    blocC1(b,type);
    break;
  case 22:
    blocC2(b,type);
    break;
  case 23:
    blocC3(b,type);
    break;
  case 24:
    blocC4(b,type);
    break;
  case 25:
    blocC5(b,type);
    break;
  case 26:
    blocC6(b,type);
    break;
  case 27:
    blocC7(b,type);
    break;
  case 28:
    blocC8(b,type);
    break;
  case 29:
    blocC9(b,type);
    break;
  case 30:
    blocC10(b,type);
    break;
  case 31:
    blocC11(b,type);
    break;
  case 32:
    blocC12(b,type);
    break;
  case 33:
    blocL1(b,type);
    break;
  case 34:
    blocL2(b,type);
    break;
  case 35:
    blocL3(b,type);
    break;
  case 36:
    blocL4(b,type);
    break;
  case 37:
    blocL5(b,type);
    break;
  case 38:
    blocL6(b,type);
    break;
  case 39:
    blocL7(b,type);
    break;
  case 40:
    blocL8(b,type);
    break;
  case 41:
    blocL9(b,type);
    break;
  case 42:
    blocL10(b,type);
    break;
  case 43:
    blocL11(b,type);
    break;
  case 44:
    blocL12(b,type);
    break;
  case 45:
    blocL13(b,type);
    break;
  case 46:
    blocL14(b,type);
    break;
  case 47:
    blocT1(b,type);
    break;
  case 48:
    blocT2(b,type);
    break;
  case 49:
    blocT3(b,type);
    break;
  case 50:
    blocT4(b,type);
    break;
  case 51:
    blocT5(b,type);
    break;
  case 52:
    blocT6(b,type);
    break;
  case 53:
    blocT7(b,type);
    break;
  case 54:
    blocT8(b,type);
    break;
  case 55:
    blocT9(b,type);
    break;
  case 56:
    blocT10(b,type);
    break;
  case 57:
    blocT11(b,type);
    break;
  }
}



void init_tabl_bloc(game * g){

  int i;
  
  if(g->type_board==1){
    g->nb_bloc = 32;
    g->tabl_bloc = (bloc*) malloc(32 * sizeof(*g->tabl_bloc));
    for(i=20 ; i<32 ; i++){
      create_bloc(&(g->tabl_bloc[i]),i+1);
    }
  }
  else if(g->type_board==2){
    g->nb_bloc = 34;
    g->tabl_bloc = (bloc*) malloc(34 * sizeof(*g->tabl_bloc));
    for(i=20 ; i<34 ; i++){
      create_bloc(&(g->tabl_bloc[i]),i+13);
    }
  }
  else{
    g->nb_bloc = 31;
    g->tabl_bloc = (bloc*) malloc(31 * sizeof(*g->tabl_bloc));
    for(i=20 ; i<31 ; i++){
      create_bloc(&(g->tabl_bloc[i]),i+27);
    }
  }
  for(i=0 ; i<20 ; i++){
    create_bloc(&(g->tabl_bloc[i]),i+1);
  }
}

void create_board(int type, int width){

  int i, j, a, b;
  int n, row, c, x, y;


  
  
  switch(type){
  case 1:

    alloc_board(width/2+1,width);
    init_board(0);
    g->type_board = type;
    init_tabl_bloc(g);


    for(j=0 ; j<width/2+1 ; j++){
      for(i=width/2-j ; i<=width/2+j ; i++){
	g->board[j][i] = 1;
	g->slide_board[j][i] = 1;
      }
    }
    break;



    
    /*
    for(j=3 ; j<18 ; j++){
      for(i=0 ; i<21 ; i++){
	g->board[j][i] = 1;
	g->slide_board[j][i] = 1;
      }
    }
    for(j=0, a=7 ; j<3 ; j++, a++){
      for(i=10-a ; i<=10+a ; i++){
	g->board[j][i] = 1;
	g->slide_board[j][i] = 1;
      }
    }
    for(j=20, a=7 ; j>17 ; j--, a++){
      for(i=10-a ; i<=10+a ; i++){
	g->board[j][i] = 1;
	g->slide_board[j][i] = 1;
      }
    }
    break;
    */
    
  case 2:
    alloc_board(width,width);
    init_board(0);
    g->type_board = type;
    init_tabl_bloc(g);

    for(j=0 ; j<width/2+1 ; j++){
      for(i=width/2-j ; i<=width/2+j ; i++){
	g->board[j][i] = 1;
	g->slide_board[j][i] = 1;
      }
    }
    for(j=width-1, a=0 ; j>width/2 ; j--, a++){
      for(i=width/2-a ; i<=width/2+a ; i++){
	g->board[j][i] = 1;
	g->slide_board[j][i] = 1;
      }
    }
    break;

  case 3:

    alloc_board(width,width);
    width /= 2;
    init_board(0);
    g->type_board = type;
    init_tabl_bloc(g);
    n = 2*width+1;

    for (i=0; i<n; i++) {
      for (j=0; j<n; j++) {
	cout << i << " / " << j << endl;
	
        x = i-width; 
        y = j-width; 

        if (x*x + y*y <= width*width+1 ){
	  g->board[i][j] = 1;
	  //g->slide_board[i+width][j+width] = 1;
	}
      }
    }
    break;

  }
}

void display_bloc(bloc * b){

  int i, j;

  for(i=0 ; i<b->haut ; i++){
    for(j=0 ; j<b->larg ; j++){
      cout << b->mat[i][j] << "  ";
    }
    cout << endl;
  }
  cout << endl;
  cout << endl; 
}





void bestiaire(int debut, int fin){

  bloc * b;
  int i;

  for(i=debut ; i<=fin ; i++){
    b = (bloc*) malloc(sizeof(*b));
    cout << "B" << endl; 
    create_bloc(b,i);
    display_bloc(b);
    free(b);
  }
}

void add_bloc(bloc * b, game * g){

  int i, j;
  cout << "ADDBLOC" << endl << b->y << endl << b->x << endl << endl;
  for(i=0 ; i<b->haut ; i++){
    for(j=0 ; j<b->larg ; j++){
      if(b->mat[i][j]){
	g->board[b->y+i][b->x+j] = 8;
      }
    }
  }
}

void test_init_blocs(int width){

  int i, j;
  bloc * b;

  for(i=1 ; i<4 ; i++){
    for(j=1 ; j<21 ; j++){
      g = (game*) malloc(sizeof(*g));
      create_board(i, width);
      cout << "i == " << i << endl;
      cout << "j == " << j << endl << endl;
      b = (bloc*) malloc(sizeof(*b));
      cout << "FREE 1" << endl;
      create_bloc(b,j);
      add_bloc(b,g);
      display_board();
      cout << endl << endl;
      display_bloc(b);
      free(b);
      free(g);

    }
  }
}



void display_bloc_tabl(){

  int i;

  for(i=0 ; i<g->nb_bloc ; i++){
    cout << i << endl;
    display_bloc(&(g->tabl_bloc[i]));
  }
}

void clear_slide_board(){

  int i, j;

  for(i=0 ; i<g->haut ; i++){
    for(j=0 ; j<g->larg ; j++){
      if(g->slide_board[i][j]>1){
	g->slide_board[i][j] = 1;
      }
    }
  }
}

/*
void init_row_board(int ** tabl, int row, int val){

}

void build_slide_board(){

  int i;

  for(i=0 ; i<g->haut ; i++){
    if(row_is_full(i)){
    }
  }
}
*/

/*
int main(){

  int i, width;
  cin >> width;


  /*
    create_board(3);
    blocT5( );
    add_bloc();
    display_board();
    cout << endl << endl;
    display_bloc();
  
    test_init_blocs();

    cout << "A" << endl;
  
    bestiaire(57,57);

    for(i=0 ; i<10 ; i++){
    cout << rand_a_b(0,100);
    }
    create_board(1);
    init_tabl_bloc(g);
    display_bloc_tabl();
 

  current_b = (bloc*) malloc(sizeof(*current_b));
  create_board(2,width);
  display_board();
  cout << "222" << endl;
  blocL1(current_b);
  cout << "222" << endl;
  //add_bloc(current_b, g);
  display_board();
  cout << can_right(current_b,g) << endl;
  cout << can_left(current_b,g) << endl;
  cout << can_top(current_b,g) << endl;
  cout << can_bot(current_b,g) << endl;
  add_bloc(current_b, g);
  display_board();
  free(g);
 
}
*/
