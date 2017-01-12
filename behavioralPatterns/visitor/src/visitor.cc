#include <iostream>
#include <string.h>
using namespace std;

// 1. Add on accept(Visitor) method to the "element" hierarchy
class Element {
public:
  virtual void accept(class Visitor &v)=0;
};
class This: public Element {
public:
  /*virtual*/void accept(Visitor &v);
  string thiss(){return "This";}
};
class That: public Element {
public:
  /*virtual*/void accept(Visitor &v);
  string that(){return "That";}
};

class TheOther: public Element {
public:
  /*virtual*/ void accept(Visitor &v);
  string theOther(){ return "TheOther";}
};

// 2. Crete a "visitor" base class w/ a visit() method for every "element" type
class Visitor {
public:
  virtual void visit(This *e)=0;
  virtual void visit(That *e)=0;
  virtual void visit(TheOther *e)=0;
};

/*virtual*/void This::accept(Visitor &v){v.visit(this);}
/*virtual*/void That::accept(Visitor &v){v.visit(this);}
/*virtual*/void TheOther::accept(Visitor &v){v.visit(this);}

// 3. Create a "visitor" derived class for each "operation" to do on "elements"
class UpVisitor: public Visitor {
public:
  /**/void visit(This *e){ cout << "do Up on" << e->thiss() << endl;}
  /**/void visit(That *e){ cout << "do Up on" << e->that() << endl;}
  /**/void visit(TheOther *e){ cout << "do Up on" << e->theOther() << endl;}
};

class DownVisitor: public Visitor {
public:
  /**/void visit(This *e){cout << "do Down on " << e->thiss() << endl;}
  /**/void visit(That *e){cout << "do Down on " << e->that() << endl;}
  /**/void visit(TheOther *e){cout << "do Down on " << e->theOther() << endl;}
};



int main(int argc, char *argv[]) {
  Element *list[]={new This(), new That(), new TheOther(), 0};
  UpVisitor up;
  DownVisitor down;
  //  LeftVisitor left;
  //  RightVisitor right;
  for (int i = 0; list[i]; i++)
    // and passes each
    list[i]->accept(up);
  for (int i = 0; list[i]; i++)
    // to accept() calls
    list[i]->accept(down);
  //  for (int i = 0; list[i]; i++)
  //    // to accept() calls
  //    list[i]->accept(left);
  //  for (int i = 0; list[i]; i++)
  //    // to accept() calls
  //    list[i]->accept(right);
  return 0;

}
class LeftVisitor: public Visitor {
public:
  /**/void visit(This *e){cout << "do Left on " << e->thiss() << endl;}
  /**/void visit(That *e){cout << "do Left on " << e->that() << endl;}
  /**/void visit(TheOther *e){cout << "do Left on " << e->theOther() << endl;}
};

class RightVisitor: public Visitor {
public:
  /**/void visit(This *e){cout << "do Right on " << e->thiss() << endl;}
  /**/void visit(That *e){cout << "do Right on " << e->that() << endl;}
  /**/void visit(TheOther *e){cout << "do Right on " << e->theOther() << endl;}
};
