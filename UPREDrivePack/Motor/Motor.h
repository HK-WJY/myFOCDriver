#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "tim.h"

#ifdef __cplusplus
};
#endif

class Motor{
public:
    Motor(){};
    void Start(TIM_HandleTypeDef *htim);
    void setCCR(float ccr1,float ccr2,float ccr3);
protected:
    TIM_HandleTypeDef *_htim;
};

extern Motor motor;
