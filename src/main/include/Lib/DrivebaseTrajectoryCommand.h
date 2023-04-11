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

    DrivebaseTrajectoryCommand(std::string path, DrivebaseSubsystem* drivebaseSubsystem) : drivebase{drivebaseSubsystem}, trajectoryName{path}
    {
        AddRequirements(drivebase);

        
    }

    void Initialize() override
    {
        

        try
        {

            std::string deployDirectory = frc::filesystem::GetDeployDirectory();

            std::string pathDirectory = deployDirectory + "\\" + (trajectoryName + ".wpilib.json");

            frc::SmartDashboard::PutString("pathDirectory", pathDirectory);

            trajectory = frc::TrajectoryUtil::FromPathweaverJson(pathDirectory);
            trajectorySecOffset = units::second_t{drivebase->timerData->timeSinceEnabled};
        }
        catch (...)
        {

        }

        if (!drivebase->odometryInitialized)
        {
            units::second_t zeroSec{0};


            frc::Trajectory::State trajectoryState = trajectory.Sample(zeroSec);
            frc::Pose2d firstPose = trajectoryState.pose;

            double firstX = firstPose.X().to<double>();
            double firstY = firstPose.Y().to<double>();
            
            double firstRadians = firstPose.Rotation().Radians().to<double>();
            // frc::SmartDashboard::PutNumber("firstRadians", firstRadians);

            drivebase->ResetOdometry(firstX, firstY, firstRadians, 0);
            // zeroEncoders();s
            // frc::smartDashboard::PutNumber("autonStep OdoInit", autonData.autonStep);

            drivebase->odometryInitialized = true;
        }

        totalTime = trajectory.TotalTime();
    }

    void Execute() override
    {
        sampleSec = units::second_t{drivebase->timerData->timeSinceEnabled} - trajectorySecOffset;

        frc::Trajectory::State trajectoryState = trajectory.Sample(sampleSec);

        frc::Pose2d desiredPose = trajectoryState.pose;

        double trajX = desiredPose.X().to<double>();
        double trajY = desiredPose.Y().to<double>();

        frc::ChassisSpeeds chassisSpeeds = drivebase->ramseteController.Calculate(drivebase->odometry.GetEstimatedPosition(), trajectoryState);

        frc::DifferentialDriveWheelSpeeds wheelSpeeds = drivebase->kinematics.ToWheelSpeeds(chassisSpeeds);

        double leftWheelSpeed = wheelSpeeds.left.to<double>();
        double rightWheelSpeed = wheelSpeeds.right.to<double>();

        drivebase->SetVelocity(leftWheelSpeed, rightWheelSpeed);

        

    }

    bool IsFinished()
    {
        return (sampleSec > totalTime + units::second_t{100});
    }

private:

    units::second_t sampleSec;
    frc::Trajectory trajectory{};
    units::second_t totalTime;
    DrivebaseSubsystem* drivebase;

    units::second_t trajectorySecOffset{0};
    std::string trajectoryName;
     

};