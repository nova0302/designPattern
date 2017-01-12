#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

class EnemyShip {
  string name;
  double amtDamage;
public:
  string getName(){return name;}
  void setName(string newName){name = newName;}
  void followHeroShip(){cout << getName() << "is following the hero";}
  void setDamage(double newDamage){amtDamage = newDamage;}
};

class UFOEnemyShip : public EnemyShip{
public:
  UFOEnemyShip(){
    setName("UFO Enemy Ship");
    setDamage(20.0);
  }
};
class RocketEnemyShip : public EnemyShip{
public:
  RocketEnemyShip(){
    setName("Rocket Enemy Ship");
    setDamage(10.0);
  }
};
class BigEnemyShip : public EnemyShip{
public:
  BigEnemyShip(){
    setName("Big Enemy Ship");
    setDamage(20.0);
  }
};
class EnemyShipFactory {
public:
  EnemyShip *makeEnemyShip(string newShipType){
    if (newShipType.compare("U") == 0)
      return new UFOEnemyShip();
    else if (newShipType.compare("B") == 0)
      return new BigEnemyShip();
    else if (newShipType.compare("R") == 0)
      return new RocketEnemyShip();
    else
      return new UFOEnemyShip();
  }
};
int main(int argc, char *argv[]) {
  string shipType;
  EnemyShipFactory theFactory;
  EnemyShip *theShip;
  vector<EnemyShip*> enemyShipVector;
  while(1){
    cout << "Enter the enemyShip type(U, B, R, Q for quit): " ;
    cin >> shipType;
    if (shipType.compare("Q") == 0)
      break;
    theShip = theFactory.makeEnemyShip(shipType);
    enemyShipVector.push_back(theShip);

    cout << endl;
    cout << "enemyshipvector.size()" << enemyShipVector.size() << endl;
  }

  for (int i = enemyShipVector.size(); i; i--) {
    (enemyShipVector.back())->followHeroShip();
    enemyShipVector.pop_back();
    cout << endl;
  }
  return 0;
}
