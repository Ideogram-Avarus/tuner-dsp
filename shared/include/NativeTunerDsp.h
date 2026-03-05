#pragma once
#include "tuner_engine.h"
#include "types.h"


namespace native_side {

    
    class NativeTunerDsp {
        public:
        explicit NativeTunerDsp(int sampleRate);
        
        void cxxProcessFrame(const float* samples, int size);
        TunerResult cxxGetLatestResult() const;
        void cxxReset();
        
        private:
        tuner::TunerEngine engine_;
    };


}