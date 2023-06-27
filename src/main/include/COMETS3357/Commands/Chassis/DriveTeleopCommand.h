#pragma once

#include <frc2/command/CommandHelper.h>

#include "COMETS3357/Subsystems/Chassis/DrivebaseSubsystem.h"

class DriveTeleopCommand : public frc2::CommandHelper<frc2::CommandBase, DriveTeleopCommand>
{
public:

    DriveTeleopCommand(double leftY, double leftX, DrivebaseSubsystem* drivebase);

    void Execute() override;
    

};