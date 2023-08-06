#include "COMETS3357/GyroSubsystem.h"

using namespace COMETS3357;

GyroSubsystem::GyroSubsystem() : COMETS3357::Subsystem<GyroState>("GyroSubsystem") , m_navx{frc::SPI::Port::kMXP}
{
    
}

void GyroSubsystem::Periodic()
{
    subsystemData->GetEntry("angle").SetDouble(-m_navx.GetAngle() * 3.14159 / 180);
    subsystemData->GetEntry("angleRate").SetDouble(m_navx.GetRate() * 3.14159 / 180);

}