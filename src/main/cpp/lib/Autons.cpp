#include "Lib/Autons.h"

Autons::Autons(SwerveSubsystem* drivebase)
{
    swerveSubsystem = drivebase;

}

void Autons::RunAuton(std::string autonName)
{
    if (autons.contains(autonName))
    autons[autonName]->Schedule();
}


void Autons::LoadAutons()
{
    std::vector<pathplanner::PathPlannerTrajectory> pathGroup = pathplanner::PathPlanner::loadPathGroup("FullAuto", {pathplanner::PathConstraints{4_mps, 3_mps_sq}});

    pathplanner::SwerveAutoBuilder autoBuilder(
        [this]() {return swerveSubsystem->GetPose();},
        [this](auto initPose) {swerveSubsystem->ResetOdometry(initPose);},
        pathplanner::PIDConstants(5.0, 0.0, 0.0),
        pathplanner::PIDConstants(0.5, 0.0, 0.0),
        [this](auto speeds) {swerveSubsystem->SetChassisSpeed(speeds);},
        eventMap,
        {swerveSubsystem},
        false
    );


    std::string const filePath = frc::filesystem::GetDeployDirectory() + "/pathplanner/";
    
    for (const auto& entry : std::filesystem::directory_iterator(filePath))
    {
        if (entry.is_regular_file())
        {
            std::string autonName = entry.path().stem().string();
            std::vector<pathplanner::PathPlannerTrajectory> pathGroup = pathplanner::PathPlanner::loadPathGroup(autonName, {pathplanner::PathConstraints{4_mps, 3_mps_sq}});

            autons[autonName] = std::make_unique<frc2::CommandPtr>(autoBuilder.fullAuto(pathGroup));
        }
    }


}




