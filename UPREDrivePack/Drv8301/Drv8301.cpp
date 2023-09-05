#include "Drv8301.h"
#include "usbd_cdc_if.h"
void Drv8301::setParam(uint16_t Gc,//Gate_Current
                       uint16_t Gr,
                       uint16_t Pm,
                       uint16_t OcpM,
                       uint16_t Oas,
                       uint16_t Om,
                       uint16_t Gv,
                       uint16_t Dcc1,
                       uint16_t Dcc2,
                       uint16_t Ot){
    this->Gate_Current = Gc;
    this->Gate_Reset   = Gr;
    this->Pwm_Mode     = Pm;
    this->Ocp_Mode     = OcpM;
    this->Oc_Adj_Set   = Oas;
    this->Octw_Mode    = Om;
    this->GainValue    = Gv;
    this->Dc_Cal_Ch1   = Dcc1;
    this->Dc_Cal_Ch2   = Dcc2;
    this->Oc_Toff      = Ot;
}

uint16_t Drv8301::read() {
    uint16_t result = 0;
    DRV_SPI_ON();
    HAL_SPI_Receive_DMA(&hspi3,(uint8_t*)&result,1);
    while(hspi3.State == HAL_SPI_STATE_BUSY_RX){}
    DRV_SPI_OFF();
    return result;
}

void Drv8301::write(uint16_t data) {
    DRV_SPI_ON();
    HAL_SPI_Transmit_DMA(&hspi3,(uint8_t*)&data,1);
    while(hspi3.State == HAL_SPI_STATE_BUSY_TX){}
    DRV_SPI_OFF();
}

uint8_t Drv8301::Start(){
    //设置初始化参数
    setParam(CURRENT1_7A,GATE_RST_NORMAL,PHASE6PWM,OCLATCHSTDOWN,17,OCOTBOTH,20,CONNECTLOADPH1,CONNECTLOADPH2,CYCLEBYCYCLE);

    //启动Drv8301

    DRV_OFF();
    HAL_Delay(500);
    DRV_ON();
    HAL_Delay(500);

    //初始化Drv8301寄存器
    uint16_t config1 = 0,config2 = 0,regvalue = 0;
    //config1  = DRV8301WRITE | REGCTRL1<<11 | ((this->Gate_Current | this->Gate_Reset | this->Pwm_Mode | this->Ocp_Mode | this->Oc_Adj_Set));
    config1  = DRV8301WRITE | REGCTRL1<<11 | ((21<<6 | 0b01<<4 | 0b0<<3 | 0b0<<2 | 0b00<<0) & 0X07FF);
    write(config1);
    config2 = DRV8301READ | REGCTRL1 << 11;
    write(config2);
    regvalue = read();

    if((regvalue & 0X7FF)!=(config1 & 0X7FF)){
        return 1;
    }

    config1 = 0;
   // config1 = DRV8301WRITE | REGCTRL2<<11 | this->Octw_Mode | this->GainValue | this->Dc_Cal_Ch1 | this->Dc_Cal_Ch2 | this->Oc_Toff << 6;
    config1 = DRV8301WRITE | REGCTRL2<<11 | ((0b0<<6|0b00<<4|0<<2|0b00<<0));
    write(config1);
    config2 = DRV8301READ | REGCTRL2 << 11;
    write(config2);
    regvalue = read();
    if((regvalue & 0X7FF)!=(config1 & 0X7FF)){
        return 2;
    }
    return 0;
}