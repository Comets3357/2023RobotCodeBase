#pragma once

#include <frc2/command/CommandHelper.h>

#include "COMETS3357/Subsystems/SparkMax/RollerSparkMax.h"


class RunRollerSparkMaxCommand : public frc2::CommandHelper<frc2::CommandBase, RunRollerSparkMaxCommand>
{
public:

    RunRollerSparkMaxCommand(frc2::Subsystem* subsystem, double power, RollerSparkMax* motor);

    void Initialize() override;

    bool IsFinished() override;

private:
    
    double motorPower;
    RollerSparkMax* roller;

};