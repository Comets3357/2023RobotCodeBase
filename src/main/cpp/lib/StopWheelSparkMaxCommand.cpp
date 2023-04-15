#include "Lib/StopWheelSparkMaxCommand.h"

StopWheelSparkMaxCommand::StopWheelSparkMaxCommand(frc2::Subsystem* subsystem, WheelSparkMax* motor) : wheel{motor}
{
    AddRequirements(subsystem);
}


void StopWheelSparkMaxCommand::Initialize()
{
    wheel->SetVelocity(0);
}

bool StopWheelSparkMaxCommand::IsFinished()
{
    return true;
}