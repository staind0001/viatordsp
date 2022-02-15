/*
  ==============================================================================

    LV_Dial.h
    Created: 20 Jul 2021 9:43:18pm
    Author:  landon viator

  ==============================================================================
*/

#pragma once
#include "../Widgets/StyleSheet.h"

namespace viator_gui
{

class LV_NumberBox  : public juce::Slider
{
public:
    
    LV_NumberBox
    
    (   juce::String suffix,
        double rangeStart,
        double rangeEnd,
        double intervalValue,
        double returnValue
    )
    {
        setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
        setSliderSnapsToMousePosition(false);
        setMouseDragSensitivity(2500);
        setTextBoxStyle(juce::Slider::TextBoxBelow, false, 96, 32);
        setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::transparentBlack);
        setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
        setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::whitesmoke.withAlpha(0.25f));
        setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour::fromFloatRGBA(0.392f, 0.584f, 0.929f, 1.0f).darker(1.0f));
        setRange(rangeStart, rangeEnd, intervalValue);
        setDoubleClickReturnValue(true, returnValue);
        setTextValueSuffix(suffix);
        setLookAndFeel(&customNumberBox);
    }
    
    ~LV_NumberBox() override
    {
        setLookAndFeel(nullptr);
    }

    
private:
    
    void mouseEnter (const juce::MouseEvent& event) override
    {
        setColour(juce::Slider::ColourIds::textBoxTextColourId, findColour(juce::Slider::ColourIds::textBoxTextColourId).withAlpha(1.0f));
    }
    
    void mouseExit (const juce::MouseEvent& event) override
    {
        setColour(juce::Slider::ColourIds::textBoxTextColourId, findColour(juce::Slider::ColourIds::textBoxTextColourId).withAlpha(0.5f));
    }
    
    /** Slider ================================================================*/
    juce::Slider dial;
    juce::LV_CustomNumberBox customNumberBox;
};
}

