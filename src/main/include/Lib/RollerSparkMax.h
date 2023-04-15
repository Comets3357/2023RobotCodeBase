#pragma once

#include <rev/CANSparkMax.h>
#include "Lib/ConfigFiles.h"

class RollerSparkMax
{
public:

    RollerSparkMax(const int ID);

    void SetPower(double power);

    void SetConfig(std::string name);

private:

    rev::CANSparkMax motor;

};