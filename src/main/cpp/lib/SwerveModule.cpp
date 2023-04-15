#include "Lib/SwerveModule.h"

SwerveModule::SwerveModule(SwerveModuleConfig config) : azimuthMotor{config.azimuthID, POSITION_SPARK_MAX_RELATIVE}, driveMotor{config.driveID}, state{0_mps, frc::Rotation2d{units::degree_t{0}}}
{
    PID pid;
    pid.FF = 1.0;

    driveMotor.SetVelocityPID(pid);
}

void SwerveModule::DisabledPeriodic()
{
    azimuthMotor.ZeroRelativeEncoder();
}



void SwerveModule::SetAsimuthPosition(frc::Rotation2d degree)
{
    double currentPositionDegrees = (double)degree.Degrees();
    double angleDegrees = std::fmod(currentPositionDegrees - lastDegree + 540.0, 360.0) - 180.0;
    speedMultiplier *= angleDegrees > 90.0 || angleDegrees < -90.0 ? -1.0 : 1.0;
    angleDegrees += angleDegrees > 90.0 ? -180.0 : angleDegrees < -90.0 ? 180.0 : 0.0;
    
    azimuthMotor.SetPosition(angleDegrees);


    lastDegree = azimuthMotor.absoluteEncoderPosition;
}

void SwerveModule::SetSpeed(units::meters_per_second_t velocity)
{
    driveMotor.SetVelocity((double)velocity * speedMultiplier);
}

void SwerveModule::Periodic()
{
    position.distance = units::meter_t{driveMotor.GetPosition()};
    position.angle = frc::Rotation2d{units::degree_t{azimuthMotor.absoluteEncoderPosition}};
}

frc::SwerveModulePosition SwerveModule::GetPosition()
{
    return position;
}