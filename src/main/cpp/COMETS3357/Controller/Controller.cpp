#include "COMETS3357/Configs/ControllerMap.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DriverStation.h>
#include <COMETS3357/Commands/ChangeModeCommand.h>
#include "commands/test.h"
using namespace COMETS3357;

Controller::Controller(int controllerSlot, std::unordered_map<std::string, std::shared_ptr<frc2::Command>> &actions) : slot{controllerSlot}, controller{controllerSlot}, actionMap{actions} 
{

}
//


void Controller::LoadConfig(picojson::value &controllers)
{
    for (auto& controllerType : controllers.get<picojson::object>())
    {
        for (auto& mode : controllerType.second.get<picojson::object>())
        {
            if (frc::DriverStation::GetJoystickName(slot) == "FrSky Taranis Joystick")
            {
               
            }
            else
            {
                controllerMap[controllerType.first][mode.first][mode.second.get("D-padLeft").get<std::string>()] = frc2::Trigger{[this](){return controller.GetPOV() == 270;}};
                controllerMap[controllerType.first][mode.first][mode.second.get("D-padRight").get<std::string>()] = frc2::Trigger([this]() {return controller.GetPOV() == 90;});
                controllerMap[controllerType.first][mode.first][mode.second.get("D-padUp").get<std::string>()] = frc2::Trigger([this]() {return controller.GetPOV() == 0;});
                controllerMap[controllerType.first][mode.first][mode.second.get("D-padDown").get<std::string>()] = frc2::Trigger([this]() {return controller.GetPOV() == 180;});
                controllerMap[controllerType.first][mode.first][mode.second.get("RightStickButton").get<std::string>()] = controller.RightStick();
                controllerMap[controllerType.first][mode.first][mode.second.get("LeftStickButton").get<std::string>()] = controller.LeftStick();
                controllerMap[controllerType.first][mode.first][mode.second.get("AButton").get<std::string>()] = controller.A();
                controllerMap[controllerType.first][mode.first][mode.second.get("BButton").get<std::string>()] = controller.B();
                controllerMap[controllerType.first][mode.first][mode.second.get("XButton").get<std::string>()] = controller.X();
                controllerMap[controllerType.first][mode.first][mode.second.get("YButton").get<std::string>()] = controller.Y();
                controllerMap[controllerType.first][mode.first][mode.second.get("LeftTrigger").get<std::string>()] = frc2::Trigger([this]() {return frc::ApplyDeadband(controller.GetLeftTriggerAxis(), 0.08) != 0;});
                controllerMap[controllerType.first][mode.first][mode.second.get("RightTrigger").get<std::string>()] = frc2::Trigger{[this]() {return frc::ApplyDeadband(controller.GetLeftTriggerAxis(), 0.08) != 0;}};
                controllerMap[controllerType.first][mode.first][mode.second.get("LeftBumper").get<std::string>()] = controller.LeftBumper();
                controllerMap[controllerType.first][mode.first][mode.second.get("RightBumper").get<std::string>()] = controller.RightBumper();
                controllerMap[controllerType.first][mode.first][mode.second.get("StartButton").get<std::string>()] = controller.Start();
                controllerMap[controllerType.first][mode.first][mode.second.get("BackButton").get<std::string>()] = controller.Back();

                controllerMap[controllerType.first][mode.first][mode.second.get("RightStickButtonPressed").get<std::string>()] = frc2::Trigger{[this]() {return controller.GetRightStickButtonPressed();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("LeftStickButtonPressed").get<std::string>()] = frc2::Trigger{[this]() {return controller.GetLeftStickButtonPressed();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("XButtonPressed").get<std::string>()] = frc2::Trigger{[this]() {return controller.GetXButtonPressed();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("YButtonPressed").get<std::string>()] = frc2::Trigger{[this]() {return controller.GetYButtonPressed();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("AButtonPressed").get<std::string>()] = frc2::Trigger{[this]() {return controller.GetAButtonPressed();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("BButtonPressed").get<std::string>()] = frc2::Trigger{[this]() {return controller.GetBButtonPressed();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("LeftBumperPressed").get<std::string>()] = frc2::Trigger{[this]() {return controller.GetLeftBumperPressed();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("RightBumperPressed").get<std::string>()] = frc2::Trigger{[this]() {return controller.GetRightBumperPressed();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("StartButtonPressed").get<std::string>()] = frc2::Trigger{[this]() {return controller.GetStartButtonPressed();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("BackButtonPressed").get<std::string>()] = frc2::Trigger{[this]() {return controller.GetBackButtonPressed();}};

                controllerMap[controllerType.first][mode.first][mode.second.get("RightStickButtonReleased").get<std::string>()] = frc2::Trigger{[this]() {return controller.GetRightStickButtonReleased();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("LeftStickButtonReleased").get<std::string>()] = frc2::Trigger{[this]() {return controller.GetLeftStickButtonReleased();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("XButtonReleased").get<std::string>()] = frc2::Trigger{[this]() {return controller.GetXButtonReleased();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("YButtonReleased").get<std::string>()] = frc2::Trigger{[this]() {return controller.GetYButtonReleased();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("AButtonReleased").get<std::string>()] = frc2::Trigger{[this]() {return controller.GetAButtonReleased();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("BButtonReleased").get<std::string>()] = frc2::Trigger{[this]() {return controller.GetBButtonReleased();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("LeftBumperReleased").get<std::string>()] = frc2::Trigger{[this]() {return controller.GetLeftBumperReleased();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("RightBumperReleased").get<std::string>()] = frc2::Trigger{[this]() {return controller.GetRightBumperReleased();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("StartButtonReleased").get<std::string>()] = frc2::Trigger{[this]() {return controller.GetStartButtonReleased();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("BackButtonReleased").get<std::string>()] = frc2::Trigger{[this]() {return controller.GetBackButtonReleased();}};
            }

            if (controllerMap[controllerType.first][mode.first].find("NONE") != controllerMap[controllerType.first][mode.first].end())
            {
                controllerMap[controllerType.first][mode.first].erase("NONE");
            }
            

            
        }
    }

    LoadControls();

}

bool Controller::LoadControls()
{
    if (true)//controller.IsConnected())
    {
        for (auto& mode : controllerMap["XBOX"])//controller.GetName()])
        {
            if (mode.first == currentMode)
            {
                for (auto& action : mode.second)
                {
                    if (actionMap.find(action.first) != actionMap.end())
                    {
                        action.second.WhileTrue(actionMap.at(action.first).get());
                    }
                    if (controllerMap["XBOX"].find(action.first) != controllerMap["XBOX"].end())
                    {
                        action.second.WhenActive([this, action] {currentMode = action.first; LoadControls();});
                    }
                }
            }
            else
            {
                for (auto& action : mode.second)
                {
                    frc2::CommandScheduler::GetInstance().Cancel(actionMap.at(action.first).get());
                }
            }

            
        }
    }
    else
    {
        return false;
    }
    return true;
}
