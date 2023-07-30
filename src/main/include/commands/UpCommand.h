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

#include "Subsystems/ArmSubsystem.h"

#include "Robot.h"
class UpCommand : public frc2::CommandHelper<frc2::CommandBase, UpCommand>
{

public:

UpCommand(ArmSubsystem* armSubsystem) : arm{armSubsystem}
{
    
}


void Initialize() override
{
}

ArmSubsystem* arm;


};