#ifndef __EEPROM__H_
#define __EEPROM__H_

// Includes
#include <string>
#include "mbed.h"

// Defines
#define EEPROM_Address     0xA0

#define EEPROM_NoError     0x00
#define EEPROM_BadAddress  0x01
#define EEPROM_I2cError    0x02
#define EEPROM_ParamError  0x03
#define EEPROM_OutOfRange  0x04
#define EEPROM_MallocError 0x05

#define EEPROM_MaxError       6

static std::string _ErrorMessageEEPROM[EEPROM_MaxError] = { "",
                                                            "Bad chip address",
                                                            "I2C error (nack)",
                                                            "Invalid parameter",
                                                            "Data address out of range",
                                                            "Memory allocation error"};

// Class
class EEPROM
{
public:
    enum TypeEeprom {T24C01=128,T24C02=256,T24C04=512,T24C08=1024,T24C16=2048,
                     T24C32=4096,T24C64=8192,T24C128=16384,T24C256=32768,
                     T24C512=65536,T24C1024=131072,T24C1025=131073
                    } Type;

    /*
     * Constructor, initialize the eeprom on i2c interface.
     * @param sda : sda i2c pin (PinName)
     * @param scl : scl i2c pin (PinName)
     * @param address : eeprom address, according to eeprom type (uint8_t)
     * @param type : eeprom type (TypeEeprom)
     * @return none
    */
    EEPROM(PinName sda, PinName scl, uint8_t address, TypeEeprom type=T24C64);

    /*
     * Random read byte
     * @param address : start address (uint16_t)
     * @param data : byte to read (int8_t&)
     * @return none
    */
    void read(uint16_t address, int8_t& data);

    /*
     * Random read short
     * @param address : start address (uint16_t)
     * @param data : short to read (int16_t&)
     * @return none
    */
    void read(uint16_t address, int16_t& data);

    /*
     * Random read long
     * @param address : start address (uint16_t)
     * @param data : long to read (int32_t&)
     * @return none
    */
    void read(uint16_t address, int32_t& data);

    /*
     * Random read float
     * @param address : start address (uint16_t)
     * @param data : float to read (float&)
     * @return none
    */
    void read(uint16_t address, float& data);

    /*
     * Random read anything
     * @param address : start address (uint16_t)
     * @param data : data to read (void *)
     * @param size : number of bytes to read (uint16_t)
     * @return none
    */
    void read(uint16_t address, void *data, uint16_t size);

    /*
     * Current address read byte
     * @param data : byte to read (int8_t&)
     * @return none
    */
    void read(int8_t& data);

    /*
     * Sequential read byte
     * @param address : start address (uint16_t)
     * @param data : bytes array to read (int8_t[]&)
     * @param size : number of bytes to read (uint16_t)
     * @return none
    */
    void read(uint16_t address, int8_t *data, uint16_t size);

    /*
     * Write byte
     * @param address : start address (uint16_t)
     * @param data : byte to write (int8_t)
     * @return none
    */
    void write(uint16_t address, int8_t data);

    /*
     * Write short
     * @param address : start address (uint16_t)
     * @param data : short to write (int16_t)
     * @return none
    */
    void write(uint16_t address, int16_t data);

    /*
     * Write long
     * @param address : start address (uint16_t)
     * @param data : long to write (int32_t)
     * @return none
    */
    void write(uint16_t address, int32_t data);

    /*
     * Write float
     * @param address : start address (uint16_t)
     * @param data : float to write (float)
     * @return error number if > 0 (uint8_t)
    */
    void write(uint16_t address, float data);

    /*
     * Write anything
     * @param address : start address (uint16_t)
     * @param data : data to write (void *)
     * @param size : number of bytes to read (uint16_t)
     * @return none
    */
    void write(uint16_t address, void *data, uint16_t size);

    /*
     * Write page
     * @param address : start address (uint16_t)
     * @param data : bytes array to write (int8_t[])
     * @param size : number of bytes to write (uint16_t)
     * @return none
    */
    void write(uint16_t address, int8_t data[], uint16_t size);

    /*
     * Wait eeprom ready
     * @param : none
     * @return none
    */
    void ready(void);

    /*
     * Get eeprom size in bytes
     * @param : none
     * @return size in bytes (uint16_t)
    */
    uint32_t getSize(void);

    /*
    * Get the current error number (EEPROM_NoError if no error)
    * @param  : none
    * @return current error number (uint8_t)
    */
    uint8_t getError(void);

    /*
     * Get current error message
     * @param  : none
     * @return current error message(std::string)
    */
    std::string getErrorMessage(void) {
        return(_ErrorMessageEEPROM[_errnum]);
    }

//---------- local variables ----------
private:
    I2C _i2c;             // Local i2c communication interface instance
    int _address;         // Local ds1621 i2c address
    uint8_t _errnum;      // Error number
    TypeEeprom _type;     // EEPROM type
    uint8_t _page_write;  // Page write size
    uint8_t _page_number; // Number of page
    uint32_t _size;       // Size in bytes
    bool checkAddress(uint16_t address); // Check address range
//-------------------------------------
};
#endif
