#pragma once

#include <iostream>
#include <fstream>
#include "Json/picojson.h"
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <frc2/command/button/Trigger.h>
#include <filesystem>
#include <frc/fileSystem.h>
#include <frc2/command/button/CommandXboxController.h>
#include <frc/MathUtil.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/Command.h>

namespace COMETS3357
{

    class Controller
    {
    public:

        /**
         * @brief Contructs a new controller
         * @param slot the slot of the controller
         * @param actions an event list of actions to pair to control bindings
        */
        Controller(int slot, std::unordered_map<std::string, std::shared_ptr<frc2::Command>> &actions);

        /**
         * @brief Loads the config of the controller
         * @param controllers The json value of the controller
        */
        void LoadConfig(picojson::value &controllers);

        /**
         * @brief Loads the controls from the json file
         * @return Did the controls load Successfully
        */
        bool LoadControls();

        int slot;
        frc2::CommandXboxController controller;
        std::map<std::string, std::map<std::string, std::map<std::string, frc2::Trigger>>> controllerMap;
        std::string currentMode = "SemiAuto";
        std::string currentController = "XBOX";
        std::unordered_map<std::string, std::shared_ptr<frc2::Command>> &actionMap;
        frc2::Trigger controllerConnectionTrigger{[this]() {return controller.IsConnected();}};

    };


    class ControllerMap
    {
    public:


        /**
         * @brief Constructs a controllerMap object
         * This object is used to automatically bind controller buttons to actions
         * @param actionMap This is the action map that contains each action being paired
         * @param fileName This is the filename of the Controller Config file
         */
        ControllerMap(std::unordered_map<std::string, std::shared_ptr<frc2::Command>> &actionMap, std::string fileName);


        Controller primary;
        Controller secondary;
        Controller test;
        /**
         * Loads data out of the selected config file and loads the data into a 
         * RobotConfig object which is then distributed out to subsystems
         *
         * @param fileName The name of the config file that is being loaded
         */
        void LoadControllerMap(std::string fileName);

        /**
         * Returns a reference to the RobotConfig data while making sure that it is generated
         */


    private:



        
    };

};