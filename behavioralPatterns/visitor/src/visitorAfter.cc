#include <iostream>
using namespace std;

class Color {
public:
  virtual void accept(class Visitor*)=0;
};

class Red: public Color {
public:
  /**/void accept(Visitor*);
  void eye(){ cout << "Red::eye\n";}
  void show(){ cout << "I'm Red\n";}
};

class Blu: public Color {
public:
  /**/void accept(Visitor*);
  void sky(){cout << "Blu::sky\n";}
  void show(){ cout << "I'm Blue\n";}
};

class Visitor {
public:
  virtual void visit(Red*)=0;
  virtual void visit(Blu*)=0;
};

void Red::accept(Visitor *v){ v->visit(this);}
void Blu::accept(Visitor *v){ v->visit(this);}

class CountVisitor: public Visitor {
public:
  CountVisitor(){m_num_red = m_num_blu = 0;}
  /**/void visit(Red*){++m_num_red;}
  /**/void visit(Blu*){++m_num_blu;}
  void report_num(){ cout << "Reds:" << m_num_red << ",  "
                          << "Blus:" << m_num_blu << '\n';}
private:
  int m_num_red, m_num_blu;
};

class CallVisitor: public Visitor {
public:
  /**/void visit(Red *r){r->eye();}
  /**/void visit(Blu *b){b->sky();}
};

class ShowVisitor :public Visitor{
public:
  /**/void visit(Red *r){r->show();}
  /**/void visit(Blu *b){b->show();}
};

int main(int argc, char *argv[]) {

  Color *set[]={new Red, new Blu, new Blu, new Red, new Red, 0};
  CountVisitor count_operation;
  CallVisitor call_operation;
  ShowVisitor showOperation;

  for (int i = 0; set[i]; i++) {
    set[i]->accept(&count_operation);
    set[i]->accept(&call_operation);
    set[i]->accept(&showOperation);
  }
  count_operation.report_num();
  return 0;
}
