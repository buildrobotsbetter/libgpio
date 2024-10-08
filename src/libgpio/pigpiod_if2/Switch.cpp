#include <libgpio/pigpiod_if2/Switch.hpp>

#include <stdexcept>
#include <fmt/core.h>

namespace _libgpio
{
namespace pigpiod_if2
{

Switch::Switch(uint32_t gpioPin, libgpio::PullDirection pullDirection):
    m_gpioPin(gpioPin),
    m_pullDirection(pullDirection)
{
    configurePull();
    configureMode();
}

void Switch::configurePull()
{
    int result = set_pull_up_down(getGpioHandle(), m_gpioPin, m_pullDirection);
    if (result == 0)
    {
        return;
    }

    switch (result)
    {       
        case PI_BAD_GPIO:
        {
            throw std::runtime_error(fmt::format("{} is a bad gpio pin", m_gpioPin));
        }

        case PI_BAD_MODE:
        {
            throw std::runtime_error(fmt::format("Bad mode specified for gpio pin {}", m_gpioPin));
        }

        default:
        {
            throw std::runtime_error(fmt::format("Unexpected error encountered when setting mode specified for gpio pin {} (Error = {})", m_gpioPin, result));
        }
    }

}

void Switch::configureMode()
{
    auto result = set_mode(getGpioHandle(), m_gpioPin, PI_INPUT);
    if (result == 0)
    {
        return;
    }

    switch (result)
    {       
        case PI_BAD_GPIO:
        {
            throw std::runtime_error(fmt::format("{} is a bad gpio pin", m_gpioPin));
        }

        case PI_BAD_MODE:
        {
            throw std::runtime_error(fmt::format("Bad mode specified for gpio pin {}", m_gpioPin));
        }

        default:
        {
            throw std::runtime_error(fmt::format("Unexpected error encountered when setting mode specified for gpio pin {} (Error = {})", m_gpioPin, result));
        }
    }
}


bool Switch::getInput() const
{
    int result = gpio_read(getGpioHandle(), m_gpioPin);
    if (result < 0)
    {
        throw std::runtime_error(fmt::format("Unexpected error encountered when reading from gpio pin {} (Error = {})", m_gpioPin, result));
    }

    return (result == 1); 
}

} // namespace pigpiod_if2
} // namespace _libgpio
