/**
 * @file main.cpp
 *
 * @brief A C++ program demonstrating the usage of the Stream and Device classes.
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

int streamcounter; ///< Global variable to keep track of stream creation.

/**
 * @class Stream
 * @brief Represents a data stream with a name and mass flow.
 */
class Stream
{
private:
    double mass_flow; ///< The mass flow rate of the stream.
    string name;      ///< The name of the stream.

public:
    /**
     * @brief Constructor to create a Stream with a unique name.
     * @param s An integer used to generate a unique name for the stream.
     */
    Stream(int s) { setName("s" + std::to_string(s)); }

    /**
     * @brief Set the name of the stream.
     * @param s The new name for the stream.
     */
    void setName(string s) { name = s; }

    /**
     * @brief Get the name of the stream.
     * @return The name of the stream.
     */
    string getName() { return name; }

    /**
     * @brief Set the mass flow rate of the stream.
     * @param m The new mass flow rate value.
     */
    void setMassFlow(double m) { mass_flow = m; }

    /**
     * @brief Get the mass flow rate of the stream.
     * @return The mass flow rate of the stream.
     */
    double getMassFlow() { return mass_flow; }

    /**
     * @brief Print information about the stream.
     */
    void print() { cout << "Stream " << getName() << " flow = " << getMassFlow() << endl; }
};

/**
 * @class Device
 * @brief Represents a device that manipulates data streams.
 */
class Device
{
protected:
    vector<shared_ptr<Stream>> inputs;  ///< Input streams connected to the device.
    vector<shared_ptr<Stream>> outputs; ///< Output streams produced by the device.

public:
    /**
     * @brief Add an input stream to the device.
     * @param s A shared pointer to the input stream.
     */
    void addInput(shared_ptr<Stream> s) { inputs.push_back(s); }

    /**
     * @brief Add an output stream to the device.
     * @param s A shared pointer to the output stream.
     */
    void addOutput(shared_ptr<Stream> s) { outputs.push_back(s); }

    /**
     * @brief Update the output streams of the device (to be implemented by derived classes).
     */
    virtual void updateOutputs() = 0;
};

/**
 * @brief The entry point of the program.
 * @return 0 on successful execution.
 */
int main()
{
    streamcounter = 0;

    // Create streams
    shared_ptr<Stream> s1(new Stream(++streamcounter));
    shared_ptr<Stream> s2(new Stream(++streamcounter));
    shared_ptr<Stream> s3(new Stream(++streamcounter));

    // Set mass flows
    s1->setMassFlow(10.0);
    s2->setMassFlow(5.0);

    // Create a device (e.g., Mixer) and add input/output streams
    // Mixer d1;
    // d1.addInput(s1);
    // d1.addInput(s2);
    // d1.addOutput(s3);

    // Update the outputs of the device
    // d1.updateOutputs();

    // Print stream information
//    s1->print();
//    s2->print();
//    s3->print();

    return 0;
}
