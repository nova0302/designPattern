#include <iostream>
using namespace std;

class Shape {
public:
  Shape(){id_ = total_++;}
  virtual void draw() = 0;
protected:
  int id_;
  static int total_;
};
int Shape::total_ = 0;
class Circle : public Shape {
public:
  void draw(){cout << "circle " << id_ << ": draw" << endl;}
};
class Square :public Shape{
public:
  void draw(){cout << "square " << id_ << ": draw" << endl;}
};
class Ellipse: public Shape {
public:
  void draw(){cout << "ellipse " << id_ << ": draw" << endl;}
};
class Rectangle: public Shape {
public:
  void draw(){cout << "rectangle " << id_ << ": draw" << endl;}
};
class Factory {
public:
  virtual Shape *createCurvedInstance()=0;
  virtual Shape *createStraightInstance()=0;
};
class SimpleShapeFactory: public Factory {
public:
  virtual Shape *createCurvedInstance(){return new Circle;}
  virtual Shape *createStraightInstance(){return new Square;}
};
class RobustShapeFactory:public Factory {
public:
  virtual Shape *createCurvedInstance(){return new Ellipse;}
  virtual Shape *createStraightInstance(){return new Rectangle;}
};
//#define SIMPLE
int main(int argc, char *argv[]) {

  #ifdef SIMPLE
  Factory *f = new SimpleShapeFactory();
  #else
  Factory *f = new RobustShapeFactory();
  #endif
  Shape *shapes[4] = {0,0,0,0};
  shapes[0] = f->createCurvedInstance();
  shapes[1] = f->createStraightInstance();
  shapes[2] = f->createCurvedInstance();
  for (int i = 0;  shapes[i]; i++)
    shapes[i]->draw();
  return 0;
}
