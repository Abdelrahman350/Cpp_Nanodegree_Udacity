#include "../include/Layer.hpp"

// Constructor
Layer::Layer(int size) {
    this->size = size;

    for (int i = 0; i < size; i++) {
        shared_ptr<Neuron> n (new Neuron(0.0000000));
        neurons_.push_back(n);
    }
}

Layer::Layer(int size, activation activationType) {
    this->size = size;

    for (int i = 0; i < size; i++) {
        shared_ptr<Neuron> n (new Neuron(0.0000000, activationType));
        neurons_.push_back(n);
    }
}


void Layer::setVal(int i, double v) {
    neurons_.at(i)->setNeuronValue(v);
}

vector<double> Layer::getActivatedVals() {
    vector<double> ret;
    for (int i = 0; i < neurons_.size(); i++) {
        double v = neurons_.at(i)->getActivatedValue();
        ret.push_back(v);
    }

    return ret;
}

shared_ptr<Matrix> Layer::vectorizeNeoronsValues() {
    shared_ptr<Matrix> m = shared_ptr<Matrix> (new Matrix(1, neurons_.size(), false));
    for (int i = 0; i < neurons_.size(); i++) {
        m->setMatrixValue(0, i, neurons_.at(i)->getNeuronValue());
    }
    return m;
}

shared_ptr<Matrix> Layer::vectorizeActivatedValues() {
    shared_ptr<Matrix> m = shared_ptr<Matrix> (new Matrix(1, neurons_.size(), false));
    for (int i = 0; i < neurons_.size(); i++) {
        m->setMatrixValue(0, i, neurons_.at(i)->getActivatedValue());
    }
    return m;
}

shared_ptr<Matrix> Layer::vectorizeDerivedValues() {
    shared_ptr<Matrix> m = shared_ptr<Matrix> (new Matrix(1, neurons_.size(), false));
    for (int i = 0; i < neurons_.size(); i++) {
        m->setMatrixValue(0, i, neurons_.at(i)->getDerivedValue());
    }
    return m;
}
