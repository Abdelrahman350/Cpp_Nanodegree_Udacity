# Fully Connected Neural Network\

This project is a simple implementation for a fully connected neural network using C++ for Udacity C++ NanoDegree Capstone Project. The chosen problem to apply this neural network was a simple autoencoder. Autoencoders are a specific type of feedforward neural networks where the input is the same as the output.

# How to Run:
* `cd build && cmake ..`
* `make`
* `./NeuralNetwork`

# Project Structure:
1. main.cpp 
    * Program Main.
2. Neuron.cpp / Neuron.hpp
    * This Class is responsible for the implementation of the neurons of the neural network.
3. Matrix.cpp / Matrix.hpp
    * This class is responsible for the implementation of the matrix data structure and its transpose operation.
4. Math.cpp / Math.hpp
    * This class is responsible for the implementation of the static matrix multiblication operation. 
5. Layer.cpp / Layer.hpp
    * This class is responsible for the implementation of the layer and its associated operations.
6. NeuralNetwork.cpp / NeuralNetwork.hpp
    * This class is responsible for the implementation of the Neural Network data structure and basic operations   like set input layer, feed forward and back propagation.
