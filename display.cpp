#include <iostream>
#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include "proj.cpp"

#define WIDTHWINDOW 700;
#define HEIGHTWINDOW 700;

// TESTING TETRIS

using namespace std;

int choosingpiece;
float deplacex, deplacey, xx, yy;
float move_unit = 0.18f;

int shape;
int width;

float xborder = 0.2;
float yborder = 0.2;
float x0board = -1 + xborder;
float y0board = 1 - yborder;
float squaresize = 0.08;

void display_plateau(int shape, int width)
{

  int row, c;

  float x1, x2, y1, y2;
  width /= 2;
  width += 1;

  x1 = -1 + xborder;
  y1 = 1 - yborder;

  switch (shape)
  {
  case 1:
  {

    // Triangle

    for (row = 1; row <= width; row++)
    {

      for (c = 0; c < width - row; c++)
      {
        x1 += squaresize;
      }
      for (c = 1; c <= 2 * row - 1; c++)
      {

        x2 = x1 + squaresize;
        y2 = y1 - squaresize;

        glColor3f(0.90, 0.22, 0);

        glBegin(GL_QUADS);
        glVertex2f(x2, y1);
        glVertex2f(x1, y1);
        glVertex2f(x1, y2);
        glVertex2f(x2, y2);
        glEnd();

        x1 += squaresize;
      }
      x1 = -1 + xborder;

      y1 -= squaresize;

      cout << "\n";
    }
    break;
  }
// this is a test

  case 2:
  {

    // Diamond

    for (row = 1; row <= width; row++)
    {

      for (c = 0; c < width - row; c++)
      {
        x1 += squaresize;
      }
      for (c = 1; c <= 2 * row - 1; c++)
      {

        x2 = x1 + squaresize;
        y2 = y1 - squaresize;

        glColor3f(0.90, 0.22, 0);

        glBegin(GL_QUADS);
        glVertex2f(x2, y1);
        glVertex2f(x1, y1);
        glVertex2f(x1, y2);
        glVertex2f(x2, y2);
        glEnd();

        x1 += squaresize;
      }
      x1 = -1 + xborder;

      y1 -= squaresize;

      cout << "\n";
    }

    for (row = width; row > 1; row--)
    {

      for (c = 0; c < width - row + 1; c++)
      {
        x1 += squaresize;
      }
      for (c = 1; c <= 2 * row - 3; c++)
      {
        x2 = x1 + squaresize;
        y2 = y1 - squaresize;

        glColor3f(0.90, 0.22, 0);

        glBegin(GL_QUADS);
        glVertex2f(x2, y1);
        glVertex2f(x1, y1);
        glVertex2f(x1, y2);
        glVertex2f(x2, y2);
        glEnd();

        x1 += squaresize;
      }
      x1 = -1 + xborder;

      y1 -= squaresize;
    }
    break;
  }

  case 3:
  {

    int n = 2 * width + 1;

    int i, j, x, y;

    for (i = 0; i < n; i++)
    {
      for (j = 0; j < n; j++)
      {

        x = i - width;
        y = j - width;

        if (x * x + y * y <= width * width + 1)
        {

          x1 += i * squaresize;
          y1 -= j * squaresize;

          x2 = x1 + squaresize;
          y2 = y1 - squaresize;

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

void init()
{
  // set clear color to black
  glClearColor(0.0, 0.0, 0.0, 0.0);

  // set fill color to white
  glColor3f(1.0, 1.0, 1.0);
}

void ProcessNormalKeys(unsigned char key, int x, int y)
{

  int c;

  if (key == ' ')
  {
    cout << "SPACEBAR" << endl;
    //g->choosing = 1;
    placement_bloc(current_b);
    for (c = 0; c < g->larg; c++)
    {
      if (column_full(c))
      {
        delete_col(c);
      }
    }
    free(current_b);
    current_b = (bloc *)malloc(sizeof(*current_b));
    bloc20(current_b);
  }
    glutPostRedisplay();

}

void keyboardown(int key, int x, int y)
{

  switch (key)
  {
  case GLUT_KEY_RIGHT:
    if (can_right(current_b, g) == 1)
    {
      right(current_b);
    }
    break;

  case GLUT_KEY_LEFT:
    if (can_left(current_b, g) == 1)
    {
      left(current_b);
    }
    break;

  case GLUT_KEY_UP:
    if (can_top(current_b, g) == 1)
    {
      top(current_b);
    }
    break;

  case GLUT_KEY_DOWN:
    if (can_bot(current_b, g) == 1)
    {
      bot(current_b);
    }
    break;

  case GLUT_KEY_END:

    choosingpiece *= -1;

    break;

  default:
    break;
  }
  glutPostRedisplay();
}

void display_bloc(bloc *b, float scaling, float r, float g, float blue, float x, float y)
{

  int i, j;

  glColor3f(r, g, blue);

  for (i = 0; i < b->haut; i++)
  {
    for (j = 0; j < b->larg; j++)
    {
      if (b->mat[i][j] == 1)
      {
        glBegin(GL_QUADS);
        glVertex2f(x + j * squaresize * scaling, y - i * squaresize * scaling);
        glVertex2f(x + (j + 1) * squaresize * scaling, y - i * squaresize * scaling);
        glVertex2f(x + (j + 1) * squaresize * scaling, y - (i + 1) * squaresize * scaling);
        glVertex2f(x + (j)*squaresize * scaling, y - (i + 1) * squaresize * scaling);
        glEnd();
      }
    }
  }
}

void dis(game *g, float scaling, float r, float green, float blue, float x, float y)
{

  int i, j;

  for (i = 0; i < g->haut; i++)
  {
    for (j = 0; j < g->larg; j++)
    {
      if (g->board[i][j] == 0)
      {
        glColor3f(0.2, 0.2, 0.2);
      }
      else if (g->board[i][j] == 1)
      {
        glColor3f(0.90, 0.22, 0);
      }
      else
      {
        glColor3f(0.5, 0.5, 0);
      }
      glBegin(GL_QUADS);
      glVertex2f(x + j * squaresize * scaling, y - i * squaresize * scaling);
      glVertex2f(x + (j + 1) * squaresize * scaling, y - i * squaresize * scaling);
      glVertex2f(x + (j + 1) * squaresize * scaling, y - (i + 1) * squaresize * scaling);
      glVertex2f(x + (j)*squaresize * scaling, y - (i + 1) * squaresize * scaling);
      glEnd();
    }
  }
}

void display()
{

  glClear(GL_COLOR_BUFFER_BIT);

  dis(g, 1, 1, 1, 1, x0board, y0board);

  display_bloc(current_b, 1, 1, 1, 1, x0board + current_b->x * squaresize, y0board - current_b->y * squaresize);

  glFlush();
}

int main(int argc, char **argv)
{

  int i;

  cout << "Triangle: 1   -   Diamond: 2   -   Circle: 3\n"
       << endl;
  cin >> shape;
  cout << "Width" << endl;
  cin >> width;

  if (shape == 1)
  {
    squaresize = (2 - 2 * xborder) / (2 * width - 1);
  }
  if (shape == 2)
  {
    squaresize = (2 - 2 * xborder) / (2 * width - 1);
  }

  if (shape == 3)
  {
    squaresize = (2 - 2 * xborder) / (2 * width - 1);
  }

  move_unit = squaresize;
  cout << "AZE" << endl;
  create_board(shape, width);
  cout << "AZER" << endl;
  current_b = (bloc *)malloc(sizeof(*current_b));
  bloc7(current_b);
  cout << "AZERT" << endl;

  /*
  create_board(3);
  blocT5( );
  add_bloc();
  display_board();
  cout << endl << endl;
  display_bloc();
  */
  //  test_init_blocs();

  cout << x0board << endl;
  cout << y0board << endl;
  cout << current_b->x << endl;
  cout << current_b->y << endl;

  /*
  bestiaire(57,57);

  for(i=0 ; i<10 ; i++){
    cout << rand_a_b(0,100);
  }
  */

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(1000, 700);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("TETRIS");
  // glutTimerFunc(1.0, animate, 0);
  glutDisplayFunc(display);
  // glutTimerFunc(TIMERSECS, animate, 0);
  // init();
  glutKeyboardFunc(ProcessNormalKeys);
  glutSpecialFunc(keyboardown);

  glutPostRedisplay();
  glutMainLoop();
}
