#pragma once

#include <frc2/Command/SubsystemBase.h>
#include <COMETS3357/Subsystems/SubsystemManager.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include <string>

namespace COMETS3357
{
    template <typename state>
    class Subsystem : public frc2::SubsystemBase
    {
    public:

        Subsystem(std::string_view name)
        {
            COMETS3357::SubsystemManager::GetInstance().AddInit([this]{Initialize();});
            SetName(name);
            subsystemData = nt::NetworkTableInstance::GetDefault().GetTable(name);

        }

    
        std::shared_ptr<nt::NetworkTable> GetSubsystemData(std::string_view name)
        {
            return nt::NetworkTableInstance::GetDefault().GetTable(name);
        }


        /**
         * @brief An Initialization function for a Subsystem
        */
        virtual void Initialize() {}

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
        std::shared_ptr<nt::NetworkTable> subsystemData;


    private:

        
    

    };
};