#pragma once

#include <frc2/command/CommandHelper.h>

#include "WheelSparkMax.h"

class StopWheelSparkMaxCommand : public frc2::CommandHelper<frc2::CommandBase, StopWheelSparkMaxCommand>
{
public:

    StopWheelSparkMaxCommand(frc2::Subsystem* subsystem, WheelSparkMax* motor) : wheel{motor}
    {
        AddRequirements(subsystem);
    }
    

    void Initialize() override
    {
        wheel->SetVelocity(0);
    }

    bool IsFinished() override
    {
        return true;
    }

private:

    WheelSparkMax* wheel;

};