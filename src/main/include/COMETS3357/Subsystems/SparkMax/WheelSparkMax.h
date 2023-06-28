#pragma once

#include <rev/CANSparkMax.h>

#include "COMETS3357/PID.h"
#include "COMETS3357/Configs/ConfigFiles.h"

namespace COMETS3357
{
    class WheelSparkMax
    {
    public:

        COMETS3357::WheelMotorConfig config;

        WheelSparkMax(std::string configName);

        void RobotInit();
        void SetVelocityPID(PID velocityPID);
        void SetVelocity(double velocity);
        double GetRelativeVelocity();
        void SetPercent(double power);

        PID GetPID();

        double GetRelativePosition();
        void SetRelativePosition(double position);

        rev::CANSparkMax motor;


    private:

        rev::SparkMaxRelativeEncoder encoder;
        rev::SparkMaxPIDController PIDController;

        

        COMETS3357::PID pid;

    };
};