#include "../include/NeuralNetwork.hpp"
#include "../include/Math.hpp"

NeuralNetwork::NeuralNetwork(
    vector<int> architecture,
    double bias,
    double learningRate,
    double momentum
) {
    architecture_      = architecture;
    architectureSize_  = architecture_.size();
    learningRate_  = learningRate;
    momentum_      = momentum;
    bias_          = bias;

  for (int i = 0; i < architectureSize_; i++) {
    if (i > 0 && i < (architectureSize_ - 1)) {
      std::unique_ptr<Layer> l(new Layer(architecture_.at(i), hiddenActivationType_));
      layers_.push_back(std::move(l));
    } else if (i == (architectureSize_ - 1)) {
      std::unique_ptr<Layer> l(new Layer(architecture_.at(i), outputActivationType_));
      layers_.push_back(std::move(l));
    } else {
      std::unique_ptr<Layer> l(new Layer(architecture_.at(i)));
      layers_.push_back(std::move(l));
    }
  }

    for (int i = 0; i < (architectureSize_ - 1); i++) {
        std::unique_ptr<Matrix> weightMatrix(new Matrix(architecture.at(i), architecture.at(i + 1), true));
        weightMatrices_.push_back(std::move(weightMatrix));
    }

    for (int i = 0; i < architecture_.at(architectureSize_ - 1); i++) {
        errors.push_back(0.00);
        derivedErrors.push_back(0.00);        
    }

    error = 0.00;
}

NeuralNetwork::NeuralNetwork(
    vector<int> architecture,
    activation hiddenActivationType,
    activation outputActivationType,
    costFunctions costFunctionType,
    double bias,
    double learningRate,
    double momentum
) {
    architecture_      = architecture;
    architectureSize_  = architecture_.size();
    learningRate_  = learningRate;
    momentum_      = momentum;
    bias_          = bias;
    hiddenActivationType_      = hiddenActivationType;
    outputActivationType_      = outputActivationType;
    costFunctionType_          = costFunctionType;

  for (int i = 0; i < architectureSize_; i++) {
    if (i > 0 && i < (architectureSize_ - 1)) {
      std::unique_ptr<Layer> l(new Layer(architecture_.at(i), hiddenActivationType_));
      layers_.push_back(std::move(l));
    } else if (i == (architectureSize_ - 1)) {
      std::unique_ptr<Layer> l(new Layer(architecture_.at(i), outputActivationType_));
      layers_.push_back(std::move(l));
    } else {
      std::unique_ptr<Layer> l(new Layer(architecture_.at(i)));
      layers_.push_back(std::move(l));
    }
  }

    for (int i = 0; i < (architectureSize_ - 1); i++) {
        std::unique_ptr<Matrix> weightMatrix(new Matrix(architecture_.at(i), architecture_.at(i + 1), true));
        weightMatrices_.push_back(std::move(weightMatrix));
    }

    for (int i = 0; i < architecture_.at(architectureSize_ - 1); i++) {
        errors.push_back(0.00);
        derivedErrors.push_back(0.00);
    }

    error = 0.00;
}

void NeuralNetwork::setInputLayer(vector<double> input) {
   input_ = input;

   for (int i = 0; i < input.size(); i++) {
       layers_.at(0)->setVal(i, input.at(i));
   }
}

void NeuralNetwork::train(
    vector<double> input,
    vector<double> output,
    double bias,
    double learningRate,
    double momentum
) {
    learningRate_ = learningRate;
    momentum_ = momentum;
    bias_ = bias;
    
    setInputLayer(input);
    setDesiredOutput(output);

    feedForward();
    setErrors();
    backPropagation();
}

void NeuralNetwork::setErrors() {
    switch(costFunctionType_) {
        case(costFunctions::COST_MSE): setErrorMSE(); break;
        default: setErrorMSE(); break;
    }
}

void NeuralNetwork::setErrorMSE() {
    int outputLayerIndex            = layers_.size() - 1;
    vector<shared_ptr<Neuron>> outputNeurons  = layers_.at(outputLayerIndex)->getNeurons();

    error= 0.00;
 
    for (int i = 0; i < output_.size(); i++) { 
        double t = output_.at(i);
        double y = outputNeurons.at(i)->getActivatedValue();

        errors.at(i)        = 0.5 * pow(abs((t - y)), 2);
        derivedErrors.at(i) = (y - t);

        error += errors.at(i);
    }
}

void NeuralNetwork::feedForward() {
    shared_ptr<Matrix> a; // Matrix of neurons to the left
    shared_ptr<Matrix> b; // Matrix of weights to the right of the layer 
    shared_ptr<Matrix> c; // Matrix of neurons to the right

    for (int i = 0; i < (architectureSize_ - 1); i++) {
        a = shared_ptr<Matrix> (getNeuronMatrix(i));
        b = shared_ptr<Matrix> (getWeightMatrix(i));
        c = shared_ptr<Matrix> (new Matrix(a->getNumRows(), b->getNumCols(), false));

        if (i != 0) {
            a = shared_ptr<Matrix> (getActivatedNeuronMatrix(i));
        }

        c = utils::Math::multiplyMatrix(a, b);

        for (int c_index = 0; c_index < c->getNumCols(); c_index++) {
            setNeuronValue(i + 1, c_index, c->getMatrixValue(0, c_index) + bias_);
        }
    }
}

void NeuralNetwork::backPropagation() {
  vector<shared_ptr<Matrix>> newWeights;
  shared_ptr<Matrix> deltaWeights;
  shared_ptr<Matrix> gradients;
  shared_ptr<Matrix> derivedValues;
  shared_ptr<Matrix> gradientsTransposed;
  shared_ptr<Matrix> zActivatedVals;
  shared_ptr<Matrix> tempNewWeights;
  shared_ptr<Matrix> pGradients;
  shared_ptr<Matrix> transposedPWeights;
  shared_ptr<Matrix> hiddenDerived;
  shared_ptr<Matrix> transposedHidden;

  /**
   *  PART 1: OUTPUT TO LAST HIDDEN LAYER
   */
  int indexOutputLayer  = architecture_.size() - 1;

  gradients = shared_ptr<Matrix> (new Matrix(1, architecture_.at(indexOutputLayer), false));

  derivedValues = shared_ptr<Matrix> (layers_.at(indexOutputLayer)->vectorizeDerivedValues());

  for(int i = 0; i < architecture_.at(indexOutputLayer); i++) {
    double e  = derivedErrors.at(i);
    double y  = derivedValues->getMatrixValue(0, i);
    double g  = e * y;
    gradients->setMatrixValue(0, i, g);
  }

  gradientsTransposed = shared_ptr<Matrix> (gradients->transpose());
  zActivatedVals      = shared_ptr<Matrix> (layers_.at(indexOutputLayer - 1)->vectorizeActivatedValues());

  deltaWeights  = shared_ptr<Matrix> (new Matrix(gradientsTransposed->getNumRows(), zActivatedVals->getNumCols(), false));

  deltaWeights = utils::Math::multiplyMatrix(gradientsTransposed, zActivatedVals);

  /**
   * COMPUTE FOR NEW WEIGHTS (LAST HIDDEN <-> OUTPUT)
   */
  tempNewWeights  = shared_ptr<Matrix> (new Matrix(architecture_.at(indexOutputLayer - 1), architecture_.at(indexOutputLayer), false));

  for(int r = 0; r < architecture_.at(indexOutputLayer - 1); r++) {
    for(int c = 0; c < architecture_.at(indexOutputLayer); c++) {

      double originalValue  = weightMatrices_.at(indexOutputLayer - 1)->getMatrixValue(r, c);
      double deltaValue     = deltaWeights->getMatrixValue(c, r);

      originalValue = momentum_ * originalValue;
      deltaValue    = learningRate_ * deltaValue;
      
      tempNewWeights->setMatrixValue(r, c, (originalValue - deltaValue));
    }
  }

  newWeights.push_back(shared_ptr<Matrix> (new Matrix(*tempNewWeights)));


  /**
   *  PART 2: LAST HIDDEN LAYER TO INPUT LAYER
   */
  for(int i = (indexOutputLayer - 1); i > 0; i--) {
    pGradients  = gradients;

    transposedPWeights  = shared_ptr<Matrix> (weightMatrices_.at(i)->transpose());

    gradients   = shared_ptr<Matrix> (new Matrix(pGradients->getNumRows(), transposedPWeights->getNumCols(), false));

    gradients = utils::Math::multiplyMatrix(pGradients, transposedPWeights);

    hiddenDerived       = shared_ptr<Matrix> (layers_.at(i)->vectorizeDerivedValues());

    for(int colCounter = 0; colCounter < hiddenDerived->getNumRows(); colCounter++) {
      double  g = gradients->getMatrixValue(0, colCounter) * hiddenDerived->getMatrixValue(0, colCounter);
      gradients->setMatrixValue(0, colCounter, g);
    }

    if(i == 1) {
      zActivatedVals  = shared_ptr<Matrix> (layers_.at(0)->vectorizeNeoronsValues());
    } else {
      zActivatedVals  = shared_ptr<Matrix> (layers_.at(0)->vectorizeActivatedValues());
    }

    transposedHidden  = shared_ptr<Matrix> (zActivatedVals->transpose());

    deltaWeights      = shared_ptr<Matrix> (new Matrix(
                          transposedHidden->getNumRows(),
                          gradients->getNumCols(),
                          false
                        ));

    deltaWeights = utils::Math::multiplyMatrix(transposedHidden, gradients);

    // update weights
    tempNewWeights  = shared_ptr<Matrix> (new Matrix(weightMatrices_.at(i - 1)->getNumRows(), weightMatrices_.at(i - 1)->getNumCols(), false));

    for(int r = 0; r < tempNewWeights->getNumRows(); r++) {
      for(int c = 0; c < tempNewWeights->getNumCols(); c++) {
        double originalValue  = weightMatrices_.at(i - 1)->getMatrixValue(r, c);
        double deltaValue     = deltaWeights->getMatrixValue(r, c);

        originalValue = momentum_ * originalValue;
        deltaValue    = learningRate_ * deltaValue;
        
        tempNewWeights->setMatrixValue(r, c, (originalValue - deltaValue));
      }
    }

    newWeights.push_back(shared_ptr<Matrix> (new Matrix(*tempNewWeights)));

  }


  weightMatrices_.clear();

  reverse(newWeights.begin(), newWeights.end());

  for(int i = 0; i < newWeights.size(); i++) {
    weightMatrices_.push_back(shared_ptr<Matrix> (new Matrix(*newWeights[i])));
  }
}
