#include "../include/Neuron.hpp"

// Constructor
Neuron::Neuron(double value) {
    setNeuronValue(value);
}

Neuron::Neuron(double value, activation activationType) {
    activationType_ = activationType;
    setNeuronValue(value);    
}


void Neuron::setNeuronValue(double value) {
    value_ = value;
    activate();
    derive();
}

void Neuron::activate() {
    if (activationType_ == activation::Tanh) {
        activatedValue_ = tanh(value_);
    } else if (activationType_ == activation::Relu) {
        if (value_ > 0) {
            activatedValue_ = value_;
        } else {
            activatedValue_ = 0;
        }
    } else if (activationType_ == activation::Sigmoid) {
        activatedValue_ = (1 / (1 + exp(-value_)));
    } else {
        activatedValue_ = (1 / (1 + exp(-value_)));
    }
}

void Neuron::derive() {
    if (activationType_ == activation::Tanh) {
        derivedValue_ = (1.0 - (activatedValue_ * activatedValue_));
    } else if (activationType_ == activation::Relu) {
        if (value_ > 0) {
            derivedValue_ = 1;
        } else {
            derivedValue_ = 0;
        }
    } else if (activationType_ == activation::Sigmoid) {
        derivedValue_ = (activatedValue_ * (1 - activatedValue_));
    } else {
        derivedValue_ = (activatedValue_ * (1 - activatedValue_));
    }
}
