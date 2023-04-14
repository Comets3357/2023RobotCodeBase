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
        RollerMotorConfig config = ConfigFiles::getInstance().robot_config.roller_motor_configs[name];

        if (
            motor.GetInverted() != config.inverted_relative || 
            motor.GetIdleMode() != config.idleMode
        )
        {
            motor.RestoreFactoryDefaults();
            motor.SetInverted(config.inverted_relative);
            motor.SetSmartCurrentLimit(config.current_limit);
            motor.SetIdleMode(config.idleMode);
            motor.BurnFlash();
        }
    }

private:

    rev::CANSparkMax motor;

};