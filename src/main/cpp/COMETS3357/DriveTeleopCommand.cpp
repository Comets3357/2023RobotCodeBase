#include "COMETS3357/Commands/Chassis/DriveTeleopCommand.h"

DriveTeleopCommand::DriveTeleopCommand(double leftY, double leftX, DrivebaseSubsystem* drivebase)
{
    AddRequirements(drivebase);
}


void DriveTeleopCommand::Execute()
{
    
}