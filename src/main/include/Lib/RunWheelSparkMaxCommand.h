#pragma once

#include <frc2/command/CommandHelper.h>

#include "WheelSparkMax.h"

class RunWheelSparkMaxCommand : public frc2::CommandHelper<frc2::CommandBase, RunWheelSparkMaxCommand>
{
public:

    RunWheelSparkMaxCommand(frc2::Subsystem* subsystem, double velocity, WheelSparkMax* motor);

    void Initialize() override;

    bool IsFinished() override;

private:

    double motorVelocity = 0;
    WheelSparkMax* wheel;

};