#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <cstring>

// Neural network parameters
const int inputSize = 100;  // Adjust this according to the image size
const int hiddenSize = 64;
const int outputSize = 2;
const double learningRate = 0.1;
const int numEpochs = 100;

// Activation function (sigmoid)
double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

// Derivative of the sigmoid function
double sigmoidDerivative(double x) {
    double sigmoidX = sigmoid(x);
    return sigmoidX * (1 - sigmoidX);
}

// Matrix multiplication
std::vector<std::vector<double>> multiply(const std::vector<std::vector<double>>& a,
                                          const std::vector<std::vector<double>>& b) {
    int rowsA = a.size();
    int colsA = a[0].size();
    int colsB = b[0].size();

    std::vector<std::vector<double>> result(rowsA, std::vector<double>(colsB, 0.0));

    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            for (int k = 0; k < colsA; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return result;
}

// Neural network class
class NeuralNetwork {
private:
    std::vector<std::vector<double>> weightsInputHidden;
    std::vector<std::vector<double>> weightsHiddenOutput;

public:
    NeuralNetwork() {
        // Initialize weights with random values between -1 and 1
        weightsInputHidden = std::vector<std::vector<double>>(inputSize, std::vector<double>(hiddenSize, 0.0));
        weightsHiddenOutput = std::vector<std::vector<double>>(hiddenSize, std::vector<double>(outputSize, 0.0));

        for (int i = 0; i < inputSize; i++) {
            for (int j = 0; j < hiddenSize; j++) {
                weightsInputHidden[i][j] = (double)rand() / RAND_MAX * 2 - 1;
            }
        }

        for (int i = 0; i < hiddenSize; i++) {
            for (int j = 0; j < outputSize; j++) {
                weightsHiddenOutput[i][j] = (double)rand() / RAND_MAX * 2 - 1;
            }
        }
    }

    // Forward propagation
    std::vector<double> forward(const std::vector<double>& input) {
        std::vector<std::vector<double>> hiddenLayer(hiddenSize, std::vector<double>(1, 0.0));
        std::vector<std::vector<double>> outputLayer(outputSize, std::vector<double>(1, 0.0));

        // Compute hidden layer activations
        hiddenLayer = multiply(weightsInputHidden, { input });

        // Apply activation function to hidden layer activations
        for (int i = 0; i < hiddenSize; i++) {
            hiddenLayer[i][0] = sigmoid(hiddenLayer[i][0]);
        }

        // Compute output layer activations
        outputLayer = multiply(weightsHiddenOutput, hiddenLayer);

        // Apply activation function to output layer activations
        for (int i = 0; i < outputSize; i++) {
            outputLayer[i][0] = sigmoid(outputLayer[i][0]);
        }

        return outputLayer[0];  // Return the output of the neural network
    }

    // Backward propagation and weight update
    void backward(const std::vector<double>& input, double target) {
        std::vector<std::vector<double>> hiddenLayer(hiddenSize, std::vector<double>(1, 0.0));
        std::vector<std::vector<double>> outputLayer(outputSize, std::vector<double>(1, 0.0));

        // Compute hidden layer activations
        hiddenLayer = multiply(weightsInputHidden, { input });

        // Apply activation function to hidden layer activations
        for (int i = 0; i < hiddenSize; i++) {
            hiddenLayer[i][0] = sigmoid(hiddenLayer[i][0]);
        }

        // Compute output layer activations
        outputLayer = multiply(weightsHiddenOutput, hiddenLayer);

        // Apply activation function to output layer activations
        for (int i = 0; i < outputSize; i++) {
            outputLayer[i][0] = sigmoid(outputLayer[i][0]);
        }

        // Compute the error at the output layer
        std::vector<double> outputError(outputSize, 0.0);
        for (int i = 0; i < outputSize; i++) {
            outputError[i] = (target[i] - outputLayer[i][0]) * sigmoidDerivative(outputLayer[i][0]);
        }

        // Compute the error at the hidden layer
        std::vector<double> hiddenError(hiddenSize, 0.0);
        for (int i = 0; i < hiddenSize; i++) {
            double sum = 0.0;
            for (int j = 0; j < outputSize; j++) {
                sum += weightsHiddenOutput[i][j] * outputError[j];
            }
            hiddenError[i] = sum * sigmoidDerivative(hiddenLayer[i][0]);
        }

        // Update the weights between the hidden and output layers
        for (int i = 0; i < hiddenSize; i++) {
            for (int j = 0; j < outputSize; j++) {
                weightsHiddenOutput[i][j] += learningRate * outputError[j] * hiddenLayer[i][0];
            }
        }

        // Update the weights between the input and hidden layers
        for (int i = 0; i < inputSize; i++) {
            for (int j = 0; j < hiddenSize; j++) {
                weightsInputHidden[i][j] += learningRate * hiddenError[j] * input[i];
            }
        }
    }
};
// Compute the loss
double computeLoss(const std::vector<double>& output, int label) {
    double target = (label == 0) ? 0.0 : 1.0;
    double error = output[0] - target;
    return error * error;
}

// Image preprocessing functions
std::vector<double> loadImage(const std::string& imagePath) {
    std::ifstream file(imagePath, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Failed to open image: " << imagePath << std::endl;
        exit(1);
    }

    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> imageBuffer(fileSize);
    if (!file.read(reinterpret_cast<char*>(imageBuffer.data()), fileSize)) {
        std::cerr << "Failed to read image: " << imagePath << std::endl;
        exit(1);
    }

    std::vector<double> imagePixels(imageBuffer.size());
    for (size_t i = 0; i < imageBuffer.size(); i++) {
        imagePixels[i] = static_cast<double>(imageBuffer[i]) / 255.0;
    }

    return imagePixels;
}

std::vector<double> preprocessImage(const std::vector<double>& imagePixels) {
    // Perform image preprocessing steps (e.g., resize, normalize, etc.)

    // Placeholder implementation: return the original image as is
    return imagePixels;
}

int main() {
    // Load the training images and labels
    std::vector<std::string> imagePaths = {
        "../../data/cat1.jpg",
        "../../data/cat2.jpg",
        "../../data/cat3.jpg",
        "../../data/cat4.jpg",
        "../../data/cat5.jpg",
        "../../data/dog1.jpg",
        "../../data/dog2.jpg",
        "../../data/dog3.jpg",
        "../../data/dog4.jpg",
        "../../data/dog5.jpg"
    };

    std::vector<double> labels = {
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1
    };

    // Preprocess the training images
    std::vector<std::vector<double>> preprocessedImages;
    for (const std::string& imagePath : imagePaths) {
        std::vector<double> imagePixels = loadImage(imagePath);
        std::vector<double> preprocessedImage = preprocessImage(imagePixels);
        preprocessedImages.push_back(preprocessedImage);
    }

    // Initialize the neural network
    NeuralNetwork neuralNetwork;

    // Train the network
    for (int epoch = 0; epoch < numEpochs; epoch++) {
        double totalLoss = 0.0;

        for (int i = 0; i < preprocessedImages.size(); i++) {
            // Forward pass
            std::vector<double> output = neuralNetwork.forward(preprocessedImages[i]);

            // Compute the loss
            double loss = computeLoss(output, labels[i]);
            totalLoss += loss;

            // Backward pass and weight update
            neuralNetwork.backward(preprocessedImages[i], labels[i]);
        }

        // Print average loss for the epoch
        double averageLoss = totalLoss / preprocessedImages.size();
        std::cout << "Epoch " << epoch << " Loss: " << averageLoss << std::endl;
    }

    // Classify new images
    std::string newImagePath = "../../data/staffy.jpg";
    std::vector<double> newImagePixels = loadImage(newImagePath);
    std::vector<double> preprocessedNewImage = preprocessImage(newImagePixels);

    // Forward pass
    std::vector<double> output = neuralNetwork.forward(preprocessedNewImage);

    // Perform classification based on the output

    return 0;
}

