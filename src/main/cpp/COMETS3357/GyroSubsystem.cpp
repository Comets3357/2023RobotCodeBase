#include "COMETS3357/GyroSubsystem.h"


GyroSubsystem::GyroSubsystem(GyroData& data) : gyroData{data}, m_navx{frc::SPI::Port::kMXP}
{

}

void GyroSubsystem::Periodic()
{
    gyroData.angle = m_navx.GetAngle();
    gyroData.angleRate = m_navx.GetRate();
}