#include "level_meter.hpp"

LevelMeter::LevelMeter(int ch, PluginProcessor &p)
    : channel(ch), pluginProcessor(p), level(-70.0f) {
  startTimerHz(30);
}

void LevelMeter::paint(juce::Graphics &g) {
  auto bounds = getLocalBounds().toFloat();

  g.setColour(juce::Colours::grey.withBrightness(0.4f));
  g.fillRoundedRectangle(bounds, 5.0f);

  g.setColour(juce::Colours::blue);
  const auto scaledY =
      juce::jmap(level, -70.0f, 6.0f, 0.0f, static_cast<float>(getHeight()));
  g.fillRoundedRectangle(bounds.removeFromBottom(scaledY), 5.0f);
}

void LevelMeter::timerCallback() {
  auto gainProcessor = pluginProcessor.getGainProcessor();

  if (gainProcessor) {
    level = gainProcessor->getRmsValue(channel);
  }

  repaint();
}