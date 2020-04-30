#ifndef _NEURON_HPP_
#define _NEURON_HPP_

#include <iostream>
#include <cmath>

using namespace std;

enum class activation {Relu, Tanh, Sigmoid};

class Neuron {
public:
    Neuron(double value);
    Neuron(double value, activation activationType);

    void setNeuronValue(double value);
    void activate();
    void derive();

    // Getters
    double getNeuronValue() { return value_; }
    double getActivatedValue() { return activatedValue_; }
    double getDerivedValue() { return derivedValue_; }

private:
    double value_;
    double activatedValue_;
    double derivedValue_;
    activation activationType_;
};

#endif
