#include "COMETS3357/Commands/SparkMax/RunRollerSparkMaxCommand.h"

RunRollerSparkMaxCommand::RunRollerSparkMaxCommand(frc2::Subsystem* subsystem, double power, RollerSparkMax* motor) : motorPower{power}, roller{motor}
{
    AddRequirements(subsystem);
}

void RunRollerSparkMaxCommand::Initialize()
{
    roller->SetPower(motorPower);
}

bool RunRollerSparkMaxCommand::IsFinished()
{
    return true;
}