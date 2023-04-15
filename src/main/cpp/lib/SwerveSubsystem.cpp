#include "Lib/SwerveSubsystem.h"

SwerveSubsystem::SwerveSubsystem(SwerveInputData data, TimerData* timer) : timerData{timer}, trackWidth{data.trackWidth}, wheelBase{data.wheelBase},
    frontLeftModule{data.azimuthFLID, data.driveFLID}, frontRightModule{data.azimuthFRID, data.driveFRID}, backRightModule{data.azimuthBRID, data.driveBRID}, backLeftModule{data.azimuthBLID, data.driveBLID},
    frontLeftLocation{-trackWidth/2, -wheelBase/2},
    frontRightLocation{trackWidth/2, -wheelBase/2},
    backRightLocation{trackWidth/2, wheelBase/2},
    backLeftLocation{-trackWidth/2, wheelBase/2},
    kinematics{frontLeftLocation, frontRightLocation, backLeftLocation, backRightLocation},
    speeds{data.xSpeed, data.ySpeed, data.maxTurnSpeed},
    odometry{kinematics, frc::Rotation2d{0_deg}, {frc::SwerveModulePosition{0_m, 0_deg}, frc::SwerveModulePosition{0_m, 0_deg}, frc::SwerveModulePosition{0_m, 0_deg}, frc::SwerveModulePosition{0_m, 0_deg}}, frc::Pose2d{0_m, 0_m, 0_rad}},
    swerveModuleStates{frc::SwerveModuleState{}, frc::SwerveModuleState{}, frc::SwerveModuleState{}, frc::SwerveModuleState{}}
    {}

void SwerveSubsystem::SetSpeed(units::meters_per_second_t y, units::meters_per_second_t x, units::radians_per_second_t rotation)
{
    speeds = frc::ChassisSpeeds::FromFieldRelativeSpeeds(x, y, rotation, frc::Rotation2d(units::degree_t{gyro.yaw}));
    SetChassisSpeed(speeds);
}

void SwerveSubsystem::CheckResetOdometry(frc::Trajectory trajectory)
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

void SwerveSubsystem::SetModuleStates(wpi::array<frc::SwerveModuleState, 4> desiredStates) {

    swerveModuleStates[0] = frc::SwerveModuleState::Optimize(desiredStates[0], frontLeftModule.GetPosition().angle);
    swerveModuleStates[1] = frc::SwerveModuleState::Optimize(desiredStates[1], frontRightModule.GetPosition().angle);
    swerveModuleStates[2] = frc::SwerveModuleState::Optimize(desiredStates[2], backLeftModule.GetPosition().angle);
    swerveModuleStates[3] = frc::SwerveModuleState::Optimize(desiredStates[3], backRightModule.GetPosition().angle);

    frontLeftModule.SetAsimuthPosition(swerveModuleStates[0].angle);
    frontLeftModule.SetSpeed(swerveModuleStates[0].speed);

    frontRightModule.SetAsimuthPosition(swerveModuleStates[1].angle);
    frontRightModule.SetSpeed(swerveModuleStates[1].speed);

    backLeftModule.SetAsimuthPosition(swerveModuleStates[2].angle);
    backLeftModule.SetSpeed(swerveModuleStates[2].speed);

    backRightModule.SetAsimuthPosition(swerveModuleStates[3].angle);
    backRightModule.SetSpeed(swerveModuleStates[3].speed);


}

void SwerveSubsystem::SetChassisSpeed(frc::ChassisSpeeds chassisSpeed)
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

    frc::SmartDashboard::PutNumber("Degree", (double)swerveModuleStates[3].angle.Degrees());
    frc::SmartDashboard::PutNumber("Vel", (double)swerveModuleStates[3].speed);

}

void SwerveSubsystem::Periodic()
{
    odometry.Update(frc::Rotation2d{units::degree_t{gyro.yaw}}, {frontLeftModule.GetPosition(), frontRightModule.GetPosition(), backLeftModule.GetPosition(), backRightModule.GetPosition()});
}

void SwerveSubsystem::ResetOdometry(frc::Rotation2d angle, frc::Pose2d pose2D)
{
    odometry.ResetPosition(angle, {frontLeftModule.GetPosition(), frontRightModule.GetPosition(), backLeftModule.GetPosition(), backRightModule.GetPosition()}, pose2D);
}

frc::SwerveDriveKinematics<4> SwerveSubsystem::GetKinematics()
{

    return kinematics;
}

frc::Pose2d SwerveSubsystem::GetPose()
{
    return odometry.GetEstimatedPosition();
}

frc::Rotation2d SwerveSubsystem::GetRotation()
{
    return frc::Rotation2d{units::degree_t{gyro.yaw}};
}

double SwerveSubsystem::GetRobotSpeed()
{
    return 0.0;
}

double SwerveSubsystem::GetRobotStrafe()
{
    return 0.0;
}

double SwerveSubsystem::GetRobotRotation()
{
    return 0.0;
}