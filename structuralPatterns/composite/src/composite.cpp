#include <iostream>
#include <vector>
using namespace std;

// 2. create an "interface" (lowest common denominator)
class Component {
public:
  virtual void traverse()=0;
};

class Leaf:public Component {
  //1. Scalar class 3. "is a" relationship
  int value;
public:
  Leaf(int val){value = val;}
  void traverse(){cout << value << ' ';}
};

class Composite: public Component {
  // 1. vector class 3. "is a" relationship
  vector<Component*>children; //4. "container" coupled to the interface
public:
  // 4. "container" class coupled to the interface
  void add(Component *ele){children.push_back(ele);}
  void traverse(){
    for (unsigned int i=0; i<children.size(); i++)
      // 5. Use polymorphism to delegate to children
      children[i]->traverse();
  }
};

int main(int argc, char *argv[]) {
  Composite containers[4];
  for (int i=0; i<4; i++)
    for (int j=0; j<3; j++)
      containers[i].add(new Leaf(i*3+j));

  for (int i=1; i<4; i++) containers[0].add(&(containers[i]));

  for (int i=0; i<4; i++) {
    containers[i].traverse();
    cout << endl;
  }

  return 0;
}
