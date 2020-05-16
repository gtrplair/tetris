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

int indice_bloc = 0;

int time1;
float speed = 1.0f;
int blink = 100;

/*
void display_plateau(int shape, int width) {
  int row, c;

  float x1, x2, y1, y2;
  width /= 2;
  width += 1;

  // xsquaresize = 2 * (1-xborder) / width;
  // ysquaresize = 2 * (1-yborder) / width;

  x1 = -1 + xborder;
  y1 = 1 - yborder;

  switch (shape) {
    case 1: {
      // Triangle

      for (row = 1; row <= width; row++) {
        for (c = 0; c < width - row; c++) {
          x1 += xsquaresize;
        }
        for (c = 1; c <= 2 * row - 1; c++) {
          x2 = x1 + xsquaresize;
          y2 = y1 - ysquaresize;

          glColor3f(0.90, 0.22, 0);

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
      // this is a test

    case 2: {
      // Diamond

      for (row = 1; row <= width; row++) {
        for (c = 0; c < width - row; c++) {
          x1 += xsquaresize;
        }
        for (c = 1; c <= 2 * row - 1; c++) {
          x2 = x1 + xsquaresize;
          y2 = y1 - ysquaresize;

          glColor3f(0.90, 0.22, 0);

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

          glColor3f(0.90, 0.22, 0);

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

    case 3: {
      int n = 2 * width + 1;

      int i, j, x, y;

      for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
          x = i - width;
          y = j - width;

          if (x * x + y * y <= width * width + 1) {
            x1 += i * xsquaresize;
            y1 -= j * ysquaresize;

            x2 = x1 + xsquaresize;
            y2 = y1 - ysquaresize;

            glColor3f(0.90, 0.22, 0);

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
      cout << "Goodbye";
  }
}
*/

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
  int c;

  if (key == ' ') {
    cout << "SPACEBAR" << endl;
    if (g->choosing == 0) {
      cout << "111" << endl;
      placement_bloc(current_b);
      g->choosing = (g->choosing + 1) % 2;
      for (c = 0; c < g->larg; c++) {
        if (column_full(c)) {
          delete_col(c);
        }
      }
    } else {
      cout << "222" << endl;
      free(current_b);
      current_b = (bloc*)malloc(sizeof(*current_b));
      create_bloc(current_b, g->tabl_bloc[indice_bloc].type);
      cout << can_be_init(current_b) << endl;
      g->choosing = (g->choosing + 1) % 2;
    }
  }
  glutPostRedisplay();
}

void keyboardown(int key, int x, int y) {
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
        indice_bloc = (indice_bloc - 1 + g->nb_bloc) % g->nb_bloc;
      }
      break;

    case GLUT_KEY_DOWN:
      if (g->choosing == 0) {
        if (can_bot(current_b, g) == 1) {
          bot(current_b);
        }
      } else {
        indice_bloc = (indice_bloc + 1) % g->nb_bloc;
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
        glColor3f(0.2, 0.2, 0.2);
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

void display() {
  int indice_plus = (indice_bloc + 1) % g->nb_bloc;
  int indice_moins = (indice_bloc - 1 + g->nb_bloc) % g->nb_bloc;
  glClear(GL_COLOR_BUFFER_BIT);

  dis(g, 1, 1, 1, 1, x0board, y0board);

  if (g->choosing == 0) {
    display_bloc(current_b, 1, 0.15, 0.5, 0.15,
                 x0board + current_b->x * xsquaresize,
                 y0board - current_b->y * ysquaresize);
  }

  else if (g->choosing == 1) {
    display_bloc(&(g->tabl_bloc[indice_plus]), 0.9, 0.1, 0.1, 0.1, x0board + 1,
                 y0board - 0.2);
    display_bloc(&(g->tabl_bloc[indice_bloc]), 1.1, 0.9, 0.9, 0.9, x0board + 1,
                 y0board - 0.5);
    display_bloc(&(g->tabl_bloc[indice_moins]), 0.9, 0.1, 0.1, 0.1, x0board + 1,
                 y0board - 0.8);
  }

  glFlush();
}

/*







}






*/

void animate(int value) {
  glutTimerFunc(speed, animate, 0);
  time1++;
  if (time1 >= blink)
    time1 = 0;
  glutPostRedisplay();
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
