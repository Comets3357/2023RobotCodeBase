#include "Lib/Autons.h"
#include "Lib/ControllerMap.h"

Autons::Autons(SwerveSubsystem* drivebase, std::unordered_map<std::string, std::shared_ptr<frc2::Command>> &actionMap) : swerveSubsystem{drivebase}, autoBuilder(
        [this]() {return swerveSubsystem->GetPose();},
        [this](auto initPose) {swerveSubsystem->ResetOdometry(initPose);},
        pathplanner::PIDConstants(5.0, 0.0, 0.0),
        pathplanner::PIDConstants(0.5, 0.0, 0.0),
        [this](auto speeds) {swerveSubsystem->SetChassisSpeed(speeds);},
        actionMap,
        {swerveSubsystem},
        false
    )
{
    LoadAutons();
}

void Autons::RunAuton(std::string autonName)
{
    if (autons.contains(autonName))
    autons[autonName]->Schedule();
}

void Autons::AutonomousInit()
{
    RunAuton(autoChooser.GetSelected());
}

void Autons::LoadAutons()
{

    std::string const filePath = frc::filesystem::GetDeployDirectory() + "/pathplanner/";
    
    for (const auto& entry : std::filesystem::directory_iterator(filePath))
    {
        if (entry.is_regular_file())
        {
            std::string autonName = entry.path().stem().string();
            autoChooser.AddOption(autonName, autonName);
            std::vector<pathplanner::PathPlannerTrajectory> pathGroup = pathplanner::PathPlanner::loadPathGroup(autonName, {pathplanner::PathConstraints{4_mps, 3_mps_sq}});

            autons[autonName] = std::make_unique<frc2::CommandPtr>(autoBuilder.fullAuto(pathGroup));
        }
    }

    frc::SmartDashboard::PutData("Autonomous Mode", &autoChooser);

}

