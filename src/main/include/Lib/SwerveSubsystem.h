#pragma once

#include <frc2/command/SubsystemBase.h>
#include "SwerveModule.h"
#include <frc/kinematics/SwerveDriveKinematics.h>
#include <frc/kinematics/SwerveDriveOdometry.h>
#include <frc/Trajectory/Trajectory.h>
#include <frc/geometry/Rotation2d.h>
#include <frc/geometry/Translation2d.h>
#include <frc/estimator/SwerveDrivePoseEstimator.h>
#include "lib/TimerSubsystem.h"
#include "Lib/ConfigFiles.h"



//temp
struct GyroData
{
    double yaw;
};

class SwerveSubsystem : public frc2::SubsystemBase
{
public:
    SwerveSubsystem(std::string configFileName, TimerData* timer);

    void SetSpeed(units::meters_per_second_t y, units::meters_per_second_t x, units::radians_per_second_t rotation);

    void CheckResetOdometry(frc::Trajectory trajectory);

    void SetModuleStates(wpi::array<frc::SwerveModuleState, 4> desiredStates);

    void SetChassisSpeed(frc::ChassisSpeeds chassisSpeed);

    void Periodic() override;

    void ResetOdometry(frc::Rotation2d angle, frc::Pose2d pose2D);

    frc::SwerveDriveKinematics<4> GetKinematics();

    frc::Pose2d GetPose();

    frc::Rotation2d GetRotation();

    double GetRobotSpeed();

    double GetRobotStrafe();

    double GetRobotRotation();

    TimerData* timerData;

private:

    //temp
    GyroData gyro{};

    wpi::array<frc::SwerveModuleState, 4> swerveModuleStates{frc::SwerveModuleState{units::meters_per_second_t{0}, frc::Rotation2d{units::degree_t{0}}}, frc::SwerveModuleState{units::meters_per_second_t{0}, frc::Rotation2d{units::degree_t{0}}}, frc::SwerveModuleState{units::meters_per_second_t{0}, frc::Rotation2d{units::degree_t{0}}}, frc::SwerveModuleState{units::meters_per_second_t{0}, frc::Rotation2d{units::degree_t{0}}}};

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

    frc::SwerveDrivePoseEstimator<4> odometry;

    frc::Pose2d pose;

    bool odometryInitialized = false;

    SwerveConfig swerveConfig;

};