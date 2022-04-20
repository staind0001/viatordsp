/*
  ==============================================================================

    Fader.h
    Created: 21 Jul 2021 12:58:40pm
    Author:  landon viator

  ==============================================================================
*/

/*
  ==============================================================================

    FaderComponent.h
    Created: 23 Oct 2021 2:38:27am
    Author:  Landon Viator
 
    In your main editor, make sure to call setColour first, then enableShadow, if not,
    the shadow won't show up.

  ==============================================================================
*/

#pragma once

#include "../Widgets/Label.h"
#include "../Widgets/StyleSheet.h"

//==============================================================================
/*
*/
namespace viator_gui
{
    class Fader  : public juce::Slider
    {
    public:
        Fader
        (
            juce::String suffix,
            juce::String labelText,
            double rangeStart,
            double rangeEnd,
            double intervalValue,
            double returnValue
        )
        {
            initShadows();
            initProps(suffix, rangeStart, rangeEnd, intervalValue, returnValue);
            faderReturnValue = returnValue;
        }
        
        ~Fader() override
        {
            setLookAndFeel(nullptr);
        }
        
        void paint(juce::Graphics& g) override
        {
            juce::Slider::paint(g);
            
            if (isSelectable)
            {
                g.setColour(juce::Colours::purple.withAlpha(0.25f));
                g.fillRect(getLocalBounds());
                
                if (isSelected || hasMidiMap)
                {
                    g.resetToDefaultState();
                    g.setColour(juce::Colours::whitesmoke.withAlpha(0.25f));
                    g.fillRect(getLocalBounds());
                }
            }
        }
        
        void mouseDoubleClick (const juce::MouseEvent &event) override
        {
            if (isSelectable)
            {
                isSelected ? isSelected = false : isSelected = true;
            }
            
            setValue(faderReturnValue);
        }
        
        void setSelectable(bool sliderISSelectable)
        {
            isSelectable = sliderISSelectable;
            repaint();
        }
        
        
        bool getIsSelectable()
        {
            return isSelectable;
        }
        
        void setSelected(bool newSelectState)
        {
            isSelected = newSelectState;
            
            if (isSelected)
            {
                setSelectable(false);
            }
        }
        
        bool getIsSelected()
        {
            return isSelected;
        }
        
        
        void setHasMidiMap(bool newHasMidiMap)
        {
            hasMidiMap = newHasMidiMap;
            
            if (!hasMidiMap)
            {
                setSelectable(true);
            }
        }
        
        bool getHasMidiMap()
        {
            return hasMidiMap;
        }
        
        void setToBeDeleted(bool newIsToBeDeleted)
        {
            isToBeDeleted = newIsToBeDeleted;
        }
        
        bool getIsToBeDeleted()
        {
            return isToBeDeleted;
        }
        
        void forceShadow();
        
    private:
        
        /** Methods ===============================================================*/
//        void mouseDown(const juce::MouseEvent &event) override
//        {
//            /** Delete mapping on right click*/
//            const auto& modifiers = juce::ModifierKeys::getCurrentModifiers();
//            
//            if (modifiers.isRightButtonDown())
//            {
//                setToBeDeleted(true);
//            }
//            
//            else
//            {
//                return;
//            }
//        }
        
        void mouseEnter (const juce::MouseEvent& event) override;
        void mouseExit (const juce::MouseEvent& event) override;
        
        void initProps
        (
            juce::String suffix,
            double rangeStart,
            double rangeEnd,
            double intervalValue,
            double returnValue
         );
        
        /** Fader shadow */
        void initShadows();
        
        /** Slider */
        juce::Slider slider;
        juce::FaderLAF customFader;
        
        /** Fader shadow */
        juce::DropShadow sliderShadowProperties;
        juce::DropShadowEffect sliderShadow;
        
        /** Label */
        Label trimLabel;
        
        /** Midi Map*/
        bool isSelectable = false;
        bool isSelected = false;
        bool hasMidiMap = false;
        bool isToBeDeleted = false;
        
        double faderReturnValue;
    };
}
