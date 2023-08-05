#include "Subsystems/ElevatorSubsystem.h"
#include <frc/smartdashboard/SmartDashboard.h>
void ElevatorSubsystem::SetOutput(double leftX, double leftY, double rightX, double rightY)
{
frc::SmartDashboard::PutNumber("LeftX", leftX);
frc::SmartDashboard::PutNumber("LeftY", leftY);
frc::SmartDashboard::PutNumber("RightX", rightX);
frc::SmartDashboard::PutNumber("RightY", rightY);

}