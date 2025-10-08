#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <stdexcept>

// Объявляем классы прямо здесь (без включения device.cpp)
class Stream {
private:
    int id;
    double massFlow;

public:
    Stream(int streamId) : id(streamId), massFlow(0.0) {}
    void setMassFlow(double flow) { massFlow = flow; }
    double getMassFlow() const { return massFlow; }
    int getId() const { return id; }
};

class Separator {
private:
    std::vector<std::shared_ptr<Stream>> inputs;
    std::vector<std::shared_ptr<Stream>> outputs;

public:
    void addInput(std::shared_ptr<Stream> input) {
        inputs.push_back(input);
    }

    void addOutput(std::shared_ptr<Stream> output) {
        outputs.push_back(output);
    }

    void updateOutputs() {
        if (inputs.size() != 1) {
            throw "Separator must have exactly 1 input";
        }
        if (outputs.size() != 2) {
            throw "Separator must have exactly 2 outputs";
        }

        double totalMassFlow = inputs[0]->getMassFlow();
        double splitMassFlow = totalMassFlow / outputs.size();

        for (auto& output : outputs) {
            output->setMassFlow(splitMassFlow);
        }
    }
};

class TestFramework {
private:
    std::vector<std::pair<std::string, bool>> testResults;
    int passed = 0;
    int failed = 0;

public:
    void assertTrue(bool condition, const std::string& testName) {
        testResults.emplace_back(testName, condition);
        if (condition) {
            passed++;
            std::cout << "PASS: " << testName << std::endl;
        } else {
            failed++;
            std::cout << "FAIL: " << testName << std::endl;
        }
    }

    template<typename T>
    void assertEqual(const T& actual, const T& expected, const std::string& testName) {
        bool condition = (actual == expected);
        testResults.emplace_back(testName, condition);
        if (condition) {
            passed++;
            std::cout << "PASS: " << testName << " (expected: " << expected << ", actual: " << actual << ")" << std::endl;
        } else {
            failed++;
            std::cout << "FAIL: " << testName << " (expected: " << expected << ", actual: " << actual << ")" << std::endl;
        }
    }

    void assertDoubleEqual(double actual, double expected, const std::string& testName, double epsilon = 1e-10) {
        bool condition = std::abs(actual - expected) < epsilon;
        testResults.emplace_back(testName, condition);
        if (condition) {
            passed++;
            std::cout << "PASS: " << testName << " (expected: " << expected << ", actual: " << actual << ")" << std::endl;
        } else {
            failed++;
            std::cout << "FAIL: " << testName << " (expected: " << expected << ", actual: " << actual << ")" << std::endl;
        }
    }

    void printSummary() {
        std::cout << "\n=== TEST SUMMARY ===" << std::endl;
        std::cout << "Total tests: " << (passed + failed) << std::endl;
        std::cout << "Passed: " << passed << std::endl;
        std::cout << "Failed: " << failed << std::endl;
        
        if (failed > 0) {
            std::cout << "\nFailed tests:" << std::endl;
            for (const auto& testResult : testResults) {
                const std::string& testName = testResult.first;
                bool result = testResult.second;
            }
        }
    }

    bool allTestsPassed() const {
        return failed == 0;
    }
};

// Тест 1: базовое разделение
void testSplitsMassFlowEqually(TestFramework& tf) {
    Separator sep;
    auto in = std::make_shared<Stream>(1);
    auto out1 = std::make_shared<Stream>(2);
    auto out2 = std::make_shared<Stream>(3);

    in->setMassFlow(100.0);

    sep.addInput(in);
    sep.addOutput(out1);
    sep.addOutput(out2);

    sep.updateOutputs();

    tf.assertDoubleEqual(out1->getMassFlow(), 50.0, "SplitsMassFlowEqually - out1");
    tf.assertDoubleEqual(out2->getMassFlow(), 50.0, "SplitsMassFlowEqually - out2");
}

// Тест 2: ошибка при неправильном числе входов
void testThrowsOnInvalidInputCount(TestFramework& tf) {
    Separator sep;
    auto in1 = std::make_shared<Stream>(1);
    auto in2 = std::make_shared<Stream>(2);
    auto out1 = std::make_shared<Stream>(3);
    auto out2 = std::make_shared<Stream>(4);

    sep.addInput(in1);
    sep.addInput(in2); // лишний вход
    sep.addOutput(out1);
    sep.addOutput(out2);

    try {
        sep.updateOutputs();
        tf.assertTrue(false, "ThrowsOnInvalidInputCount - should have thrown");
    } catch (const char* msg) {
        tf.assertTrue(true, "ThrowsOnInvalidInputCount - threw correctly");
    } catch (...) {
        tf.assertTrue(false, "ThrowsOnInvalidInputCount - threw wrong exception type");
    }
}

// Тест 3: ошибка при неправильном числе выходов
void testThrowsOnInvalidOutputCount(TestFramework& tf) {
    Separator sep;
    auto in = std::make_shared<Stream>(1);
    auto out = std::make_shared<Stream>(2);

    sep.addInput(in);
    sep.addOutput(out); // только один выход

    try {
        sep.updateOutputs();
        tf.assertTrue(false, "ThrowsOnInvalidOutputCount - should have thrown");
    } catch (const char* msg) {
        tf.assertTrue(true, "ThrowsOnInvalidOutputCount - threw correctly");
    } catch (...) {
        tf.assertTrue(false, "ThrowsOnInvalidOutputCount - threw wrong exception type");
    }
}

// Тест 4: дробное значение делится корректно
void testSplitsFractionalFlow(TestFramework& tf) {
    Separator sep;
    auto in = std::make_shared<Stream>(1);
    auto out1 = std::make_shared<Stream>(2);
    auto out2 = std::make_shared<Stream>(3);

    in->setMassFlow(5.0);

    sep.addInput(in);
    sep.addOutput(out1);
    sep.addOutput(out2);

    sep.updateOutputs();

    tf.assertDoubleEqual(out1->getMassFlow(), 2.5, "SplitsFractionalFlow - out1");
    tf.assertDoubleEqual(out2->getMassFlow(), 2.5, "SplitsFractionalFlow - out2");
}

// Тест 5: повторные вызовы работают стабильно
void testMultipleUpdates(TestFramework& tf) {
    Separator sep;
    auto in = std::make_shared<Stream>(1);
    auto out1 = std::make_shared<Stream>(2);
    auto out2 = std::make_shared<Stream>(3);

    in->setMassFlow(200.0);

    sep.addInput(in);
    sep.addOutput(out1);
    sep.addOutput(out2);

    sep.updateOutputs();
    tf.assertDoubleEqual(out1->getMassFlow(), 100.0, "MultipleUpdates - first update out1");
    tf.assertDoubleEqual(out2->getMassFlow(), 100.0, "MultipleUpdates - first update out2");

    in->setMassFlow(50.0);
    sep.updateOutputs();
    tf.assertDoubleEqual(out1->getMassFlow(), 25.0, "MultipleUpdates - second update out1");
    tf.assertDoubleEqual(out2->getMassFlow(), 25.0, "MultipleUpdates - second update out2");
}

int main() {
    TestFramework tf;
    
    std::cout << "Running Separator tests..." << std::endl;
    std::cout << "==========================" << std::endl;
    
    testSplitsMassFlowEqually(tf);
    testThrowsOnInvalidInputCount(tf);
    testThrowsOnInvalidOutputCount(tf);
    testSplitsFractionalFlow(tf);
    testMultipleUpdates(tf);
    
    tf.printSummary();
    
    return tf.allTestsPassed() ? 0 : 1;
}