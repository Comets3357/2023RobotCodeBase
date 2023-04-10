#pragma once

#include <rev/CANSparkMax.h>

#include "PID.h"

class WheelSparkMax
{
public:

    WheelSparkMax(const int ID) : motor{ID, rev::CANSparkMax::MotorType::kBrushless}, encoder{motor.GetEncoder()}, PIDController{motor.GetPIDController()}
    {
        
    }

    void SetVelocityPID(PID velocityPID)
    {
        pid = velocityPID;
        PIDController.SetP(pid.P, 0);
        PIDController.SetI(pid.I, 0);
        PIDController.SetD(pid.D, 0);
        PIDController.SetFF(pid.FF, 0);
    }

    void SetVelocity(double velocity)
    {
        PIDController.SetReference(velocity, rev::CANSparkMax::ControlType::kVelocity, 0);
    }

    void SetPercent(double power)
    {
        motor.Set(power);
    }

    PID GetPID()
    {
        return pid;
    }

    double GetPosition()
    {
        return encoder.GetPosition();
    }

        rev::CANSparkMax motor;


private:

    rev::SparkMaxRelativeEncoder encoder;
    rev::SparkMaxPIDController PIDController;

    PID pid;

};