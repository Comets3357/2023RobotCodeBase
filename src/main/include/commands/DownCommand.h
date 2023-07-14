#pragma once

#include <frc/controller/ProfiledPIDController.h>
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/controller/ArmFeedforward.h>
#include <frc2/command/ProfiledPIDCommand.h>
#include <units/acceleration.h>
#include <units/length.h>
#include <units/time.h>
#include <units/velocity.h>
#include <units/voltage.h>
#include <units/angle.h>
#include <math.h>
#include <thread>
#include <frc/smartdashboard/SmartDashboard.h>
#include <COMETS3357/Commands/SparkMax/PositionSparkMaxTrapCommand.h>
#include "Subsystems/ArmSubsystem.h"


class DownCommand : public frc2::CommandHelper<frc2::CommandBase, DownCommand>
{

public:

DownCommand(ArmSubsystem* armSubsystem) : arm{armSubsystem}
{

}


void Initialize() override
{
    arm->Elbow.SetPosition(50);
}


ArmSubsystem* arm;

};