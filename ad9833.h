/*
 * Written by vigneshwaran m <mvigneshwaran274@gmail.com>
 * File:   ad9833.h
 * Created on 2018-02-16 14:54:14
 */

#ifndef AD9833_H
#define AD9833_H


#define FREQUENCY_MAX	12000000

/**
  * @brief  Transmits a byte through the SPI peripheral.
  * @param  Data
  */
extern void SPI_SendData(uint8_t Data);


/**
 * @brief Function to toggle FSYNC of ad9833
 * Active Low Control Input. FSYNC is the frame synchronization signal for the input data. When FSYNC is taken low,
 * the internal logic is informed that a new word is being loaded into the device.
 * @param Level 
 */
extern void FSYNC_Write(uint8_t Level);

/**
 * @brief This function eliminate the need of 64bit variable during Arithmetic operation
 * 
 * @param a Frequency
 * @param b 2 power 28
 * @param c master clock frequency
 * @return uint32_t Frequency request number
 */ 
uint32_t muldiv(uint32_t a, uint32_t b, uint32_t c); 

/**
 * @brief 
 * @param Freq  output frequency
 * @param lsb   out-  Address of LSB
 * @param hsb   out-  Address of HSB
 * @return int 
 *      -1 - Error
 *       0 - Success
 */
int frequencyReq(uint32_t *Freq,uint16_t *lsb,uint16_t *hsb);

/**
 * @brief set AD933 Control Register Bits
 * @param cmdH 
 * @param cmdL 
 */
void ad9833_send(uint8_t cmdH,uint8_t cmdL);

/**
 * @brief set output Frequency (sinewave)
 * @param frequency 
 * @return int
 *      -1 - Error
 *       0 - Success
 */
int ad9833_setFreq(uint32_t frequency);


#endif      //AD9833_H