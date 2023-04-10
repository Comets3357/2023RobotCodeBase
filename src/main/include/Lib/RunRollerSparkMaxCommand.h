#pragma once

#include <frc2/command/CommandHelper.h>

#include "RollerSparkMax.h"


class RunRollerSparkMaxCommand : public frc2::CommandHelper<frc2::CommandBase, RunRollerSparkMaxCommand>
{
public:

    RunRollerSparkMaxCommand(frc2::Subsystem* subsystem, double power, RollerSparkMax* motor) : motorPower{power}, roller{motor}
    {
        AddRequirements(subsystem);
    }

    void Initialize() override
    {
        roller->SetPower(motorPower);
    }

    bool IsFinished() override
    {
        return true;
    }

private:
    
    double motorPower;
    RollerSparkMax* roller;

};