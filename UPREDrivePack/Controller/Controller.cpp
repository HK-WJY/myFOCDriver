#include "Controller.h"
#include "FOC.h"
#include "Motor.h"
#include "usbd_cdc_if.h"
#include "Encoder.h"
extern float dcBus,currentA,currentB,currentC;;
void Controller::OpenLoop(float vd, float vq, float dcBus, float tick, float rad) {
    this->lasttick = this->tick;
    this->tick = tick;

    //radio += (rad * 0.001f)*(this->tick - this->lasttick);
    radio = rad;//+(rad * 0.001f * (this->tick - this->lasttick));
    radio = radio >= 28*PI ? 0 : radio;

    _foc->Svm(vd,vq,dcBus,radio);
    _motor->setCCR(_foc->CCRs[0],_foc->CCRs[1],_foc->CCRs[2]);

    vofa_float[0] =  dcBus;
    vofa_float[1] =  currentA;
    vofa_float[2] =  currentB;
    vofa_float[3] =  currentC;
    vofa_float[4] =  radio;
    vofa_float[5] =  encoder.getRadio();
//    vofa_float[0] =  radio;
//    vofa_float[1] =  encoder.getRadio();
//    vofa_float[2] =  0;
//    vofa_float[3] =  0;
//    vofa_float[4] =  0;
//    vofa_float[5] =  0;
    memcpy(vofa_data,(uint8_t*)vofa_float,sizeof(vofa_float));
    vofa_data[26] = 0X80;
    vofa_data[27] = 0X7F;

    CDC_Transmit_FS(vofa_data,28);

}