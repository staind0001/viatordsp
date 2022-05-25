/*
  ==============================================================================

    SettingsPage.h
    Created: 21 May 2022 11:48:39pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../LookAndFeel/MenuSliderLAF.h"
#include "../LookAndFeel/ToggleButtonLAF.h"
#include "../LookAndFeel/LabelLAF.h"
#include "../LookAndFeel/ColorButtonLAF.h"
#include "../Globals.h"
#include "SettingsComps/ToolTipSettingsComp.h"


//==============================================================================
/*
*/
class SettingsPage  : public juce::Component
{
public:
    SettingsPage();
    ~SettingsPage() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    bool getShouldUseToolTips();
private:
    
    juce::Slider menuSlider1;
    MenuSliderLAF customMenuSlider;
    
    ToolTipSettingsComp tooltipSettingsComp;
    LabelLAF customLabelLAF;
    
    juce::TextButton color1Button;
    juce::TextButton color2Button;
    juce::TextButton color3Button;
    juce::TextButton color4Button;
    ColorButtonLAF customColorButtonLAF;
    
    float rowheight;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsPage)
};