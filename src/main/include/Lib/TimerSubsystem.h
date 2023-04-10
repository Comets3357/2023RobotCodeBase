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

    TimerSubsystem(TimerData* data) : timerData{data}
    {

    }

    void Periodic() override
    {
        timerData->timeSinceEnabled = (double)timer.Get();

        frc::SmartDashboard::PutNumber("TImE", (double)timer.Get());
    }

    void ResetAndBeginTimer()
    {
        timer.Reset();
        timer.Start();
    }

    TimerData* timerData{};

    private:

    frc::Timer timer{};

};