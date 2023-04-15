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
    PositionSparkMaxTrapCommand(double goal, double acceleration, double velocity, frc2::SubsystemBase* drive, PositionSparkMax* motor);
  
  bool IsFinished() override;
};