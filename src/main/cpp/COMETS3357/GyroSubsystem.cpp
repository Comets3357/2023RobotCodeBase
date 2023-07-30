#include "COMETS3357/GyroSubsystem.h"

using namespace COMETS3357;

GyroSubsystem::GyroSubsystem() : m_navx{frc::SPI::Port::kMXP}
{
    Register("GyroSubsystem");
}

void GyroSubsystem::Periodic()
{
    m_data.angle = -m_navx.GetAngle() * 3.14159 / 180;
    m_data.angleRate = m_navx.GetRate() * 3.14159 / 180;
}