//
// Created by Daniel Hammerl on 09.11.22.
//

#ifndef DCAEMULATOR_GLOBALSTATE_H
#define DCAEMULATOR_GLOBALSTATE_H

#include "base.h"

class GlobalState {
public:
#ifdef MODE_DEBUG
    static inline bool debugMode = false;
#endif
    static inline bool showPerformanceData = false;
    static inline bool noGpu = false;
    static inline bool debugRegisterValues = false;
};


#endif //DCAEMULATOR_GLOBALSTATE_H
