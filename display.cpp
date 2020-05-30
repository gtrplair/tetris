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
float aspect_ratio = (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH;

int choosingpiece;
float deplacex, deplacey, xx, yy;
float xmove_unit;
float ymove_unit;

int shape = 1;
int width = 21;
int welcome = 1;
int politique = 1;
int choose_politique = -1;
int show_menu = -1;
int transition = -1;
int validate_size = -1;
int shape_select = 1;
int playing_game = -1;

float triangle_radius = 0.3;
float losange_radius = 0.3;
float circle_radius = 0.3;
float triangle_center = -0.6;
float losange_center = 0;
float circle_center = 0.6;
float shape_scale = 1.0;
float triangle_red = 0.3;
float losange_red = 0.3;
float circle_red = 0.3;
float shape_white = 0.0;

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

void DisplayMenu(void) {
  int n;

  char ligne1[] = "WELCOME TO TETRIS 2099";
  char ligne2[] = "Use the arrows and spacebar to make your choices";
  char ligne3[] =
      "Choose if you want all pieces available, or just three random pieces";
  char ligne4[] = "Choose the shape and size of your game";
  char ligne7[] = "Select your pieces with the arrow keys and the spacebar";
  char ligne6[] = "Fill a column or row to make them disappear";
  char ligne5[] = "The game is over when you cannot play any more pieces";
  char ligne8[] = "Press spacebar to continue";

  // background
  // middle
  glBegin(GL_POLYGON);
  glColor3f(0.0, 0.0, 0.0);
  glVertex2f(-1.0, -0.9);
  glVertex2f(-1.0, 0.9);
  glVertex2f(1.0, 0.9);
  glVertex2f(1.0, -0.9);
  glEnd();

  glColor3f(1.0, 1.0, 1.0);
  // top
  glBegin(GL_POLYGON);
  glVertex2f(1.0, 1.0);
  glVertex2f(-1.0, 1.0);
  glVertex2f(-1.0, 0.9);
  glVertex2f(1.0, 0.9);
  glEnd();
  // bottom
  glBegin(GL_POLYGON);
  glVertex2f(1.0, -0.9);
  glVertex2f(-1.0, -0.9);
  glVertex2f(-1.0, -1.0);
  glVertex2f(1.0, -1.0);
  glEnd();

  // text

  glColor3f(0.0, 0.0, 0.0);
  glRasterPos2f(-0.11, 0.93);
  for (n = 0; n < 22; n++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ligne1[n]);
  }

  glColor3f(1.0, 1.0, 1.0);
  glRasterPos2f(-0.8, 0.64);
  for (n = 0; n < 48; n++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ligne2[n]);
  }

  glRasterPos2f(-0.8, 0.39);
  for (n = 0; n < 70; n++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ligne3[n]);
  }

  glRasterPos2f(-0.8, 0.14);
  for (n = 0; n < 38; n++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ligne4[n]);
  }

  glRasterPos2f(-0.8, -0.11);
  for (n = 0; n < 43; n++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ligne6[n]);
  }

  glRasterPos2f(-0.8, -0.36);
  for (n = 0; n < 55; n++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ligne7[n]);
  }

  glColor3f(1.0, 0.0, 0.0);
  glRasterPos2f(-0.8, -0.61);
  for (n = 0; n < 54; n++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ligne5[n]);
  }

  glColor3f(0.0, 0.0, 0.0);
  glRasterPos2f(-0.8, -0.97);
  for (n = 0; n < 26; n++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ligne8[n]);
  }
}

void show_politique(void) {
  int n;

  char ligne1[] = "CHOOSE YOUR PLAY STYLE";
  char ligne2[] = "Access to all available pieces or to only 3 at a time";
  char ligne3[] = "Three";
  char ligne4[] = "All";
/*
  glBegin(GL_POLYGON);
  glColor3f(0.0, 0.0, 0.0);
  glVertex2f(-1.0, -0.9);
  glVertex2f(-1.0, 0.9);
  glVertex2f(1.0, 0.9);
  glVertex2f(1.0, -0.9);
  glEnd();
  */

  glColor3f(1.0, 1, 1);

  glBegin(GL_POLYGON);
  glVertex2f(1.0, 1.0);
  glVertex2f(-1.0, 1.0);
  glVertex2f(-1.0, 0.9);
  glVertex2f(1.0, 0.9);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(1.0, -0.9);
  glVertex2f(-1.0, -0.9);
  glVertex2f(-1.0, -1.0);
  glVertex2f(1.0, -1.0);
  glEnd();

  // text
  glRasterPos2f(-0.4, 0.69);
  for (n = 0; n < 22; n++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ligne1[n]);
  }

  glRasterPos2f(-0.5, 0.49);
  for (n = 0; n < 56; n++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ligne2[n]);
  }


  if (politique == 2) {
    glColor3f(0, 0, 0);
  } else {
    glColor3f(1, 1, 1);
  }

  glRasterPos2f(0.57, -0.0);
  for (n = 0; n < 5; n++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ligne3[n]);
  }
    if (politique == 2) {
    glColor3f(1, 1, 1);
    ;
  } else {
    glColor3f(0, 0, 0);
    ;
  }
    glRasterPos2f(-0.63, -0.0);
  for (n = 0; n < 3; n++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ligne4[n]);
  }
}

void init() {
  // set clear color to black
  glClearColor(0.0, 0.0, 0.0, 0.0);

  // set fill color to white
  glColor3f(1.0, 1.0, 1.0);
}

void politique_display() {
  if (politique == 1) {
    glColor3f(1, 1, 1);
    ;
  } else {
    glColor3f(0, 0, 0);
    ;
  }

  // diamond
  glBegin(GL_QUADS);
  glVertex2f(-losange_radius * aspect_ratio + triangle_center, 0);
  glVertex2f(+triangle_center, losange_radius);
  glVertex2f(losange_radius * aspect_ratio + triangle_center, 0);
  glVertex2f(+triangle_center, -losange_radius);
  glEnd();

  if (politique == 1) {
    glColor3f(0, 0, 0);
  } else {
    glColor3f(1, 1, 1);
  }

  // diamond
  glBegin(GL_QUADS);
  glVertex2f(-losange_radius * aspect_ratio + circle_center, 0);
  glVertex2f(+circle_center, losange_radius);
  glVertex2f(losange_radius * aspect_ratio + circle_center, 0);
  glVertex2f(+circle_center, -losange_radius);
  glEnd();
}

void choose_board() {
  glColor3f(triangle_red, shape_white, shape_white);
  // triangle
  glBegin(GL_POLYGON);
  glVertex2f(triangle_center - triangle_radius * aspect_ratio, 0);
  glVertex2f(triangle_center, triangle_radius);
  glVertex2f(triangle_center + triangle_radius * aspect_ratio, 0);
  glEnd();

  glColor3f(losange_red, shape_white, shape_white);
  // diamond
  glBegin(GL_QUADS);
  glVertex2f(-losange_radius * aspect_ratio + losange_center, 0);
  glVertex2f(+losange_center, losange_radius);
  glVertex2f(losange_radius * aspect_ratio + losange_center, 0);
  glVertex2f(+losange_center, -losange_radius);
  glEnd();

  glColor3f(circle_red, shape_white, shape_white);
  // circle
  int edges = 50;

  GLfloat centerx, centery, temp;

  glBegin(GL_POLYGON);
  temp = 360.0 / (float)edges;
  for (float i = 0; i < 360; i += temp) {
    centerx =
        circle_radius * cos(i * M_PI / 180.0f) * aspect_ratio + circle_center;
    centery = circle_radius * sin(i * M_PI / 180.0f);

    glVertex2f(centerx, centery);
    centerx = 0;
    centery = 0;
  }
  glEnd();
}
/*
void background() {


    GLfloat centerx, centery, temp;
  int acc = 0;;
  int edges = 16;
  glBegin(GL_POLYGON);
  temp = 360.0 / (float)edges;
  for (float i = 0; i < 360; i += temp) {
    acc++;
    if (acc%2 == 1){
  glColor3f(0, 0.5, 0);
    }else{
        glColor3f(0, 1, 0);
    }
    centerx =
        (circle_radius+2.5) * cos(i * M_PI / 180.0f) * aspect_ratio + (x0board +
0.8 * aspect_ratio); centery = (circle_radius+2.5) * sin(i * M_PI / 180.0f);

    glVertex2f(centerx, centery);
    centerx = 0;
    centery = 0;
  }
  glEnd();
}
*/

void transition_board(int shape_select) {
  if (triangle_radius >= 0.8 || losange_radius >= 0.8 ||
      circle_radius >= 0.80) {
    transition *= -1;
    validate_size *= -1;
  }
  if (triangle_radius < 0.8 || losange_radius < 0.8 ||
      circle_radius < 0.85 && shape_white < 1.0) {
    shape_white += 0.006;
  }
  switch (shape_select) {
    case 0:
      if (triangle_radius < 0.80) {
        triangle_radius += 0.002;
      }
      if (triangle_center < (x0board + 0.8 * aspect_ratio)) {
        triangle_center += ((x0board + 0.8 * aspect_ratio) + 0.6) / 200;
      }
      if (circle_radius > 0) {
        circle_radius -= 0.002;
      }
      if (losange_radius > 0) {
        losange_radius -= 0.002;
      }
      break;
    case 1:
      if (losange_radius < 0.80) {
        losange_radius += 0.002;
      }
      cout << losange_center << "EEEEEEEEEEEEEEEEEEEEEEEEEEEE" << endl;
      if (losange_center > -0.24) {
        losange_center -= 0.0012;
      }
      if (circle_radius > 0) {
        circle_radius -= 0.002;
      }
      if (triangle_radius > 0) {
        triangle_radius -= 0.002;
      }
      break;
    case 2:
      if (circle_radius < 0.80) {
        circle_radius += (0.8 - 0.3) / 300;
      }
      if (circle_center > (x0board + 0.8 * aspect_ratio)) {
        circle_center -= (0.6 + x0board + 0.8 * aspect_ratio) / 100;
      }
      if (triangle_radius > 0) {
        triangle_radius -= 0.002;
      }
      if (losange_radius > 0) {
        losange_radius -= 0.002;
      }
      break;
    default:
      break;
  }
}

void highlight_board() {
  //  glColor3f(triangle_red, 0, 0);

  glColor3f(losange_red, 0, 0);
  if (shape_select == 1 && losange_radius < 0.4) {
    losange_radius += 0.001;
    losange_red += 0.005;
    if (triangle_radius > 0.3) {
      triangle_radius -= 0.001;
      triangle_red -= 0.005;
    }
    if (circle_radius > 0.3) {
      circle_radius -= 0.001;
      circle_red -= 0.005;
    }
  }
  glColor3f(triangle_red, 0, 0);
  if (shape_select == 0 && triangle_radius < 0.4) {
    triangle_radius += 0.001;
    triangle_red += 0.005;

    if (losange_radius > 0.3) {
      losange_radius -= 0.001;
      losange_red -= 0.005;
    }
    if (circle_radius > 0.3) {
      circle_radius -= 0.001;
      circle_red -= 0.005;
    }
  }
  glColor3f(circle_red, 0, 0);
  if (shape_select == 2 && circle_radius < 0.4) {
    circle_red += 0.005;
    circle_radius += 0.001;
    if (triangle_radius > 0.3) {
      triangle_radius -= 0.001;
      triangle_red -= 0.005;
    }
    if (losange_radius > 0.3) {
      losange_radius -= 0.001;
      losange_red -= 0.005;
    }
  }
}

void board_size(int shape, int width) {
  int row, c;

  float x1, x2, y1, y2;

  glColor3f(1, 1, 1);

  if (shape == 0) {
    xsquaresize = (2 - 2 * xborder) / (width)*aspect_ratio;
    ysquaresize = (2 - 2 * yborder) / width;
  }
  if (shape == 1) {
    xsquaresize = (2 - 2 * xborder) / (width)*aspect_ratio;
    ysquaresize = (2 - 2 * yborder) / (width);
  }

  if (shape == 2) {
    xsquaresize = (2 - 2 * xborder) / (width)*aspect_ratio;
    ysquaresize = (2 - 2 * yborder) / (width);
  }

  width /= 2;
  width += 1;

  x1 = -1 + xborder;
  y1 = 1 - yborder;

  switch (shape) {
    case 0: {
      // Triangle

      for (row = 1; row <= width; row++) {
        for (c = 0; c < width - row; c++) {
          x1 += xsquaresize;
        }
        for (c = 1; c <= 2 * row - 1; c++) {
          x2 = x1 + xsquaresize;
          y2 = y1 - ysquaresize;

          glBegin(GL_QUADS);
          glVertex2f(x2, y1);
          glVertex2f(x1, y1);
          glVertex2f(x1, y2);
          glVertex2f(x2, y2);
          glEnd();

          x1 += xsquaresize;
        }
        x1 = -1 + xborder;

        y1 -= ysquaresize;

        cout << "\n";
      }
      break;
    }

    case 1: {
      // Diamond

      for (row = 1; row <= width; row++) {
        for (c = 0; c < width - row; c++) {
          x1 += xsquaresize;
        }
        for (c = 1; c <= 2 * row - 1; c++) {
          x2 = x1 + xsquaresize;
          y2 = y1 - ysquaresize;

          glColor3f(1, 1, 1);

          glBegin(GL_QUADS);
          glVertex2f(x2, y1);
          glVertex2f(x1, y1);
          glVertex2f(x1, y2);
          glVertex2f(x2, y2);
          glEnd();

          x1 += xsquaresize;
        }
        x1 = -1 + xborder;

        y1 -= ysquaresize;

        cout << "\n";
      }

      for (row = width; row > 1; row--) {
        for (c = 0; c < width - row + 1; c++) {
          x1 += xsquaresize;
        }
        for (c = 1; c <= 2 * row - 3; c++) {
          x2 = x1 + xsquaresize;
          y2 = y1 - ysquaresize;

          glBegin(GL_QUADS);
          glVertex2f(x2, y1);
          glVertex2f(x1, y1);
          glVertex2f(x1, y2);
          glVertex2f(x2, y2);
          glEnd();

          x1 += xsquaresize;
        }
        x1 = -1 + xborder;

        y1 -= ysquaresize;
      }
      break;
    }

    case 2: {
      int n = 2 * width + 1;

      width -= 1;

      int i, j, x, y;

      for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
          x = i - width;
          y = j - width;

          if (x * x + y * y <= width * width + 1) {
            x1 += (i)*xsquaresize;
            y1 -= (j)*ysquaresize;

            x2 = x1 + xsquaresize;
            y2 = y1 - ysquaresize;

            glBegin(GL_QUADS);
            glVertex2f(x2, y1);
            glVertex2f(x1, y1);
            glVertex2f(x1, y2);
            glVertex2f(x2, y2);
            glEnd();
          }
          x1 = -1 + xborder;
          y1 = 1 - yborder;
        }
        cout << "\n";
      }
      break;
    }
    default:
      cout << "Goodbye" << shape << endl;
  }
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

int actualisation_slideboard() {
  int i, j;
  int again = 0;
  cout << "ACTUAL SLIDEB" << endl;

  for (i = 0; i < g->larg; i++) {
    for (j = g->haut - 1; j >= 0; j--) {
      if (g->slide_board[j][i].slide_value > 4) {
        g->slide_board[j + 1][i].slide_value =
            g->slide_board[j][i].slide_value - 1;
        g->slide_board[j + 1][i].indice_color =
            g->slide_board[j][i].indice_color;
        g->slide_board[j][i].slide_value = 3;
        again = 1;
      } else if (g->slide_board[j][i].slide_value > 3) {
        g->slide_board[j + 1][i].slide_value =
            g->slide_board[j][i].slide_value - 1;
        g->slide_board[j][i].slide_value = 3;
        g->board[j + 1][i] = g->slide_board[j][i].indice_color + 2;
      }
    }
  }
  return again;
}

void slide() {
  int nbslide;
  int i, j;

  cout << "MAGIQUE" << endl;

  for (j = 0; j < g->haut; j++) {
    for (i = 0; i < g->larg; i++) {
      if (g->slide_board[j][i].slide_value > 3) {
        display_one_bloc(g->slide_board[j][i].indice_color, 1,
                         x0board + i * xsquaresize,
                         y0board - j * ysquaresize - g->slide);
      }
    }
  }
  g->slide += 0.001;
  if (g->slide >= ysquaresize) {
    g->slide = 0;
    if (actualisation_slideboard() == 0) {
      cout << "STOPSsLIDE" << endl;
      g->anim_slide = 0;
    }
  }
  cout << "BLABLA" << endl;
}

void print_slide_b() {
  int i, j;
  for (j = 0; j < g->haut; j++) {
    for (i = 0; i < g->larg; i++) {
      cout << g->slide_board[j][i].slide_value << " ";
    }
    cout << endl;
  }
}

void ProcessNormalKeys(unsigned char key, int x, int y) {
  int i;
  int start_anim = 0;

  if (key == ' ') {
    cout << "SPACEBAR" << endl;

    if (welcome == 1) {
      welcome *= -1;
      choose_politique *= -1;
    }

    else if (choose_politique == 1) {
      choose_politique *= -1;
      show_menu *= -1;
    }

    else if (show_menu == 1) {
      show_menu *= -1;
      transition *= -1;
      //  validate_size *= -1;
    } else if (validate_size == 1) {
      playing_game *= -1;
      validate_size *= -1;
      cout << "shape_select" << shape_select << endl;
      ;
      cout << "shape" << shape << endl;
      shape = shape_select + 1;
      create_board(shape, width);
      cout << shape_select << endl;
      init_color_tabl();
      color_table();

    } else if (playing_game == 1) {
      /*
  shape = shape_select;
        cout << "AZE" << endl;
  create_board(shape, width);
  cout << "AZER" << endl;
    init_color_tabl();
color_table();
*/
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
            valeur_row_slideboard(i);
            delete_row(i);
            start_anim = 1;
          }
        }
        if (start_anim == 1) {
          set_slide_board();
          print_slide_b();
          g->anim_slide = 1;
          start_anim = 0;
        }
        /*
        for (i = 0; i < g->larg; i++) {
          if (column_full(i)) {
            delete_col(i);
          }
        }
        */
      } else {
        cout << "222" << endl;
        free(current_b);
        current_b = (bloc*)malloc(sizeof(*current_b));
        create_bloc(current_b, g->tabl_bloc[indice_bloc].type);
        cout << "CAN_BE_INIT" << can_be_init(current_b) << endl;
        g->choosing = (g->choosing + 1) % 2;
      }
    }
    if (key == 'm') {
      show_menu *= -1;
    }
    if (key == 'n') {
      transition *= -1;
    }
    if (key == 'v') {
      validate_size *= -1;
      transition *= -1;
      // show_menu *= -1;
    }
    /*
    if (key == 's') {
      shape_select *= -1;
    }
    */

    if (key == 'b') {
      transition *= -1;
    }
    if (key == 'p') {
      width += 2;
    }
    /*
    if (key == '1') {
      if (choose_politique == 1) {
        choose_politique *= -1;
        show_menu *= -1;
        politique = 1;
      }
    }
        if (key == '2') {
      if (choose_politique == 1) {
        choose_politique *= -1;
        show_menu *= -1;
        politique = 2;
      }
    }
    */
  }
  glutPostRedisplay();
}

void keyboardown(int key, int x, int y) {
  int i;
  switch (key) {
    case GLUT_KEY_RIGHT:
      if (validate_size == 1) {
        width += 2;
      }
      if (choose_politique == 1) {
        politique++;
      }
      if (show_menu == 1 && playing_game != 1) {
        shape_select += 1;
      }
      if (g->choosing == 0) {
        if (can_right(current_b, g) == 1) {
          right(current_b);
        }
      }
      break;

    case GLUT_KEY_LEFT:
      if (validate_size == 1) {
        width -= 2;
      }
      if (show_menu == 1 && playing_game != 1) {
        shape_select -= 1;
      }
      if (choose_politique == 1) {
        politique--;
      }

      else if (playing_game == 1) {
        if (g->choosing == 0) {
          if (can_left(current_b, g) == 1) {
            left(current_b);
          }
        }
      }
      break;

    case GLUT_KEY_UP:
      if (playing_game == 1) {
        if (g->choosing == 0) {
          if (can_top(current_b, g) == 1) {
            top(current_b);
          }
        } else {
          counter = 0;
          select_counter = 1;
          // indice_bloc = (indice_bloc - 1 + g->nb_bloc) % g->nb_bloc;
        }
      }
      break;

    case GLUT_KEY_DOWN:
      if (playing_game == 1) {
        if (g->choosing == 0) {
          if (can_bot(current_b, g) == 1) {
            bot(current_b);
          }
        } else {
          counter = 0;
          select_counter = -1;
          // indice_bloc = (indice_bloc + 1) % g->nb_bloc;
        }
      }
      break;

    case GLUT_KEY_END:
      if (validate_size == 1) {
        width += 2;
      }
      if (choose_politique == 1) {
        politique++;
      }
      if (show_menu == 1 && playing_game != 1) {
        shape_select += 1;
      }
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
  int i = 1;
  int j = 1;
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

void animate(int value) {
  glutTimerFunc(speed, animate, 0);
  time1++;
  if (time1 >= blink) {
    time1 = 0;
    counter++;
  }
  glutPostRedisplay();
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

void black() {
  // background
  glColor3f(0, 0, 0);
  glBegin(GL_QUADS);
  glVertex2f(-1, 1);
  glVertex2f(1, 1);
  glVertex2f(1, -1);
  glVertex2f(-1, -1);
  glEnd();
}

void display() {
  black();
  cout << width << endl;
  cout << shape_select << endl;
  if (shape_select < 0) {
    shape_select = 2;
  }
  if (shape_select > 2) {
    shape_select = 0;
  }
  if (width < 21) {
    width = 37;
  }
  if (width > 37) {
    width = 21;
  }

  if (politique < 1) {
    politique = 1;
  }
  if (politique > 2) {
    politique = 2;
  }

  if (welcome == 1) {
    DisplayMenu();
  } else if (choose_politique == 1) {
        politique_display();
    show_politique();

  }

  else if (show_menu == 1) {
    //  width = 1;
    choose_board();
    highlight_board();
  } else if (transition == 1) {
    choose_board();
    highlight_board();
    transition_board(shape_select);
  } else if (validate_size == 1) {
    // choose_board();
    board_size(shape_select, width);
  }

  else if (playing_game == 1) {
    int indice_plus = (indice_bloc + 1) % g->nb_bloc;
    int indice_plus2 = (indice_bloc + 2) % g->nb_bloc;
    int indice_moins = (indice_bloc - 1 + g->nb_bloc) % g->nb_bloc;
    int indice_moins2 = (indice_bloc - 2 + g->nb_bloc) % g->nb_bloc;
    glClear(GL_COLOR_BUFFER_BIT);
    glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
    // dis(g, 1, 1, 1, 1, x0board, y0board);
    // background();
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

    if (g->anim_slide == 1) {
      display_one_bloc(5, 1, 0.5, 0.5);
      slide();
    }

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
      display_bloc(&(g->tabl_bloc[indice_plus2]), small_scale1,
                   g->color_tabl[indice_plus2].r, g->color_tabl[indice_plus2].g,
                   g->color_tabl[indice_plus2].b,
                   x0board + 1.5 -
                       small_scale1 * xsquaresize *
                           (g->tabl_bloc[indice_plus2]).larg / 2,
                   y0board - ypos1 +
                       (small_scale1 * ysquaresize *
                        (g->tabl_bloc[indice_plus2]).haut / 2));
      display_bloc(
          &(g->tabl_bloc[indice_plus]), small_scale2,
          g->color_tabl[indice_plus].r, g->color_tabl[indice_plus].g,
          g->color_tabl[indice_plus].b,
          x0board + 1.5 -
              small_scale2 * xsquaresize * (g->tabl_bloc[indice_plus]).larg / 2,
          y0board - ypos2 +
              (small_scale2 * ysquaresize * (g->tabl_bloc[indice_plus]).haut /
               2));
      display_bloc(&(g->tabl_bloc[indice_moins]), small_scale3,
                   g->color_tabl[indice_moins].r, g->color_tabl[indice_moins].g,
                   g->color_tabl[indice_moins].b,
                   x0board + 1.5 -
                       small_scale3 * xsquaresize *
                           (g->tabl_bloc[indice_moins]).larg / 2,
                   y0board - ypos4 +
                       (small_scale3 * ysquaresize *
                        (g->tabl_bloc[indice_moins]).haut / 2));
      display_bloc(&(g->tabl_bloc[indice_moins2]), small_scale1,
                   g->color_tabl[indice_moins2].r,
                   g->color_tabl[indice_moins2].g,
                   g->color_tabl[indice_moins2].b,
                   x0board + 1.5 -
                       small_scale1 * xsquaresize *
                           (g->tabl_bloc[indice_moins2]).larg / 2,
                   y0board - ypos5 +
                       (small_scale1 * ysquaresize *
                        (g->tabl_bloc[indice_moins2]).haut / 2));
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

    // background();
  }

  glFlush();
}

int main(int argc, char** argv) {
  int i;
  current_b = (bloc*)malloc(sizeof(*current_b));

  /*

    shape = shape_select;
    create_board(shape, width);
    cout << "AZER" << endl;
    init_color_tabl();
    color_table();


  */

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
