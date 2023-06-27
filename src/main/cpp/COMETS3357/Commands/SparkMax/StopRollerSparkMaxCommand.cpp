#include "COMETS3357/Commands/SparkMax/StopRollerSparkMaxCommand.h"

StopRollerSparkMaxCommand::StopRollerSparkMaxCommand(frc2::Subsystem* subsystem, RollerSparkMax* motor) : roller{motor}
{
    AddRequirements(subsystem);
}

void StopRollerSparkMaxCommand::Initialize()
{
    roller->SetPower(0);
}

bool StopRollerSparkMaxCommand::IsFinished()
{
    return true;
}