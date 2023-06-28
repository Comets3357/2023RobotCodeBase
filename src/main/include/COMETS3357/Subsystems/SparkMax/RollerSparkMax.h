#pragma once

#include <rev/CANSparkMax.h>
#include "COMETS3357/Configs/ConfigFiles.h"

namespace COMETS3357
{
    class RollerSparkMax
    {
    public:

        RollerSparkMax(std::string configName);

        COMETS3357::RollerMotorConfig config;

        void SetPower(double power);

        void RobotInit();

    private:

        rev::CANSparkMax motor;
        

    };
};