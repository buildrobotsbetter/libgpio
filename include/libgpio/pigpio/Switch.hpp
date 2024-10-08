#ifndef LIBGPIO_PIGPIO_SWITCH
#define LIBGPIO_PIGPIO_SWITCH

#include <libgpio/pigpio/Device.hpp>
#include <libgpio/PullDirection.hpp>

namespace _libgpio
{
namespace pigpio
{
    
class Switch : public Device
{
public:
    Switch(uint32_t gpioPin, libgpio::PullDirection pullDirection);
    ~Switch() = default;

    /// @brief Get the input generated by the switch
    /// @param value true = HIGH, false = LOW
    bool getInput() const;

private:
    void configurePull();
    void configureMode();

    uint32_t m_gpioPin;
    libgpio::PullDirection m_pullDirection;
};

} // namespace pigpio
} // namespace _libgpio

#endif // LIBGPIO_PIGPIO_SWITCH
