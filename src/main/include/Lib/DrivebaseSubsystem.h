#pragma once

#include <frc2/command/SubsystemBase.h>
#include "Lib/WheelSparkMax.h"
#include "Lib/PID.h"
#include "TimerSubsystem.h"


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

#define M_PI 3.14159265358979323846

struct DrivebaseData
{

};

class DrivebaseSubsystem : public frc2::SubsystemBase
{
public:

    DrivebaseSubsystem(DrivebaseData* data, TimerData* data2) : drivebaseData{data}, timerData{data2}
    {
        dbFR.motor.Follow(dbR.motor);
        dbFL.motor.Follow(dbL.motor);

        dbR.motor.SetSmartCurrentLimit(60);
        dbL.motor.SetSmartCurrentLimit(60);
        dbFR.motor.SetSmartCurrentLimit(60);
        dbFL.motor.SetSmartCurrentLimit(60);

        dbR.motor.SetInverted(true);
        dbL.motor.SetInverted(false);
        dbFR.motor.SetInverted(true);
        dbFL.motor.SetInverted(false);
        
        pid.FF = 1;
        pid.P = 1;

        SetVelocityPID(pid);

    }

    void SetTicksToMetersConversion(double wheelDiameterInches, double gearRatio)
    {

    }

    void SetTicksToMetersConversion(double conversion)
    {

    }

    void SetVelocityPID(PID pid)
    {
        dbR.SetVelocityPID(pid);
        dbL.SetVelocityPID(pid);
        dbFR.SetVelocityPID(pid);
        dbFL.SetVelocityPID(pid);
    }

    void SetVelocity(double left, double right)
    {
        dbR.SetVelocity(right);
        dbL.SetVelocity(left);
        dbFR.SetVelocity(right);
        dbFL.SetVelocity(left);
    }

    void SetPercent(double left, double right)
    {
        dbR.SetPercent(right);
        dbL.SetPercent(left);
        dbFR.SetPercent(right);
        dbFL.SetPercent(left);
    }

    void ResetOdometry(double x, double y, double radians, double gyroYaw) 
    {
        const units::meter_t meterX{x};
        const units::meter_t meterY{y};

        const units::radian_t radianYaw{radians};
        // frc::SmartDashboard::PutNumber("Pi", pi);
        // frc::SmartDashboard::PutNumber("radian yaw", robotData.gyroData.rawYaw / 180 * pi);

        const units::radian_t gyroRadians{gyroYaw / 180 * M_PI};
        // frc::SmartDashboard::PutNumber("RORaw Yaw", robotData.gyroData.rawYaw);

        const frc::Rotation2d gyroRotation{gyroRadians};
        const frc::Pose2d resetPose{meterX, meterY, radianYaw};
        // zeroEncoders();
        odometry.ResetPosition(gyroRotation, units::meter_t{getEncoderDistance(dbL.GetPosition())}, units::meter_t{getEncoderDistance(dbR.GetPosition())},  resetPose);

        //zeroEncoders();
    }

    double getEncoderDistance(double encoderPosition)
    {
        return encoderPosition*rotationsToMeters;
    }

    void resetOdometry(const frc::Pose2d &pose, double gyroAngle) 
    {
        const units::radian_t gyroRadians{gyroAngle};
        frc::Rotation2d gyroRotation{gyroRadians};

        odometry.ResetPosition(gyroRotation, units::meter_t{getEncoderDistance(dbL.GetPosition())}, units::meter_t{getEncoderDistance(dbR.GetPosition())},  pose);
        //zeroEncoders();
    }

    double rotationsToMeters = 0;

    frc::RamseteController ramseteController{};

    const units::radian_t kZeroAngle{0.0};
    units::meter_t meterX{0};
    units::meter_t meterY{0};
    const frc::Translation2d testTrans{meterX, meterY};
    units::radian_t zeroRadians{0};
    const frc::Rotation2d testRot{zeroRadians};
    const frc::Pose2d kZeroPose{testTrans, testRot};

    const units::meter_t kTrackWidth{0.48};
    frc::DifferentialDriveKinematics kinematics{kTrackWidth};

    frc::DifferentialDrivePoseEstimator odometry{kinematics, testRot, units::meter_t{0.0}, units::meter_t{0.0}, kZeroPose};   

    bool odometryInitialized = false;

    WheelSparkMax dbR{1};
    WheelSparkMax dbL{2};
    WheelSparkMax dbFR{3};
    WheelSparkMax dbFL{4};


    PID pid{};

    TimerData* timerData;
    DrivebaseData* drivebaseData;
};