#include <TouchDisplayDoorControlModule.h>
#include <Arduino.h>
#include <ui.h>

TouchDisplayDoorControlModule::TouchDisplayDoorControlModule(TouchDisplayModule* touchDisplayModule) {
    TouchDisplayDoorControlModule::_touchDisplayModule = touchDisplayModule;
}

const std::string TouchDisplayDoorControlModule::name()
{
    return "TouchDisplayDoorControl";
}

const std::string TouchDisplayDoorControlModule::version()
{
    return "0.0dev";
}

void TouchDisplayDoorControlModule::setup()
{
    TouchDisplayDoorControlModule::doorState = DoorState::UNDEFINED;

    TouchDisplayDoorControlModule::_touchDisplayModule->initUi();
    ui_init();
}

void TouchDisplayDoorControlModule::update_button_states(DoorState newDoorState)
{
    if (TouchDisplayDoorControlModule::_touchDisplayModule->isBacklightOn()) {
        TouchDisplayDoorControlModule::doorState = newDoorState;
        logDebugP("New door state: %d\n", doorState);
    }

    TouchDisplayDoorControlModule::_touchDisplayModule->displayTouched();

    switch (TouchDisplayDoorControlModule::doorState)
    {
        case DoorState::CLOSED:
            lv_imgbtn_set_state(ui_ImgButtonClosed, LV_IMGBTN_STATE_CHECKED_RELEASED);
            lv_imgbtn_set_state(ui_ImgButtonOpen, LV_IMGBTN_STATE_RELEASED);
            lv_imgbtn_set_state(ui_ImgButtonAuto, LV_IMGBTN_STATE_RELEASED);
            break;

        case DoorState::OPEN:
            lv_imgbtn_set_state(ui_ImgButtonClosed, LV_IMGBTN_STATE_RELEASED);
            lv_imgbtn_set_state(ui_ImgButtonOpen, LV_IMGBTN_STATE_CHECKED_RELEASED);
            lv_imgbtn_set_state(ui_ImgButtonAuto, LV_IMGBTN_STATE_RELEASED);
            break;

        case DoorState::AUTO:
            lv_imgbtn_set_state(ui_ImgButtonClosed, LV_IMGBTN_STATE_RELEASED);
            lv_imgbtn_set_state(ui_ImgButtonOpen, LV_IMGBTN_STATE_RELEASED);
            lv_imgbtn_set_state(ui_ImgButtonAuto, LV_IMGBTN_STATE_CHECKED_RELEASED);
            break;

        default:
            lv_imgbtn_set_state(ui_ImgButtonClosed, LV_IMGBTN_STATE_RELEASED);
            lv_imgbtn_set_state(ui_ImgButtonOpen, LV_IMGBTN_STATE_RELEASED);
            lv_imgbtn_set_state(ui_ImgButtonAuto, LV_IMGBTN_STATE_RELEASED);
            break;
    }
}

void TouchDisplayDoorControlModule::ui_ImgButtonClosed_event(lv_event_t * event)
{
    update_button_states(DoorState::CLOSED);
}

void TouchDisplayDoorControlModule::ui_ImgButtonOpen_event(lv_event_t * event)
{
    update_button_states(DoorState::OPEN);
}

void TouchDisplayDoorControlModule::ui_ImgButtonAuto_event(lv_event_t * event)
{
    update_button_states(DoorState::AUTO);
}

void TouchDisplayDoorControlModule::ui_Main_event(lv_event_t * event)
{
    TouchDisplayDoorControlModule::_touchDisplayModule->displayTouched();
    logDebugP("Main pressed.");
}

void TouchDisplayDoorControlModule::loop()
{
    TouchDisplayDoorControlModule::_touchDisplayModule->loopUi();
}

void TouchDisplayDoorControlModule::processInputKo(GroupObject& iKo)
{
}

void TouchDisplayDoorControlModule::processAfterStartupDelay()
{
}

// void TouchDisplayDoorControlModule::writeFlash()
// {
//     for (size_t i = 0; i < flashSize(); i++)
//     {
//         //openknx.flash.writeByte(0xd0 + i);
//     }
// }

// void TouchDisplayDoorControlModule::readFlash(const uint8_t* data, const uint16_t size)
// {
//     // printHEX("RESTORE:", data,  len);
// }

// uint16_t TouchDisplayDoorControlModule::flashSize()
// {
//     return 10;
// }