#pragma once

#include <frc2/command/CommandHelper.h>

#include "WheelSparkMax.h"

class StopWheelSparkMaxCommand : public frc2::CommandHelper<frc2::CommandBase, StopWheelSparkMaxCommand>
{
public:

    StopWheelSparkMaxCommand(frc2::Subsystem* subsystem, WheelSparkMax* motor);

    void Initialize() override;

    bool IsFinished() override;

private:

    WheelSparkMax* wheel;

};