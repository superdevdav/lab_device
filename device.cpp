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

class Stream
{
    private:
      double mass_flow;
      string name;
    public:
      Stream(int s){setName("s"+std::to_string(s));}
      void setName(string s){name=s;}
      string getName(){return name;}
      void setMassFlow(double m){mass_flow=m;}
      double getMassFlow(){return mass_flow;}
      void print(){cout<<"Stream "<<getName()<<" flow = "<<getMassFlow()<<endl;}
};

int main()
{
    Stream s1,s2,s3;
    s1.setMassFlow(10.0);
    s2.setMassFlow(5.0);
}
