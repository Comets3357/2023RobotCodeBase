#include "COMETS3357/Commands/SparkMax/RunWheelSparkMaxCommand.h"

using namespace COMETS3357;

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