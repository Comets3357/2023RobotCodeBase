#include "Lib/RollerSparkMax.h"

RollerSparkMax::RollerSparkMax(const int ID) : motor{ID, rev::CANSparkMax::MotorType::kBrushless}
{
    
}

void RollerSparkMax::SetPower(double power)
{
    motor.Set(power);
}

void RollerSparkMax::SetConfig(std::string name)
{
    RollerMotorConfig config = ConfigFiles::getInstance().robot_config.rollerMotorConfigs[name];

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