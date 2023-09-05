#include "FOC.h"
#include "arm_math.h"
void FOC::RevPark(float Vd,float Vq,float Theta,float *VAlpha,float *VBeta){
    *VAlpha = Vd * arm_cos_f32(Theta) - Vq * arm_sin_f32(Theta);
    *VBeta  = Vd * arm_sin_f32(Theta) + Vq * arm_cos_f32(Theta);
}

uint8_t FOC::GetSector(float VAlpha,float VBeta){
    uint8_t A =  VBeta > 0 ? 1 : 0;
    uint8_t B = (VAlpha*sqrt3/2.0f  - VBeta/2.0f) > 0 ? 1 : 0;
    uint8_t C = (-VAlpha*sqrt3/2.0f  - VBeta/2.0f) > 0 ? 1 : 0;
    return 4*C + 2*B + A;
}

void FOC::CalcVectorTime(float *Ta,float *Tb,uint32_t TPwm,uint8_t Sector,float Udc,float VAlpha,float VBeta)
{
    float X = (sqrt3 * (float)TPwm) / Udc * VBeta;
    float Y = (sqrt3 * (float)TPwm) / Udc * ( (sqrt3 / 2.0f)*VAlpha - 0.5f * VBeta);
    float Z = (sqrt3 * (float)TPwm) / Udc * (-(sqrt3 / 2.0f)*VAlpha - 0.5f * VBeta);

    Sector == 3 ? *Ta =  Y,*Tb =  X : 0;
    Sector == 1 ? *Ta = -Y,*Tb = -Z : 0;
    Sector == 5 ? *Ta =  X,*Tb =  Z : 0;
    Sector == 4 ? *Ta = -X,*Tb = -Y : 0;
    Sector == 6 ? *Ta =  Z,*Tb =  Y : 0;
    Sector == 2 ? *Ta = -Z,*Tb = -X : 0;
}

void FOC::CalcCCRs(float Ta,float Tb,float TPwm,uint8_t Sector){
    float total = Ta + Tb;
    if(total > (float)TPwm){
        Ta = Ta / total * (float)TPwm;
        Tb = Tb / total * (float)TPwm;
    }
    float v1 = ((float)TPwm - Ta - Tb) / 4.0f;
    float v2 = v1 + Ta / 2.0f;
    float v3 = v2 + Tb / 2.0f;

    switch (Sector) {
        case 3:{
            CCRs[0] = v1;CCRs[1] = v2;CCRs[2] = v3;
        }break;
        case 1:{
            CCRs[0] = v2;CCRs[1] = v1;CCRs[2] = v3;
        }break;
        case 5:{
            CCRs[0] = v3;CCRs[1] = v1;CCRs[2] = v2;
        }break;
        case 4:{
            CCRs[0] = v3;CCRs[1] = v2;CCRs[2] = v1;
        }break;
        case 6:{
            CCRs[0] = v2;CCRs[1] = v3;CCRs[2] = v1;
        }break;
        case 2:{
            CCRs[0] = v1;CCRs[1] = v3;CCRs[2] = v2;
        }break;
        default:break;
    }
}

void FOC::Svm(float Vd, float Vq, float dcBus, float radio) {
    float VAlpha,VBeta;
    uint8_t Sector;
    float Ta,Tb;

    RevPark(Vd,Vq,radio,&VAlpha,&VBeta);
    Sector = GetSector(VAlpha,VBeta);
    CalcVectorTime(&Ta,&Tb,_tpwm,Sector,24,VAlpha,VBeta);
    CalcCCRs(Ta,Tb,_tpwm , Sector);
}