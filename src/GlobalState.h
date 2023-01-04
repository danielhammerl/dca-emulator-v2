//
// Created by Daniel Hammerl on 09.11.22.
//

#ifndef DCAEMULATOR_GLOBALSTATE_H
#define DCAEMULATOR_GLOBALSTATE_H


class GlobalState {
public:
    static inline bool debugMode = false;
    static inline bool showPerformanceData = false;
    static inline bool noGpu = false;
    static inline bool debugRegisterValues = false;
};


#endif //DCAEMULATOR_GLOBALSTATE_H
