#include "COMETS3357/Subsystems/SparkMax/WheelSparkMax.h"
#include <frc/smartdashboard/SmartDashboard.h>

using namespace COMETS3357;

WheelSparkMax::WheelSparkMax(std::string configName) : config{ConfigFiles::getInstance().GetConfigFiles().wheelMotorConfigs[configName]},
motor{config.ID, rev::CANSparkMax::MotorType::kBrushless}, encoder{motor.GetEncoder()}, PIDController{motor.GetPIDController()}
{

}

void WheelSparkMax::RobotInit()
{

    if (
        motor.GetInverted() != config.invertedRelative || 
        motor.GetIdleMode() != config.idleMode || 
        encoder.GetPositionConversionFactor() != config.relativePositionConversionFactor ||
        encoder.GetVelocityConversionFactor() != config.relativeVelocityConversionFactor
    )
    {
        motor.RestoreFactoryDefaults();
        motor.SetInverted(config.invertedRelative);
        motor.SetSmartCurrentLimit(config.currentLimit);
        motor.SetIdleMode(config.idleMode);
        SetVelocityPID(config.velocityPID);
        encoder.SetPositionConversionFactor(config.relativePositionConversionFactor);
        encoder.SetVelocityConversionFactor(config.relativeVelocityConversionFactor);
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

double WheelSparkMax::GetRelativeVelocity()
{
    return encoder.GetVelocity();
}

void WheelSparkMax::SetPercent(double power)
{
    motor.Set(power);
}

PID WheelSparkMax::GetPID()
{
    return pid;
}

double WheelSparkMax::GetRelativePosition()
{
    return encoder.GetPosition();
}


void WheelSparkMax::SetRelativePosition(double position)
{
    encoder.SetPosition(position);
}