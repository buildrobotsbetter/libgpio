#include <libgpio/pigpio/Device.hpp>

#include <stdexcept>
#include <fmt/core.h>

namespace _libgpio
{
namespace pigpio
{

// Initialize the static variable
uint64_t Device::m_deviceCount = 0;

Device::Device()
{
    if (m_deviceCount == 0)
    {
        #ifndef USE_PIGPIO_SIGNALHANDLER
        // Disable built-in pigpio signal handling
        // Must be called before gpioInitialise()
        int cfg = gpioCfgGetInternals();
        cfg |= PI_CFG_NOSIGHANDLER;
        gpioCfgSetInternals(cfg);
        #endif

        // Initialize pigpio library
        int result = gpioInitialise();
        if (result == PI_INIT_FAILED)
        {
            throw std::runtime_error(fmt::format("pigpio initialization Failed"));
        }
    }
    m_deviceCount++;
}

Device::~Device()
{
    m_deviceCount--;
    if (m_deviceCount == 0)
    {
        gpioTerminate();
    }
}

} // namespace pigpio
} // namespace _libgpio
