#pragma once

#include <rev/CANSparkMax.h>
#include "COMETS3357/Configs/ConfigFiles.h"

namespace COMETS3357
{
    class RollerSparkMax
    {
    public:
        /**
         * @brief Constructs a new RollerSparkMax
         * This is a class that represents a motor that is purely controlled by percent output
         * @param configName This is the name of the config for the motor being created.
        */
        RollerSparkMax(std::string configName);

        /**
         * @brief Sets the percent output of the motor
         * @param power The power ranging from -1 to 1 to set to the motor
        */
        void SetPower(double power);

        COMETS3357::RollerMotorConfig config;
        rev::CANSparkMax motor;

    private:

        /**
         * @brief This is the initialization method for the Motor. This is already called in the constructor
        */
        void RobotInit();
        

    };
};