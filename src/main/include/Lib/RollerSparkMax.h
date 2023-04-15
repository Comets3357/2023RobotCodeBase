#pragma once

#include <rev/CANSparkMax.h>
#include "Lib/ConfigFiles.h"

class RollerSparkMax
{
public:

    RollerSparkMax(const int ID) : motor{ID, rev::CANSparkMax::MotorType::kBrushless}
    {
        
    }

    void SetPower(double power)
    {
        motor.Set(power);
    }

    void SetConfig(std::string name)
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

private:

    rev::CANSparkMax motor;

};