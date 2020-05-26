// utiliser tableau d'indices pour affichage blocs qu'on peut choisir
// baser l'affichage bloc sur une fonction qui affiche seulement un carré
// (facilite le slide, et l'affichage du board);
//

#include <unistd.h>

#include <iostream>

using namespace std;

struct value_sb{
  int slide_value;
  int indice_color;
};
typedef struct value_sb value_sb;

struct rgb {
  double r;
  double g;
  double b;
};
typedef struct rgb rgb;

struct bloc {
  int** mat;
  int haut;
  int larg;
  int x;
  int y;
  int valide;
  int type;
};
typedef struct bloc bloc;

struct game {
  int** board;
  value_sb** slide_board;
  int haut;
  int larg;
  int score;
  int type_board;
  bloc* tabl_bloc;
  rgb* color_tabl;
  int nb_bloc;
  int* indices;
  int choosing;
  int anim_slide;
  float slide;
};
typedef struct game game;

// On suppose a<b
int rand_a_b(int a, int b) {
  return rand() % (b - a) + a;
}

game* g;
bloc* current_b;
int indice_bloc = 0;

void init_color_tabl() {
  int i;
  srand(time(NULL));

  g->color_tabl = (rgb*)malloc(g->nb_bloc * sizeof(*(g->color_tabl)));
  for (i = 0; i < g->nb_bloc; i++) {
    g->color_tabl[i].r =
        1 / (double(rand_a_b(2, 10))) + 1 / (double(rand_a_b(2, 10)));
    g->color_tabl[i].g =
        1 / (double(rand_a_b(2, 10))) + 1 / (double(rand_a_b(2, 10)));
    g->color_tabl[i].b =
        1 / (double(rand_a_b(2, 10))) + 1 / (double(rand_a_b(2, 10)));
    cout << i << endl;
    cout << g->color_tabl[i].r << " / " << g->color_tabl[i].g << " / "
         << g->color_tabl[i].b << endl
         << endl;
  }
}

void color_table() {
  int i = 0;
  int color_table[71][3];

  color_table[i][0] = 100;
  color_table[i][1] = 100;
  color_table[i][2] = 100;
  i++;

  color_table[i][0] = 0;
  color_table[i][1] = 0;
  color_table[i][2] = 255;
  i++;

  color_table[i][0] = 255;
  color_table[i][1] = 0;
  color_table[i][2] = 0;
  i++;

  color_table[i][0] = 1;
  color_table[i][1] = 255;
  color_table[i][2] = 254;
  i++;

  color_table[i][0] = 255;
  color_table[i][1] = 166;
  color_table[i][2] = 254;
  i++;

  color_table[i][0] = 255;
  color_table[i][1] = 219;
  color_table[i][2] = 102;
  i++;

  color_table[i][0] = 0;
  color_table[i][1] = 100;
  color_table[i][2] = 1;
  i++;

  color_table[i][0] = 1;
  color_table[i][1] = 0;
  color_table[i][2] = 103;
  i++;

  color_table[i][0] = 149;
  color_table[i][1] = 0;
  color_table[i][2] = 58;
  i++;

  color_table[i][0] = 0;
  color_table[i][1] = 125;
  color_table[i][2] = 181;
  i++;

  color_table[i][0] = 255;
  color_table[i][1] = 0;
  color_table[i][2] = 246;
  i++;

  color_table[i][0] = 255;
  color_table[i][1] = 238;
  color_table[i][2] = 232;
  i++;

  color_table[i][0] = 119;
  color_table[i][1] = 77;
  color_table[i][2] = 0;
  i++;

  color_table[i][0] = 144;
  color_table[i][1] = 251;
  color_table[i][2] = 146;
  i++;

  color_table[i][0] = 0;
  color_table[i][1] = 118;
  color_table[i][2] = 255;
  i++;

  color_table[i][0] = 213;
  color_table[i][1] = 255;
  color_table[i][2] = 0;
  i++;

  color_table[i][0] = 255;
  color_table[i][1] = 147;
  color_table[i][2] = 126;
  i++;

  color_table[i][0] = 106;
  color_table[i][1] = 130;
  color_table[i][2] = 108;
  i++;

  color_table[i][0] = 255;
  color_table[i][1] = 2;
  color_table[i][2] = 157;
  i++;

  color_table[i][0] = 254;
  color_table[i][1] = 137;
  color_table[i][2] = 0;
  i++;

  color_table[i][0] = 122;
  color_table[i][1] = 71;
  color_table[i][2] = 130;
  i++;

  color_table[i][0] = 126;
  color_table[i][1] = 45;
  color_table[i][2] = 210;
  i++;

  color_table[i][0] = 133;
  color_table[i][1] = 169;
  color_table[i][2] = 0;
  i++;

  color_table[i][0] = 255;
  color_table[i][1] = 0;
  color_table[i][2] = 86;
  i++;

  color_table[i][0] = 164;
  color_table[i][1] = 36;
  color_table[i][2] = 0;
  i++;

  color_table[i][0] = 0;
  color_table[i][1] = 174;
  color_table[i][2] = 126;
  i++;

  color_table[i][0] = 104;
  color_table[i][1] = 61;
  color_table[i][2] = 59;
  i++;

  color_table[i][0] = 189;
  color_table[i][1] = 198;
  color_table[i][2] = 255;
  i++;

  color_table[i][0] = 38;
  color_table[i][1] = 52;
  color_table[i][2] = 0;
  i++;

  color_table[i][0] = 189;
  color_table[i][1] = 211;
  color_table[i][2] = 147;
  i++;

  color_table[i][0] = 0;
  color_table[i][1] = 185;
  color_table[i][2] = 23;
  i++;

  color_table[i][0] = 158;
  color_table[i][1] = 0;
  color_table[i][2] = 142;
  i++;

  color_table[i][0] = 0;
  color_table[i][1] = 174;
  color_table[i][2] = 126;
  i++;

  color_table[i][0] = 104;
  color_table[i][1] = 61;
  color_table[i][2] = 59;
  i++;

  color_table[i][0] = 189;
  color_table[i][1] = 198;
  color_table[i][2] = 255;
  i++;

  color_table[i][0] = 38;
  color_table[i][1] = 52;
  color_table[i][2] = 0;
  i++;

  color_table[i][0] = 189;
  color_table[i][1] = 211;
  color_table[i][2] = 147;
  i++;

  color_table[i][0] = 0;
  color_table[i][1] = 185;
  color_table[i][2] = 23;
  i++;

  color_table[i][0] = 158;
  color_table[i][1] = 0;
  color_table[i][2] = 142;
  i++;

  color_table[i][0] = 0;
  color_table[i][1] = 21;
  color_table[i][2] = 68;
  i++;

  color_table[i][0] = 194;
  color_table[i][1] = 140;
  color_table[i][2] = 159;
  i++;

  color_table[i][0] = 255;
  color_table[i][1] = 116;
  color_table[i][2] = 163;
  i++;

  color_table[i][0] = 1;
  color_table[i][1] = 208;
  color_table[i][2] = 255;
  i++;

  color_table[i][0] = 0;
  color_table[i][1] = 71;
  color_table[i][2] = 84;
  i++;

  color_table[i][0] = 229;
  color_table[i][1] = 111;
  color_table[i][2] = 254;
  i++;

  color_table[i][0] = 120;
  color_table[i][1] = 130;
  color_table[i][2] = 49;
  i++;

  color_table[i][0] = 14;
  color_table[i][1] = 76;
  color_table[i][2] = 161;
  i++;

  color_table[i][0] = 145;
  color_table[i][1] = 208;
  color_table[i][2] = 203;
  i++;

  color_table[i][0] = 190;
  color_table[i][1] = 153;
  color_table[i][2] = 112;
  i++;

  color_table[i][0] = 150;
  color_table[i][1] = 138;
  color_table[i][2] = 232;
  i++;

  color_table[i][0] = 187;
  color_table[i][1] = 136;
  color_table[i][2] = 0;
  i++;

  color_table[i][0] = 67;
  color_table[i][1] = 0;
  color_table[i][2] = 44;
  i++;

  color_table[i][0] = 222;
  color_table[i][1] = 255;
  color_table[i][2] = 116;
  i++;

  color_table[i][0] = 0;
  color_table[i][1] = 255;
  color_table[i][2] = 198;
  i++;

  color_table[i][0] = 255;
  color_table[i][1] = 229;
  color_table[i][2] = 2;
  i++;

  color_table[i][0] = 98;
  color_table[i][1] = 14;
  color_table[i][2] = 0;
  i++;

  color_table[i][0] = 0;
  color_table[i][1] = 143;
  color_table[i][2] = 156;
  i++;

  color_table[i][0] = 152;
  color_table[i][1] = 255;
  color_table[i][2] = 82;
  i++;

  color_table[i][0] = 117;
  color_table[i][1] = 255;
  color_table[i][2] = 177;
  i++;

  color_table[i][0] = 181;
  color_table[i][1] = 0;
  color_table[i][2] = 255;
  i++;

  color_table[i][0] = 0;
  color_table[i][1] = 255;
  color_table[i][2] = 120;
  i++;

  color_table[i][0] = 255;
  color_table[i][1] = 110;
  color_table[i][2] = 65;
  i++;

  color_table[i][0] = 0;
  color_table[i][1] = 95;
  color_table[i][2] = 57;
  i++;

  color_table[i][0] = 107;
  color_table[i][1] = 104;
  color_table[i][2] = 130;
  i++;

  color_table[i][0] = 95;
  color_table[i][1] = 173;
  color_table[i][2] = 78;
  i++;

  color_table[i][0] = 167;
  color_table[i][1] = 87;
  color_table[i][2] = 64;
  i++;

  color_table[i][0] = 165;
  color_table[i][1] = 255;
  color_table[i][2] = 210;
  i++;

  color_table[i][0] = 255;
  color_table[i][1] = 177;
  color_table[i][2] = 103;
  i++;

  color_table[i][0] = 0;
  color_table[i][1] = 155;
  color_table[i][2] = 255;
  i++;

  color_table[i][0] = 232;
  color_table[i][1] = 94;
  color_table[i][2] = 190;

  for (i = 0; i < g->nb_bloc; i++) {
    g->color_tabl[i].r =
        (float)color_table[i][0]/255;
    g->color_tabl[i].g =
        (float)color_table[i][1]/255;
    g->color_tabl[i].b =
        (float)color_table[i][2]/255;
  }
}

int can_move(bloc* b, game* g, int m, int n) {
  int i, j;

  for (i = 0; i < b->haut; i++) {
    for (j = 0; j < b->larg; j++) {
      if (b->mat[i][j] && (i + b->y + m < 0 || i + b->y + m >= g->haut ||
                           j + b->x + n < 0 || j + b->x + n >= g->larg)) {
        return 0;
      }
      if (b->mat[i][j] && (g->board[i + b->y + m][j + b->x + n] != 1)) {
        return 0;
      }
    }
  }
  return 1;
}

int can_left(bloc* b, game* g) {
  return can_move(b, g, 0, -1);
}

int can_right(bloc* b, game* g) {
  return can_move(b, g, 0, 1);
}

int can_top(bloc* b, game* g) {
  return can_move(b, g, -1, 0);
}

int can_bot(bloc* b, game* g) {
  return can_move(b, g, 1, 0);
}

void left(bloc* b) {
  b->x += -1;
  b->y += 0;
}
void right(bloc* b) {
  b->x += 1;
  b->y += 0;
}
void top(bloc* b) {
  b->x += 0;
  b->y += -1;
}
void bot(bloc* b) {
  b->x += 0;
  b->y += 1;
}

void placement_bloc(bloc* b) {
  int i, j;

  for (i = 0; i < b->haut; i++) {
    for (j = 0; j < b->larg; j++) {
      if (b->mat[i][j]) {
        g->board[i + b->y][j + b->x] = indice_bloc + 2;
      }
    }
  }
}

void valeur_row_slideboard(int row){

  int i;
  
  for(i=0 ; i<g->larg ; i++){
    if(g->slide_board[row][i].slide_value == 3){
      g->slide_board[row][i].slide_value = 2;
    }
  }
}

void init_slide_val(int col){
  
  int add = 0;
  int j;

  for(j=g->haut-1 ; j>=0 ; j--){
    if(g->slide_board[j][col].slide_value==2){
      ++add;
    }
    else if(g->board[j][col]>1){
      g->slide_board[j][col].slide_value += add;
      if(g->slide_board[j][col].slide_value>3){
        g->slide_board[j][col].indice_color = g->board[j][col]-2;
        g->board[j][col]=1;
      }
    }
  }
}

int row_is_full(int l) {
  int i = 0;
  while (!(g->board[l][i])) {
    ++i;
  }
  while (g->board[l][i]) {
    if (g->board[l][i] == 1) {
      return 0;
    }
    ++i;
  }
  return 1;
}

int column_full(int c) {
  int i = 0;
  while (i < g->haut && !(g->board[i][c])) {
    ++i;
  }
  while (i < g->haut && g->board[i][c]) {
    if (g->board[i][c] == 1) {
      return 0;
    }
    ++i;
  }
  return 1;
}

void set_slide_board(){

  int i;

  for(i=0 ; i<g->larg ; i++){
    cout << "GRIS" << i << endl;
    init_slide_val(i);
  }
}


void delete_col(int c) {
  int i;

  for (i = 0; i < g->haut; i++) {
    if (g->board[i][c] > 1) {
      g->board[i][c] = 1;
    }
  }
}

void delete_row(int r) {
  int i;

  for (i = 0; i < g->larg; i++) {
    if (g->board[r][i] > 1) {
      g->board[r][i] = 1;
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

void alloc_bloc(bloc* b, int val) {
  int i, j;

  b->mat = (int**)malloc(b->haut * sizeof(*(b->mat)));
  for (i = 0; i < b->haut; i++) {
    b->mat[i] = (int*)malloc(b->larg * sizeof(int));
  }
  for (i = 0; i < b->haut; i++) {
    for (j = 0; j < b->larg; j++) {
      b->mat[i][j] = val;
    }
  }
}

void bloc1(bloc* b, int type) {
  /* 0
     0 0
  */
  b->haut = 2;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b, 1);
  b->mat[0][1] = 0;
  /**********************/
  b->y = 0;
  b->x = g->larg / 2;
}

void bloc2(bloc* b, int type) {
  /*   0
     0 0
  */
  b->haut = 2;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b, 1);
  b->mat[0][0] = 0;
  /**********************/
  b->y = 0;
  b->x = g->larg / 2 - 1;
}

void bloc3(bloc* b, int type) {
  /* 0
     0 0 0
  */
  b->haut = 2;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b, 1);
  b->mat[0][1] = 0;
  b->mat[0][2] = 0;
  /**********************/
  g->type_board == 3 ? b->y = 0 : b->y = 1;
  b->x = g->larg / 2 - 1;
}

void bloc4(bloc* b, int type) {
  /* 0 0
       0
       0
  */
  b->haut = 3;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b, 1);
  b->mat[1][0] = 0;
  b->mat[2][0] = 0;
  /**********************/
  g->type_board == 3 ? b->y = 0 : b->y = 1;
  b->x = g->larg / 2 - 1;
}

void bloc5(bloc* b, int type) {
  /* 0
     0 0
     0
  */
  b->haut = 3;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b, 1);
  b->mat[0][1] = 0;
  b->mat[2][1] = 0;
  /**********************/
  b->y = 0;
  b->x = g->larg / 2;
}

void bloc6(bloc* b, int type) {
  /*   0
     0 0 0
  */
  b->haut = 2;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b, 1);
  b->mat[0][0] = 0;
  b->mat[0][2] = 0;
  /**********************/
  b->y = 0;
  b->x = g->larg / 2 - 1;
}

void bloc7(bloc* b, int type) {
  /* 0 0
       0 0
  */
  b->haut = 2;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b, 1);
  b->mat[0][2] = 0;
  b->mat[1][0] = 0;
  /**********************/
  g->type_board == 3 ? (b->y = 0, b->x = g->larg / 2 - 1)
                     : (b->y = 1, b->x = g->larg / 2);
}

void bloc8(bloc* b, int type) {
  /* 0
     0 0
       0
  */
  b->haut = 3;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b, 1);
  b->mat[0][1] = 0;
  b->mat[2][0] = 0;
  /**********************/
  b->y = 0;
  b->x = g->larg / 2;
}

void bloc9(bloc* b, int type) {
  /* 0
     0
     0
     0
  */
  b->haut = 4;
  b->larg = 1;
  b->type = type;
  alloc_bloc(b, 1);
  /**********************/
  b->y = 0;
  b->x = g->larg / 2;
}

void bloc10(bloc* b, int type) {
  /* 0 0
     0 0
  */
  b->haut = 2;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b, 1);
  /**********************/
  g->type_board == 3 ? b->y = 0 : b->y = 1;
  b->x = g->larg / 2;
}

void bloc11(bloc* b, int type) {
  /* 0 0
       0
  */
  b->haut = 2;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b, 1);
  b->mat[1][0] = 0;
  /**********************/
  g->type_board == 3 ? b->y = 0 : b->y = 1;
  b->x = g->larg / 2;
}

void bloc12(bloc* b, int type) {
  /* 0 0
     0
  */
  b->haut = 2;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b, 1);
  b->mat[1][1] = 0;
  /**********************/
  g->type_board == 3 ? b->y = 0 : b->y = 1;
  b->x = g->larg / 2;
}

void bloc13(bloc* b, int type) {
  /*     0
     0 0 0
  */
  b->haut = 2;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b, 1);
  b->mat[0][0] = 0;
  b->mat[0][1] = 0;
  /**********************/
  g->type_board == 3 ? b->y = 0 : b->y = 1;
  b->x = g->larg / 2 - 1;
}

void bloc14(bloc* b, int type) {
  /* 0
     0
     0 0
  */
  b->haut = 3;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b, 1);
  b->mat[0][1] = 0;
  b->mat[1][1] = 0;
  /**********************/
  b->y = 0;
  b->x = g->larg / 2;
}

void bloc15(bloc* b, int type) {
  /*   0
     0 0
       0
  */
  b->haut = 3;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b, 1);
  b->mat[0][0] = 0;
  b->mat[2][0] = 0;
  /**********************/
  b->y = 0;
  b->x = g->larg / 2 - 1;
}

void bloc16(bloc* b, int type) {
  /* 0 0 0
       0
  */
  b->haut = 2;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b, 1);
  b->mat[1][0] = 0;
  b->mat[1][2] = 0;
  /**********************/
  g->type_board == 3 ? (b->y = 0, b->x = g->larg / 2 - 1)
                     : (b->y = 1, b->x = g->larg / 2 - 1);
}

void bloc17(bloc* b, int type) {
  /*   0 0
     0 0
  */
  b->haut = 2;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b, 1);
  b->mat[0][0] = 0;
  b->mat[1][2] = 0;
  /**********************/
  g->type_board == 3 ? (b->y = 0, b->x = g->larg / 2 - 1)
                     : (b->y = 1, b->x = g->larg / 2 - 2);
}

void bloc18(bloc* b, int type) {
  /*   0
     0 0
     0
  */
  b->haut = 3;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b, 1);
  b->mat[0][0] = 0;
  b->mat[2][1] = 0;
  /**********************/
  b->y = 0;
  b->x = g->larg / 2 - 1;
}

void bloc19(bloc* b, int type) {
  /*  0 0 0 0
   */
  b->haut = 1;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b, 1);
  /**********************/
  g->type_board == 3 ? (b->y = 1, b->x = g->larg / 2 - 1)
                     : (b->y = 2, b->x = g->larg / 2 - 1);
}

void bloc20(bloc* b, int type) {
  /*  0
   */
  b->haut = 1;
  b->larg = 1;
  b->type = type;
  alloc_bloc(b, 1);
  /**********************/
  b->y = 0;
  b->x = g->larg / 2;
}

void blocC1(bloc* b, int type) {
  /*  0 0 0 0
      0 0 0 0
      0 0 0 0
      0 0 0 0
  */
  b->haut = 4;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b, 1);
  /**********************/
  b->y = 1;
  b->x = g->larg / 2 - 1;
}

void blocC2(bloc* b, int type) {
  /*    0 0
      0 0 0 0
      0 0 0 0
        0 0
  */
  b->haut = 4;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b, 1);
  b->mat[0][0] = 0;
  b->mat[0][3] = 0;
  b->mat[3][0] = 0;
  b->mat[3][3] = 0;
  /**********************/
  b->y = 0;
  b->x = g->larg / 2 - 1;
}

void blocC3(bloc* b, int type) {
  /*  0     0
      0     0
      0     0
      0 0 0 0
  */
  int i, j;
  b->haut = 4;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b, 1);
  for (i = 0; i < 3; i++) {
    for (j = 1; j < 3; j++) {
      b->mat[i][j] = 0;
    }
  }
  /**********************/
  b->y = 1;
  b->x = g->larg / 2 - 1;
}

void blocC4(bloc* b, int type) {
  /*  0 0 0 0
            0
            0
            0
  */
  int i, j;
  b->haut = 4;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b, 1);
  for (i = 1; i < 4; i++) {
    for (j = 0; j < 3; j++) {
      b->mat[i][j] = 0;
    }
  }
  /**********************/
  b->y = 1;
  b->x = g->larg / 2 - 1;
}

void blocC5(bloc* b, int type) {
  /*  0 0 0 0
      0 0 0
  */
  b->haut = 2;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b, 1);
  b->mat[1][3] = 0;
  /**********************/
  b->y = 1;
  b->x = g->larg / 2 - 1;
}

void blocC6(bloc* b, int type) {
  /*  0 0 0
          0
          0
      0 0 0
  */
  int i, j;
  b->haut = 4;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b, 1);
  for (i = 1; i < 3; i++) {
    for (j = 0; j < 2; j++) {
      b->mat[i][j] = 0;
    }
  }
  /**********************/
  b->y = 0;
  b->x = g->larg / 2 - 1;
}

void blocC7(bloc* b, int type) {
  /*  0 0
      0 0
      0 0
      0 0
  */
  b->haut = 4;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b, 1);
  /**********************/
  b->y = 0;
  b->x = g->larg / 2 - 1;
}

void blocC8(bloc* b, int type) {
  /*  0 0 0 0
      0 0 0 0
  */
  b->haut = 2;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b, 1);
  b->y = 1;
  b->x = g->larg / 2 - 1;
}

void blocC9(bloc* b, int type) {
  /*  0
      0
      0
      0
      0
  */
  b->haut = 5;
  b->larg = 1;
  b->type = type;
  alloc_bloc(b, 1);
  /**********************/
  b->y = 0;
  b->x = g->larg / 2;
}

void blocC10(bloc* b, int type) {
  /*  0 0 0 0 0
      0       0
  */
  int i;
  b->haut = 2;
  b->larg = 5;
  b->type = type;
  alloc_bloc(b, 1);
  for (i = 1; i < 4; i++) {
    b->mat[1][i] = 0;
  }
  /**********************/
  b->y = 1;
  b->x = g->larg / 2 - 2;
}

void blocC11(bloc* b, int type) {
  /*  0 0 0 0 0
   */
  b->haut = 1;
  b->larg = 5;
  b->type = type;
  alloc_bloc(b, 1);
  /**********************/
  b->y = 1;
  b->x = g->larg / 2 - 2;
}

void blocC12(bloc* b, int type) {
  /*  0
      0
      0     0
      0 0 0 0
  */
  int i, j;
  b->haut = 4;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b, 1);
  for (i = 0; i < 3; i++) {
    for (j = 1; j < 3; j++) {
      b->mat[i][j] = 0;
    }
  }
  b->mat[0][3] = 0;
  b->mat[1][3] = 0;
  /**********************/
  b->y = 0;
  b->x = g->larg / 2 - 1;
}

void blocL1(bloc* b, int type) {
  /*      0 0
        0 0
      0 0
      0
  */
  int i, j;
  b->haut = 4;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b, 0);
  for (i = 0; i < 4; i++) {
    for (j = 3 - i; j > 1 - i && j >= 0; j--) {
      b->mat[i][j] = 1;
    }
  }
  /**********************/
  b->y = 1;
  b->x = g->larg / 2 - 3;
}

void blocL2(bloc* b, int type) {
  /*  0 0
        0 0
          0 0
            0
  */
  int i, j;
  b->haut = 4;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b, 0);
  for (i = 0; i < 4; i++) {
    for (j = i; j < 2 + i && j < 4; j++) {
      b->mat[i][j] = 1;
    }
  }
  /**********************/
  b->y = 1;
  b->x = g->larg / 2;
}

void blocL3(bloc* b, int type) {
  /*  0 0 0 0
        0 0
        0 0
        0 0
  */
  int i, j;
  b->haut = 4;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b, 1);
  for (i = 1; i < 4; i++) {
    b->mat[i][0] = 0;
  }
  for (i = 1; i < 4; i++) {
    b->mat[i][3] = 0;
  }
  /**********************/
  b->y = 2;
  b->x = g->larg / 2 - 1;
}

void blocL4(bloc* b, int type) {
  /*  0     0
        0 0
        0 0
      0     0
  */
  int i, j;
  b->haut = 4;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b, 0);
  for (i = 0, j = 0; i < 4; i++, j++) {
    b->mat[i][j] = 1;
    b->mat[i][3 - j] = 1;
  }
  /**********************/
  b->y = 2;
  b->x = g->larg / 2 - 1;
}

void blocL5(bloc* b, int type) {
  /*  0 0 0 0 0
        0 0 0
          0
  */
  int i, j;
  b->haut = 3;
  b->larg = 5;
  b->type = type;
  alloc_bloc(b, 0);
  for (i = 0; i < 3; i++) {
    for (j = i; j < 5 - i; j++) {
      b->mat[i][j] = 1;
    }
  }
  /**********************/
  b->y = 2;
  b->x = g->larg / 2 - 2;
}

void blocL6(bloc* b, int type) {
  /*  0 0 0 0
      0 0 0 0
      0 0 0 0
      0 0 0 0
  */
  int i, j;
  b->haut = 4;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b, 1);
  /**********************/
  b->y = 2;
  b->x = g->larg / 2 - 1;
}

void blocL7(bloc* b, int type) {
  /*  0
      0 0
        0 0
          0 0
  */
  int i, j;
  b->haut = 4;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b, 0);
  for (i = 0; i < 4; i++) {
    for (j = i; j < i + 2 && j < 4; j++) {
      b->mat[j][i] = 1;
    }
  }
  /**********************/
  b->y = 0;
  b->x = g->larg / 2;
}

void blocL8(bloc* b, int type) {
  /*       0
         0 0
       0 0
     0 0
  */
  int i, j;
  b->haut = 4;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b, 0);
  for (i = 3; i >= 0; i--) {
    for (j = 3 - i; j < 5 - i && j < 4; j++) {
      b->mat[j][i] = 1;
    }
  }
  /**********************/
  b->y = 0;
  b->x = g->larg / 2 - 3;
}

void blocL9(bloc* b, int type) {
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
  alloc_bloc(b, 1);
  /**********************/
  b->y = 0;
  b->x = g->larg / 2;
}

void blocL10(bloc* b, int type) {
  /*       0
     0 0 0 0
           0
  */
  int i;
  b->haut = 3;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b, 1);
  for (i = 0; i < 3; i++) {
    b->mat[0][i] = 0;
    b->mat[2][i] = 0;
  }
  /**********************/
  b->y = 1;
  b->x = g->larg / 2 - 2;
}

void blocL11(bloc* b, int type) {
  /*  0 0 0 0 0
   */
  b->haut = 1;
  b->larg = 5;
  b->type = type;
  alloc_bloc(b, 1);
  /**********************/
  b->y = 2;
  b->x = g->larg / 2 - 2;
}

void blocL12(bloc* b, int type) {
  /*  0 0 0 0
            0
  */
  int i;
  b->haut = 2;
  b->larg = 4;
  b->type = type;
  alloc_bloc(b, 1);
  for (i = 0; i < 3; i++) {
    b->mat[1][i] = 0;
  }
  /**********************/
  b->y = 2;
  b->x = g->larg / 2 - 1;
}

void blocL13(bloc* b, int type) {
  /*  0 0
        0
        0
        0
  */
  int i;
  b->haut = 4;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b, 1);
  for (i = 1; i < 4; i++) {
    b->mat[i][0] = 0;
  }
  /**********************/
  b->y = 1;
  b->x = g->larg / 2;
}

void blocL14(bloc* b, int type) {
  /*  0
      0
      0
      0 0
  */
  int i;
  b->haut = 4;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b, 1);
  for (i = 0; i < 3; i++) {
    b->mat[i][1] = 0;
  }
  /**********************/
  b->y = 0;
  b->x = g->larg / 2;
}

void blocT1(bloc* b, int type) {
  /*  0
      0 0 0
          0
  */
  int i;
  b->haut = 3;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b, 1);
  for (i = 0; i < 2; i++) {
    b->mat[0][i + 1] = 0;
    b->mat[2][i] = 0;
  }
  /**********************/
  b->y = 1;
  b->x = g->larg / 2 - 1;
}

void blocT2(bloc* b, int type) {
  /*  0 0
        0
        0 0
  */
  int i;
  b->haut = 3;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b, 1);
  for (i = 0; i < 2; i++) {
    b->mat[i + 1][0] = 0;
    b->mat[i][2] = 0;
  }
  /**********************/
  b->y = 1;
  b->x = g->larg / 2 - 1;
}

void blocT3(bloc* b, int type) {
  /*      0
      0 0 0
      0
  */
  int i;
  b->haut = 3;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b, 1);
  for (i = 0; i < 2; i++) {
    b->mat[0][i] = 0;
    b->mat[2][i + 1] = 0;
  }
  /**********************/
  b->y = 1;
  b->x = g->larg / 2 - 1;
}

void blocT4(bloc* b, int type) {
  /*    0 0
        0
      0 0
  */
  int i;
  b->haut = 3;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b, 1);
  for (i = 0; i < 2; i++) {
    b->mat[i][0] = 0;
    b->mat[i + 1][2] = 0;
  }
  /**********************/
  b->y = 1;
  b->x = g->larg / 2 - 1;
}

void blocT5(bloc* b, int type) {
  /*      0
        0
      0
  */
  int i;
  b->haut = 3;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b, 0);
  for (i = 0; i < 3; i++) {
    b->mat[2 - i][0 + i] = 1;
  }
  /**********************/
  b->y = 0;
  b->x = g->larg / 2 - 2;
}

void blocT6(bloc* b, int type) {
  /*  0
        0
          0
  */
  int i;
  b->haut = 3;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b, 0);
  for (i = 0; i < 3; i++) {
    b->mat[i][i] = 1;
  }
  /**********************/
  b->y = 0;
  b->x = g->larg / 2;
}

void blocT7(bloc* b, int type) {
  /*  0
      0
      0
  */
  int i;
  b->haut = 3;
  b->larg = 1;
  b->type = type;
  alloc_bloc(b, 1);
  /**********************/
  b->y = 0;
  b->x = g->larg / 2;
}

void blocT8(bloc* b, int type) {
  /*
     0 0 0
  */
  int i;
  b->haut = 1;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b, 1);
  /**********************/
  b->y = 1;
  b->x = g->larg / 2 - 1;
}

void blocT9(bloc* b, int type) {
  /*
     0
     0
  */
  int i;
  b->haut = 2;
  b->larg = 1;
  b->type = type;
  alloc_bloc(b, 1);
  /**********************/
  b->y = 0;
  b->x = g->larg / 2;
}

void blocT10(bloc* b, int type) {
  /*   0
     0 0 0
       0
  */
  int i;
  b->haut = 3;
  b->larg = 3;
  b->type = type;
  alloc_bloc(b, 0);
  for (i = 0; i < 3; i++) {
    b->mat[i][1] = 1;
    b->mat[1][i] = 1;
  }
  /**********************/
  b->y = 0;
  b->x = g->larg / 2 - 1;
}

void blocT11(bloc* b, int type) {
  /*
      0 0
  */
  int i, j;
  b->haut = 1;
  b->larg = 2;
  b->type = type;
  alloc_bloc(b, 1);
  /**********************/
  b->y = 1;
  b->x = g->larg / 2;
}

void alloc_board(int m, int n) {
  int i;
  g = (game*)malloc(sizeof(*g));
  g->larg = n;
  g->haut = m;
  g->score = 0;
  g->choosing = 1;
  g->board = (int**)malloc(m * sizeof(*(g->board)));
  g->slide_board = (value_sb**)malloc(m * sizeof(*(g->slide_board)));
  for (i = 0; i < m; i++) {
    g->board[i] = (int*)malloc(n * sizeof(int));
    g->slide_board[i] = (value_sb*)malloc(n * sizeof(value_sb));
  }
}

void init_board(int val) {
  int i, j;

  for (j = 0; j < g->haut; j++) {
    for (i = 0; i < g->larg; i++) {
      g->board[j][i] = val;
      g->slide_board[j][i].slide_value = val;
    }
  }
}

void display_board() {
  int i, j;

  for (j = 0; j < g->haut; j++) {
    for (i = 0; i < g->larg; i++) {
      cout << g->board[j][i] << "  ";
    }
    cout << endl;
  }
}

void create_bloc(bloc* b, int type) {
  cout << "C" << endl << endl;

  switch (type) {
    case 0:
      bloc1(b, type);
      break;
    case 1:
      bloc2(b, type);
      break;
    case 2:
      bloc3(b, type);
      break;
    case 3:
      bloc4(b, type);
      break;
    case 4:
      bloc5(b, type);
      break;
    case 5:
      bloc6(b, type);
      break;
    case 6:
      bloc7(b, type);
      break;
    case 7:
      bloc8(b, type);
      break;
    case 8:
      bloc9(b, type);
      break;
    case 9:
      bloc10(b, type);
      break;
    case 10:
      bloc11(b, type);
      break;
    case 11:
      bloc12(b, type);
      break;
    case 12:
      bloc13(b, type);
      break;
    case 13:
      bloc14(b, type);
      break;
    case 14:
      bloc15(b, type);
      break;
    case 15:
      bloc16(b, type);
      break;
    case 16:
      bloc17(b, type);
      break;
    case 17:
      bloc18(b, type);
      break;
    case 18:
      bloc19(b, type);
      break;
    case 19:
      bloc20(b, type);
      break;
    case 20:
      blocC1(b, type);
      break;
    case 21:
      blocC2(b, type);
      break;
    case 22:
      blocC3(b, type);
      break;
    case 23:
      blocC4(b, type);
      break;
    case 24:
      blocC5(b, type);
      break;
    case 25:
      blocC6(b, type);
      break;
    case 26:
      blocC7(b, type);
      break;
    case 27:
      blocC8(b, type);
      break;
    case 28:
      blocC9(b, type);
      break;
    case 29:
      blocC10(b, type);
      break;
    case 30:
      blocC11(b, type);
      break;
    case 31:
      blocC12(b, type);
      break;
    case 32:
      blocL1(b, type);
      break;
    case 33:
      blocL2(b, type);
      break;
    case 34:
      blocL3(b, type);
      break;
    case 35:
      blocL4(b, type);
      break;
    case 36:
      blocL5(b, type);
      break;
    case 37:
      blocL6(b, type);
      break;
    case 38:
      blocL7(b, type);
      break;
    case 39:
      blocL8(b, type);
      break;
    case 40:
      blocL9(b, type);
      break;
    case 41:
      blocL10(b, type);
      break;
    case 42:
      blocL11(b, type);
      break;
    case 43:
      blocL12(b, type);
      break;
    case 44:
      blocL13(b, type);
      break;
    case 45:
      blocL14(b, type);
      break;
    case 46:
      blocT1(b, type);
      break;
    case 47:
      blocT2(b, type);
      break;
    case 48:
      blocT3(b, type);
      break;
    case 49:
      blocT4(b, type);
      break;
    case 50:
      blocT5(b, type);
      break;
    case 51:
      blocT6(b, type);
      break;
    case 52:
      blocT7(b, type);
      break;
    case 53:
      blocT8(b, type);
      break;
    case 54:
      blocT9(b, type);
      break;
    case 55:
      blocT10(b, type);
      break;
    case 56:
      blocT11(b, type);
      break;
  }
}

void init_tabl_bloc(game* g) {
  int i;

  if (g->type_board == 3) {
    g->nb_bloc = 32;
    g->tabl_bloc = (bloc*)malloc(32 * sizeof(*g->tabl_bloc));
    for (i = 20; i < 32; i++) {
      create_bloc(&(g->tabl_bloc[i]), i);
    }
  } else if (g->type_board == 2) {
    g->nb_bloc = 34;
    g->tabl_bloc = (bloc*)malloc(34 * sizeof(*g->tabl_bloc));
    for (i = 20; i < 34; i++) {
      create_bloc(&(g->tabl_bloc[i]), i + 12);
    }
  } else {
    g->nb_bloc = 31;
    g->tabl_bloc = (bloc*)malloc(31 * sizeof(*g->tabl_bloc));
    for (i = 20; i < 31; i++) {
      create_bloc(&(g->tabl_bloc[i]), i + 26);
    }
  }
  for (i = 0; i < 20; i++) {
    create_bloc(&(g->tabl_bloc[i]), i);
  }
}

void create_board(int type, int width) {
  int i, j, a, b;
  int n, row, c, x, y;

  switch (type) {
    case 1:

      alloc_board(width / 2 + 1, width);
      init_board(0);
      g->type_board = type;
      init_tabl_bloc(g);

      for (j = 0; j < width / 2 + 1; j++) {
        for (i = width / 2 - j; i <= width / 2 + j; i++) {
          g->board[j][i] = 1;
          g->slide_board[j][i].slide_value = 3;
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
      alloc_board(width, width);
      init_board(0);
      g->type_board = type;
      init_tabl_bloc(g);

      for (j = 0; j < width / 2 + 1; j++) {
        for (i = width / 2 - j; i <= width / 2 + j; i++) {
          g->board[j][i] = 1;
          g->slide_board[j][i].slide_value = 1;
        }
      }
      for (j = width - 1, a = 0; j > width / 2; j--, a++) {
        for (i = width / 2 - a; i <= width / 2 + a; i++) {
          g->board[j][i] = 1;
          g->slide_board[j][i].slide_value = 3;
        }
      }
      break;

    case 3:

      alloc_board(width, width);
      width /= 2;
      init_board(0);
      g->type_board = type;
      init_tabl_bloc(g);
      n = 2 * width + 1;

      for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
          cout << i << " / " << j << endl;

          x = i - width;
          y = j - width;

          if (x * x + y * y <= width * width + 1) {
            g->board[i][j] = 1;
            g->slide_board[i][j].slide_value = 3;
          }
        }
      }
      break;
  }
}

void display_bloc(bloc* b) {
  int i, j;

  for (i = 0; i < b->haut; i++) {
    for (j = 0; j < b->larg; j++) {
      cout << b->mat[i][j] << "  ";
    }
    cout << endl;
  }
  cout << endl;
  cout << endl;
}

void bestiaire(int debut, int fin) {
  bloc* b;
  int i;

  for (i = debut; i <= fin; i++) {
    b = (bloc*)malloc(sizeof(*b));
    cout << "B" << endl;
    create_bloc(b, i);
    display_bloc(b);
    free(b);
  }
}

void add_bloc(bloc* b, game* g) {
  int i, j;
  cout << "ADDBLOC" << endl << b->y << endl << b->x << endl << endl;
  for (i = 0; i < b->haut; i++) {
    for (j = 0; j < b->larg; j++) {
      if (b->mat[i][j]) {
        g->board[b->y + i][b->x + j] = 8;
      }
    }
  }
}

void test_init_blocs(int width) {
  int i, j;
  bloc* b;

  for (i = 1; i < 4; i++) {
    for (j = 1; j < 21; j++) {
      g = (game*)malloc(sizeof(*g));
      create_board(i, width);
      cout << "i == " << i << endl;
      cout << "j == " << j << endl << endl;
      b = (bloc*)malloc(sizeof(*b));
      cout << "FREE 1" << endl;
      create_bloc(b, j);
      add_bloc(b, g);
      display_board();
      cout << endl << endl;
      display_bloc(b);
      free(b);
      free(g);
    }
  }
}

void display_bloc_tabl() {
  int i;

  for (i = 0; i < g->nb_bloc; i++) {
    cout << i << endl;
    display_bloc(&(g->tabl_bloc[i]));
  }
}

void clear_slide_board() {
  int i, j;

  for (i = 0; i < g->haut; i++) {
    for (j = 0; j < g->larg; j++) {
      if (g->slide_board[i][j].slide_value > 1) {
        g->slide_board[i][j].slide_value = 1;
      }
    }
  }
}

int can_be_init(bloc* b) {
  int i, j;
  for (i = 0; i < b->haut; i++) {
    for (j = 0; j < b->larg; j++) {
      if ((b->mat[i][j] == 1) && (g->board[i + b->y][j + b->x] != 1)) {
        return 0;
      }
    }
  }
  return 1;
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
