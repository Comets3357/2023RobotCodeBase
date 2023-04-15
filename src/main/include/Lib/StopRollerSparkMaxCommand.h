#pragma once

#include <frc2/command/CommandHelper.h>

#include "RollerSparkMax.h"


class StopRollerSparkMaxCommand : public frc2::CommandHelper<frc2::CommandBase, StopRollerSparkMaxCommand>
{
public:

    StopRollerSparkMaxCommand(frc2::Subsystem* subsystem, RollerSparkMax* motor);

    void Initialize() override;

    bool IsFinished() override;

private:
    
    RollerSparkMax* roller;

};