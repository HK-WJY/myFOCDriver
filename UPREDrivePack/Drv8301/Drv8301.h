#ifndef __DRV8301_H__
#define __DRV8301_H__

#ifdef __cplusplus
extern "C" {
#endif
#define CURRENT1_7A     0X0000
#define CURRENT0_7A     0X0001
#define CURRENT0_25A    0X0002
#define GATE_RST_NORMAL 0X0000
#define GATE_RST_LATCH  0X0004
#define PHASE6PWM       0X0000
#define PHASE3PWM       0X0008
#define CURRENTLIMIT    0x0000
#define OCLATCHSTDOWN   0X0010
#define REPORTONLY      0X0020
#define OCDISABLE       0X0030
#define OCOTBOTH        0X0000
#define OTONLY          0X0001
#define OCONLY          0X0002
#define OCONLYRSVD      0X0003
#define GAIN10          0X0000
#define GAIN20          0X0004
#define GAIN40          0X0008
#define GAIN80          0X000C
#define CONNECTLOADPH1  0X0000
#define SHORTINPUTPH1   0X0010
#define CONNECTLOADPH2  0X0000
#define SHORTINPUTPH2   0X0020
#define CYCLEBYCYCLE    0X0000
#define OFFTIMECTRL     0X0040
#define DRV8301WRITE    (0X00 << 15)
#define DRV8301READ     (0X01 << 15)
#define REGSTATUS1       0X00
#define REGSTATUS2       0X01
#define REGCTRL1         0X02
#define REGCTRL2         0X03

#include "main.h"
#include "spi.h"

#ifdef __cplusplus
};
#endif

#ifdef __cplusplus
class Drv8301{
public:
    Drv8301(){}
    void setParam(uint16_t Gc,uint16_t Gr,uint16_t Pm,uint16_t OcpM,uint16_t Oas,uint16_t Om,uint16_t Gv,uint16_t Dcc1,uint16_t Dcc2,uint16_t Ot);
    uint16_t read();
    void write(uint16_t data);
    uint8_t Start();
    uint32_t get_error();
protected:
    uint16_t Gate_Current=0,Gate_Reset=0,Pwm_Mode=0,Ocp_Mode=0,Oc_Adj_Set=0,Octw_Mode=0,GainValue=0,Dc_Cal_Ch1=0,Dc_Cal_Ch2=0,Oc_Toff=0;
};
#endif

extern Drv8301 drv8301;
#endif
