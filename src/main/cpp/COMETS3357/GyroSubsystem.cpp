#include "COMETS3357/GyroSubsystem.h"

using namespace COMETS3357;

GyroSubsystem::GyroSubsystem() : m_navx{frc::SPI::Port::kMXP}
{

}

void GyroSubsystem::Periodic()
{
    m_data.angle = m_navx.GetAngle();
    m_data.angleRate = m_navx.GetRate();
}