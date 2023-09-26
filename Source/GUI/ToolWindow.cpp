#include "ToolWindow.h"
#include "../Utility/RuntimeRootProperties.h"

ToolWindow::ToolWindow ()
{
    progressUpdateLabel.setColour (juce::Label::ColourIds::textColourId, juce::Colours::white);
    addAndMakeVisible (progressUpdateLabel);
}

void ToolWindow::init (juce::ValueTree rootPropertiesVT)
{
    RuntimeRootProperties runtimeRootProperties (rootPropertiesVT, RuntimeRootProperties::WrapperType::client, RuntimeRootProperties::EnableCallbacks::no);
    validatorProperties.wrap (runtimeRootProperties.getValueTree (), ValidatorProperties::WrapperType::client, ValidatorProperties::EnableCallbacks::yes);
    validatorProperties.onProgressUpdateChanged = [this] (juce::String progressUpdate)
    {
        juce::MessageManager::callAsync ([this, progressUpdate] ()
        {
            updateProgress (progressUpdate);
        });
    };
}

void ToolWindow::updateProgress (juce::String progressUpdate)
{
    progressUpdateLabel.setText (progressUpdate, juce::NotificationType::dontSendNotification);
}

void ToolWindow::paint (juce::Graphics& g)
{
    g.fillAll (progressUpdateLabel.findColour (juce::Label::ColourIds::backgroundColourId).brighter (0.9f));
}

void ToolWindow::resized ()
{
    auto localBounds { getLocalBounds () };
    localBounds.reduce (5, 3);

    progressUpdateLabel.setBounds (localBounds);
}
