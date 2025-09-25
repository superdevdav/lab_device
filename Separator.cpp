#include "device.cpp"
using namespace std;

class Separator : public Device {
      private:
            int _inputs_count = 1;
            int _outputs_count = 2;
};