#pragma once

#include <rev/CanSparkMax.h>
#include "PositionSparkMax.h"
#include "WheelSparkMax.h"

#include <frc/kinematics/SwerveDriveKinematics.h>
#include <frc/kinematics/SwerveDriveOdometry.h>
#include <frc/geometry/Rotation2d.h>
#include <frc/geometry/Translation2d.h>

class SwerveModule
{
public:

    SwerveModule(const int AzimuthID, const int DriveID) : azimuthMotor{AzimuthID, POSITION_SPARK_MAX_RELATIVE}, driveMotor{DriveID}, state{0_mps, frc::Rotation2d{units::degree_t{0}}}
    {
        PID pid;
        pid.FF = 1.0;

        driveMotor.SetVelocityPID(pid);
    }

    void DisabledPeriodic()
    {
        azimuthMotor.ZeroRelativeEncoder();
    }



    void SetAsimuthPosition(frc::Rotation2d degree)
    {
        double currentPositionDegrees = (double)degree.Degrees();
        double angleDegrees = std::fmod(currentPositionDegrees - lastDegree + 540.0, 360.0) - 180.0;
        speedMultiplier *= angleDegrees > 90.0 || angleDegrees < -90.0 ? -1.0 : 1.0;
        angleDegrees += angleDegrees > 90.0 ? -180.0 : angleDegrees < -90.0 ? 180.0 : 0.0;
        
        azimuthMotor.SetPosition(angleDegrees);


        lastDegree = azimuthMotor.absoluteEncoderPosition;
    }

    void SetSpeed(units::meters_per_second_t velocity)
    {
        driveMotor.SetVelocity((double)velocity * speedMultiplier);
        
    }

    void Periodic()
    {
        position.distance = units::meter_t{driveMotor.GetPosition()};
        position.angle = frc::Rotation2d{units::degree_t{azimuthMotor.absoluteEncoderPosition}};
    }

    frc::SwerveModulePosition GetPosition()
    {
        return position;
    }

    frc::SwerveModuleState state;

private:

    PositionSparkMax azimuthMotor;
    WheelSparkMax driveMotor;

    double lastDegree;
    short speedMultiplier = 1;

    frc::SwerveModulePosition position;



};