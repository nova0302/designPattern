#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

enum PersistenceType{File, Queue, Pathway};
struct PersistenceAttribute {
  PersistenceType type;
  char value[30];
};
class DistrWorkPackage {
  char _desc[200], _temp[80];
public:
  DistrWorkPackage(char *type){
    sprintf(_desc, "Distributed Work Package for: %s", type);
  }
  void setFile(char *f, char *v){
    sprintf(_temp, "\n File(%s): %s", f, v);
    strcat(_desc, _temp);
  }
  void setQueue(char *q, char *v){
    sprintf(_temp, "\n Queue(%s): %s", q, v);
    strcat(_desc, _temp);
  }
  void setPathway(char *q, char *v){
    sprintf(_temp, "\n Pathway(%s): %s", q, v);
    strcat(_desc, _temp);
  }
  const char *getState(){ return _desc;}
};

class Builder {
protected:
  DistrWorkPackage *_result;
public:
  virtual void configureFile(char*) = 0;
  virtual void configureQueue(char*) = 0;
  virtual void configurePathway(char*) = 0;
  DistrWorkPackage *getResult(){return _result;}
};

class UnixBuilder: public Builder {
public:
  UnixBuilder(){_result = new DistrWorkPackage((char*)"Unix");}
  void configureFile(char *name){ _result->setFile((char*)"flatFile", name);}
  void configureQueue(char *queue){_result->setQueue((char*)"FIFO", queue);}
  void configurePathway(char *type){_result->setPathway((char*)"thread", type);}
};

class VmsBuilder: public Builder {
public:
  VmsBuilder(){_result = new DistrWorkPackage((char*)"Vms");}
  void configureFile(char *name){ _result->setFile((char*)"ISAM", name);}
  void configureQueue(char *queue){_result->setQueue((char*)"priority", queue);}
  void configurePathway(char *type){_result->setPathway(strdup("LWP"), type);}
};

class Reader {
private:
  Builder *_builder;
public:
  void setBuilder(Builder *b){ _builder = b;}
  void construct(PersistenceAttribute[], int);
};
void Reader::construct(PersistenceAttribute list[], int num){
  for (int i=0; i<num; i++) {
    if(list[i].type == File)
      _builder->configureFile(list[i].value);
    else if(list[i].type == Queue)
      _builder->configureQueue(list[i].value);
    else if(list[i].type == Pathway)
      _builder->configurePathway(list[i].value);
  }
}
const int NUM_ENTRIES = 6;
PersistenceAttribute input[NUM_ENTRIES]={
  {File, "state.dat"},
  {File, "confif.sys"},
  {Queue, "compute"},
  {Queue, "log"},
  {Pathway, "authentication"},
  {Pathway, "error processing"}
};

int main(int argc, char *argv[])
{
  UnixBuilder unixBuilder;
  VmsBuilder vmsBuilder;
  Reader reader;

  reader.setBuilder(&unixBuilder);
  reader.construct(input, NUM_ENTRIES);
  cout << unixBuilder.getResult()->getState() << endl;

  reader.setBuilder(&vmsBuilder);
  reader.construct(input, NUM_ENTRIES);
  cout << vmsBuilder.getResult()->getState() << endl;
  return 0;
}
