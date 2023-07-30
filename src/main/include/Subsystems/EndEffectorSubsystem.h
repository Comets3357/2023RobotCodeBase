#pragma once


#include <COMETS3357/Subsystems/Subsystem.h>
#include <COMETS3357/Subsystems/SparkMax/RollerSparkMax.h>


struct EndEffectorData
{

};

enum EndEffectorState
{
    END_EFFECTOR_CONE,
    END_EFFECTOR_CUBE,
    END_EFFECTOR_NONE
};

class EndEffector : public COMETS3357::Subsystem<EndEffectorState, EndEffectorData>
{
public:

    COMETS3357::RollerSparkMax endEffectorRoller{"EndEffectorRoller"};

};