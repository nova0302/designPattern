#include <iostream>
#include <string.h>

using namespace std;

class Icon {
public:
  Icon(char *fileName){
    strcpy(_name, fileName);
    if (!strcmp(fileName, "go")) {
      _width = 20;
      _height = 20;
    }
    if (!strcmp(fileName, "stop")) {
      _width = 40;
      _height = 40;
    }
    if (!strcmp(fileName, "select")) {
      _width = 60;
      _height = 80;
    }
    if (!strcmp(fileName, "undo")) {
      _width = 30;
      _height = 30;
    }
  }
  const char *getName(){return _name;}
  void draw(int x, int y){
    cout << "   drawing " << _name
         << " : upper left (" << x
         << "," << y
         << ") - lower right (" << x + _width
         << "," << y + _height
         << ")" << endl;
  }
private:
  char _name[20];
  int _width, _height;
};

class FlyweightFactory {
public:
  static Icon *getIcon(char *name){
    for (int i = 0; i < _numIcons; i++)
      if (!strcmp(name, _icons[i]->getName()))
        return _icons[i];
      _icons[_numIcons] = new Icon(name);
      return _icons[_numIcons++];
  }
  static void reportTheIcons(){
    cout << "Active Flyweights: ";
    for (int i = 0; i < _numIcons; i++)
      cout << _icons[i]->getName() << " ";
    cout << endl;
  }
private:
  enum {MAX_ICONS = 5};
  static int _numIcons;
  static Icon *_icons[MAX_ICONS];
};

int FlyweightFactory::_numIcons = 0;
Icon *FlyweightFactory::_icons[];

class DialogBox {
public:
  DialogBox(int x, int y, int incr):_iconsOriginX(x), _iconsOriginY(y),
                                    _iconsXIncrement(incr){};
  virtual void draw() = 0;
  protected:
  Icon *_icons[4];
  int _iconsOriginX, _iconsOriginY, _iconsXIncrement;
};
class FileSelcetion: public DialogBox {
public:
  FileSelcetion(Icon *first, Icon *second, Icon *third): DialogBox(100, 100, 100){
    _icons[0] = first;
    _icons[1] = second;
    _icons[2] = third;
    _icons[3] = 0;
  };
  void draw(){
    cout << "drawing FileSelection:" << endl;
    //for (int i = 0; i < 3; i++)
    for (int i = 0; _icons[i]; i++)
      _icons[i]->draw(_iconsOriginX+(i*_iconsXIncrement), _iconsOriginY);
  }
};
class CommitTransaction: public DialogBox {
public:
  CommitTransaction(Icon *first, Icon *second, Icon *third):DialogBox(150, 150, 150){
    _icons[0] = first;
    _icons[1] = second;
    _icons[2] = third;
  };
  void draw(){
    cout << "drawing CommmitTransaction:" << endl;
    for (int i = 0; i < 3; i++)
      _icons[i]->draw(_iconsOriginX+(i*_iconsXIncrement), _iconsOriginY);
  }
};
int main(int argc, char *argv[]) {
  DialogBox *dialogs[3];
  dialogs[0] =
    new FileSelcetion(
                      FlyweightFactory::getIcon((char*)"go"),
                      FlyweightFactory::getIcon((char*)"stop"),
                      FlyweightFactory::getIcon((char*)"select")
                      );
  dialogs[1] =
    new CommitTransaction(
                          FlyweightFactory::getIcon((char*)"select"),
                          FlyweightFactory::getIcon((char*)"stop"),
                          FlyweightFactory::getIcon((char*)"undo")
                      );
  dialogs[2] = 0;
  //for (unsigned int i = 0; i < 2; i++)
  for (int i = 0; dialogs[i]; i++)
    dialogs[i]->draw();
  FlyweightFactory::reportTheIcons();
  return 0;
}
