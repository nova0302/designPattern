// stratege.cpp ---
//
// Filename: stratege.cpp
// Description:
// Author:
// Maintainer:
// Created: ¼ö 12 31 12:56:36 2014 (+0900)
// Version:
// Package-Requires: ()
// Last-Updated:
//           By:
//     Update #: 1
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

using namespace std;
class Strategy{
public:
  virtual void execute()=0;
};

class ConcreteStrategyA :public Strategy {
public:
  virtual void execute(){
    cout << "ConcreteStrategyA's behavior" <<endl;
  }
};

class ConcreteStrategyB :public Strategy {
public:
  virtual void execute(){
    cout << "ConcreteStrategyB's behavior" <<endl;
  }
};

class Context
{
private:
  Strategy * stg;
public:
  void setStrategy(Strategy * stg){
    this->stg = stg;
  }
  void perForm(){
    stg->execute();
  }
};

int main(){
  Context *S = new Context();

  Strategy *A = new ConcreteStrategyA();
  S->setStrategy(A);
  S->perForm();
  delete s;

  Strategy *B = new ConcreteStrategyB();
  S->setStrategy(B);
  S->perForm();
  delete s;
}

//
// stratege.cpp ends here
