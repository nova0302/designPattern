#include <iostream>
#include <vector>

using namespace std;

class Component {
public:
  virtual void traverse()=0;
};

class Primitive: public Component {
  int value;
public:
  Primitive(int val){value = val;}
  void traverse(){
    cout << value << ' ';
  }
};

class Composite:public Component {
  vector<Component*>children;
  int value;
public:
  Composite(int val){value = val;}
  void add(Component *c){children.push_back(c);}
  void traverse(){
    cout << value << " ";
    for (int i=0; i<children.size(); i++) {
      children[i]->traverse();
    }
  }
};

class Row: public Composite {
public:
  // Two different kinds of "con
  Row(int val):Composite(val){}
  //tainer" classes. Most of the
  void traverse(){
    // "meat" is in the Composite
    cout << "Row"; //base class
    Composite::traverse();
  }
};

class Column:public Composite {
public:
  Column(int val):Composite(val){}
  void traverse(){
    cout << "Col";
    Composite::traverse();
  }
};
int main(int argc, char *argv[])
{
  Row first(1);
  Column second(2);
  Column third(2);
  Row fourth(4);
  Row fifth(5);
  first.add(&second);
  first.add(&third);
  third.add(&fourth);
  third.add(&fifth);
  first.add(&Primitive(6));
  second.add(&Primitive(7));
  third.add(&Primitive(8));
  fourth.add(&Primitive(9));
  fifth.add(&Primitive(10));
  first.traverse();
  cout <<'\n';


  return 0;
}
