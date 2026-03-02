#pragma once
#include <vector>


namespace tuner {

    
class PitchDetector {
public:
    explicit PitchDetector(int sampleRate);

    // Returns detected frequency in Hz.
    // Returns -1 if no pitch detected.
    double detect(const std::vector<float>& buffer);

private:
    int sampleRate;

    double difference(const std::vector<float>& buffer, int tau);
    double cumulativeMeanNormalizedDifference(
        const std::vector<float>& diff,
        int tau
    );
};


};