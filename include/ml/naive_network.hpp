#ifndef NAIVE_NET_HPP
#define NAIVE_NET_HPP

#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

typedef float Scalar;
typedef Eigen::MatrixXf Matrix;
typedef Eigen::RowVectorXf RowVector;
typedef Eigen::VectorXf ColVector;


namespace mtpk {

class NaiveNet {
    public:
        // contructor
        naive_network(std::vector<uint> topology, 
                    Scalar learningRate = Scalar(0.005));

        /* perform forward propagation */
        void forward_prop(RowVector& input);
        /* perform backward propagation*/
        void backward_prop(RowVector& output);
        /* calculate neuron errors */
        void errors(RowVector& output);
        /* update weights of neuron connections */
        void update_weights();
        /* train neural network given vector of data points */
        void train(std::vector<RowVector*> data);


        /* Naive Network storage objects */

        /* store layers of the network*/
        std::vector<RowVector*> neuron_layers; 
        /* stored un-evaluated values of the layers */
        std::vector<RowVector*> cache_layers; 
        /* stores error contribution of each neuron */
        std::vector<RowVector*> deltas; 
        /* the connection weight */
        std::vector<Matrix*> weights; 
        /* learning rate  */
        Scalar learning_rate;
};

} // namespace

#endif

