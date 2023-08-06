#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Timer.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <COMETS3357/Subsystems/Subsystem.h>

namespace COMETS3357
{

    enum TimerState
    {
        TIMER_RUNNING
    };

    class TimerSubsystem : public COMETS3357::Subsystem<TimerState>
    {
    public:

        /**
         * @brief Constructs a TimerSubsystem
        */
        TimerSubsystem();

        /**
         * @brief The Periodic Function for the TimerSubsystem
        */
        void Periodic() override;

        /**
         * @brief Restarts the Timer
        */
        void ResetAndBeginTimer();

    private:

        frc::Timer timer{};

        units::second_t timeSinceEnabled{0};
        units::second_t deltaTime{0};
        units::second_t lastTime{0};
    };
};