#pragma once

#include "Lib/DrivebaseSubsystem.h"
#include <frc2/command/SequentialCommandGroup.h>
#include "Lib/DrivebaseTrajectoryCommand.h"
#include <frc/trajectory/Trajectory.h>
#include <frc/trajectory/TrajectoryUtil.h>
#include "lib/SwerveSubsystem.h"
#include "lib/SwerveTrajectoryCommand.h"
#include <frc2/command/WaitCommand.h>

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
    void LoadPaths();
    void LoadAutons();

    //Autons
    std::map<std::string, autonCommandGroups> autons;
    std::map<std::string, frc::Trajectory> paths;
    std::map<std::string, std::function<void(std::string)>> commands;

    SwerveSubsystem* swerveSubsystem;


    template <typename T>
    void AddAutonAction()
    {
        commands[typeid(T).name()] = [this](std::string pathName) {autons[pathName].actionCommands.AddCommands(T{});};
    }

};