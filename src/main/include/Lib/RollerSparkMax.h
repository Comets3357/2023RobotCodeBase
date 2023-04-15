#pragma once

#include <rev/CANSparkMax.h>
#include "Lib/ConfigFiles.h"

class RollerSparkMax
{
public:

    RollerSparkMax(std::string configName);

    void SetPower(double power);

    void RobotInit();

private:

    rev::CANSparkMax motor;
    RollerMotorConfig config;

};