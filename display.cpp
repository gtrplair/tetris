#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include "proj.cpp"

// TESTING TETRIS

using namespace std;

int SCREEN_WIDTH = 1000;
int SCREEN_HEIGHT = 700;
float aspect_ratio = SCREEN_HEIGHT / SCREEN_WIDTH;

int choosingpiece;
float deplacex, deplacey, xx, yy;
float xmove_unit;
float ymove_unit;

int shape;
int width;

float xborder = 0.2;
float yborder = 0.2;
float x0board = -1 + xborder;
float y0board = 1 - yborder;
float xsquaresize, ysquaresize;
float xbezel = 0.2;
float ybezel = 0.2;
float xbezel_frame = 0.05;
float ybezel_frame = 0.05;

int time1;
float speed = 1.0f;
int blink = 100;
int select_counter = 0;
int counter;

float ypos1 = 0.18;
float ypos2 = 0.38;
float ypos3 = 0.75;
float ypos4 = 1.12;
float ypos5 = 1.32;
float ypos6;
float big_select_slide = ypos3 - ypos2;
float small_select_slide = ypos2 - ypos1;
float small_scale1 = 0.15;
float small_scale2 = 0.55;
float small_scale3 = 0.55;
float big_scale = 1.35;
int sel_speed = 100;

void select_reset() {
  ypos1 = 0.18;
  ypos2 = 0.38;
  ypos3 = 0.75;
  ypos4 = 1.12;
  ypos5 = 1.32;
  ypos6;
  big_select_slide = ypos3 - ypos2;
  small_select_slide = ypos2 - ypos1;
  small_scale1 = 0.15;
  small_scale2 = 0.55;
  small_scale3 = 0.55;
  big_scale = 1.35;
}

void move_select_up() {
  ypos1 -= small_select_slide / sel_speed;
  small_scale1 -= (small_scale2 - small_scale1) / sel_speed;
  ypos2 -= small_select_slide / sel_speed;
  ypos3 -= big_select_slide / sel_speed;
  ypos4 -= big_select_slide / sel_speed;
  ypos5 -= small_select_slide / sel_speed;
  big_scale -= (big_scale - small_scale1) / sel_speed;
  small_scale3 += (big_scale - small_scale1) / sel_speed;
  small_scale2 -= (small_scale2 - small_scale1) / sel_speed;
}

void move_select_down() {
  ypos1 += small_select_slide / sel_speed;
  ypos2 += small_select_slide / sel_speed;
  ypos3 += big_select_slide / sel_speed;
  ypos4 += big_select_slide / sel_speed;
  ypos5 += small_select_slide / sel_speed;
  big_scale -= (big_scale - small_scale1) / sel_speed;
  small_scale2 += (big_scale - small_scale1) / sel_speed;
  small_scale3 -= (small_scale3 - small_scale1) / sel_speed;
}

void init() {
  // set clear color to black
  glClearColor(0.0, 0.0, 0.0, 0.0);

  // set fill color to white
  glColor3f(1.0, 1.0, 1.0);
}
/*
void choose_board() {
  // triangle
  glBegin(GL_POLYGON);
  glVertex2f(-0.85 * aspect_ratio, 0);
  glVertex2f(0, -0.55);
  glVertex2f(0.15, 0);
  glEnd();

  // diamond
  glBegin(GL_QUADS);
  glVertex2f(-0.15 * aspect_ratio, 0);
  glVertex2f(0, 0.15);
  glVertex2f(0.15, 0);
  glVertex2f(0, -1.5);
  glEnd();

  // circle
  glBegin(GL_QUADS);

  glEnd();
}

*/
void ProcessNormalKeys(unsigned char key, int x, int y) {
  int i;

  if (key == ' ') {
    cout << "SPACEBAR" << endl;
    if (g->choosing == 0) {
      cout << "111" << endl;
      placement_bloc(current_b);
      g->choosing = (g->choosing + 1) % 2;
      for (i = 0; i < g->larg; i++) {
        if (column_full(i)) {
          delete_col(i);
        }
      }

      for (i = 0; i < g->haut; i++) {
        if (row_is_full(i)) {
          delete_row(i);
        }
      }
    } else {
      cout << "222" << endl;
      free(current_b);
      current_b = (bloc*)malloc(sizeof(*current_b));
      create_bloc(current_b, g->tabl_bloc[indice_bloc].type);
      cout << "CAN_BE_INIT" << can_be_init(current_b) << endl;
      g->choosing = (g->choosing + 1) % 2;
    }
  }
  glutPostRedisplay();
}

void keyboardown(int key, int x, int y) {
  int i;
  switch (key) {
    case GLUT_KEY_RIGHT:
      if (g->choosing == 0) {
        if (can_right(current_b, g) == 1) {
          right(current_b);
        }
      }
      break;

    case GLUT_KEY_LEFT:
      if (g->choosing == 0) {
        if (can_left(current_b, g) == 1) {
          left(current_b);
        }
      }
      break;

    case GLUT_KEY_UP:
      if (g->choosing == 0) {
        if (can_top(current_b, g) == 1) {
          top(current_b);
        }
      } else {
        counter = 0;
        select_counter = 1;
        // indice_bloc = (indice_bloc - 1 + g->nb_bloc) % g->nb_bloc;
      }
      break;

    case GLUT_KEY_DOWN:
      if (g->choosing == 0) {
        if (can_bot(current_b, g) == 1) {
          bot(current_b);
        }
      } else {
        counter = 0;
        select_counter = -1;
        // indice_bloc = (indice_bloc + 1) % g->nb_bloc;
      }
      break;

    case GLUT_KEY_END:

      if (can_right(current_b, g) == 1) {
        right(current_b);
      }

      break;

    default:
      break;
  }
  glutPostRedisplay();
}

void display_frame(float scaling,
                  float r,
                  float g,
                  float blue,
                  float x,
                  float y) {
  glColor3f(r, g, blue);
int i=1;
int j=1;
  /////////////////////////////////////////////////////
  glColor3f(r + 0.4 * (1 - r), g + 0.4 * (1 - r), blue + 0.4 * (1 - r));
  glBegin(GL_QUADS);
  glVertex2f(x + (j)*xsquaresize * scaling, y - (i)*ysquaresize * scaling);
  glVertex2f(x + (j + xbezel_frame) * xsquaresize * scaling,
             y - (i + ybezel_frame) * ysquaresize * scaling);
  glVertex2f(x + (j + xbezel_frame) * xsquaresize * scaling,
             y - (i + 1 - ybezel_frame) * ysquaresize * scaling);
  glVertex2f(x + (j)*xsquaresize * scaling,
             y - (i + 1) * ysquaresize * scaling);
  glEnd();
  glColor3f(r + 0.7 * (1 - r), g + 0.7 * (1 - r), blue + 0.7 * (1 - r));
  glBegin(GL_QUADS);
  glVertex2f(x + (j)*xsquaresize * scaling, y - (i)*ysquaresize * scaling);
  glVertex2f(x + (j + 1) * xsquaresize * scaling,
             y - (i)*ysquaresize * scaling);
  glVertex2f(x + (j + 1 - xbezel_frame) * xsquaresize * scaling,
             y - (i + ybezel_frame) * ysquaresize * scaling);
  glVertex2f(x + (j + xbezel_frame) * xsquaresize * scaling,
             y - (i + ybezel_frame) * ysquaresize * scaling);
  glEnd();
  glColor3f(0.7 * r, 0.7 * g, 0.7 * blue);
  glBegin(GL_QUADS);
  glVertex2f(x + (j + 1 - xbezel_frame) * xsquaresize * scaling,
             y - (i + ybezel_frame) * ysquaresize * scaling);
  glVertex2f(x + (j + 1) * xsquaresize * scaling,
             y - (i)*ysquaresize * scaling);
  glVertex2f(x + (j + 1) * xsquaresize * scaling,
             y - (i + 1) * ysquaresize * scaling);
  glVertex2f(x + (j + 1 - xbezel_frame) * xsquaresize * scaling,
             y - (i + 1 - ybezel_frame) * ysquaresize * scaling);
  glEnd();
  glColor3f(0.4 * r, 0.4 * g, 0.4 * blue);
  glBegin(GL_QUADS);
  glVertex2f(x + (j)*xsquaresize * scaling,
             y - (i + 1) * ysquaresize * scaling);
  glVertex2f(x + (j + xbezel_frame) * xsquaresize * scaling,
             y - (i + 1 - ybezel_frame) * ysquaresize * scaling);
  glVertex2f(x + (j + 1 - xbezel_frame) * xsquaresize * scaling,
             y - (i + 1 - ybezel_frame) * ysquaresize * scaling);
  glVertex2f(x + (j + 1) * xsquaresize * scaling,
             y - (i + 1) * ysquaresize * scaling);
  glEnd();
}


void display_bloc(bloc* b,
                  float scaling,
                  float r,
                  float g,
                  float blue,
                  float x,
                  float y) {
  int i, j;
  glColor3f(r, g, blue);
  for (i = 0; i < b->haut; i++) {
    for (j = 0; j < b->larg; j++) {
      if (b->mat[i][j] == 1) {
        /*
        glColor3f(r, g, blue);
        glBegin(GL_QUADS);
        glVertex2f(x + j * xsquaresize * scaling,
                   y - i * ysquaresize * scaling);
        glVertex2f(x + (j + 1) * xsquaresize * scaling,
                   y - i * ysquaresize * scaling);
        glVertex2f(x + (j + 1) * xsquaresize * scaling,
                   y - (i + 1) * ysquaresize * scaling);
        glVertex2f(x + (j)*xsquaresize * scaling,
                   y - (i + 1) * ysquaresize * scaling);
        glEnd();
        */
        glColor3f(r, g, blue);
        glBegin(GL_QUADS);
        glVertex2f(x + (j + xbezel) * xsquaresize * scaling,
                   y - (i + ybezel) * ysquaresize * scaling);
        glVertex2f(x + (j + 1 - xbezel) * xsquaresize * scaling,
                   y - (i + ybezel) * ysquaresize * scaling);
        glVertex2f(x + (j + 1 - xbezel) * xsquaresize * scaling,
                   y - (i + 1 - ybezel) * ysquaresize * scaling);
        glVertex2f(x + (j + xbezel) * xsquaresize * scaling,
                   y - (i + 1 - ybezel) * ysquaresize * scaling);
        glEnd();
        /////////////////////////////////////////////////////
        glColor3f(r + 0.4 * (1 - r), g + 0.4 * (1 - r), blue + 0.4 * (1 - r));
        glBegin(GL_QUADS);
        glVertex2f(x + (j)*xsquaresize * scaling,
                   y - (i)*ysquaresize * scaling);
        glVertex2f(x + (j + xbezel) * xsquaresize * scaling,
                   y - (i + ybezel) * ysquaresize * scaling);
        glVertex2f(x + (j + xbezel) * xsquaresize * scaling,
                   y - (i + 1 - ybezel) * ysquaresize * scaling);
        glVertex2f(x + (j)*xsquaresize * scaling,
                   y - (i + 1) * ysquaresize * scaling);
        glEnd();
        glColor3f(r + 0.7 * (1 - r), g + 0.7 * (1 - r), blue + 0.7 * (1 - r));
        glBegin(GL_QUADS);
        glVertex2f(x + (j)*xsquaresize * scaling,
                   y - (i)*ysquaresize * scaling);
        glVertex2f(x + (j + 1) * xsquaresize * scaling,
                   y - (i)*ysquaresize * scaling);
        glVertex2f(x + (j + 1 - xbezel) * xsquaresize * scaling,
                   y - (i + ybezel) * ysquaresize * scaling);
        glVertex2f(x + (j + xbezel) * xsquaresize * scaling,
                   y - (i + ybezel) * ysquaresize * scaling);
        glEnd();
        glColor3f(0.7 * r, 0.7 * g, 0.7 * blue);
        glBegin(GL_QUADS);
        glVertex2f(x + (j + 1 - xbezel) * xsquaresize * scaling,
                   y - (i + ybezel) * ysquaresize * scaling);
        glVertex2f(x + (j + 1) * xsquaresize * scaling,
                   y - (i)*ysquaresize * scaling);
        glVertex2f(x + (j + 1) * xsquaresize * scaling,
                   y - (i + 1) * ysquaresize * scaling);
        glVertex2f(x + (j + 1 - xbezel) * xsquaresize * scaling,
                   y - (i + 1 - ybezel) * ysquaresize * scaling);
        glEnd();
        glColor3f(0.4 * r, 0.4 * g, 0.4 * blue);
        glBegin(GL_QUADS);
        glVertex2f(x + (j)*xsquaresize * scaling,
                   y - (i + 1) * ysquaresize * scaling);
        glVertex2f(x + (j + xbezel) * xsquaresize * scaling,
                   y - (i + 1 - ybezel) * ysquaresize * scaling);
        glVertex2f(x + (j + 1 - xbezel) * xsquaresize * scaling,
                   y - (i + 1 - ybezel) * ysquaresize * scaling);
        glVertex2f(x + (j + 1) * xsquaresize * scaling,
                   y - (i + 1) * ysquaresize * scaling);
        glEnd();
      }
    }
  }
  /*

    for (i = 0; i < b->haut; i++) {
      for (j = 0; j < b->larg; j++) {
        if (b->mat[i][j] == 1) {
          glBegin(GL_QUADS);
          glVertex2f(x + j * xsquaresize * scaling, y - i * ysquaresize *
    scaling); glVertex2f(x + (j + 1) * xsquaresize * scaling, y - i *
    ysquaresize * scaling); glVertex2f(x + (j + 1) * xsquaresize * scaling, y
    - (i + 1) * ysquaresize * scaling); glVertex2f(x + (j)*xsquaresize *
    scaling, y - (i + 1) * ysquaresize * scaling); glEnd();
        }
      }
    }
*/
}

void dis(game* g,
         float scaling,
         float r,
         float green,
         float blue,
         float x,
         float y) {
  int i, j;

  for (i = 0; i < g->haut; i++) {
    for (j = 0; j < g->larg; j++) {
      if (g->board[i][j] == 0) {
        glColor3f(0, 0, 0);
      } else if (g->board[i][j] == 1) {
        glColor3f(0.90, 0.22, 0);
      } else {
        glColor3f(0.5, 0.5, 0);
      }
      glBegin(GL_QUADS);
      glVertex2f(x + j * xsquaresize * scaling, y - i * ysquaresize * scaling);
      glVertex2f(x + (j + 1) * xsquaresize * scaling,
                 y - i * ysquaresize * scaling);
      glVertex2f(x + (j + 1) * xsquaresize * scaling,
                 y - (i + 1) * ysquaresize * scaling);
      glVertex2f(x + (j)*xsquaresize * scaling,
                 y - (i + 1) * ysquaresize * scaling);
      glEnd();

      glEnd();
    }
  }
}

/*







}






*/

void animate(int value) {
  glutTimerFunc(speed, animate, 0);
  time1++;
  if (time1 >= blink) {
    time1 = 0;
    counter++;
  }
  glutPostRedisplay();
}

void display_one_bloc(int indice_color, float scaling, float x, float y) {
  float red = g->color_tabl[indice_color].r;
  float green = g->color_tabl[indice_color].g;
  float blue = g->color_tabl[indice_color].b;

  glColor3f(red, green, blue);

  /*

        glColor3f(r, g, blue);
        glBegin(GL_QUADS);
        glVertex2f(x + j * xsquaresize * scaling,
                   y - i * ysquaresize * scaling);
        glVertex2f(x + (j + 1) * xsquaresize * scaling,
                   y - i * ysquaresize * scaling);
        glVertex2f(x + (j + 1) * xsquaresize * scaling,
                   y - (i + 1) * ysquaresize * scaling);
        glVertex2f(x + (j)*xsquaresize * scaling,
                   y - (i + 1) * ysquaresize * scaling);
        glEnd();

        */

  glBegin(GL_QUADS);
  glVertex2f(x + (xbezel)*xsquaresize * scaling,
             y - (ybezel)*ysquaresize * scaling);
  glVertex2f(x + (1 - xbezel) * xsquaresize * scaling,
             y - (ybezel)*ysquaresize * scaling);
  glVertex2f(x + (1 - xbezel) * xsquaresize * scaling,
             y - (1 - ybezel) * ysquaresize * scaling);
  glVertex2f(x + (xbezel)*xsquaresize * scaling,
             y - (1 - ybezel) * ysquaresize * scaling);
  glEnd();

  /////////////////////////////////////////////////////

  glColor3f(red + 0.4 * (1 - red), green + 0.4 * (1 - red),
            blue + 0.4 * (1 - red));
  glBegin(GL_QUADS);
  glVertex2f(x, y);
  glVertex2f(x + (xbezel)*xsquaresize * scaling,
             y - (ybezel)*ysquaresize * scaling);
  glVertex2f(x + (xbezel)*xsquaresize * scaling,
             y - (1 - ybezel) * ysquaresize * scaling);
  glVertex2f(x, y - ysquaresize * scaling);
  glEnd();

  glColor3f(red + 0.7 * (1 - red), green + 0.7 * (1 - red),
            blue + 0.7 * (1 - red));
  glBegin(GL_QUADS);
  glVertex2f(x, y);
  glVertex2f(x + xsquaresize * scaling, y);
  glVertex2f(x + (1 - xbezel) * xsquaresize * scaling,
             y - (ybezel)*ysquaresize * scaling);
  glVertex2f(x + (xbezel)*xsquaresize * scaling,
             y - (ybezel)*ysquaresize * scaling);
  glEnd();

  glColor3f(0.7 * red, 0.7 * green, 0.7 * blue);
  glBegin(GL_QUADS);
  glVertex2f(x + (1 - xbezel) * xsquaresize * scaling,
             y - ybezel * ysquaresize * scaling);
  glVertex2f(x + xsquaresize * scaling, y);
  glVertex2f(x + xsquaresize * scaling, y - ysquaresize * scaling);
  glVertex2f(x + (1 - xbezel) * xsquaresize * scaling,
             y - (1 - ybezel) * ysquaresize * scaling);
  glEnd();

  glColor3f(0.4 * red, 0.4 * green, 0.4 * blue);
  glBegin(GL_QUADS);
  glVertex2f(x, y - ysquaresize * scaling);
  glVertex2f(x + (xbezel)*xsquaresize * scaling,
             y - (1 - ybezel) * ysquaresize * scaling);
  glVertex2f(x + (1 - xbezel) * xsquaresize * scaling,
             y - (1 - ybezel) * ysquaresize * scaling);
  glVertex2f(x + xsquaresize * scaling, y - ysquaresize * scaling);
  glEnd();
}

void affich_board(game* g, float scaling, float x, float y) {
  int i, j;

  for (i = 0; i < g->haut; i++) {
    for (j = 0; j < g->larg; j++) {
      if (g->board[i][j] == 1) {
        glColor3f(1, 1, 1);

        glBegin(GL_QUADS);
        glVertex2f(x + j * xsquaresize * scaling,
                   y - i * ysquaresize * scaling);
        glVertex2f(x + (j + 1) * xsquaresize * scaling,
                   y - i * ysquaresize * scaling);
        glVertex2f(x + (j + 1) * xsquaresize * scaling,
                   y - (i + 1) * ysquaresize * scaling);
        glVertex2f(x + (j)*xsquaresize * scaling,
                   y - (i + 1) * ysquaresize * scaling);
        glEnd();
      }

      if (g->board[i][j] > 1) {
        display_one_bloc(g->board[i][j] - 2, 1, x0board + j * xsquaresize,
                         y0board - i * ysquaresize);
      }
    }
  }
}

void display() {
  int indice_plus = (indice_bloc + 1) % g->nb_bloc;
  int indice_plus2 = (indice_bloc + 2) % g->nb_bloc;
  int indice_moins = (indice_bloc - 1 + g->nb_bloc) % g->nb_bloc;
  int indice_moins2 = (indice_bloc - 2 + g->nb_bloc) % g->nb_bloc;
  glClear(GL_COLOR_BUFFER_BIT);
  glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
  // dis(g, 1, 1, 1, 1, x0board, y0board);

  affich_board(g, 1, x0board, y0board);

  // entourer la piece a selectioner
  /*
    glBegin(GL_QUADS);
    glVertex2f(x0board + 1.5 - 3 * xsquaresize * 1.35,
               y0board - 0.75 + 1.35 * 3 * ysquaresize);
    glVertex2f(x0board + 1.5 + 3 * xsquaresize * 1.35,
               y0board - 0.75 + 1.35 * 3 * ysquaresize);
    glVertex2f(x0board + 1.5 + 3 * xsquaresize * 1.35,
               y0board - 0.75 - 1.35 * 3 * ysquaresize);
    glVertex2f(x0board + 1.5 - 3 * xsquaresize * 1.35,
               y0board - 0.75 - 1.35 * 3 * ysquaresize);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(x0board + 1.5 - 3 * xsquaresize * 1.35,
               y0board - 0.75 + 1.35 * 3 * ysquaresize);
    glVertex2f(x0board + 1.5 + 3 * xsquaresize * 1.35,
               y0board - 0.75 + 1.35 * 3 * ysquaresize);
    glVertex2f(x0board + 1.5 + 3 * xsquaresize * 1.35,
               y0board - 0.75 - 1.35 * 3 * ysquaresize);
    glVertex2f(x0board + 1.5 - 3 * xsquaresize * 1.35,
               y0board - 0.75 - 1.35 * 3 * ysquaresize);
    glEnd();
    */

  if (g->choosing == 0) {
    display_bloc(current_b, 1, g->color_tabl[indice_bloc].r,
                 g->color_tabl[indice_bloc].g, g->color_tabl[indice_bloc].b,
                 x0board + current_b->x * xsquaresize,
                 y0board - current_b->y * ysquaresize);
  }

  else if (g->choosing == 1) {
    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    if ((select_counter == 1) && (counter < sel_speed)) {
      move_select_up();
      counter++;
      if (counter == sel_speed - 1) {
        indice_bloc = (indice_bloc - 1 + g->nb_bloc) % g->nb_bloc;
        select_reset();
      }
    }
    if ((select_counter == -1) && (counter < sel_speed)) {
      move_select_down();
      counter++;
      if (counter == sel_speed - 1) {
        indice_bloc = (indice_bloc + 1) % g->nb_bloc;
        select_reset();
      }
    }
    display_bloc(
        &(g->tabl_bloc[indice_plus2]), small_scale1,
        g->color_tabl[indice_plus2].r, g->color_tabl[indice_plus2].g,
        g->color_tabl[indice_plus2].b,
        x0board + 1.5 -
            small_scale1 * xsquaresize * (g->tabl_bloc[indice_plus2]).larg / 2,
        y0board - ypos1 +
            (small_scale1 * ysquaresize * (g->tabl_bloc[indice_plus2]).haut /
             2));
    display_bloc(
        &(g->tabl_bloc[indice_plus]), small_scale2,
        g->color_tabl[indice_plus].r, g->color_tabl[indice_plus].g,
        g->color_tabl[indice_plus].b,
        x0board + 1.5 -
            small_scale2 * xsquaresize * (g->tabl_bloc[indice_plus]).larg / 2,
        y0board - ypos2 +
            (small_scale2 * ysquaresize * (g->tabl_bloc[indice_plus]).haut /
             2));
    display_bloc(
        &(g->tabl_bloc[indice_moins]), small_scale3,
        g->color_tabl[indice_moins].r, g->color_tabl[indice_moins].g,
        g->color_tabl[indice_moins].b,
        x0board + 1.5 -
            small_scale3 * xsquaresize * (g->tabl_bloc[indice_moins]).larg / 2,
        y0board - ypos4 +
            (small_scale3 * ysquaresize * (g->tabl_bloc[indice_moins]).haut /
             2));
    display_bloc(
        &(g->tabl_bloc[indice_moins2]), small_scale1,
        g->color_tabl[indice_moins2].r, g->color_tabl[indice_moins2].g,
        g->color_tabl[indice_moins2].b,
        x0board + 1.5 -
            small_scale1 * xsquaresize * (g->tabl_bloc[indice_moins2]).larg / 2,
        y0board - ypos5 +
            (small_scale1 * ysquaresize * (g->tabl_bloc[indice_moins2]).haut /
             2));
    // piece de blocs a selectionner
    display_bloc(
        &(g->tabl_bloc[indice_bloc]), big_scale, g->color_tabl[indice_bloc].r,
        g->color_tabl[indice_bloc].g, g->color_tabl[indice_bloc].b,
        x0board + 1.5 -
            big_scale * xsquaresize * (g->tabl_bloc[indice_bloc]).larg / 2,
        y0board - ypos3 +
            (big_scale * ysquaresize * (g->tabl_bloc[indice_bloc]).haut / 2));
  }
  glColor3f(0, 0, 0);
  glBegin(GL_QUADS);
  glVertex2f(0.6, 1);
  glVertex2f(1, 1);
  glVertex2f(1, 0.52);
  glVertex2f(0.6, 0.52);
  glEnd();

  glBegin(GL_QUADS);
  glVertex2f(0.6, -1);
  glVertex2f(1, -1);
  glVertex2f(1, -0.42);
  glVertex2f(0.6, -0.42);
  glEnd();

  // entourer la piece a selectioner
/*
  glColor3f(0, 1, 0);
  display_frame(9, 0,1,0, x0board+1.5-9*xsquaresize*1.35, y0board - 0.75 + 1.35 * 8 * ysquaresize);
  glColor3f(0, 0, 1);
  display_frame(7, 0,1,0, x0board+1.5-7.5*xsquaresize*1.35, y0board - 0.75 + 1.35 * 13 * ysquaresize);
*/
/*
  glBegin(GL_QUADS);
  glVertex2f(x0board + 1.5 - 3 * xsquaresize * 1.35,
             y0board - 0.75 + 1.35 * 3 * ysquaresize);
  glVertex2f(x0board + 1.5 - 2.7 * xsquaresize * 1.35,
             y0board - 0.75 + 1.35 * 3 * ysquaresize);
  glVertex2f(x0board + 1.5 - 2.7 * xsquaresize * 1.35,
             y0board - 0.75 - 1.35 * 3 * ysquaresize);
  glVertex2f(x0board + 1.5 - 3 * xsquaresize * 1.35,
             y0board - 0.75 - 1.35 * 3 * ysquaresize);
  glEnd();

  glBegin(GL_QUADS);
  glVertex2f(x0board + 1.5 + 2.7 * xsquaresize * 1.35,
             y0board - 0.75 + 1.35 * 3 * ysquaresize);
  glVertex2f(x0board + 1.5 + 3 * xsquaresize * 1.35,
             y0board - 0.75 + 1.35 * 3 * ysquaresize);
  glVertex2f(x0board + 1.5 + 3 * xsquaresize * 1.35,
             y0board - 0.75 - 1.35 * 3 * ysquaresize);
  glVertex2f(x0board + 1.5 + 2.7 * xsquaresize * 1.35,
             y0board - 0.75 - 1.35 * 3 * ysquaresize);
  glEnd();

  glBegin(GL_QUADS);
  glVertex2f(x0board + 1.5 - 3 * xsquaresize * 1.35,
             y0board - 0.75 + 1.35 * 3 * ysquaresize);
  glVertex2f(x0board + 1.5 + 3 * xsquaresize * 1.35,
             y0board - 0.75 + 1.35 * 3 * ysquaresize);
  glVertex2f(x0board + 1.5 + 3 * xsquaresize * 1.35,
             y0board - 0.75 + 1.35 * 2.7 * ysquaresize);
  glVertex2f(x0board + 1.5 - 3 * xsquaresize * 1.35,
             y0board - 0.75 + 1.35 * 2.7 * ysquaresize);
  glEnd();

  glBegin(GL_QUADS);
  glVertex2f(x0board + 1.5 - 3 * xsquaresize * 1.35,
             y0board - 0.75 - 1.35 * 3 * ysquaresize);
  glVertex2f(x0board + 1.5 + 3 * xsquaresize * 1.35,
             y0board - 0.75 - 1.35 * 3 * ysquaresize);
  glVertex2f(x0board + 1.5 + 3 * xsquaresize * 1.35,
             y0board - 0.75 - 1.35 * 2.7 * ysquaresize);
  glVertex2f(x0board + 1.5 - 3 * xsquaresize * 1.35,
             y0board - 0.75 - 1.35 * 2.7 * ysquaresize);
  glEnd();
  */

  glFlush();
}

int main(int argc, char** argv) {
  int i;
  current_b = (bloc*)malloc(sizeof(*current_b));

  cout << "Triangle: 1   -   Diamond: 2   -   Circle: 3\n" << endl;
  cin >> shape;
  cout << "Width" << endl;
  cin >> width;

  if (shape == 1) {
    xsquaresize = (2 - 2 * xborder) / (width)*SCREEN_HEIGHT / SCREEN_WIDTH;
    ysquaresize = (2 - 2 * yborder) / width;
  }
  if (shape == 2) {
    xsquaresize = (2 - 2 * xborder) / (width)*SCREEN_HEIGHT / SCREEN_WIDTH;
    ysquaresize = (2 - 2 * yborder) / (width);
  }

  if (shape == 3) {
    xsquaresize = (2 - 2 * xborder) / (width)*SCREEN_HEIGHT / SCREEN_WIDTH;
    ysquaresize = (2 - 2 * yborder) / (width);
  }

  xmove_unit = xsquaresize;
  ymove_unit = ysquaresize;

  cout << "AZE" << endl;
  create_board(shape, width);
  cout << "AZER" << endl;

  init_color_tabl();
  color_table();

  /*
create_board(3);
blocT5( );
add_bloc();
display_board();
cout << endl << endl;
display_bloc();
*/
  //  test_init_blocs();

  /*
bestiaire(57,57);

for(i=0 ; i<10 ; i++){
cout << rand_a_b(0,100);
}
*/
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("TETRIS");
  glutTimerFunc(1.0, animate, 0);
  glutDisplayFunc(display);
  // init();
  glutKeyboardFunc(ProcessNormalKeys);
  glutSpecialFunc(keyboardown);
  glutPostRedisplay();
  glutMainLoop();
}
