#pragma once

#include <frc2/Command/SubsystemBase.h>
#include <COMETS3357/Subsystems/SubsystemManager.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

namespace COMETS3357
{
    template <typename state, typename data>
    class Subsystem : public frc2::SubsystemBase
    {
    public:

        Subsystem()
        {
            COMETS3357::SubsystemManager::GetInstance().AddInit([this]{Initialize();});

        }

        template <typename T>
        std::shared_ptr<T> GetSubsystem(std::string name)
        {
            return COMETS3357::SubsystemManager::GetInstance().GetSubsystem<T>(name);
        }

        /**
         * @brief An Initialization function for a Subsystem
        */
        virtual void Initialize() {}

        /**
         * @brief Registers the Subsystem in a place that is accesible everywhere
         * 
         * @param name The name of the subsystem
        */
        void Register(std::string name)
        {
            COMETS3357::SubsystemManager::GetInstance().RegisterSubsystem(name, this);
        }

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

    private:
    

    };
};