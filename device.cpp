#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Stream
{
    private:
      double mass_flow;
      string name;
    public:
      void setName(string s){name=s;}
      string getName(){return name;}
      void setMassFlow(double m){mass_flow=m;}
      double getMassFlow(){return mass_flow;}
      void print(){cout<<"Stream "<<getName()<<" "<<getMassFlow()<<endl;}
};
