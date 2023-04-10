#pragma once

#include "Lib/DrivebaseSubsystem.h"
#include <frc2/command/SequentialCommandGroup.h>
#include "Lib/DrivebaseTrajectoryCommand.h"
#include <frc/trajectory/Trajectory.h>
#include <frc/trajectory/TrajectoryUtil.h>
#include "lib/SwerveSubsystem.h"
#include "lib/SwerveTrajectoryCommand.h"

#include <map>
#include <string>
#include <vector>

struct autonCommandGroups
{
    frc2::SequentialCommandGroup drivebaseCommands;
    frc2::SequentialCommandGroup actionCommands;
};

class Autons
{
public:

    Autons(SwerveSubsystem* drivebase);

    void RunAuton(std::string AutonName);
    void LoadPaths();

    //Autons
    std::map<std::string, autonCommandGroups> autons;
    std::map<std::string, frc::Trajectory> paths;
    std::vector<std::string> pathNames = 
    {
        "Path",
        "Path2"
    };

};