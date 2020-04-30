#ifndef _NEURAL_NETWORK_HPP_
#define _NEURAL_NETWORK_HPP_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>

#include "Matrix.hpp"
#include "Layer.hpp"

using namespace std;

enum class costFunctions {COST_MSE};

class NeuralNetwork {
public:
    // Constructors
    NeuralNetwork(
        vector<int> topology,
        double bias = 1,
        double learningRate = 0.05,
        double momentum = 1
    );

    NeuralNetwork(
        vector<int> topology,
        activation hiddenActivationType,
        activation outputActivationType,
        costFunctions costFunctionType,
        double bias = 1,
        double learningRate = 0.05,
        double momentum = 1
    );

    // Setters
    void setInputLayer(vector<double> input);
    void setDesiredOutput(vector<double> output) { output_ = output; }
    void setNeuronValue(int indexLayer, int indexNeuron, double val) { layers_.at(indexLayer)->setVal(indexNeuron, val); }

    // Getters
    vector<double> getActivatedVals(int index) { return layers_.at(index)->getActivatedVals(); };
    shared_ptr<Matrix> getNeuronMatrix(int index) { return shared_ptr<Matrix> (layers_.at(index)->vectorizeNeoronsValues()); }
    shared_ptr<Matrix> getActivatedNeuronMatrix(int index) { return shared_ptr<Matrix> (layers_.at(index)->vectorizeActivatedValues()); }
    shared_ptr<Matrix> getDerivedNeuronMatrix(int index) { return shared_ptr<Matrix> (layers_.at(index)->vectorizeDerivedValues()); }
    shared_ptr<Matrix> getWeightMatrix(int index) { return shared_ptr<Matrix> (new Matrix(*weightMatrices_.at(index))); }

    // Core methods
    void feedForward();
    void backPropagation();
    void setErrors();
    void train(
        vector<double> input,
        vector<double> output, 
        double bias, 
        double learningRate, 
        double momentum
    );

    int architectureSize_;
    activation hiddenActivationType_   = activation::Relu;
    activation outputActivationType_   = activation::Sigmoid;
    costFunctions costFunctionType_    = costFunctions::COST_MSE;

    vector<int> architecture_;
    vector<std::unique_ptr<Layer>> layers_;
    vector<shared_ptr<Matrix>> weightMatrices_;
    vector<shared_ptr<Matrix>> gradientMatrices;
    vector<double> input_;
    vector<double> output_;
    vector<double> errors;
    vector<double> derivedErrors;

    double error                = 0;
    double bias_                = 1;
    double momentum_;
    double learningRate_; 

private:
    void setErrorMSE();
};

#endif
