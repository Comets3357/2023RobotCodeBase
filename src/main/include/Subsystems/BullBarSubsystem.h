#pragma once


#include <COMETS3357/Subsystems/Subsystem.h>
#include <COMETS3357/Subsystems/SparkMax/PositionSparkMax.h>
#include <COMETS3357/Subsystems/SparkMax/RollerSparkMax.h>


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

    COMETS3357::PositionSparkMax bullBarExtension{"BullBarExtension"};
    COMETS3357::RollerSparkMax bullBarRoller{"BullBarRoller"};

};