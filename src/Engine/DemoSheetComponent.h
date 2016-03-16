#pragma once
#include "RenderComponent.h"

class DemoSheetComponent : public RenderComponent
{
public:
    virtual void BeginPlay() override;
    virtual void Tick(float dt) override;
    virtual void Render() override;
private:
    // Configurables
    void LoadConfigData();
    float ConfigWidth, ConfigDepth;
    float ConfigWidthSep, ConfigDepthSep;
    float ConfigPeriod, ConfigVisibleFrequency;
    float ConfigAmplitude, ConfigDampingFactor;

    float ElapsedTime;
    using Super = RenderComponent;
};
