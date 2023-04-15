#include "Lib/RollerSparkMax.h"

RollerSparkMax::RollerSparkMax(std::string configName) : config{ConfigFiles::getInstance().robotConfig.rollerMotorConfigs[configName]}, motor{config.ID, rev::CANSparkMax::MotorType::kBrushless}
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