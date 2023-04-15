#include "Lib/SwerveTrajectoryCommand.h"

SwerveTrajectoryCommand::SwerveTrajectoryCommand(frc::Trajectory trajectoryName, SwerveSubsystem* subsystem) : swerveSubsystem{subsystem}, trajectory{trajectoryName} {};

void SwerveTrajectoryCommand::Initialize()
{

    swerveSubsystem->CheckResetOdometry(trajectory);
    trajectorySecOffset = units::second_t{swerveSubsystem->timerData->timeSinceEnabled};
    totalTime = trajectory.TotalTime();

    
}

void SwerveTrajectoryCommand::Execute()
{
    sampleSec = units::second_t{swerveSubsystem->timerData->timeSinceEnabled} - trajectorySecOffset;
    frc::Trajectory::State trajectoryState = trajectory.Sample(sampleSec);
    chassisSpeed = controller.Calculate(swerveSubsystem->GetPose(), trajectoryState, swerveSubsystem->GetRotation());
    swerveSubsystem->SetChassisSpeed(chassisSpeed);


    
}

bool SwerveTrajectoryCommand::IsFinished()
{
    return sampleSec > totalTime;
}