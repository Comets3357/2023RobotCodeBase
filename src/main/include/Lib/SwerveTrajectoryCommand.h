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

    SwerveTrajectoryCommand(frc::Trajectory trajectoryName, SwerveSubsystem* subsystem);

    void Initialize() override;
    void Execute() override;

    bool IsFinished() override;
    


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