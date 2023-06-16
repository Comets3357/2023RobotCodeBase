#pragma once

#include <rev/CANSparkMax.h>

#include "PID.h"
#include "Lib/ConfigFiles.h"


class WheelSparkMax
{
public:

    WheelMotorConfig config;

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

    

    PID pid;

};