#pragma once

#include "Lib/DrivebaseSubsystem.h"
#include <frc2/command/SequentialCommandGroup.h>
#include "Lib/DrivebaseTrajectoryCommand.h"
#include <frc/trajectory/Trajectory.h>
#include <frc/trajectory/TrajectoryUtil.h>
#include "lib/SwerveSubsystem.h"
#include "lib/SwerveTrajectoryCommand.h"
#include <frc2/command/WaitCommand.h>
#include "pathplanner/lib/commands/PPSwerveControllerCommand.h"
#include "pathplanner/lib/auto/SwerveAutoBuilder.h"
#include "pathplanner/lib/PathPlanner.h"
#include <frc2/command/CommandPtr.h>

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

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
    

    //Autons
    std::map<std::string, frc2::CommandPtr> autons;

    std::unordered_map<std::string, std::shared_ptr<frc2::Command>> eventMap;

    SwerveSubsystem* swerveSubsystem;

    void LoadAutons();
    void AddAutonAction(frc2::CommandPtr* command, std::string name);

};