#pragma once

#include <rev/CanSparkMax.h>
#include "PositionSparkMax.h"
#include "WheelSparkMax.h"

#include <frc/kinematics/SwerveDriveKinematics.h>
#include <frc/kinematics/SwerveDriveOdometry.h>
#include <frc/geometry/Rotation2d.h>
#include <frc/geometry/Translation2d.h>
#include "Lib/SwerveModule.h"

class SwerveModule
{
public:

    SwerveModule(SwerveModuleConfig config);
    void DisabledPeriodic();

    void SetAsimuthPosition(frc::Rotation2d degree);

    void SetSpeed(units::meters_per_second_t velocity);

    void Periodic();
    frc::SwerveModulePosition GetPosition();

    frc::SwerveModuleState state;

private:

    PositionSparkMax azimuthMotor;
    WheelSparkMax driveMotor;

    double lastDegree;
    short speedMultiplier = 1;

    frc::SwerveModulePosition position;



};