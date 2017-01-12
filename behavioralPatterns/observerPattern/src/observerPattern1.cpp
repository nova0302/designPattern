// observerPattern.cpp ---
//
// Filename: observerPattern.cpp
// Description:
// Author:
// Maintainer:
// Created: ¼ö 12 31 13:07:07 2014 (+0900)
// Version:
// Package-Requires: ()
// Last-Updated:
//           By:
//     Update #: 8
// URL:
// Doc URL:
// Keywords:
// Compatibility:
//
//

// Commentary:
//
//
//
//

// Change Log:
//
//
//
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 3, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; see the file COPYING.  If not, write to
// the Free Software Foundation, Inc., 51 Franklin Street, Fifth
// Floor, Boston, MA 02110-1301, USA.
//
//

// Code:
#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

string dec2bin (int v) {
  if (v > 255) {return "";
  } else {
    string bin;
    int oneorzero;
    for(int i=8;i>0;i--) {
      oneorzero = v % 2;
      if (oneorzero == 1) {
	bin = "1" + bin;
      }
      else {
	bin = "0" + bin;
      }
      v /= 2;
    }
    return bin;
  }
}
class Observer {
public:
  virtual void update( int st1)=0;
};

class Subject {
public:
  virtual void attach(Observer *o)=0;
  virtual void detach(Observer *o)=0;
  virtual void notify()=0;
};

class ConcreteSubject : public Subject{
private:
  Observer *objs[100];
  int st1, index;

public:
  ConcreteSubject(){index=0;}
  virtual void attach(Observer *o){objs[index++] = o;}
  virtual void detach(Observer *o){
    for (int i = 0; i < index; ++i) {
      if (objs[i] == o) {
	memmove(objs+i, objs+i+1, sizeof(Observer)*(100-i));}
    }
  }
  virtual void notify(){
    for (int i = 0; i < index; i++) {
      objs[i]->update(st1);
    }
  }
  void setStatus(int st1){
    this->st1 = st1;
    notify();
  }
};

class hexObser : public Observer {
private:

public:
  hexObser(Subject *info){
    info->attach(this);
  }
  virtual void update(int st1){
    printf("%d is %x in hex\n", st1,st1);
  }
};

class binObser : public Observer {
private:

public:
  binObser(Subject *info){
    info->attach(this);
  }

  virtual void update(int st1){
    string s = dec2bin(st1);
    printf("%d is %s in bin\n", st1, s.c_str());
  }
};

class octObser : public Observer {
private:

public:
  octObser(Subject *info){
    info->attach(this);
  }

  virtual void update(int st1){
    printf("%d is %o in oct\n", st1,st1);
  }
};

int main(){
  int i=1;
  ConcreteSubject * CS = new ConcreteSubject();
  Observer *o1 = new hexObser(CS);
  Observer *o2 = new octObser(CS);
  Observer *o3 = new binObser(CS);
  do{
    CS->setStatus(i);
    cout << endl;
  }while(i++ < 20);
  //  CS->notify();
}


//
// observerPattern.cpp ends here
