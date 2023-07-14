#pragma once

#include <frc2/Command/SubsystemBase.h>

namespace COMETS3357
{
    template <typename state, typename data>
    class Subsystem : public frc2::SubsystemBase
    {
    public:

        /**
         * @brief Gets the Subsystem Data
         * 
         * @return Subsystem Data Struct
        */
        data& Data()
        {
            return m_data;
        }

        /**
         * @brief Gets the Subsystem State
         * 
         * @return Subsystem State Enum
        */
        state& State()
        {
            return m_state;
        }

    protected:

        state m_state{};
        data m_data{};

    };
};