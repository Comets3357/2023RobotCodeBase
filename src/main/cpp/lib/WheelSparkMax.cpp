#include "Lib/WheelSparkMax.h"

WheelSparkMax::WheelSparkMax(const int ID) : motor{ID, rev::CANSparkMax::MotorType::kBrushless}, encoder{motor.GetEncoder()}, PIDController{motor.GetPIDController()}
{
    
}

void WheelSparkMax::SetConfig(std::string name)
{
    WheelMotorConfig config = ConfigFiles::getInstance().robot_config.wheelMotorConfigs[name];

    if (
        motor.GetInverted() != config.invertedRelative || 
        motor.GetIdleMode() != config.idleMode || 
        encoder.GetPositionConversionFactor() != config.relativeConversionFactor
    )
    {
        motor.RestoreFactoryDefaults();
        motor.SetInverted(config.invertedRelative);
        motor.SetSmartCurrentLimit(config.currentLimit);
        motor.SetIdleMode(config.idleMode);
        SetVelocityPID(config.velocityPID);
        encoder.SetPositionConversionFactor(config.relativeConversionFactor);
        motor.BurnFlash();
    }
}

void WheelSparkMax::SetVelocityPID(PID velocityPID)
{
    pid = velocityPID;
    PIDController.SetP(pid.P, 0);
    PIDController.SetI(pid.I, 0);
    PIDController.SetD(pid.D, 0);
    PIDController.SetFF(pid.FF, 0);
}

void WheelSparkMax::SetVelocity(double velocity)
{
    PIDController.SetReference(velocity, rev::CANSparkMax::ControlType::kVelocity, 0);
}

void WheelSparkMax::SetPercent(double power)
{
    motor.Set(power);
}

PID WheelSparkMax::GetPID()
{
    return pid;
}

double WheelSparkMax::GetPosition()
{
    return encoder.GetPosition();
}