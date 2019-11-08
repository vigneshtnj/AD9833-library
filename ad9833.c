/*
 * Written by vigneshwaran m <mvigneshwaran274@gmail.com>
 * File:   ad9833.c
 * Created on 2018-02-20 14:02:29
 */
#include "ad9833.h"

uint32_t muldiv(uint32_t a, uint32_t b, uint32_t c)
{
	//	x=(a*b)/c
    uint32_t q = 0;              // the quotient
    uint32_t r = 0;              // the remainder
    uint32_t qn = b / c;
    uint32_t rn = b % c;
    while(a)
    {
        if (a & 1)
        {
            q += qn;
            r += rn;
            if (r >= c)
            {
                q++;
                r -= c;
            }
        }
        a  >>= 1;
        qn <<= 1;
        rn <<= 1;
        if (rn >= c)
        {
            qn++; 
            rn -= c;
        }
    }
    return q;
}
int frequencyReq(uint32_t *Freq,uint16_t *lsb,uint16_t *hsb){
    uint32_t FreqReq;
    if(*Freq > FREQUENCY_MAX){
        return -1;
    }
    FreqReq=muldiv(*Freq,268435456,25000000);
    *lsb = (FreqReq|0x4000)&0x7fff;
	*hsb = ((FreqReq >> 14)|(0x4000))&0x7fff;
    return 0;
}

void ad9833_send(uint8_t cmdH,uint8_t cmdL){
        FSYNC_Write(0);
        SPI_SendData(cmdH);
        SPI_SendData(cmdL);
        while(!SPI_GetFlagStatus(SPI_FLAG_TXE));
        FSYNC_Write(1);
        _asm("nop");
}

int ad9833_setFreq(uint32_t frequency){
    uint16_t lsb,hsb;
    uint8_t lsb_h,lsb_l;
    uint8_t hsb_h,hsb_l;

    if(frequencyReq(&frequency,&lsb,&hsb) >= 0){
        lsb_h = lsb >> 8;
        lsb_l = lsb&0xff;
        hsb_h = hsb >> 8;
        hsb_l = hsb&0xff;

        ad9833_send(0x21,0x00);
        ad9833_send(lsb_h,lsb_l);
        ad9833_send(hsb_h,hsb_l);
        ad9833_send(0xC0,0x00);
        ad9833_send(0x20,0x00);

        return 0;
    }
    return -1;

}