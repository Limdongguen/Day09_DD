#include "device_driver.h"
#include "gmock/gmock.h"

class ReadFiveTimeFail : public std::exception {};
class WriteFail : public std::exception {};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{} 

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    int result;
    result = (int)(m_hardware->read(address));
    for (int i = 0; i < 4; i++) {
        if (result != (int)(m_hardware->read(address))) {
            throw ReadFiveTimeFail();
        }
    }
    return result;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    if ((int)(m_hardware->read(address)) != (int)0xFF) throw WriteFail();
    m_hardware->write(address, (unsigned char)data);
}