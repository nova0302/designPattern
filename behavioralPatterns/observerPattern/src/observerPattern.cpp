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

using namespace std;

class Observer {
public:
  virtual void update(double st1, double st2, int st3)=0;
};

class Subject {
public:
  virtual void attach(Observer *o)=0;
  virtual void detach(Observer *o)=0;
  virtual void notify()=0;
};

class ConcreteSubject : public Subject{
private:
  double st1, st2;
  Observer *objs[100];
  int st3, index;

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
      objs[i]->update(st1, st2, st3);
    }
  }
  void setStatus(double st1, double st2, int st3){
    this->st1 = st1;
    this->st2 = st2;
    this->st3 = st3;
    notify();
  }
};

class ConcreteObserverA : public Observer {
private:
  double st1, st2;
  int st3;
  Subject *info;

public:
  ConcreteObserverA(Subject *info){
    this->info = info;
    info->attach(this);
  }
  virtual void update(double st1, double st2, int st3){
    this->st1 = st1;
    this->st2 = st2;
    this->st3 = st3;
    cout << st1 << " & " << st2 <<endl;
  }
};

class ConcreteObserverB : public Observer {
private:
  double st1, st2;
  int st3;
  Subject *info;

public:
  ConcreteObserverB(Subject *info){
    this->info = info;
    info->attach(this);
  }

  virtual void update(double st1, double st2, int st3){
    this->st1 = st1;
    this->st2 = st2;
    this->st3 = st3;
    cout << st2 << " & " << st3 << endl;
  }
};

int main(){
  ConcreteSubject * CS = new ConcreteSubject();
  Observer *o1 = new ConcreteObserverA(CS);
  Observer *o2 = new ConcreteObserverB(CS);
  CS->setStatus(400.5, 39.3, 9);
  //  CS->notify();
  cout << endl;
  CS->setStatus(40.5, 3.3, 99);
}


//
// observerPattern.cpp ends here
