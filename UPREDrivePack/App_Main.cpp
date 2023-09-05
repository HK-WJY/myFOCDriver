#ifdef __cplusplus
extern "C" {
#endif
#include "usbd_cdc_if.h"
#include "main.h"
#include "adc.h"
#ifdef __cplusplus
};
#endif
#include "Drv8301.h"
#include "Motor.h"
#include "FOC.h"
#include "Controller.h"
#include "Encoder.h"
float vd = 0,vq =0,rad = 0;


Drv8301 drv8301;
Motor motor;
FOC foc(TPWM);
Controller controller(&motor,&foc);
Encoder encoder(&htim4,&hspi1,0);//11900
uint32_t CNT_ms=0;
uint32_t ADC_Values[16];
float dcBus,currentA,currentB,currentC;
bool isok = false;

void App_Main()
{
    while(drv8301.Start()){}

    motor.Start(&htim1);
    HAL_TIM_Base_Start_IT(&htim14);

    HAL_ADC_Start_DMA(&hadc1,ADC_Values,16);
    HAL_ADCEx_InjectedStart(&hadc1);
    HAL_ADCEx_InjectedStart(&hadc2);
    HAL_ADCEx_InjectedStart(&hadc3);

    vd=1.0f;vq=0;rad=0;
    HAL_Delay(1000);
    encoder._error = encoder.getAbusoluteCNT();
    HAL_Delay(1000);
    isok=true;
    for(;;)
    {
        vd=0;
        vq=8.f;
        HAL_Delay(1000);
    }

}


#ifdef __cplusplus
extern "C"{
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM14){
        CNT_ms++;

    }

    if(htim->Instance == TIM1){

    }

}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim){
    if(htim->Instance == TIM1){
        uint16_t Vbus,Ib,Ic;

        Vbus = ADC1->JDR1;
        Ib   = ADC2->JDR1;
        Ic   = ADC3->JDR1;

        dcBus    =  ((float)Vbus/4096.f)*3.3f*11.f;
        currentB =  (float)(Ib - 2048) * (3.3f / 4096.f) / 80.f / 0.001f;
        currentC =  0.8f*(float)(Ic - 2048) * (3.3f / 4096.f) / 80.f / 0.001f;
        currentA = -0.8f*(currentB + currentC);
        if(isok)rad = encoder.getRadio();//+0.00000001*PI;
        controller.OpenLoop(vd,vq,dcBus,CNT_ms,rad);

    }
}
};
#endif


