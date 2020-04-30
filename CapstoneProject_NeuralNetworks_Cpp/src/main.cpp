#include <iostream>
#include <vector>
#include <cstdio>
#include <fstream>
#include <ostream>
#include <streambuf>
#include <ctime> 
#include <memory>

#include "../include/Matrix.hpp"
#include "../include/Math.hpp"
#include "../include/NeuralNetwork.hpp"

using namespace std;

int main() {
        vector<double> input;
        input.push_back(0.2);
        input.push_back(0.5);
        input.push_back(0.1);
       
        vector<double> output;
        output.push_back(0.2); 
        output.push_back(0.5); 
        output.push_back(0.1);
    
        double learningRate  = 0.05;
        double momentum      = 1;
        double bias          = 1;

        vector<int> architecture;
        architecture.push_back(650);
        architecture.push_back(213);
        architecture.push_back(650);

	activation hiddenActivationType = activation::Relu;
        activation outputActivationType = activation::Sigmoid;
        costFunctions costFunctionType = costFunctions::COST_MSE;

        std::unique_ptr<NeuralNetwork> n(new NeuralNetwork(architecture, hiddenActivationType, outputActivationType, costFunctionType, bias, learningRate, momentum));

        for (int i = 0; i < 1000; i++) {
            // cout << "Training at index " << i << endl;
            n->train(input, output, bias, learningRate, momentum);
            cout << "Iteration # "<< i <<"-----> Error = " << n->error << endl;
        }

    return 0;
}
