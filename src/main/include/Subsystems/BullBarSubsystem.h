#pragma once


#include <COMETS3357/Subsystems/Subsystem.h>
#include <COMETS3357/Subsystems/SparkMax/PositionSparkMax.h>
#include <COMETS3357/Subsystems/SparkMax/RollerSparkMax.h>
#include "Subsystems/ArmSubsystem.h"
#include "COMETS3357/Subsystems/SubsystemManager.h"
#include <frc/smartDashboard/SmartDashboard.h>

struct BullBarData
{

};

enum BullBarState
{
    BULL_BAR_RETRACTED,
    BULL_BAR_CONE_POSITION,
    BULL_BAR_CUBE_POSITION,
    BULL_BAR_FLANGE_POSITION
};

class BullBarSubsystem : public COMETS3357::Subsystem<BullBarState, BullBarData>
{
public:

    BullBarSubsystem()
    {
        COMETS3357::SubsystemManager::GetInstance().GetSubsystem<ArmSubsystem>("ArmSubsystem");
    }

    void Initialize() override
    {
        arm = COMETS3357::SubsystemManager::GetInstance().GetSubsystem<ArmSubsystem>("ArmSubsystem");
    }

    void Periodic() override{
        frc::SmartDashboard::PutNumber("ADSASD", arm->k);
    }

    std::shared_ptr<ArmSubsystem> arm;



};