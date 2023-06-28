#include "COMETS3357/Subsystems/SparkMax/RollerSparkMax.h"

using namespace COMETS3357;

RollerSparkMax::RollerSparkMax(std::string configName) : config{ConfigFiles::getInstance().GetConfigFiles().rollerMotorConfigs[configName]}, motor{config.ID, rev::CANSparkMax::MotorType::kBrushless}
{
    
}

void RollerSparkMax::SetPower(double power)
{
    motor.Set(power);
}

void RollerSparkMax::RobotInit()
{

    if (
        motor.GetInverted() != config.invertedRelative || 
        motor.GetIdleMode() != config.idleMode
    )
    {
        motor.RestoreFactoryDefaults();
        motor.SetInverted(config.invertedRelative);
        motor.SetSmartCurrentLimit(config.currentLimit);
        motor.SetIdleMode(config.idleMode);
        motor.BurnFlash();
    }
}