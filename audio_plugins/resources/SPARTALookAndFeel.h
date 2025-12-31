#pragma once

namespace ColoursUI {
    const juce::Colour bgDark1          { 0xff12242e }; //const juce::Colour bgDark1   { 0xff142833 };
    const juce::Colour bgDark2          { 0xff041316 }; //const juce::Colour bgDark2   { 0xff041518 };
    const juce::Colour panelFill        { 0x0ef4f4f4 }; //const juce::Colour panelFill { 0x10f4f4f4 };
    const juce::Colour panelFillLight   { 0x07f4f4f4 }; //const juce::Colour panelFillLight { 0x08f4f4f4 };
    const juce::Colour panelStroke { 0x67a0a0a0 };
    const juce::Colour panelStrokeLight { 0x35a0a0a0 };
    const juce::Colour textWhite { juce::Colours::white };
    const juce::Colour borderGrey { 0xffb9b9b9 };
    const juce::Colour borderGreyDarker { borderGrey.darker(0.2f) };
    const juce::Colour accentCyan { 0xff00d8df };
    const juce::Colour accentOrange { 0xffdf8400 }; 
}

inline void drawPanelRect(juce::Graphics& g,
                          juce::Rectangle<float> r,
                          juce::Colour fill,
                          juce::Colour stroke,
                          float thickness = 1)
{
    g.setColour(fill);
    g.fillRect(r);

    auto topTint    = fill.withAlpha(0.0f);
    auto bottomTint = fill.withAlpha(0.03f);
    g.setGradientFill(juce::ColourGradient{
        topTint,
        0.0f, (float)r.getY(),
        bottomTint,
        0.0f, (float)r.getBottom(),
        false
    });
    g.fillRect(r);
    g.setColour(stroke);
    g.drawRect(r, thickness);
}

inline void drawPanel(juce::Graphics& g,
                      juce::Rectangle<float> r,
                      juce::Colour fill,
                      juce::Colour stroke,
                      float thickness = 1,
                      float cornerSize = 5.0f)
{
    juce::Rectangle<float> rr = r.reduced(2.0f, 2.0f);
    g.setColour(fill);
    g.fillRoundedRectangle(rr, cornerSize);

    auto topTint    = fill.withAlpha(0.0f);
    auto bottomTint = fill.withAlpha(0.03f);
    g.setGradientFill(juce::ColourGradient{
        topTint,
        0.0f, (float)r.getY(),
        bottomTint,
        0.0f, (float)r.getBottom(),
        false
    });
    g.fillRoundedRectangle(rr, cornerSize);
    g.setColour(stroke);
    g.drawRoundedRectangle(rr, cornerSize, thickness);
}

inline void drawVerticalGradient(juce::Graphics& g, juce::Rectangle<int> r, juce::Colour top, juce::Colour bottom)
{
    g.setGradientFill(juce::ColourGradient(top, r.getX(), r.getY(), bottom, r.getX(), r.getBottom(), false));
    g.fillRect(r);
}

inline void drawLabel(juce::Graphics& g, juce::Rectangle<int> r, const juce::String& text,
                      float size, juce::Justification just = juce::Justification::centredLeft,
                      juce::Colour colour = ColoursUI::textWhite,
                      juce::Font::FontStyleFlags style = juce::Font::bold)
{
    g.setColour(colour);

    static auto interRegular = juce::Typeface::createSystemTypefaceFor(
        BinaryData::InterRegular_ttf,
        BinaryData::InterRegular_ttfSize
    );

    static auto interBold = juce::Typeface::createSystemTypefaceFor(
        BinaryData::InterBold_ttf,
        BinaryData::InterBold_ttfSize
    );

    juce::FontOptions font = juce::FontOptions(
        (style & juce::Font::bold) ? interBold : interRegular
    ).withHeight(size).withKerningFactor(0.03f);
    
    g.setFont(font);
    g.drawText(text, r, just, true);
}

inline void drawPluginBackgroundAndBanner(juce::Graphics& g,
                                          juce::Rectangle<int> bounds)
{
    using namespace ColoursUI;
    
    const int w = bounds.getWidth();
    const int h = bounds.getHeight();
    const float cornerSize = 12.0f;
    auto bgNewDark1 = bgDark1.brighter(0.06f);
    auto bgNewDark2 = bgDark2.darker(0.3f);
    
    g.fillAll(borderGreyDarker);

    /* Vertical gradient */
    {
        juce::ColourGradient grad(bgNewDark1, 0.f, 30.f,
                                  bgNewDark1, 0.f, float(h), false);

        grad.addColour(0.0, bgNewDark1);
        grad.addColour(0.1, bgDark1);
        grad.addColour(0.3, bgDark2);
        grad.addColour(0.5, bgNewDark2);
        grad.addColour(0.7, bgDark2);
        grad.addColour(0.9, bgDark1);
        grad.addColour(1.0, bgNewDark1);

        g.setGradientFill(grad);
        g.fillRoundedRectangle({0, 0, (float)w, (float)h}, cornerSize);
    }
    
    /* Bottom right radial gradient */
    {
        const float diameter = (float) juce::jmax(bounds.getWidth(), bounds.getHeight());
        const float cx = (float) bounds.getRight();
        const float cy = (float) bounds.getBottom();

        juce::Colour baseColour = Colours::black;
        juce::Colour centre = baseColour.withAlpha(0.25f);
        juce::Colour edge   = baseColour.withAlpha(0.0f);

        juce::ColourGradient radial(
            centre, cx, cy,
            edge,   cx, cy + diameter * 0.5f,
            true
        );

        g.setGradientFill(radial);
        g.fillEllipse(cx - diameter * 0.5f,
                      cy - diameter * 0.5f,
                      diameter,
                      diameter);
    }
    
    /* Top banner */
    {
        juce::Rectangle<float> r {1.f, 1.f, float(w - 2), 32.f};
        g.setGradientFill(juce::ColourGradient(bgDark2,
                                               r.getX(), r.getBottom(),
                                               bgDark1,
                                               r.getRight(), r.getY(),
                                               false));
        
        juce::Path p;
        p.addRoundedRectangle(r.getX(), r.getY(), r.getWidth(), r.getHeight(), 12.0f, 12.0f, true, true, false, false);
        g.fillPath(p);
        g.setColour(borderGreyDarker);
        g.strokePath(p, juce::PathStrokeType(2.0f));
    }

    /* Outer border */
    g.setColour(borderGreyDarker);
    g.drawRoundedRectangle({1, 1, (float)w-2, (float)h-2}, 12.0f, 2.0f);
    g.drawRoundedRectangle({0, 0, (float)w, (float)h}, 11.0f, 3.0f);
}


class SPARTALookAndFeel : public juce::LookAndFeel_V4
{
public:
    // Color Palette
    Colour colourBackground = Colour(70, 75, 85);
    Colour colourAccent = Colour(70, 180, 220);
    Colour colourThumb  = Colour(140, 190, 225);
    Colour colourOutline = Colour(200, 240, 255);
    const float disabledAlpha = 0.35f;
    const float cornerSize = 3.0f;
    
    juce::Typeface::Ptr getTypefaceForFont(const juce::Font& font) override
    {
        static auto interRegular = juce::Typeface::createSystemTypefaceFor(
            BinaryData::InterRegular_ttf,
            BinaryData::InterRegular_ttfSize
        );

        static auto interBold = juce::Typeface::createSystemTypefaceFor(
            BinaryData::InterBold_ttf,
            BinaryData::InterBold_ttfSize
        );

        return font.isBold() ? interBold : interRegular;
    }

    void drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                           float sliderPos, float /*minSliderPos*/, float /*maxSliderPos*/,
                           const Slider::SliderStyle style, Slider& slider) override
    {
        const bool isHovered = slider.isMouseOverOrDragging() && slider.isEnabled();
        auto active = isHovered ? colourAccent.darker(0.1f): colourAccent.darker(0.3f);

        if (style == Slider::LinearHorizontal)
        {
            float trackHeight = 6.0f;
            float centerY = y + height * 0.5f;
            Rectangle<float> track (x, centerY - trackHeight * 0.5f, width, trackHeight);
            g.setColour(colourBackground);
            if (! slider.isEnabled()) g.setOpacity(disabledAlpha);
            g.fillRoundedRectangle(track, 3.0f);

            Rectangle<float> fill (x, centerY - trackHeight * 0.5f, sliderPos - x, trackHeight);
            g.setColour(active);
            if (! slider.isEnabled()) g.setOpacity(disabledAlpha);
            g.fillRoundedRectangle(fill, 3.0f);

            float r = isHovered ? 8.0f : 7.0f;
            g.setColour(colourThumb.darker(0.2f));
            if (! slider.isEnabled()) g.setOpacity(disabledAlpha);
            g.fillEllipse(sliderPos - r, centerY - r, r * 2, r * 2);
            g.setColour(colourOutline.darker(0.3f));
            if (! slider.isEnabled()) g.setOpacity(disabledAlpha);
            g.drawEllipse(sliderPos - r, centerY - r, r * 2, r * 2, 1.0f);
            if (isHovered) {
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
            if (! slider.isEnabled()) g.setOpacity(disabledAlpha);
            g.fillRoundedRectangle(track, 3.0f);

            float r = isHovered ? 8.0f : 7.0f;
            Rectangle<float> fill(centerX - trackWidth * 0.5f, sliderPos, trackWidth, y + height -sliderPos);
            g.setColour(active);
            if (! slider.isEnabled()) g.setOpacity(disabledAlpha);
            g.fillRoundedRectangle(fill, 3.0f);

            g.setColour(colourThumb.darker(0.2f));
            if (! slider.isEnabled()) g.setOpacity(disabledAlpha);
            g.fillEllipse(centerX - r, sliderPos - r, r * 2, r * 2);
            g.setColour(colourOutline.darker(0.3f));
            if (! slider.isEnabled()) g.setOpacity(disabledAlpha);
            g.drawEllipse(centerX - r, sliderPos - r, r * 2, r * 2, 1.0f);
            if (isHovered) {
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
        const bool isHovered = slider.isMouseOverOrDragging() && slider.isEnabled();

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
            if (! slider.isEnabled()) g.setOpacity(disabledAlpha);
            g.strokePath(arc, juce::PathStrokeType(isHovered ? 2.5f : 1.7f));
        }
        
        juce::Colour activeColour = isHovered ? colourAccent : colourOutline;

        // face
        g.setColour(colourBackground.darker(0.8f));
        if (! slider.isEnabled()) g.setOpacity(disabledAlpha);
        g.fillEllipse(centerX - radius, centerY - radius, radius * 2.0f, radius * 2.0f);

        g.setColour(activeColour);
        if (! slider.isEnabled()) g.setOpacity(disabledAlpha);
        g.drawEllipse(centerX - radius, centerY - radius, radius * 2.0f, radius * 2.0f,
                      isHovered ? 2.0f : 1.0f);

        float centerRadius = radius * 0.2f;
        g.setColour(activeColour);
        if (slider.isEnabled()){
            g.fillEllipse(centerX - centerRadius, centerY - centerRadius,
                          centerRadius * 2.0f, centerRadius * 2.0f);
        }

        float pointerLength = radius - 2.0f;
        float pointerThickness = 2.0f;

        juce::Path pointer;
        pointer.startNewSubPath(0.0f, 0.0f);
        pointer.lineTo(0.0f, -pointerLength);

        g.setColour(activeColour);
        if (! slider.isEnabled()) g.setOpacity(disabledAlpha);
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
        if (!button.isEnabled()) g.setOpacity(disabledAlpha);
        g.fillRoundedRectangle(squareBounds, 2*cornerSize);
        g.setColour(outline);
        if (!button.isEnabled()) g.setOpacity(disabledAlpha);
        g.drawRoundedRectangle(squareBounds, 2*cornerSize, 1.2f);

        // Draw tick if toggled
        if (button.getToggleState())
        {
            Path tick = getTickShape(7.1f);
            RectanglePlacement placement (RectanglePlacement::centred);
            g.setColour(colourThumb.brighter(0.5f));
            if (! button.isEnabled()) g.setOpacity(disabledAlpha);
            g.fillPath(tick, placement.getTransformToFit(tick.getBounds(), squareBounds.reduced(3.0f)));
        }
    }

    void drawButtonBackground (juce::Graphics& g, juce::Button& button,
                               const juce::Colour& /*backgroundColour*/,
                               bool isHovered, bool isPressed) override
    {
        auto bounds = button.getLocalBounds().reduced(1, 1).toFloat();

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

        g.setColour(colourBackground.darker(0.7f));
        g.fillRoundedRectangle(bounds, cornerSize);

        g.setColour(colourAccent.darker(0.3f));
        auto filled = bounds.withWidth((float)width * (float)progress);
        g.fillRoundedRectangle(filled, cornerSize);

        if (!textToShow.isEmpty())
        {
            g.setColour(Colours::white);
            g.setFont(15.0f);
            g.drawText(textToShow, bounds.toNearestInt(), Justification::centred);
        }

        g.setColour(colourOutline.withAlpha(0.7f));
        g.drawRoundedRectangle(bounds, cornerSize, 2.0f);
    }
    
    void drawTextEditorOutline (Graphics& g, int width, int height, TextEditor& editor) override
    {
        auto bounds = Rectangle<float>(0, 0, (float)width, (float)height).reduced(0.5f);

        Colour outlineCol = editor.hasKeyboardFocus(true) ? colourAccent
                                                          : colourOutline.withAlpha(0.6f);
        g.setColour(outlineCol);
        g.drawRoundedRectangle(bounds, cornerSize, 1.4f);
    }

    void drawComboBox (juce::Graphics& g, int width, int height, bool isButtonDown,
                       int /*buttonX*/, int /*buttonY*/, int /*buttonW*/, int /*buttonH*/,
                       juce::ComboBox& box) override
    {
        auto bounds = juce::Rectangle<float>(0, 0, (float)width, (float)height);

        juce::Colour fill = colourBackground.darker(0.8f);
        juce::Colour outline = colourOutline.withAlpha(0.7f);

        if (isButtonDown)
        {
            fill = colourAccent.darker(0.25f);
            outline = colourAccent;
        }

        g.setColour(fill);
        if (! box.isEnabled()) g.setOpacity(disabledAlpha);
        g.fillRoundedRectangle(bounds.reduced(1.0f), cornerSize);

        g.setColour(outline);
        if (! box.isEnabled()) g.setOpacity(disabledAlpha);
        g.drawRoundedRectangle(bounds.reduced(1.0f), cornerSize, 1.2f);
        
        Rectangle<int> arrowZone (width - 24, 0, 16, height);
        Path path;
        path.startNewSubPath ((float) arrowZone.getX() + 3.0f, (float) arrowZone.getCentreY() - 2.0f);
        path.lineTo ((float) arrowZone.getCentreX(), (float) arrowZone.getCentreY() + 3.0f);
        path.lineTo ((float) arrowZone.getRight() - 3.0f, (float) arrowZone.getCentreY() - 2.0f);
        g.strokePath (path, PathStrokeType (2.0f));
    }
};
