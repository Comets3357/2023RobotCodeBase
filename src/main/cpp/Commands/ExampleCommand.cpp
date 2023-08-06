#include "Commands/ExampleCommand.h"

ExampleCommand::ExampleCommand(int t) : num{t} {}

void ExampleCommand::Initialize()
{
    frc::SmartDashboard::PutNumber("Test", num);
}

bool ExampleCommand::IsFinished()
{
    return true;
}