#include "Lib/RunWheelSparkMaxCommand.h"


RunWheelSparkMaxCommand::RunWheelSparkMaxCommand(frc2::Subsystem* subsystem, double velocity, WheelSparkMax* motor) : motorVelocity{velocity}, wheel{motor}
{
    AddRequirements(subsystem);
}

void RunWheelSparkMaxCommand::Initialize()
{
    wheel->SetVelocity(motorVelocity);
}

bool RunWheelSparkMaxCommand::IsFinished()
{
    return true;
}