#pragma once

#include <frc2/command/SubsystemBase.h>
#include "SwerveModule.h"
#include <frc/kinematics/SwerveDriveKinematics.h>
#include <frc/kinematics/SwerveDriveOdometry.h>
#include <frc/geometry/Rotation2d.h>
#include <frc/geometry/Translation2d.h>
#include "lib/TimerSubsystem.h"

struct SwerveInputData
{
    int azimuthFLID = 1;
    int azimuthFRID = 2;
    int azimuthBLID = 3;
    int azimuthBRID = 4;
    int driveFLID = 5;
    int driveFRID = 6;
    int driveBLID = 7;
    int driveBRID = 8;
    units::meter_t trackWidth{10};
    units::meter_t wheelBase{10};
    units::meters_per_second_t minSpeed{5};
    units::meters_per_second_t maxSpeed{5};
    units::radians_per_second_t maxTurnSpeed{1};
};

//temp
struct GyroData
{
    double yaw;
};

class SwerveSubsystem : public frc2::SubsystemBase
{
public:
    SwerveSubsystem(SwerveInputData data, TimerData* timer) : timerData{timer}, trackWidth{data.trackWidth}, wheelBase{data.wheelBase},
     frontLeftModule{data.azimuthFLID, data.driveFLID}, frontRightModule{data.azimuthFRID, data.driveFRID}, backRightModule{data.azimuthBRID, data.driveBRID}, backLeftModule{data.azimuthBLID, data.driveBLID},
     frontLeftLocation{-trackWidth/2, -wheelBase/2},
     frontRightLocation{trackWidth/2, -wheelBase/2},
     backRightLocation{trackWidth/2, wheelBase/2},
     backLeftLocation{-trackWidth/2, wheelBase/2},
     kinematics{frontLeftLocation, frontRightLocation, backLeftLocation, backRightLocation},
     speeds{data.minSpeed, data.maxSpeed, data.maxTurnSpeed},
     odometry{kinematics, frc::Rotation2d{0_deg}, {frc::SwerveModulePosition{0_m, 0_deg}, frc::SwerveModulePosition{0_m, 0_deg}, frc::SwerveModulePosition{0_m, 0_deg}, frc::SwerveModulePosition{0_m, 0_deg}}, frc::Pose2d{0_m, 0_m, 0_rad}},
     swerveModuleStates{frc::SwerveModuleState{}, frc::SwerveModuleState{}, frc::SwerveModuleState{}, frc::SwerveModuleState{}}
      {}

    void SetSpeed(units::meters_per_second_t y, units::meters_per_second_t x, units::radians_per_second_t rotation)
    {
        speeds = frc::ChassisSpeeds::FromFieldRelativeSpeeds(x, y, rotation, frc::Rotation2d(units::degree_t{gyro.yaw}));
        //SetChassisSpeed(speeds);
    }

    void CheckResetOdometry(frc::Trajectory trajectory)
    {
         if (!odometryInitialized)
        {
            units::second_t zeroSec{0};

 
            frc::Trajectory::State trajectoryState = trajectory.Sample(zeroSec);
            frc::Pose2d firstPose = trajectoryState.pose;

            double firstX = firstPose.X().to<double>();
            double firstY = firstPose.Y().to<double>();
            
            frc::Rotation2d firstRadians = firstPose.Rotation().Radians();
            // frc::SmartDashboard::PutNumber("firstRadians", firstRadians);

            ResetOdometry(firstRadians, firstPose);
            // zeroEncoders();s
            // frc::smartDashboard::PutNumber("autonStep OdoInit", autonData.autonStep);

            odometryInitialized = true;
        }
        
    }

    void SetModuleStates(wpi::array<frc::SwerveModuleState, 4> desiredStates) {
    
        swerveModuleStates[0].Optimize(desiredStates[0], frontLeftModule.GetPosition().angle);
        swerveModuleStates[1].Optimize(desiredStates[1], frontRightModule.GetPosition().angle);
        swerveModuleStates[2].Optimize(desiredStates[2], backLeftModule.GetPosition().angle);
        swerveModuleStates[3].Optimize(desiredStates[3], backRightModule.GetPosition().angle);

        frontLeftModule.SetAsimuthPosition(swerveModuleStates[0].angle);
        frontLeftModule.SetSpeed(swerveModuleStates[0].speed);

        frontRightModule.SetAsimuthPosition(swerveModuleStates[1].angle);
        frontRightModule.SetSpeed(swerveModuleStates[1].speed);

        backLeftModule.SetAsimuthPosition(swerveModuleStates[2].angle);
        backLeftModule.SetSpeed(swerveModuleStates[2].speed);

        backRightModule.SetAsimuthPosition(swerveModuleStates[3].angle);
        backRightModule.SetSpeed(swerveModuleStates[3].speed);


    }

    void SetChassisSpeed(frc::ChassisSpeeds chassisSpeed)
    {
        auto [fl, fr, bl, br] = kinematics.ToSwerveModuleStates(chassisSpeed);

        swerveModuleStates[0] = frc::SwerveModuleState::Optimize(fl, frontLeftModule.GetPosition().angle);
        swerveModuleStates[1] = frc::SwerveModuleState::Optimize(fr, frontRightModule.GetPosition().angle);
        swerveModuleStates[2] = frc::SwerveModuleState::Optimize(bl, backLeftModule.GetPosition().angle);
        swerveModuleStates[3] = frc::SwerveModuleState::Optimize(br, backRightModule.GetPosition().angle);

        frontLeftModule.SetAsimuthPosition(swerveModuleStates[0].angle);
        frontLeftModule.SetSpeed(swerveModuleStates[0].speed);

        frontRightModule.SetAsimuthPosition(swerveModuleStates[1].angle);
        frontRightModule.SetSpeed(swerveModuleStates[1].speed);

        backLeftModule.SetAsimuthPosition(swerveModuleStates[2].angle);
        backLeftModule.SetSpeed(swerveModuleStates[2].speed);

        backRightModule.SetAsimuthPosition(swerveModuleStates[3].angle);
        backRightModule.SetSpeed(swerveModuleStates[3].speed);

    }

    void Periodic() override
    {
        odometry.Update(frc::Rotation2d{units::degree_t{gyro.yaw}}, {frontLeftModule.GetPosition(), frontRightModule.GetPosition(), backLeftModule.GetPosition(), backRightModule.GetPosition()});
    }

    void ResetOdometry(frc::Rotation2d angle, frc::Pose2d pose2D)
    {
        odometry.ResetPosition(angle, {frontLeftModule.GetPosition(), frontRightModule.GetPosition(), backLeftModule.GetPosition(), backRightModule.GetPosition()}, pose2D);
    }

    frc::SwerveDriveKinematics<4> GetKinematics()
    {

        return kinematics;
    }

    frc::Pose2d GetPose()
    {
        return odometry.GetPose();
    }

    frc::Rotation2d GetRotation()
    {
        return frc::Rotation2d{units::degree_t{gyro.yaw}};
    }

    double GetRobotSpeed()
    {

    }

    double GetRobotStrafe()
    {

    }

    double GetRobotRotation()
    {

    }

    TimerData* timerData;

private:

    //temp
    GyroData gyro{};

    wpi::array<frc::SwerveModuleState, 4> swerveModuleStates{frc::SwerveModuleState{units::meters_per_second_t{0}, frc::Rotation2d{units::degree_t{0}}}, frc::SwerveModuleState{units::meters_per_second_t{0}, frc::Rotation2d{units::degree_t{0}}}, frc::SwerveModuleState{units::meters_per_second_t{0}, frc::Rotation2d{units::degree_t{0}}}, frc::SwerveModuleState{units::meters_per_second_t{0}, frc::Rotation2d{units::degree_t{0}}}};;

    units::meter_t trackWidth, wheelBase;
    frc::Translation2d frontLeftLocation;
    frc::Translation2d frontRightLocation;
    frc::Translation2d backLeftLocation;
    frc::Translation2d backRightLocation;

    frc::SwerveDriveKinematics<4> kinematics;
    frc::ChassisSpeeds speeds;

    SwerveModule frontLeftModule;
    SwerveModule frontRightModule;
    SwerveModule backLeftModule;
    SwerveModule backRightModule;

    frc::SwerveDriveOdometry<4> odometry;

    frc::Pose2d pose;

    bool odometryInitialized = false;

};