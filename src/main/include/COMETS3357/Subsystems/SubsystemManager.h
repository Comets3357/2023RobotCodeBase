#pragma once


#include <map>
#include <vector>
#include <functional>
#include <frc2/command/SubsystemBase.h>

namespace COMETS3357
{


    class SubsystemManager
    {
    public:

        static SubsystemManager& GetInstance()
        {
            static SubsystemManager instance;
            return instance;
        }

        void Init()
        {
            for (const auto& lamda : initFunctions)
            {
                lamda();
            }
            initFunctions.clear();
        }

        void RegisterSubsystem(std::string name, frc2::SubsystemBase* subsystem)
        {
            subsystems[name] = std::shared_ptr<frc2::SubsystemBase>(subsystem);
        }

        template <typename T>
        std::shared_ptr<T> GetSubsystem(std::string name)
        {
            auto it = subsystems.find(name);
            if (it != subsystems.end())
            {
                // Use std::dynamic_pointer_cast to convert from std::shared_ptr<Subsystem> to std::shared_ptr<T>
                return std::dynamic_pointer_cast<T>(it->second);
            }
            return nullptr;
        }

        void AddInit(std::function<void()> func)
        {
            initFunctions.emplace_back(func);
        }

    private:


        std::map<std::string, std::shared_ptr<frc2::SubsystemBase>> subsystems;
        std::vector<std::function<void()>> initFunctions;

        SubsystemManager() {} // Private constructor to prevent instantiation outside of class
        SubsystemManager(const SubsystemManager&) = delete; // Disable copy constructor
        SubsystemManager& operator=(const SubsystemManager&) = delete; // Disable copy assignment operator
        SubsystemManager(SubsystemManager&&) = delete; // Disable move constructor
        SubsystemManager& operator=(SubsystemManager&&) = delete; // Disable move assignment operator

            
    };
};
