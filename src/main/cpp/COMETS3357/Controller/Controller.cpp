#include "COMETS3357/Configs/ControllerMap.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DriverStation.h>
#include <COMETS3357/Commands/ChangeModeCommand.h>

using namespace COMETS3357;

Controller::Controller(int controllerSlot, std::unordered_map<std::string, std::shared_ptr<frc2::Command>> &actions) : slot{controllerSlot}, controller{controllerSlot}, actionMap{actions} 
{

}



void Controller::LoadConfig(picojson::value &controllers)
{
    for (auto& controllerType : controllers.get<picojson::object>())
    {
        for (auto& mode : controllerType.second.get<picojson::object>())
        {
            if (true)//controller.GetName() == "XBOX")
            {
                controllerMap[controllerType.first][mode.first][mode.second.get("D-padLeft").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetPOV() == 270;}};
                controllerMap[controllerType.first][mode.first][mode.second.get("D-padRight").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetPOV() == 90;}};
                controllerMap[controllerType.first][mode.first][mode.second.get("D-padUp").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetPOV() == 0;}};
                controllerMap[controllerType.first][mode.first][mode.second.get("D-padDown").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetPOV() == 180;}};
                controllerMap[controllerType.first][mode.first][mode.second.get("RightStickButton").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetRightStickButton();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("LeftStickButton").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetLeftStickButton();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("AButton").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetAButton();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("BButton").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetBButton();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("XButton").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetXButton();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("YButton").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetYButton();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("LeftTrigger").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && frc::ApplyDeadband(controller.GetLeftTriggerAxis(), 0.08) != 0;}};
                controllerMap[controllerType.first][mode.first][mode.second.get("RightTrigger").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && frc::ApplyDeadband(controller.GetLeftTriggerAxis(), 0.08) != 0;}};
                controllerMap[controllerType.first][mode.first][mode.second.get("LeftBumper").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetLeftBumper();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("RightBumper").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetRightBumper();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("StartButton").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetStartButton();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("BackButton").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetBackButton();}};

                controllerMap[controllerType.first][mode.first][mode.second.get("RightStickButtonPressed").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetRightStickButtonPressed();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("LeftStickButtonPressed").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetLeftStickButtonPressed();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("XButtonPressed").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetXButtonPressed();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("YButtonPressed").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetYButtonPressed();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("AButtonPressed").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetAButtonPressed();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("BButtonPressed").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetBButtonPressed();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("LeftBumperPressed").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetLeftBumperPressed();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("RightBumperPressed").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetRightBumperPressed();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("StartButtonPressed").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetStartButtonPressed();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("BackButtonPressed").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetBackButtonPressed();}};

                controllerMap[controllerType.first][mode.first][mode.second.get("RightStickButtonReleased").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetRightStickButtonReleased();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("LeftStickButtonReleased").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetLeftStickButtonReleased();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("XButtonReleased").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetXButtonReleased();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("YButtonReleased").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetYButtonReleased();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("AButtonReleased").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetAButtonReleased();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("BButtonReleased").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetBButtonReleased();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("LeftBumperReleased").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetLeftBumperReleased();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("RightBumperReleased").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetRightBumperReleased();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("StartButtonReleased").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetStartButtonReleased();}};
                controllerMap[controllerType.first][mode.first][mode.second.get("BackButtonReleased").get<std::string>()] = frc2::Trigger{[this, mode]() {return currentMode == mode.first && controller.GetBackButtonReleased();}};
            }
            else if (controller.GetName() == "Taranus")
            {

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
            for (auto& action : mode.second)
            {
                if (actionMap.find(action.first) != actionMap.end())
                {
                    action.second.WhileTrue(wrappedEventCommand(actionMap.at(action.first)));
                }
                if (controllerMap["XBOX"].find(action.first) != controllerMap["XBOX"].end())
                {
                    action.second.WhenActive([this, action] {currentMode = action.first;});
                }
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

frc2::CommandPtr Controller::wrappedEventCommand(
        std::shared_ptr<frc2::Command> command) {
    frc2::FunctionalCommand wrapped([command]() {
        command->Initialize();
    },
    [command]() {
        command->Execute();
    },
    [command](bool interrupted) {
        command->End(interrupted);
    },
    [command]() {
        return command->IsFinished();
    }
    );
    wrapped.AddRequirements(command->GetRequirements());

    return std::move(wrapped).ToPtr();
}

