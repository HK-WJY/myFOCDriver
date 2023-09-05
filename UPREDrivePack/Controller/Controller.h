#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#ifdef __cplusplus
};
#endif
class Motor;
class FOC;

class Controller{
public:
    Controller(Motor *motor,FOC *foc):_motor(motor),_foc(foc){}
    void OpenLoop(float vd,float vq,float dcBus,float tick,float rad);
private:
    Motor *_motor;
    FOC *_foc;
    float rad = 0;
    uint32_t lasttick=0,tick=0;
    float radio = 0;
    float vofa_float[6];
    uint8_t vofa_data[28];
};

extern Controller controller;

#endif