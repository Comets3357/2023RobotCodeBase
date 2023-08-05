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

        void AddInit(std::function<void()> func)
        {
            initFunctions.emplace_back(func);
        }

    private:

        std::vector<std::function<void()>> initFunctions;

        SubsystemManager() {} // Private constructor to prevent instantiation outside of class
        SubsystemManager(const SubsystemManager&) = delete; // Disable copy constructor
        SubsystemManager& operator=(const SubsystemManager&) = delete; // Disable copy assignment operator
        SubsystemManager(SubsystemManager&&) = delete; // Disable move constructor
        SubsystemManager& operator=(SubsystemManager&&) = delete; // Disable move assignment operator

            
    };
};
