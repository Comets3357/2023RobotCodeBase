#pragma once

#include <frc2/command/CommandHelper.h>
#include "lib/SwerveSubsystem.h"
#include <string>
#include <frc/trajectory/Trajectory.h>
#include <frc2/command/SwerveControllerCommand.h>
#include <frc/trajectory/TrajectoryUtil.h>
#include <frc/controller/HolonomicDriveController.h>

class SwerveTrajectoryCommand : public frc2::CommandHelper<frc2::CommandBase, SwerveTrajectoryCommand>
{
public:

    SwerveTrajectoryCommand(frc::Trajectory trajectoryName, SwerveSubsystem* subsystem) : swerveSubsystem{subsystem}, trajectory{trajectoryName} {};

    void Initialize() override
    {

      swerveSubsystem->CheckResetOdometry(trajectory);
      trajectorySecOffset = units::second_t{swerveSubsystem->timerData->timeSinceEnabled};
      totalTime = trajectory.TotalTime();
      
    }

    void Execute() override
    {
      sampleSec = units::second_t{swerveSubsystem->timerData->timeSinceEnabled} - trajectorySecOffset;
      frc::Trajectory::State trajectoryState = trajectory.Sample(sampleSec);
      chassisSpeed = controller.Calculate(swerveSubsystem->GetPose(), trajectoryState, swerveSubsystem->GetRotation());
      swerveSubsystem->SetChassisSpeed(chassisSpeed);


      
    }

    bool IsFinished() override
    {
      return sampleSec > totalTime;
    }
    


private:

    units::second_t totalTime;
    units::second_t sampleSec;
    units::second_t trajectorySecOffset;
    frc::Trajectory trajectory;
    SwerveSubsystem* swerveSubsystem;
    frc::ChassisSpeeds chassisSpeed;
    std::unique_ptr<frc2::SwerveControllerCommand<4>> m_swerveControllerCommand;
    frc::HolonomicDriveController controller{
  frc2::PIDController{1, 0, 0}, frc2::PIDController{1, 0, 0},
  frc::ProfiledPIDController<units::radian>{
    1, 0, 0, frc::TrapezoidProfile<units::radian>::Constraints{
      6.28_rad_per_s, 3.14_rad_per_s / 1_s}}};
};