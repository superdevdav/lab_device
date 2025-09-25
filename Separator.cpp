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
            }
};