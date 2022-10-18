/*
 * testing our implemented k-fold cross-validation
 */

#include "k-foldCV.h"
using namespace std;


TEST_CASE("KF_CV-testSmallSample10Fold") {
    vector<string> small_sample = {
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    KF_CV<string> kF_CV = KF_CV<string>(smallSample, 10, 1);
    vector<string> test_sample = kF_CV.get_test_fold(0);
    REQUIRE(test_sample[0] == "2");
}

TEST_CASE("KF_CV-testSmallSample5Fold") {
    vector<string> small_sample = {
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    KF_CV<string> kF_CV = KF_CV<string>(small_sample, 5, 1);
    vector<string> test_sample = kF_CV.get_test_fold(0);
    REQUIRE(test_sample[0] == "2");
    REQUIRE(test_sample[1] == "7");
}

TEST_CASE("KF_CV-testLargeSample10Fold") {
    vector<int> large_sample;
    for (int i = 0; i < 1000; i++){
        large_sample.emplace_back(i);
    }
    KF_CV<int> kF_CV = KF_CV<int>(large_sample, 10, 1);
    for (int i = 0; i < 10; i++){
        REQUIRE(100 == kF_CV.get_test_fold(i).size());
        REQUIRE(900 == kF_CV.get_train_fold(i).size());
    }
}

TEST_CASE("KFCV-testLargeSample5Fold") {
    vector<int> large_sample;
    for (int i = 0; i < 1000; i++){
        large_sample.emplace_back(i);
    }
    KF_CV<int> kF_CV = KF_CV<int>(large_sample, 5, 1);
    for (int i = 0; i < 5; i++){
        REQUIRE(200 == kF_CV.get_test_fold(i).size());
        REQUIRE(800 == kF_CV.get_train_fold(i).size());
    }
}



