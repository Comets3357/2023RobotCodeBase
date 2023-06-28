#include "COMETS3357/TimerSubsystem.h"

using namespace COMETS3357;

TimerSubsystem::TimerSubsystem(TimerData* data) : timerData{data}
{

}

void TimerSubsystem::Periodic()
{
    timerData->timeSinceEnabled = (double)timer.Get();

    frc::SmartDashboard::PutNumber("TImE", (double)timer.Get());
}

void TimerSubsystem::ResetAndBeginTimer()
{
    timer.Reset();
    timer.Start();
}