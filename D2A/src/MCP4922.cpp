/*
 * MCP4922 - DAC library.
 */

#include "mbed.h"
#include "MCP4922.h"

using namespace mbed;

int dac =0;

MCP4922::MCP4922(PinName mosi, PinName sclk, PinName cs) : _spi(mosi, NC, sclk) {

    int i;
    _ndacs = 1;
    _ncs_array = new DigitalOut*[ _ndacs ];
    for (i=0; i<_ndacs; i++) {
        _ncs_array[i] = new DigitalOut(cs);
    }

    // Initialise the DAC SPI interface.
    _init();
}

// Destructor
MCP4922::~MCP4922() {

    // Before destroying the object, shut down all the chips.
    //shdn_all();

    // Delete all the NCS DigitalOut objects and the array pointing to
    // them.
    int i;
    for (i=0; i<_ndacs; i++) {
        delete _ncs_array[i];
    }
    delete [] _ncs_array;

    // Delete the LDAC DigitalOut object if it exists.
    if (_latched ) delete _nldac;
}

// Initialise SPI interface.
void MCP4922::_init() {

    // Set up the SPI for 16-bit values (12-bit + 4 command bits) and mode 0.
    _spi.format(16, 0);

    // Start with all the CS and LDAC signals high (disabled)
    int i;
    for (i=0; i<_ndacs; i++) {
        _ncs_array[i]->write(1);
    }

    if (_latched ) _nldac->write(1);
    return;
}

// Set SPI clock frequency.
void MCP4922::frequency( int freq ) {

    // Set the SPI interface clock frequency in Hz.
    _spi.frequency( freq );
    return;
}

/*
 * Note: There is a lot of code in common between the following 4 functions.
 * The code is kept in line to keep it efficient. Could the functions have
 * been written as templates?
 */
// Write to DAC channel A with gain 1.
void MCP4922::writeA(int value) {

    // Set up the command register with the appropriate value.
    // For efficiency, the caller is assumed to have checked dac.
    int reg;
    //int dac = 0;
    reg = (value & 0x0FFF) | MCP4922_REG_A1;

    // Select the DAC chip, write to its command register and
    // then unselect the DAC chip.
    _ncs_array[dac]->write(0);
    _spi.write(reg);
    _ncs_array[dac]->write(1);
    return;
}

// Write to DAC channel B with gain 1.
void MCP4922::writeB(int value) {

    // Set up the command register with the appropriate value.
    // For efficiency, the caller is assumed to have checked dac.
    int reg;
    reg = (value & 0x0FFF) | MCP4922_REG_B1;

    // Select the DAC chip, write to its command register and then
    // unselect the DAC chip.
    _ncs_array[dac]->write(0);
    _spi.write(reg);
    _ncs_array[dac]->write(1);
    return;
}

// Write an array of values to the DACs.
void MCP4922::write(int nchans, int values[], int gain, int latch) {

    // nchans must be at least 1 but less than or equal to ndacs x 2.
    if (nchans < 1) nchans = 1;
    const int maxchans = _ndacs * 2;
    if (nchans > maxchans) nchans = maxchans;

    if (latch && _latched)
        latch_disable();

    int i;

        for (i=0; i<nchans;) {
            dac = i/2;
            writeA(values[i]);
            i++;
            if (i < nchans) {
                writeB(values[i]);
                i++;
            } else break;
        }

    // Automatically latch the new voltages if the latch flag is 1.
    if (latch && _latched)
        latch_enable();
    return;
}

// Set latch signal to "enable".
void MCP4922::latch_enable() {

    // Latch all chips. There should be a delay of at least T_LS=40
    // nanoseconds between the last CS rising edge and the LDAC falling
    // edge. The software function calls seem to be sufficient to
    // introduce that delay. A delay may be inserted here if this
    // software is ported to a faster processor.
    if (_latched) _nldac->write(0);
    // The LDAC pulse width must be at least T_LD=100 nanoseconds long.
    // A delay can be inserted here if necessary, but so far this has
    // not been needed (see above).
    return;
}

// Set latch signal to "disable".
void MCP4922::latch_disable() {

    // Disable latch for all chips.
    if (_latched) _nldac->write(1);
    return;
}

