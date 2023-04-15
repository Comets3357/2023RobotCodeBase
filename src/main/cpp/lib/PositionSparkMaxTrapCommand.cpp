#include "Lib/PositionSparkMaxTrapCommand.h"

PositionSparkMaxTrapCommand::PositionSparkMaxTrapCommand(double goal, double acceleration, double velocity, frc2::SubsystemBase* drive, PositionSparkMax* motor)
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
  
  bool PositionSparkMaxTrapCommand::IsFinished() {
    return GetController().AtGoal();
  }