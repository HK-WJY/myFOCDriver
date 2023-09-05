#include "Motor.h"
void Motor::Start(TIM_HandleTypeDef *htim) {
    this->_htim = htim;

    //开启6路PWM通道
    HAL_TIM_Base_Start_IT(_htim);
    HAL_TIM_PWM_Start_IT(_htim,TIM_CHANNEL_4);

    HAL_TIM_PWM_Start(_htim,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(_htim,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(_htim,TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(_htim,TIM_CHANNEL_4);
    HAL_TIMEx_PWMN_Start(_htim,TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Start(_htim,TIM_CHANNEL_2);
    HAL_TIMEx_PWMN_Start(_htim,TIM_CHANNEL_3);
}

void Motor::setCCR(float ccr1,float ccr2,float ccr3) {
    _htim->Instance->CCR1 = (uint32_t)ccr1;
    _htim->Instance->CCR2 = (uint32_t)ccr2;
    _htim->Instance->CCR3 = (uint32_t)ccr3;
}