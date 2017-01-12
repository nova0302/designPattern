// file name: singleton.cpp
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class Number {
public:
  // 2. Define a public static accessor func
  static Number *instance();
  static void setType(string t) {
    type = t;
    delete inst;
    inst = 0;
  }
  virtual void setValue(int in) {value = in;}
  virtual int getValue() {return value;}
protected:
  int value;
  // 4. Define all ctors to be protected
  Number() {cout << ":ctor: ";}
  // 1. Define a private static attribute
private:
  static string type;
  static Number *inst;
};

string Number::type = "decimal";
Number *Number::inst = 0;

class Octal: public Number {
  // 6. Inheritance can be supported
public:
  friend class Number;
  void setValue(int in) {
    char buf[10];
    sprintf(buf, "%o", in);
    sscanf(buf, "%d", &value);
  }
protected:
  Octal(){}
};

class Hex: public Number {
  // 6. Inheritance can be supported
public:
  friend class Number;
  void setValue(int in) {
    char buf[10];
    sprintf(buf, "%h", in);
    sscanf(buf, "%d", &value);
  }
protected:
  Hex(){}
};
Number *Number::instance() {
  if (!inst)
    // 3. Do "lazy initialization" in the accessor function
    if (type == "octal")
      inst = new Octal();
    else if (type == "hex")
      inst = new Hex();
    else
      inst = new Number();
  return inst;
}
int add(int a, int b){
  return a+b;
}

int main() {
  // Number  myInstance; - error: cannot access protected constructor
  // 5. Clients may only use the accessor function to manipulate the Singleton
  Number::instance()->setValue(10);
  cout << "value is " << Number::instance()->getValue() << endl;
  Number::setType("octal");
  Number::instance()->setValue(10);
  cout << "value is " << Number::instance()->getValue() << endl;
  Number::setType("hex");
  Number::instance()->setValue(10);
  cout << "value is " << Number::instance()->getValue() << endl;
}
