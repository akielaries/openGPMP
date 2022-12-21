/*
 * Multi-Layer Perceptron Neural Network
 */
#ifndef MLP_NETWORK_HPP
#define MLP_NETWORK_HPP
#include <vector>
#include <stdio.h>


/*
 * TODO 
 * Think of using extended or derived classes
 *
 * Weights : MLP
 *
 */
struct neuron { 
    // exit
    double  x;
    // error
    double  e;
    // weight
    double* w;
    // last weight
    double* dw;
    // saved weight
    double* wsave;
};

struct layer {
    int     num_neurons;
    neuron* neuron_ptr;
};

class MLP {
    int    num_ayers;
    layer* layer_ptr;

    double dMSE;
    double dMAE;

    void weights_ran();

    void set_in_sig(double* input);
    void get_out_sig(double* output);

    void weights_save();
    void weights_restore();

    void prop_Sig();
    void output_err(double* target);
    void back_prop_err();
    void weights_adjust();

    void simulate(double* input, double* output, 
                double* target, bool training);


    public:
        double dEta;
        double dAlpha;
        double dGain;
        double dAvgTestError;

        MLP(int nl, int npl[]);
        ~MLP();

        int train(const char* fnames);
        int test (const char* fname);
        int evaluate();

        void run(const char* fname, const int& maxiter);

};

#endif

