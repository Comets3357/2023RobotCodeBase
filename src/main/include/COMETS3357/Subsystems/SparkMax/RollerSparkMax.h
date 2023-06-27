#pragma once

#include <rev/CANSparkMax.h>
#include "COMETS3357/Configs/ConfigFiles.h"

class RollerSparkMax
{
public:

    RollerSparkMax(std::string configName);

    RollerMotorConfig config;

    void SetPower(double power);

    void RobotInit();

private:

    rev::CANSparkMax motor;
    

};