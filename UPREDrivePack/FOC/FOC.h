#ifndef __FOC_H__
#define __FOC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "arm_math.h"

#ifdef __cplusplus
};
#endif

class Motor;

class FOC{
public:
    FOC(uint32_t Tpwm):_tpwm(Tpwm){}
    void RevPark(float Vd,float Vq,float Theta,float *VAlpha,float *VBeta);
    uint8_t GetSector(float VAlpha,float VBeta);
    void CalcVectorTime(float *Ta,float *Tb,uint32_t TPwm,uint8_t Sector,float Udc,float VAlpha,float VBeta);
    void CalcCCRs(float Ta,float Tb,float TPwm,uint8_t Sector);
    void Svm(float Vd,float Vq,float dcBus,float radio);

//private:
    float CCRs[3] = {0,0,0};
    uint32_t _tpwm = 16800;

};

extern FOC foc;
#endif