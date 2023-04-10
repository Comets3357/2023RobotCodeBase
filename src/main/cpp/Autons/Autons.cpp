#include "Autons/Autons.h"

Autons::Autons(SwerveSubsystem* drivebase)
{

    LoadPaths();

    autons["TestAuton"].drivebaseCommands.AddCommands
    (
        SwerveTrajectoryCommand{paths["New Path"], drivebase}
    );

    autons["TestAuton"].actionCommands.AddCommands
    (
        
    );
}

void Autons::RunAuton(std::string autonName)
{

}

void Autons::LoadPaths()
{
    for (auto path : pathNames)
    {
        paths[path] = frc::TrajectoryUtil::FromPathweaverJson(frc::filesystem::GetDeployDirectory() + "\\pathPlanner\\generatedJSON\\" + path + ".wpilib.json");
    }
}