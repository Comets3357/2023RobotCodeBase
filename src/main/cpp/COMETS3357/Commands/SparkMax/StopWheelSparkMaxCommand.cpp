#include "COMETS3357/Commands/SparkMax/StopWheelSparkMaxCommand.h"

using namespace COMETS3357;

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