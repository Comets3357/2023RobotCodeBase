#pragma once

#include <rev/CANSparkMax.h>

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

private:

    rev::CANSparkMax motor;

};