#pragma once

#include <rev/CANSparkMax.h>

#include "PID.h"
#include "Lib/ConfigFiles.h"

class WheelSparkMax
{
public:

    WheelSparkMax(std::string configName);

    void RobotInit();
    void SetVelocityPID(PID velocityPID);
    void SetVelocity(double velocity);
    void SetPercent(double power);

    PID GetPID();

    double GetPosition();

        rev::CANSparkMax motor;


private:

    rev::SparkMaxRelativeEncoder encoder;
    rev::SparkMaxPIDController PIDController;

    WheelMotorConfig config;

    PID pid;

};