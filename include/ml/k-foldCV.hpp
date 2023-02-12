/*
 * header for cross-validation + k-fold cross-validation
 * implementations in C++
 */

#ifndef KFOLDCV_H
#define KFOLDCV_H
#include <random>
#include <vector>

using namespace std;

namespace mtpk {

template <class T>
class CV {
    protected:
    int64_t K;

    public:
    virtual vector<T> get_train_fold(int64_t k) = 0;
    virtual vector<T> get_test_fold(int64_t k)  = 0;
};

template <class T>
class KF_CV : public CV<T> {
    private:
    int64_t N;
    vector<T> instance_list;

    public:
    KF_CV(const vector<T> &instance_list, int64_t K, uint64_t seed);
    vector<T> get_train_fold(int64_t k);
    vector<T> get_test_fold(int64_t k);
};

/**
 * A constructor of {@link KFoldCrossValidation} class which takes a
 * sample as an array of instances, a K (K in K-fold cross-validation)
 * and a seed number, then shuffles the original sample using this
 * seed as random number.
 *
 * @param instanceList Original sample
 * @param K K in K-fold cross-validation
 * @param seed Random number to create K-fold sample(s)
 */
template <class T>
KF_CV<T>::KF_CV(const vector<T> &instance_list, int64_t K, uint64_t seed) {
    this->instance_list = instance_list;
    shuffle(this->instance_list.begin(), this->instance_list.end(),
            default_random_engine(seed));
    N       = instance_list.size();
    this->K = K;
}

/**
 * getTrainFold returns the k'th train fold in K-fold
 * cross-validation.
 *
 * @param k index for the k'th train fold of the K-fold
 * cross-validation
 * @return Produced training sample
 */
template <class T>
vector<T> KF_CV<T>::get_train_fold(int64_t k) {
    vector<T> train_fold;
    for (int64_t i = 0; i < (k * N) / this->K; i++) {
        train_fold.push_back(instance_list.at(i));
    }
    for (int64_t i = ((k + 1) * N) / this->K; i < N; i++) {
        train_fold.push_back(instance_list.at(i));
    }
    return train_fold;
}

/**
 * getTestFold returns the k'th test fold in K-fold cross-validation.
 *
 * @param k index for the k'th test fold of the K-fold
 * cross-validation
 * @return Produced testing sample
 */
template <class T>
vector<T> KF_CV<T>::get_test_fold(int64_t k) {
    vector<T> test_fold;
    for (int64_t i = (k * N) / this->K; i < ((k + 1) * N) / this->K; i++) {
        test_fold.push_back(instance_list.at(i));
    }
    return test_fold;
}

} // namespace mtpk

#endif
