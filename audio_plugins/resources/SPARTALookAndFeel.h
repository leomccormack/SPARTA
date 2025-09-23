#pragma once

class SPARTALookAndFeel : public juce::LookAndFeel_V4
{
public:
    // Color Palette
    Colour colourBackground = Colour(70, 75, 85);
    Colour colourAccent = Colour(70, 180, 220);
    Colour colourThumb  = Colour(140, 190, 225);
    Colour colourOutline = Colour(200, 240, 255);

    void drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                           float sliderPos, float /*minSliderPos*/, float /*maxSliderPos*/,
                           const Slider::SliderStyle style, Slider& slider) override
    {
        const bool isHovered = slider.isMouseOverOrDragging();
        auto active = isHovered ? colourAccent.darker(0.1f): colourAccent.darker(0.3f);

        if (style == Slider::LinearHorizontal)
        {
            float trackHeight = 6.0f;
            float centerY = y + height * 0.5f;
            Rectangle<float> track (x, centerY - trackHeight * 0.5f, width, trackHeight);
            g.setColour(colourBackground);
            g.fillRoundedRectangle(track, 3.0f);

            Rectangle<float> fill (x, centerY - trackHeight * 0.5f, sliderPos - x, trackHeight);
            g.setColour(active);
            g.fillRoundedRectangle(fill, 3.0f);

            float r = isHovered ? 8.0f : 7.0f;
            g.setColour(colourThumb.darker(0.2f));
            g.fillEllipse(sliderPos - r, centerY - r, r * 2, r * 2);
            g.setColour(colourOutline.darker(0.3f));
            g.drawEllipse(sliderPos - r, centerY - r, r * 2, r * 2, 1.0f);
            if (isHovered)
            {
                g.setColour(active.withAlpha(0.55f));
                g.drawEllipse(sliderPos - r - 2, centerY - r - 2, (r + 2) * 2, (r + 2) * 2, 1.0f);
            }
        }
        else if (style == Slider::LinearVertical)
        {
            float trackWidth = 6.0f;
            float centerX = x + width * 0.5f;
            Rectangle<float> track (centerX - trackWidth * 0.5f, y, trackWidth, height);
            g.setColour(colourBackground);
            g.fillRoundedRectangle(track, 3.0f);

            float r = isHovered ? 8.0f : 7.0f;
            Rectangle<float> fill(centerX - trackWidth * 0.5f, sliderPos, trackWidth, y + height -sliderPos);
            g.setColour(active);
            g.fillRoundedRectangle(fill, 3.0f);

            g.setColour(colourThumb.darker(0.2f));
            g.fillEllipse(centerX - r, sliderPos - r, r * 2, r * 2);
            g.setColour(colourOutline.darker(0.3f));
            g.drawEllipse(centerX - r, sliderPos - r, r * 2, r * 2, 1.0f);
            if (isHovered)
            {
                g.setColour(active.withAlpha(0.55f));
                g.drawEllipse(centerX - r - 2, sliderPos - r - 2, (r + 2) * 2, (r + 2) * 2, 1.0f);
            }
        }
    }

    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
                           float /*sliderPos*/, float rotaryStartAngle, float rotaryEndAngle,
                           juce::Slider& slider) override
    {
        const auto range = slider.getRange();
        const double currentValue = slider.getValue();
        const double defaultValue = slider.getDoubleClickReturnValue();

        auto normalize = [&range](double v)
        {
            return (v - range.getStart()) / range.getLength();
        };

        const float normCurrent = juce::jlimit(0.0, 1.0, normalize(currentValue));
        const float normDefault = juce::jlimit(0.0, 1.0, normalize(defaultValue));

        const float angleCurrent = rotaryStartAngle + normCurrent * (rotaryEndAngle - rotaryStartAngle);
        const float angleDefault = rotaryStartAngle + normDefault * (rotaryEndAngle - rotaryStartAngle);

        const float radius = juce::jmin(width, height) / 2.0f - 6.0f;
        const float centerX = x + width * 0.5f;
        const float centerY = y + height * 0.5f;
        const bool isHovered = slider.isMouseOverOrDragging();

        // Arc from default to current
        if (std::abs(currentValue - defaultValue) > 1e-4)
        {
            juce::Path arc;
            float arcRadius = radius + 4.0f;

            float startAngle = angleDefault;
            float endAngle   = angleCurrent;

            if (endAngle < startAngle)
                std::swap(startAngle, endAngle);

            juce::Rectangle<float> arcBounds(centerX - arcRadius, centerY - arcRadius,
                                             arcRadius * 2.0f, arcRadius * 2.0f);

            arc.addArc(arcBounds.getX(), arcBounds.getY(),
                       arcBounds.getWidth(), arcBounds.getHeight(),
                       startAngle, endAngle, true);

            g.setColour(isHovered ? colourAccent.withAlpha(0.6f) : colourOutline.withAlpha(0.4f));
            g.strokePath(arc, juce::PathStrokeType(isHovered ? 2.5f : 1.7f));
        }
        
        juce::Colour activeColour = isHovered ? colourAccent : colourOutline;

        // face
        g.setColour(colourBackground.darker(0.8f));
        g.fillEllipse(centerX - radius, centerY - radius, radius * 2.0f, radius * 2.0f);

        g.setColour(activeColour);
        g.drawEllipse(centerX - radius, centerY - radius, radius * 2.0f, radius * 2.0f,
                      isHovered ? 2.0f : 1.0f);

        float centerRadius = radius * 0.2f;
        g.setColour(activeColour);
        g.fillEllipse(centerX - centerRadius, centerY - centerRadius,
                      centerRadius * 2.0f, centerRadius * 2.0f);

        float pointerLength = radius - 2.0f;
        float pointerThickness = 2.0f;

        juce::Path pointer;
        pointer.startNewSubPath(0.0f, 0.0f);
        pointer.lineTo(0.0f, -pointerLength);

        g.setColour(activeColour);
        g.strokePath(pointer, juce::PathStrokeType(pointerThickness),
                     juce::AffineTransform::rotation(angleCurrent).translated(centerX, centerY));

    }
    
    void drawToggleButton (Graphics& g, ToggleButton& button, bool isHovered, bool /*isPressed*/) override
    {
        auto bounds = button.getLocalBounds().toFloat().reduced(4.0f);

        // Make it a square based on the shortest dimension
        float size = jmin(bounds.getWidth(), bounds.getHeight());
        float paddingX = (bounds.getWidth() - size) * 0.5f;
        float paddingY = (bounds.getHeight() - size) * 0.5f;
        Rectangle<float> squareBounds = bounds.withTrimmedLeft(paddingX)
                                              .withTrimmedRight(paddingX)
                                              .withTrimmedTop(paddingY)
                                              .withTrimmedBottom(paddingY);

        float cornerSize = 6.0f;
        Colour fill = colourBackground.darker(0.8f);
        Colour outline = colourOutline.withAlpha(0.75f);

        if (button.getToggleState() && isHovered){
            fill = colourAccent.darker(0.70f);
            outline = colourAccent.brighter(0.65f);
        }
        else if (button.getToggleState()){
            fill = colourAccent.darker(0.45f);
            outline = colourAccent.brighter(0.2f);
        }
        else if (isHovered){
            fill = colourBackground.darker(0.3f);
            outline = colourOutline;
        }

        g.setColour(fill);
        g.fillRoundedRectangle(squareBounds, cornerSize);
        g.setColour(outline);
        g.drawRoundedRectangle(squareBounds, cornerSize, 1.2f);

        // Draw tick if toggled
        if (button.getToggleState())
        {
            Path tick = getTickShape(7.1f);
            RectanglePlacement placement (RectanglePlacement::centred);
            g.setColour(colourThumb.brighter(0.5f));
            g.fillPath(tick, placement.getTransformToFit(tick.getBounds(), squareBounds.reduced(3.0f)));
        }
    }

    void drawComboBox (juce::Graphics& g, int width, int height, bool /*isButtonDown*/,
                       int buttonX, int buttonY, int buttonW, int buttonH, juce::ComboBox& box) override
    {
        bool isActive = box.isPopupActive();

        auto background = colourBackground.darker(0.8f);

        auto outline = isActive ? colourAccent
                                 : colourOutline.withAlpha(0.75f);

        g.setColour(background);
        g.fillRoundedRectangle(0.0f, 0.0f, (float)width, (float)height, 4.0f);

        g.setColour(outline);
        g.drawRoundedRectangle(0.5f, 0.5f, (float)width - 1.0f, (float)height - 1.0f, 4.0f, 1.0f);

        // Dropdown arrow
        juce::Path arrow;
        float cx = (float)(buttonX + buttonW * 0.5f);
        float cy = (float)(buttonY + buttonH * 0.5f);
        float chevronSize = 5.0f;

        arrow.startNewSubPath(cx - chevronSize, cy - 2.0f);
        arrow.lineTo(cx, cy + 2.5f);
        arrow.lineTo(cx + chevronSize, cy - 2.0f);

        // Actual arrow fill
        g.setColour(outline);
        g.strokePath(arrow, juce::PathStrokeType(1.8f));
    }
    
    void drawPopupMenuItemWithOptions(Graphics& g, const Rectangle<int>& area,
                                      bool isHighlighted, const PopupMenu::Item& item,
                                      const PopupMenu::Options&) override
    {
        if (item.isSeparator)
        {
            g.setColour(colourOutline.withAlpha(0.3f));
            g.drawLine(area.getX() + 4.0f, area.getCentreY(), area.getRight() - 4.0f, area.getCentreY());
            return;
        }

        Colour textCol = item.colour.isTransparent() ? colourThumb : item.colour;

        if (!item.isEnabled)
            textCol = textCol.withAlpha(0.4f);

        if (item.isTicked && isHighlighted)
        {
            g.setColour(colourAccent.withAlpha(0.2f));
            g.fillRect(area);
            textCol = Colours::white;
        }
        else if (isHighlighted)
        {
            g.setColour(colourAccent.withAlpha(0.2f));
            g.fillRect(area);
            textCol = colourAccent;
        }
        else if (item.isTicked)
        {
            g.setColour(colourAccent.withAlpha(0.1f));
            g.fillRect(area);
            textCol = Colours::white;
        }

        g.setColour(textCol);
        g.setFont(14.0f);
        g.drawText(item.text, area.reduced(4), Justification::centredLeft, true);
    }
    
    void drawPopupMenuBackground (juce::Graphics& g, int width, int height) override
    {
        float cornerRadius = 3.0f;
        auto area = juce::Rectangle<float>(0, 0, width, height).reduced(1,1);
        
        g.fillAll (juce::Colours::black);

        juce::ColourGradient gradient (colourBackground.darker(0.4f), 0, 0,
                                       colourBackground.darker(0.98f), 0, (float)height, false);
        g.setGradientFill(gradient);
        g.fillRoundedRectangle(area, cornerRadius);

        g.setColour(colourAccent);
        g.drawRoundedRectangle(area, cornerRadius, 1.0f);
    }

    void drawButtonBackground (juce::Graphics& g, juce::Button& button,
                               const juce::Colour& /*backgroundColour*/,
                               bool isHovered, bool isPressed) override
    {
        auto bounds = button.getLocalBounds().reduced(1, 1).toFloat();
        float cornerSize = 3.0f;

        juce::Colour fill = colourBackground.darker(0.8f);
        juce::Colour outline = colourOutline.withAlpha(0.75f);

        if (isPressed)
        {
            fill = colourAccent.darker(0.2f);
            outline = colourAccent;
        }
        else if (isHovered)
        {
            fill = colourAccent.withAlpha(0.3f);
            outline = colourAccent.brighter(0.2f);
        }

        auto connected = button.getConnectedEdgeFlags();
        bool curveTopLeft     = !(connected & juce::Button::ConnectedOnLeft || connected & juce::Button::ConnectedOnTop);
        bool curveTopRight    = !(connected & juce::Button::ConnectedOnRight || connected & juce::Button::ConnectedOnTop);
        bool curveBottomLeft  = !(connected & juce::Button::ConnectedOnLeft || connected & juce::Button::ConnectedOnBottom);
        bool curveBottomRight = !(connected & juce::Button::ConnectedOnRight || connected & juce::Button::ConnectedOnBottom);

        juce::Path path;
        path.addRoundedRectangle(bounds.getX(), bounds.getY(),
                                 bounds.getWidth(), bounds.getHeight(),
                                 cornerSize, cornerSize,
                                 curveTopLeft, curveTopRight,
                                 curveBottomLeft, curveBottomRight);

        g.setColour(fill);
        g.fillPath(path);

        g.setColour(outline);
        g.strokePath(path, juce::PathStrokeType(1.2f));
    }
    
    void drawLabel (Graphics& g, Label& label) override
    {
        // Skip styling for labels that belong to ComboBoxes
        auto* combo = dynamic_cast<ComboBox*>(label.getParentComponent());
        if (combo) {
            LookAndFeel_V4::drawLabel(g, label);
            return;
        }
        
        bool isLinearBarVertical = false;
        if (auto* slider = dynamic_cast<Slider*>(label.getParentComponent())) {
            auto style = slider->getSliderStyle();
            if (style == Slider::LinearBarVertical) {
                isLinearBarVertical = true;
            }
        }
        
        float cornerSize = 3.0f;

        g.setColour(colourBackground.darker(0.8f));
        g.fillRoundedRectangle(label.getLocalBounds().reduced(1, 1).toFloat(), cornerSize);

        if(!(label.isBeingEdited() && isLinearBarVertical)){
            g.setColour(Colours::white);
            g.setFont(getLabelFont(label));
            g.drawText(label.getText(), label.getLocalBounds().reduced(3),
                       label.getJustificationType(), true);
        }

        g.setColour(label.isBeingEdited() ? colourAccent
                                          : colourOutline.withAlpha(0.75f));
        g.drawRoundedRectangle(label.getLocalBounds().reduced(1, 1).toFloat(), cornerSize, 1.0f);
    }

    void drawProgressBar (Graphics& g, ProgressBar& /*bar*/,
                          int width, int height, double progress,
                          const String& textToShow) override
    {
        auto bounds = Rectangle<float>(0, 0, (float)width, (float)height).reduced(1.0f);
        float cornerSize = 3.0f;

        g.setColour(colourBackground.darker(0.7f));
        g.fillRoundedRectangle(bounds, cornerSize);

        g.setColour(colourAccent);
        auto filled = bounds.withWidth((float)width * (float)progress);
        g.fillRoundedRectangle(filled, cornerSize);

        if (!textToShow.isEmpty())
        {
            g.setColour(Colours::black);
            g.setFont(15.0f);
            g.drawText(textToShow, bounds.toNearestInt(), Justification::centred);
        }

        g.setColour(colourOutline.withAlpha(0.7f));
        g.drawRoundedRectangle(bounds, cornerSize, 2.0f);
    }
    
    void drawTextEditorOutline (Graphics& g, int width, int height, TextEditor& editor) override
    {
        auto bounds = Rectangle<float>(0, 0, (float)width, (float)height).reduced(0.5f);
        float cornerSize = 3.0f;

        Colour outlineCol = editor.hasKeyboardFocus(true) ? colourAccent
                                                          : colourOutline.withAlpha(0.6f);
        g.setColour(outlineCol);
        g.drawRoundedRectangle(bounds, cornerSize, 1.4f);
    }
};
