#include "COMETS3357/Commands/Chassis/DriveTeleopCommand.h"

using namespace COMETS3357;

DriveTeleopCommand::DriveTeleopCommand(double leftY, double leftX, DrivebaseSubsystem* drivebase)
{
    AddRequirements(drivebase);
}


void DriveTeleopCommand::Execute()
{
    
}