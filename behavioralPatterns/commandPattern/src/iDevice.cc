#include <iostream>
#include <vector>

using namespace std;
//receiver
class iDevice {
protected:
  typedef enum {Off, On}State;
  State theState;
  int volume;
public:
  iDevice(State newState=Off, int newVolume=0){
    theState = newState;
    volume = newVolume;
  }
  bool isDeviceOn(){return theState == On;}
  virtual void on()=0;
  virtual void off()=0;
  virtual void volumeUp()=0;
  virtual void volumeDown()=0;
  virtual ~iDevice(){ cout << "~iDevice is called,"<< endl;}
};
//commmand
class iCommand {
protected:
  iDevice *theDevice;
public:
  iCommand(iDevice *newDevice){theDevice = newDevice;}
  virtual void execute()=0;
  virtual void undo()=0;
  //~iCommand(){delete theDevice;}
  virtual ~iCommand(){ cout << "~iCommand is called,"<< endl;}
};
//class turnItAllOff : public iCommand{
//  vector<iDevice*> theDevices;
//public:
//  turnItAllOff(vector<iDevice*> newDevices){theDevices = newDevices;}
//  void execute(){
//    for (unsigned int i = 0; i < theDevices.size(); i++) theDevices[i]->off();
//  }
//  void undo(){
//    for (unsigned int i = 0; i < theDevices.size(); i++) theDevices[i]->on();
//  }
//};
class Television: public iDevice {
public:
  Television(State newState=Off, int newVolume=0)
    :iDevice(newState, newVolume){}
  void on() {cout << "TV is On" << endl;};
  void off(){cout << "TV is Off"<< endl;};
  void volumeUp()  {
    //if (iDevice::theState == On) {
    if (isDeviceOn()) {
      if (volume < 10) volume++;
      cout   << "TV volume at : " << volume << endl;
    }else{cout << "TV is off, please turn it on first" << endl;}
  }
  void volumeDown(){
    if (isDeviceOn()) {
      if (volume >  0) volume--;
      cout << "TV volume at : " << volume << endl;
    }else{cout << "TV is off, please turn it on first" << endl;}
  }
  ~Television(){cout << "~Television is called" << endl;}
};
class turnOn : public iCommand {
public:
  turnOn(iDevice *newDevice):iCommand(newDevice){};
  void execute(){theDevice->on();};
  void undo(){theDevice->off();};
  ~turnOn(){ cout << "~turnOn is called" << endl;}
};
class turnOff : public iCommand {
public:
  turnOff(iDevice *newDevice):iCommand(newDevice){}
  void execute(){theDevice->off();};
  void undo(){theDevice->on();};
  ~turnOff(){cout << "~turnOff is called" << endl;}
};
class volumeUp : public iCommand {
public:
  volumeUp(iDevice *newDevice):iCommand(newDevice){}
  void execute(){theDevice->volumeUp();};
  void undo(){theDevice->volumeDown();};
  ~volumeUp(){ cout << "~volumeUp is called." << endl;}
};
class volumeDown : public iCommand {
public:
  volumeDown(iDevice *newDevice):iCommand(newDevice){}
  void execute(){theDevice->volumeDown();};
  void undo(){theDevice->volumeUp();};
  ~volumeDown(){ cout << "~volumeDown is called." << endl;}
};
class deviceButton {
  iCommand *theCommand;
public:
  deviceButton(iCommand *newCommand){theCommand = newCommand;};
  void onPressed(){ theCommand->execute();}
  void pressUndo(){ theCommand->undo();}
  ~deviceButton(){cout << "~deviceButton is called." << endl;}
};
class TVRemote {
public:
  static iDevice* getDevice(){return new Television();}
};
class Radio : public iDevice {
protected:
public:
  Radio(State theState=Off, int newVolume=0)
    :iDevice(theState, newVolume){}
  void on() {
    if(isDeviceOn()) {
      theState = On;
      cout << "Radio is now On" << endl;
    }else{cout << "Radio is already On" << endl;};
  }
  void off(){
    if (isDeviceOn()) {
      theState = Off;
      cout << "Radio is Off"<< endl;
    }else{cout << "Radio is already off!!" << endl;}
  }
  void volumeUp()  {
    if (isDeviceOn()) {
      if (volume < 10) volume++;
      cout   << "Radio volume at : " << volume << endl;
    }else{cout << "Radio is off, turn it on first!!" << endl;}
  };
  void volumeDown(){
    if (isDeviceOn()) {
      if (volume >  0) volume--;
      cout << "Radio volume at : " << volume << endl;
    }else{cout << "Radio is off, turn it on first!!" << endl;}
  }
};
class RadioRemote {
public:
  static iDevice* getDevice(){return new Radio();}
};

int main(int argc, char *argv[]) {

  //  iDevice *newTelevision = TVRemote::getDevice();
  iDevice *newRadio = RadioRemote::getDevice();

  turnOn *onCommand = new turnOn(newRadio);
  deviceButton *theButton = new deviceButton(onCommand);
  theButton->onPressed();
  delete onCommand;
  delete theButton;


  volumeUp *volumeUpCmd = new volumeUp(newRadio);
  theButton = new deviceButton(volumeUpCmd);
  for (unsigned int i = 0; i < 10; i++) theButton->onPressed();
  delete volumeUpCmd;
  delete theButton;

  volumeDown *volumeDownCmd = new volumeDown(newRadio);
  theButton = new deviceButton(volumeDownCmd);
  for (unsigned int i = 0; i < 4; i++) theButton->onPressed();
  delete volumeDownCmd;
  delete theButton;

  turnOff *offCommand = new turnOff(newRadio);
  theButton = new deviceButton(offCommand);
  theButton->onPressed();
  delete offCommand;
  delete theButton;

  //  onCommand = new turnOn(newTelevision);
  //  theButton = new deviceButton(onCommand);
  //  theButton->onPressed();
  //  delete onCommand;
  //  delete theButton;
  //
  //  offCommand = new turnOff(newTelevision);
  //  theButton = new deviceButton(offCommand);
  //  theButton->onPressed();
  //  delete offCommand;
  //  delete theButton;
  //
  //  volumeUpCmd = new volumeUp(newTelevision);
  //  theButton = new deviceButton(volumeUpCmd);
  //  for (unsigned int i = 0; i < 4; i++) theButton->onPressed();
  //  delete volumeUpCmd;
  //  delete theButton;
  //
  //  volumeDownCmd = new volumeDown(newTelevision);
  //  theButton = new deviceButton(volumeDownCmd);
  //  for (unsigned int i = 0; i < 4; i++) theButton->onPressed();
  //  delete volumeDownCmd;
  //  delete theButton;
  //
  //  Television *theTV = new Television();
  //  Radio *theRadio = new Radio();
  //  vector<iDevice*> allDevices;
  //  allDevices.push_back(theTV);
  //  allDevices.push_back(theRadio);
  //  Television theTelevision;

  //  turnItAllOff *turnOffDevices = new turnItAllOff(allDevices);
  //  deviceButton *turnThemOff = new deviceButton(turnOffDevices);
  //  turnThemOff->onPressed();
  //  turnThemOff->pressUndo();
  //
  //  delete theTV;
  //  delete theRadio;
  //  delete turnOffDevices;
  //  delete turnThemOff;

  return 0;
}
