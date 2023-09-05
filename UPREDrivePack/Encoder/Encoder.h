#ifndef __ENCODER_H__
#define __ENCODER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "arm_math.h"

#ifdef __cplusplus
};
#endif

class Encoder{
public:
    Encoder(TIM_HandleTypeDef *htim,SPI_HandleTypeDef *hspi,uint16_t error):_htim(htim),_hspi(hspi),_error(error){}

    inline uint16_t getAbusoluteCNT()
    {
        uint16_t command = 0X3FFF, angle = 0;
        HAL_GPIO_WritePin(ENC_NSS_GPIO_Port,ENC_NSS_Pin,GPIO_PIN_RESET);
        HAL_SPI_TransmitReceive(_hspi,(uint8_t*)&command,(uint8_t*)&angle,1,10);
        HAL_GPIO_WritePin(ENC_NSS_GPIO_Port,ENC_NSS_Pin,GPIO_PIN_SET);
        return angle&0X3FFF;
    }

    inline float getRadio(){
        uint16_t cnt = getAbusoluteCNT();
        if(cnt>=_error) cnt-=_error;
        else           cnt = cnt+16384-_error;
        return ((cnt / 16384.f) * (28*PI));
    }
//private:
    SPI_HandleTypeDef *_hspi;
    TIM_HandleTypeDef *_htim;
    uint16_t _error=0;
};
extern Encoder encoder;

#endif