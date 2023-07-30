#include "COMETS3357/TimerSubsystem.h"

using namespace COMETS3357;

TimerSubsystem::TimerSubsystem()
{
    Register("TimerSubsystem");
    ResetAndBeginTimer();
}

void TimerSubsystem::Periodic()
{
    m_data.timeSinceEnabled = timer.Get();

    frc::SmartDashboard::PutNumber("Time", (double)m_data.timeSinceEnabled);

    m_data.deltaTime = m_data.timeSinceEnabled - m_data.lastTime;
    frc::SmartDashboard::PutNumber("TicksPerSecond", 1.0/(double)m_data.deltaTime);
    frc::SmartDashboard::PutNumber("TicksadsPerSecond", (double)m_data.deltaTime);

    m_data.lastTime = m_data.timeSinceEnabled;
}

void TimerSubsystem::ResetAndBeginTimer()
{
    
    timer.Reset();
    timer.Start();
}