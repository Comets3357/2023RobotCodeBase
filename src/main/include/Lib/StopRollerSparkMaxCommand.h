#pragma once

#include <frc2/command/CommandHelper.h>

#include "RollerSparkMax.h"


class StopRollerSparkMaxCommand : public frc2::CommandHelper<frc2::CommandBase, StopRollerSparkMaxCommand>
{
public:

    StopRollerSparkMaxCommand(frc2::Subsystem* subsystem, RollerSparkMax* motor) : roller{motor}
    {
        AddRequirements(subsystem);
    }

    void Initialize() override
    {
        roller->SetPower(0);
    }

    bool IsFinished() override
    {
        return true;
    }

private:
    
    RollerSparkMax* roller;

};