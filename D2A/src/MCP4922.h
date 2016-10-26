/*
 * MCP4922 - DAC library.
 *
 * Copyright (c) 2011 Steven Beard, UK Astronomy Technology Centre.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "mbed.h"

#ifndef MCP4922_H
#define MCP4922_H

/* Reference: Microchip Technology (2005), MCP4821/MCP4822 DAC Data Sheet. */

// MCP4922 reference voltage.
//#define MCP4922_VREF     2048    // Reference voltage (mV)
#define MCP4922_VREF     3300    // Reference voltage (mV)

/* Define possible combinations of 16-bit command register bits */
#define MCP4922_REG_A1   0x3000  // Channel A gain 1
#define MCP4922_REG_B1   0xB000  // Channel B gain 1
#define MCP4922_REG_SHDN 0x0000  // Output power down

class MCP4922 {
public:

    MCP4922 (PinName mosi, PinName sclk, PinName cs);

    ~MCP4922();

    /*+
     * frequency: Set the SPI bus clock frequency in Hz.
     *        The SPI bus frequency in Hz. Must be within the range
     *        supported by both the SPI interface and the DAC chips
     *        (~10 KHz to 20 MHz).
     */
    void frequency( int freq );
    
    void writeA(int value );
    
    void writeB(int value );

    void write( int nchans, int values[], int gain=2, int latch=1 );

    void latch_enable();
    
    void latch_disable();

private:
    
    MCP4922( const MCP4922& rhs );
    
    void _init();

    int _ndacs;              // The number of DACS in the array
    int _latched;            // Is the "not LDAC" pin used (1=yes; 0=no)?
    SPI _spi;                // SPI bus object for communicating with DAC.
    DigitalOut** _ncs_array; // Array of pointers to DigitalOut objects
    // connected to "not CS" pins.
    DigitalOut* _nldac;      // Pointer to DigitalOut object connected
    // to "not LDAC" pin (if any - NULL if none).
};

#endif
