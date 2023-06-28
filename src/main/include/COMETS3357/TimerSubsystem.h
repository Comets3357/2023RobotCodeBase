#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Timer.h>
#include <frc/smartdashboard/SmartDashboard.h>

namespace COMETS3357
{
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

        COMETS3357::TimerData* timerData{};

        private:

        frc::Timer timer{};

    };
};