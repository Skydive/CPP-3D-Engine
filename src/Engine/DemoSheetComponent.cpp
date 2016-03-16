#include "DemoSheetComponent.h"

#include "Engine.h"
#include "Model.h"
#include "Texture.h"
#include "Config.h"

#define PI 3.141592f

void DemoSheetComponent::BeginPlay()
{
	Super::BeginPlay();
    LoadConfigData();
}

void DemoSheetComponent::LoadConfigData()
{
    Config OscillationConfig = Config("./Oscillation.cfg");
    ConfigWidth = OscillationConfig.GetValueFloat("SheetWidth", 25);
    ConfigDepth = OscillationConfig.GetValueFloat("SheetDepth", 25);
    ConfigWidthSep = OscillationConfig.GetValueFloat("SheetWidthSep", 7);
    ConfigDepthSep = OscillationConfig.GetValueFloat("SheetDepthSep", 7);
    ConfigPeriod = OscillationConfig.GetValueFloat("StarterPeriod", 1);
    ConfigVisibleFrequency = OscillationConfig.GetValueFloat("VisibleFrequency", 2);
    ConfigAmplitude = OscillationConfig.GetValueFloat("StarterAmplitude", 8);
    ConfigDampingFactor = OscillationConfig.GetValueFloat("DampingFactor", 1);
}

void DemoSheetComponent::Tick(float dt)
{
    Super::Tick(dt);
	static float ConfigTime = 0;
    ConfigTime += dt;
    if(ConfigTime > 5)
    {
        LoadConfigData();
        ConfigTime = 0;
    }
    ElapsedTime += dt;
}

void DemoSheetComponent::Render()
{
	/*
	float numx = ConfigWidth, sepx = ConfigWidthSep;
    float numz = ConfigDepth, sepz = ConfigDepthSep;

    float AngularVelocity = 2*PI/ConfigPeriod;

	GameEngine->GameRenderer->CurrentModel = Model;
	GameEngine->GameRenderer->CurrentTexture = Texture;

    for(float x=0; x < numx*sepx; x += sepx)
    {
        for(float z=0; z < numz*sepz; z += sepz)
        {
            int spherex = x/sepx;
			float DampenedAmplitude = ConfigAmplitude*(spherex/numx)*(1/ConfigDampingFactor);
			glm::vec3 SphereLocation = glm::vec3(x, DampenedAmplitude*glm::sin(AngularVelocity*ElapsedTime + (2*PI*spherex/numx)*ConfigVisibleFrequency), z);
			for(auto& shader : RenderShaders)
			{
				// TODO: Sort this horrible code out. Make them arguments perhaps?
				GameEngine->GameRenderer->CurrentShader = shader.get();
				GameEngine->GameRenderer->RenderModel(Location, Rotation, Scale, Color);
			}

		}
    }*/
}
