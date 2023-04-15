#pragma once

#include <frc2/command/CommandHelper.h>

#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include <frc/DriverStation.h>
#include <frc/TimedRobot.h>
#include <rev/CANSparkMax.h>
// #include <wpi/uv/Error.h>
#include <frc/geometry/Rotation2d.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
// #include <frc/kinematics/DifferentialDrivePoseEstimator.h>
#include <frc/estimator/DifferentialDrivePoseEstimator.h>
#include <frc/kinematics/DifferentialDriveWheelSpeeds.h>
#include <frc/trajectory/Trajectory.h>
#include <frc/controller/RamseteController.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/smartdashboard/Field2d.h>
#include <frc/trajectory/TrajectoryUtil.h>
#include <frc/filesystem.h>
#include <cmath>
#include <algorithm>
#include <string>
#include <fstream>
#include <deque>

#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/controller/ArmFeedforward.h>
#include <frc2/command/ProfiledPIDSubsystem.h>
#include <units/acceleration.h>
#include <units/length.h>
#include <units/time.h>
#include <units/velocity.h>
#include <units/voltage.h>
#include <units/angle.h>
#include <math.h>

#include "Lib/DrivebaseSubsystem.h"


class DrivebaseTrajectoryCommand : public frc2::CommandHelper<frc2::CommandBase, DrivebaseTrajectoryCommand>
{
public:

    DrivebaseTrajectoryCommand(std::string path, DrivebaseSubsystem* drivebaseSubsystem);
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;

private:

    units::second_t sampleSec;
    frc::Trajectory trajectory{};
    units::second_t totalTime;
    DrivebaseSubsystem* drivebase;

    units::second_t trajectorySecOffset{0};
    std::string trajectoryName;
     

};