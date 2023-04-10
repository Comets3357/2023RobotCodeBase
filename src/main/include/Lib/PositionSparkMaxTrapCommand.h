#pragma once

#include <frc2/command/ProfiledPIDCommand.h>
#include <frc2/command/SubsystemBase.h>
#include <frc/controller/ProfiledPIDController.h>
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc2/command/CommandHelper.h>
#include <units/length.h>

#include "PositionSparkMax.h"

class PositionSparkMaxTrapCommand : public frc2::CommandHelper<frc2::ProfiledPIDCommand<units::degrees>,PositionSparkMaxTrapCommand> {
    public:
    PositionSparkMaxTrapCommand(double goal, double acceleration, double velocity, frc2::SubsystemBase* drive, PositionSparkMax* motor)
      : CommandHelper{
      frc::ProfiledPIDController<units::degrees>{
      motor->positionPID.P, motor->positionPID.I, motor->positionPID.D, {units::degrees_per_second_t{velocity}, units::degree_t{acceleration}/(1_s * 1_s)}},
      [motor] { return units::degree_t{motor->GetPosition()}; },
      units::degree_t{goal},
      [motor](double output, frc::TrapezoidProfile<units::degrees>::State state) {motor->SetVelocity(output); },
      {drive}} 
  {
    AddRequirements(drive);
  }
  
  bool IsFinished() override {
    return GetController().AtGoal();
  }
};