#include "Lib/Autons.h"

Autons::Autons(SwerveSubsystem* drivebase)
{
    swerveSubsystem = drivebase;
    
    LoadPaths();
    LoadAutons();
}

void Autons::RunAuton(std::string autonName)
{

}

void Autons::LoadPaths()
{
    std::filesystem::path directory_path = frc::filesystem::GetDeployDirectory() + "\\pathPlanner\\generatedJSON";

    for (const auto& entry : std::filesystem::directory_iterator(directory_path))
    {
        if (entry.is_regular_file())
        {
            paths[entry.path().stem().string()] = frc::TrajectoryUtil::FromPathweaverJson(entry.path().string());
        }
    }
}

void Autons::LoadAutons()
{
    std::filesystem::path primaryControlPath = frc::filesystem::GetDeployDirectory() + "\\Autons\\PrimaryControl";
    std::filesystem::path secondaryControlPath = frc::filesystem::GetDeployDirectory() + "\\Autons\\SecondaryControl";

    for (const auto& entry : std::filesystem::directory_iterator(primaryControlPath))
    {
        if (entry.is_regular_file())
        {
            std::ifstream file(entry.path().filename().string());

            if (file.is_open())
            {
                std::string line;

                while (std::getline(file, line))
                {
                    if (line.find("break"))
                    {
                        double breakTime = std::stod(line.substr(6));
                        autons[entry.path().stem().string()].drivebaseCommands.AddCommands(frc2::WaitCommand(units::second_t{breakTime}));
                    }
                    else
                    {
                        if (paths.contains(line))
                        {
                            autons[entry.path().stem().string()].drivebaseCommands.AddCommands(SwerveTrajectoryCommand(paths[line], swerveSubsystem));

                            // pathplanner::PPSwerveControllerCommand path{
                            //     pathplanner::PathPlannerTrajectory{},
                            //     [this]() {return swerveSubsystem->GetPose();},
                            //     frc::PIDController{0.0, 0.0, 0.0},
                            //     frc::PIDController{0.0, 0.0, 0.0},
                            //     frc::PIDController{0.0, 0.0, 0.0},
                            //     [this](frc::ChassisSpeeds speeds) {swerveSubsystem->SetChassisSpeed(speeds);}
                            // };
                        }
                    }
                }
            }
        }
    }

    for (const auto& entry : std::filesystem::directory_iterator(secondaryControlPath))
    {
        if (entry.is_regular_file())
        {
            std::ifstream file(entry.path().filename().string());

            if (file.is_open())
            {
                std::string line;

                while (std::getline(file, line))
                {
                    if (line.find("break"))
                    {
                        double breakTime = std::stod(line.substr(6));
                        autons[entry.path().stem().string()].actionCommands.AddCommands(frc2::WaitCommand(units::second_t(breakTime)));
                    }
                    else
                    {
                        if (commands.contains(line))
                        {
                            commands[line](entry.path().stem().string());
                        }
                    }
                }
            }
        }
    }
}




