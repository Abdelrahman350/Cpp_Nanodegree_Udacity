#ifndef _LAYER_HPP_
#define _LAYER_HPP_

#include <iostream>
#include <vector>
#include "Neuron.hpp"
#include "Matrix.hpp"
#include <memory>
using namespace std;

class Layer {
public:
    Layer(int size);
    Layer(int size, activation activationType);

    // Setter
    void setVal(int i, double v);
    void setNeuron(vector<shared_ptr<Neuron>> neurons) { neurons_ = neurons; }

    // Getters
    vector<double> getActivatedVals();
    vector<shared_ptr<Neuron>> getNeurons() { return neurons_; }

    shared_ptr<Matrix> vectorizeNeoronsValues();
    shared_ptr<Matrix> vectorizeActivatedValues();
    shared_ptr<Matrix> vectorizeDerivedValues();

private:
    int size;
    vector<shared_ptr<Neuron>> neurons_;
};

#endif
