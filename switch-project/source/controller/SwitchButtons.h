#ifndef __SWITCHBUTTONS_H__
#define __SWITCHBUTTONS_H__

#include <string>
#include <unordered_map>
extern "C"
{
    #include <switch/services/hid.h>
}

namespace controller
{
    enum class AnalogStick
    {
        Left,
        Right
    };

    static std::unordered_map<AnalogStick, std::string> const analogStickOptions
    {
        { AnalogStick::Left, "Left Analog Stick" },
        { AnalogStick::Right, "Right Analog Stick" }
    };

    std::string AnalogStickToString(AnalogStick stick);
    AnalogStick ParseAnalogStickString(std::string s);

    std::string SwitchButtonToString(HidNpadButton btn);
    HidNpadButton ParseSwitchButtonString(std::string s);
    
    static std::unordered_map<HidNpadButton, std::string> const switchButtonOptions
    {
        { HidNpadButton::HidNpadButton_L, "L" },
        { HidNpadButton::HidNpadButton_R, "R" },
        { HidNpadButton::HidNpadButton_ZL, "ZL" },
        { HidNpadButton::HidNpadButton_ZR, "ZR" }
    };

    static std::unordered_map<HidNpadButton, std::string> const mouseButtonOptions
    {
        { HidNpadButton::HidNpadButton_L, "L" },
        { HidNpadButton::HidNpadButton_R, "R" },
        { HidNpadButton::HidNpadButton_ZL, "ZL" },
        { HidNpadButton::HidNpadButton_ZR, "ZR" }
    };

    HidNpadButton constexpr DefaultLeftMouseButton = HidNpadButton_R;
    HidNpadButton constexpr DefaultRightMouseButton = HidNpadButton_ZR;
}

#endif
