#include <GL/glut.h>
#include "kirito_and_asuna.h"
#include <cstdlib>
#include <cmath>
#include <ctime>

class screen{
public:
  static const int width  = 700;
  static const int height = 505;
};

typedef float Color[3];

struct Pixel{
  float x,y;
  int 	x0,y0;
  Color color;
};

Pixel bitmap[height][width];

void display(){
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POINTS);
      for(int y = 0; y < height; y++)
	for(int x=0;x<width; x++){
	  Pixel &p = bitmap[y][x];
	  glColor3f(p.color[0], p.color[1], p.color[2]);
	  glVertex2f(p.x, p.y);
	  float d = sqrt((p.x0 -p.x) * (p.x0 -p.x) + (p.y0 -p.y) * (p.y0 -p.y));
	  if(d > 10.1){
	    p.x += 10.1 * (p.x0 - p.x) / d;
	    p.y += 10.1 * (p.y0 - p.y) / d;
	  }else{
	    p.x = p.x0;
	    p.y = p.y0;
	  }
	}
  glEnd();
  glutSwapBuffers();
}

void timer(int = 0){
  display();
  glutTimerFunc(1, timer, 0);
}

int xEffect1(int x){
  return rand() % width;
}
int yEffect1(int y){
  return rand() % height;
}
int xEffect2(int x){
  return width-x;
}
int yEffect2(int y){
  return height-y;
}
int xEffect3(int x){
  return (x%2==0)? x-width : width+x;
}
int yEffect3(int y){
  return (y%2==0)? y-height : height+y;
}

int main(int argc, char **argv){
  srand( time(0) );
  const char *d = header_data;
  Color pixel;
  for(int y = 0; y < height; y++){
    for(int x = 0;x < width; x++){
      HEADER_PIXEL(d, pixel);
      Pixel &p = bitmap[y][x];
      p.color[0] = pixel[0] / 255.0;
      p.color[1] = pixel[1] / 255.0;
      p.color[2] = pixel[2] / 255.0;
      p.x0 = x;
      p.y0 = y;
      p.x = xEffect2(x);
      p.y = yEffect1(y);
    }
  }
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(screen::width, screen::height);
  glutInitWindowPosition(80, 40);
  glutCreateWindow("Program");
  glClearColor(0, 0, 0, 1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, screen::width, screen::height, 0, -1.0, 1.0);
  glutDisplayFunc(display);
  timer();
  glutMainLoop();
  return 0;
}
