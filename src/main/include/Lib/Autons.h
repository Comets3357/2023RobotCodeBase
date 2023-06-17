#pragma once

#include "Lib/DrivebaseSubsystem.h"
#include <frc/trajectory/Trajectory.h>
#include <frc/trajectory/TrajectoryUtil.h>
#include "lib/SwerveSubsystem.h"
#include <frc2/command/WaitCommand.h>
#include "pathplanner/lib/commands/PPSwerveControllerCommand.h"
#include "pathplanner/lib/auto/SwerveAutoBuilder.h"
#include "pathplanner/lib/PathPlanner.h"


#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>



class Autons
{
public:

     /**
   * Creates a new Autons object that generates and stores each auton located in
   * the auton directory. It is then able to run each auton on command.
   *
   * @param chassis A pointer to the Chassis subsystem that will be performing the auton
   */
    Autons(SwerveSubsystem* chassis);

    /**
   * Runs a selected auton with the auton name
   *
   * @param AutonName The name of the auton file that will be ran
   */
    void RunAuton(std::string AutonName);

    /**
   * Goes through the auton directory and generates Commands for each auton
   */
    void LoadAutons();

     /**
     * Runs a selected auton with the auton name
     *
     * @param command A pointer to the command that will be ran when
     * the keyword is present in the marker located on path planner
     * @param keyword The keyword that cooresponds with the command specified
     */
    void AddAutonAction(frc2::CommandPtr* command, std::string keyword);

private:

    std::map<std::string, std::unique_ptr<frc2::CommandPtr>> autons;
    std::unordered_map<std::string, std::shared_ptr<frc2::Command>> eventMap;
    SwerveSubsystem* swerveSubsystem;

};