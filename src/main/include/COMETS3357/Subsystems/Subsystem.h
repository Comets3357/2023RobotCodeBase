#pragma once

#include <frc2/Command/SubsystemBase.h>

namespace COMETS3357
{
    template <typename state, typename data>
    class Subsystem : public frc2::SubsystemBase
    {
    protected:

    state m_state{};
    data m_data{};



    public:

        data& Data()
        {
            return m_data;
        }

        state& State()
        {
            return m_state;
        }

    };
};