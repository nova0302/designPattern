#include <iostream>
using namespace std;

class Giant {
public:
  enum Type{Fee, Phi, Pheaux};
  Giant(){
    m_id = s_next++;
    m_type = (Type)(m_id % 3);
  }
  Type get_type(){return m_type;}
  void fee(){cout << m_id << "-fee " << endl;}
  void phi(){cout << m_id << "-phi " << endl;}
  void pheaux(){cout << m_id << "-pheaux " << endl;}
private:
  Type m_type;
  int m_id;
  static int s_next;
};
int Giant::s_next = 0;

class Command {
  typedef void(Giant:: *Action)();
private:
  Giant *m_object;
  Action m_method;

public:
  Command(Giant *object, Action method){
    m_object = object;
    m_method = method;
  }
  void execute(){(m_object->*m_method)();}
  ~Command(){
    cout << "~Command is called." << endl;
    delete m_object;
  }
};

template<typename T> class Queue{
public:
  Queue(){m_add = m_remove = 0;}
  void enque(T *c){
    m_array[m_add] = c;
    m_add = (m_add+1) % SIZE;
  }
  T *deque(){
    int temp = m_remove;
    m_remove = (m_remove+1) % SIZE;
    return m_array[temp];
  }
private:
  enum {SIZE = 8};
  T *m_array[SIZE];
  int m_add, m_remove;
};

int main(int argc, char *argv[]) {

  //Queue<Giant> que;
  Queue<Command> que;
  Command *input[] = {
    new Command(new Giant, &Giant::fee),
    new Command(new Giant, &Giant::phi),
    new Command(new Giant, &Giant::pheaux),
    new Command(new Giant, &Giant::fee),
    new Command(new Giant, &Giant::phi),
    new Command(new Giant, &Giant::pheaux)
    ,0
  };
  for (int i = 0; input[i]; i++) input[i]->execute();
  cout << endl;

  for(int i = 0; i < 6; i++) que.enque(input[i]);
  cout << endl;

  for(int i = 0; i < 6; i++) que.deque()->execute();

  return 0;
}
