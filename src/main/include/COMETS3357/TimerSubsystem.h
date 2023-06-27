#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Timer.h>
#include <frc/smartdashboard/SmartDashboard.h>

struct TimerData
{
    double timeSinceEnabled = 0;
};

class TimerSubsystem : public frc2::SubsystemBase
{
public:

    TimerSubsystem(TimerData* data);

    void Periodic() override;

    void ResetAndBeginTimer();

    TimerData* timerData{};

    private:

    frc::Timer timer{};

};