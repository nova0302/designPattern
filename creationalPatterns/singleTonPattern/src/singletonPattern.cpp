// file name: singleton.cpp
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class Number {
  // 1. Define a private static attribute
private:
  static string type;
  static Number *inst;
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
};

string Number::type = "decimal";
Number *Number::inst= 0;

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

class Bin: public Number {
  // 6. Inheritance can be supported
public:
  friend class Number;
  void setValue(int in) {
    char buf[10];
    sprintf(buf, "%b", in);
    sscanf(buf, "%d", &value);
  }
protected:
  Bin(){}
};

class Hex: public Number {
  // 6. Inheritance can be supported
public:
  friend class Number;
  void setValue(int in) {
    char buf[10];
    sprintf(buf, "%x", in);
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
    else if (type == "bin")
      inst = new Bin();
    else
      inst = new Number();
  return inst;
}
int add(int a, int b){
  return a+b;
}

int main() {
  char buf[50];
  int n, a=5, b=3;
  n=sprintf(buf, "%d + %d is %d", a, b, a+b);
  printf("[%s] is a string %d chars long\n", buf, n);
  printf("%d\n", 10);
  printf("%o\n", 10);
  printf("%x\n", 10);
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

  Number::setType("bin");
  Number::instance()->setValue(10);
  cout << "value is " << Number::instance()->getValue() << endl;
}
