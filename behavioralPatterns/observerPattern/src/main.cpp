#include <iostream>
#include <vector>
using namespace std;

class Subject {
  // 1. "independent" functionality
  vector < class Observer * > views; // 3. Coupled only to "interface"
  int value;
public:
  void attach(Observer *obs){views.push_back(obs);}
  void setVal(int val){
    value = val;
    notify();
  }
  int getVal(){return value;}
  void notify();
};

class Observer{
  // 2. "dependent" functionality
  Subject *model;
  int denom;
public:
  Observer(Subject *mod, int div){
    model = mod;
    denom = div;
    // 4. Observers register temselves with the Subject
    model->attach(this);
  }
  virtual void update() = 0;
protected:
  Subject *getSubject(){return model;}
  int getDivisor(){return denom;}
};

void Subject::notify(){
  // 5. Publisher broadcasts
  for(unsigned int i=0; i<views.size(); i++)
    views[i]->update();
}
class DivObserver: public Observer {
public:
  DivObserver(Subject *mod, int div): Observer(mod, div){}
  void update(){
    // 6. "pull" information of interest
    int v = getSubject()->getVal(), d = getDivisor();
    cout << v << " div " << d << "is " << v/d << '\n';
  }
};

class ModObserver: public Observer {
public:
  ModObserver(Subject *mod, int div): Observer(mod, div){}
  void update(){

    int v = getSubject()->getVal(), d = getDivisor();
    cout << v << " mod " << d << " is " << v%d << '\n';
  }

};
int main(int argc, char *argv[])
{
  Subject subj;
  DivObserver divObs1(&subj, 4);
  DivObserver divObs2(&subj, 3);
  ModObserver modObs3(&subj, 3);
  subj.setVal(14);

  return 0;
}
