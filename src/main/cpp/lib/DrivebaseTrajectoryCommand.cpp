#include "Lib/DrivebaseTrajectoryCommand.h"


DrivebaseTrajectoryCommand::DrivebaseTrajectoryCommand(std::string path, DrivebaseSubsystem* drivebaseSubsystem) : drivebase{drivebaseSubsystem}, trajectoryName{path}
{
    AddRequirements(drivebase);
}

void DrivebaseTrajectoryCommand::Initialize()
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

void DrivebaseTrajectoryCommand::Execute()
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

bool DrivebaseTrajectoryCommand::IsFinished()
{
    return (sampleSec > totalTime + units::second_t{100});
}