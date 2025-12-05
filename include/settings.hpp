#pragma once
#include "beatsaber-hook/shared/utils/typedefs.h"



struct float3 {
    float x;
    float y;
    float z;
};

struct RoomSettings {
    float3 center;
    float rotation;
};

struct SelectedProfile {
    // bool
    int builtIn;
    int index;
};

struct ControllerSettings
{
     float3 position; //Field offset: 0x0
     float3 rotation; //Field offset: 0xC
     // bool
     int hapticFeedback; //Field offset: 0x18
     SelectedProfile selectedProfile; //Field offset: 0x1C
};

struct AudioSettings
{
  float volume; //Field offset: 0x0
  float ambientVolumeScale; //Field offset: 0x4
  float latency; //Field offset: 0x8
  int overrideLatency; //Field offset: 0xC
};

struct MiscSettings
{
    enum ResponseLevel
    {
        Instant = 0,
        Long = 1,
    };

    Il2CppString* language; //Field offset: 0x0
    ResponseLevel pauseButtonResponse; //Field offset: 0x8
};


struct SmoothCameraSettings
{
 int enabled; //Field offset: 0x0
 float fov; //Field offset: 0x4
 float smoothPosition; //Field offset: 0x8
 float smoothRotation; //Field offset: 0xC
 int thirdPersonEnabled; //Field offset: 0x10
 float3 thirdPersonPosition; //Field offset: 0x14
 float3 thirdPersonRotation; //Field offset: 0x20
};

struct QualitySettings
{
     enum BloomQuality
    {
        Game = 0,
        LightBaking = 1,
    };

    enum MainEffectOption
    {
        Off = 0,
        Game_ = 1,
        LightBaking_ = 2,
    };
    enum MirrorQuality
    {
        Off_ = 0,
        Low = 1,
        Medium = 2,
        High = 3,
    };

     enum ObstacleQuality
    {
        Low_ = 0,
        Medium_ = 1,
        High_ = 2,
    };

  float renderViewportScale; //Field offset: 0x0
  float vrResolutionScale; //Field offset: 0x4
  float menuVRResolutionScaleMultiplier; //Field offset: 0x8
  int antiAliasingLevel; //Field offset: 0xC
  int targetFramerate; //Field offset: 0x10
  int vSyncCount; //Field offset: 0x14
  int maxQueuedFrames; //Field offset: 0x18
  MainEffectOption mainEffect; //Field offset: 0x1C
  BloomQuality bloom; //Field offset: 0x20
  MirrorQuality mirror; //Field offset: 0x24
  ObstacleQuality obstacles; //Field offset: 0x28
  bool screenDisplacementEffects; //Field offset: 0x2C
  bool smokeGraphics; //Field offset: 0x2D
  bool depthTexture; //Field offset: 0x2E
  bool burnMarkTrails; //Field offset: 0x2F
  int maxShockwaveParticles; //Field offset: 0x30
  int maxNumberOfCutSoundEffects; //Field offset: 0x34
};

struct QuestSettings {
    enum FoveatedRenderingLevel
    {
        Off = 0,
        Low = 1,
        Medium = 2,
        High = 3,
        HighTop = 4,
    };

    enum SuggestedPerformanceLevel
    {
        Default = 0,
        PowerSavings = 1,
        SustainedLow = 2,
        SustainedHigh = 3,
        Boost = 4,
    };

    SuggestedPerformanceLevel cpuLevel; //Field offset: 0x0
    SuggestedPerformanceLevel gpuLevel; //Field offset: 0x4
    FoveatedRenderingLevel foveatedRenderingMenu; //Field offset: 0x8
    FoveatedRenderingLevel foveatedRenderingGameplay; //Field offset: 0xC
    bool eyeTrackedFoveatedRendering; //Field offset: 0x10
    bool dynamicFoveatedRendering; //Field offset: 0x11
};

struct int2 {
 int x; //Field offset: 0x0
 int y; //Field offset: 0x4
};

struct WindowSettings {
    bool fullscreen; //Field offset: 0x0
    int2 resolution; //Field offset: 0x4
};

struct CustomServerSettings {
    bool useCustomEnvironment;
    bool forceGameLiftEnvironment; //Field offset: 0x1
    StringW hostName;
};

struct PerformanceToolSettings {
    bool recordFps; //Field offset: 0x0
    bool showFps; //Field offset: 0x1
    bool showMemory; //Field offset: 0x2
    bool saveScreenshot; //Field offset: 0x3
};

struct DebugSettings {
    bool showBeatmapLevelVersion; //Field offset: 0x0
    bool disableVRTrackingInAutoplayPS4; //Field offset: 0x1
};

struct Settings {
    RoomSettings room;
    ControllerSettings controller;
    SmoothCameraSettings smoothCamera;
    AudioSettings audioSettings;
    MiscSettings misc;
    QualitySettings quality;
    QuestSettings quest;
    WindowSettings windows;
    CustomServerSettings customServer;
    PerformanceToolSettings performanceTools;
    DebugSettings debug;
};


DEFINE_IL2CPP_ARG_TYPE(Settings, "BeatSaber.Settings", "Settings");