#include "device.cpp"
using namespace std;

class Separator : public Device {
      private:
            int inputAmount = 1;
            int outputAmount = 2;
      
      public:
            void updateOutputs() override {
                  if (inputs.size() != inputAmount) {
                        throw "INPUT STREAM LIMIT!";
                  }

                  if (outputs.size() != outputAmount) {
                        throw "OUTPUT STREAM LIMIT!";
                  }

                  double inputMass = inputs.at(0)->getMassFlow();
                  double halfMass = inputMass / 2.0;

                  outputs.at(0)->setMassFlow(halfMass);
                  outputs.at(1)->setMassFlow(halfMass);
            }
};