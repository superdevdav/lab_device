#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;
int streamcounter;

const int MIXER_OUTPUTS = 1;

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
      double getMassFlow() const {return mass_flow;}
      void print(){cout<<"Stream "<<getName()<<" flow = "<<getMassFlow()<<endl;}
};

class Device
{
    protected:
      vector<shared_ptr<Stream>> inputs;
      vector<shared_ptr<Stream>> outputs;
    public:
      void addInput(shared_ptr<Stream> s){inputs.push_back(s);}
      void addOutput(shared_ptr<Stream> s){outputs.push_back(s);}
      virtual void updateOutputs() = 0;
};

class Mixer: public Device
{
    private:
      int _inputs_count = 0;
    public:
      Mixer(int inputs_count): Device() {
        _inputs_count = inputs_count;
      }
}

int main()
{
    streamcounter=0;
    Mixer d1 = Mixer(2)
    
    shared_ptr<Stream> s1(new Stream(++streamcounter));
    shared_ptr<Stream> s2(new Stream(++streamcounter));
    shared_ptr<Stream> s2(new Stream(++streamcounter));
    s1->setMassFlow(10.0);
    s2->setMassFlow(5.0);
}
