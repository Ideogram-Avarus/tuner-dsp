#pragma once
#include "tuner/tuner_engine.h"
#include "types.h"


namespace native_side {

    
    class NativeTunerDsp {
        public:
        explicit NativeTunerDsp(TunerConfig config);
        
        void cxxProcessFrame(const float* samples, int size);
        TunerResult cxxGetLatestResult() const;
        void cxxReset();
        
        private:
        tuner::CxxTunerEngine engine_;
    };


}