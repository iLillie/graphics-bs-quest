#include "main.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "logger.hpp"
#include "modInfo.hpp"
#include "scotland2/shared/modloader.h"
#include <cmath>
#include <cstddef>
#include <cstdint>

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
struct GameObject : Il2CppObject {};
struct String : StringW {};
struct BoolSO : Il2CppObject {};
struct Renderer : Il2CppObject {};
struct Material : Il2CppObject {};
struct SystemBool {
    bool m_value;
};

struct Behaviour : Il2CppObject{};
struct MonoBehaviour : Behaviour{};
struct ImageEffectController : MonoBehaviour{};
struct MainEffectContainerSO : Il2CppObject{};
struct MainEffectSO : Il2CppObject{};
struct PyramidBloomMainEffectSO : MainEffectSO{};
struct MainEffectCore{};

struct AllocationRootWithSalt
{
    unsigned m_Salt;
    unsigned m_RootReferenceIndex;
};

enum MemLabelIdentifier
{
};

struct MemLabelId
{
    AllocationRootWithSalt m_RootReferenceWithSalt;
    MemLabelIdentifier identifier;
};

namespace core
{
    template<class T>
    class StringStorageDefault
    {
        enum
        {
            kInternalBufferCapacity = 0xF,
        };
    protected:
        T* m_data;

        union
        {
            size_t m_capacity;
            T m_internal[(kInternalBufferCapacity + 1) / sizeof(T)];
        };

        size_t m_size;
        MemLabelId m_label;
    };
};

namespace core
{
    template<class T, class TStorage = StringStorageDefault<T>>
    class basic_string : TStorage
    {
    public:
        basic_string() = default;

     T const* c_str() const {
         if (this->m_size > this->m_capacity) {
            return this->m_data;
         }

         return static_cast<T const*>(this->m_internal);
     }

     size_t length() const;
        basic_string& operator=(const T* copyStr);
        static basic_string create_from_external(const T* referenceStr, const MemLabelId& label);
        static basic_string create_from_external(const T* referenceStr, size_t referenceStrLen, const MemLabelId& label);
    };
};


DEFINE_IL2CPP_ARG_TYPE(GameObject*, "UnityEngine", "GameObject");
DEFINE_IL2CPP_ARG_TYPE(String*, "System", "String");
DEFINE_IL2CPP_ARG_TYPE(BoolSO*, "", "BoolSO");
DEFINE_IL2CPP_ARG_TYPE(SystemBool, "System", "Boolean");
DEFINE_IL2CPP_ARG_TYPE(Renderer*, "UnityEngine", "Renderer");
DEFINE_IL2CPP_ARG_TYPE(Material*, "UnityEngine", "Material");
DEFINE_IL2CPP_ARG_TYPE(ImageEffectController*, "", "ImageEffectController");
DEFINE_IL2CPP_ARG_TYPE(MainEffectContainerSO*, "", "MainEffectContainerSO");
DEFINE_IL2CPP_ARG_TYPE(MainEffectSO*, "", "MainEffectSO");
DEFINE_IL2CPP_ARG_TYPE(MainEffectCore*, "", "MainEffectCore");
DEFINE_IL2CPP_ARG_TYPE(PyramidBloomMainEffectSO*, "", "PyramidBloomMainEffectSO");
DEFINE_IL2CPP_ARG_TYPE(MonoBehaviour*, "UnityEngine", "MonoBehaviour");
DEFINE_IL2CPP_ARG_TYPE(Behaviour*, "UnityEngine", "Behaviour");

MAKE_HOOK_FIND_CLASS_UNSAFE_STATIC(MainEffectCore_SetGlobalShaderValues, "", "MainEffectCore", "SetGlobalShaderValues", void, float baseColorBoost, float baseColorBoostThreshold) {
    baseColorBoost = 0.15f;
    baseColorBoostThreshold = 0.0f;
    MainEffectCore_SetGlobalShaderValues(baseColorBoost, baseColorBoostThreshold);
}


MAKE_HOOK_FIND_CLASS_UNSAFE_INSTANCE(MainEffectController_OnPreRender, "", "MainEffectController", "OnPreRender", void, Il2CppObject* self) {
    auto imageEffectController = *il2cpp_utils::GetFieldValue<ImageEffectController*>(self, "_imageEffectController");
    auto _mainEffectContainer = *il2cpp_utils::GetFieldValue<MainEffectContainerSO*>(self, "_mainEffectContainer");
    auto mainEffect = *il2cpp_utils::GetFieldValue<MainEffectSO*>(_mainEffectContainer, "_mainEffect");
    il2cpp_utils::RunMethod<void>(mainEffect, "PreRender");
    il2cpp_utils::SetPropertyValue(imageEffectController, "enabled", true);
    auto value = SystemBool{true};
    il2cpp_utils::RunMethod<void>(reinterpret_cast<MainEffectCore*>(il2cpp_utils::GetClassFromName("", "MainEffectCore")), "UpdateKeyword", value);
}

MAKE_HOOK_FIND_CLASS_UNSAFE_INSTANCE(SettingsApplicatorSO_ApplyGraphicSettings, "", "SettingsApplicatorSO", "ApplyGraphicSettings", void, Il2CppObject* self, Settings settings, int other) {
    settings.quality.mainEffect = QualitySettings::Game_;
    settings.quality.bloom = QualitySettings::Game;
    settings.quality.obstacles = QualitySettings::High_;
    settings.quality.smokeGraphics = true;
    settings.quality.screenDisplacementEffects = true;
    settings.quality.maxShockwaveParticles = 2;
    settings.quality.burnMarkTrails = true;
    settings.quality.depthTexture = true;
    settings.quality.mirror = QualitySettings::High;
    settings.quality.antiAliasingLevel = 0;
    SettingsApplicatorSO_ApplyGraphicSettings(self, settings, other);
}

MAKE_HOOK_FIND_CLASS_UNSAFE_STATIC(SettingValidations_AdjustQuest3, "BeatSaber.Settings", "SettingValidations", "AdjustQuest3", void, Settings* settings) {
    //SettingValidations_AdjustQuest3(settings);
    settings->quality.mainEffect = QualitySettings::Game_;
    settings->quality.bloom = QualitySettings::Game;
    settings->quality.obstacles = QualitySettings::High_;
    settings->quality.smokeGraphics = true;
    settings->quality.screenDisplacementEffects = true;
    settings->quality.maxShockwaveParticles = 2;
    settings->quality.burnMarkTrails = true;
    settings->quality.depthTexture = true;
    settings->quality.mirror = QualitySettings::High;
    settings->quality.antiAliasingLevel = 0;
}

MAKE_HOOK_FIND_CLASS_UNSAFE_INSTANCE(GraphicSettingsConditionalActivator_GetGraphicsActivatorType, "", "GraphicSettingsConditionalActivator", "Start", bool, Il2CppObject* self) {
    Logger.info("GraphicsSettingsConditional Start");
    auto gameObject = *il2cpp_utils::RunMethod<GameObject*>(self, "get_gameObject").as_optional_result().value_or(nullptr);
    auto name = *il2cpp_utils::GetPropertyValue<String*>(gameObject, "name").as_optional_result().value_or(nullptr);
    auto name2 = il2cpp_utils::detail::to_string(static_cast<StringW>(name));
    Logger.info("GraphicsSettingsConditional END: {}", name2);

    return true;
}

MAKE_HOOK_FIND_CLASS_UNSAFE_INSTANCE(ObstacleController_InitGraphics, "", "ObstacleController", "InitGraphics", void, Il2CppObject* self, Settings settings) {
    settings.quality.screenDisplacementEffects = true;
    ObstacleController_InitGraphics(self, settings);
}

MAKE_HOOK_FIND_CLASS_UNSAFE_INSTANCE(ConditionalMaterialSwitcher_Awake, "", "ConditionalMaterialSwitcher", "Awake", void, Il2CppObject* self) {
    auto gameObject = *il2cpp_utils::RunMethod<GameObject*>(self, "get_gameObject").as_optional_result().value_or(nullptr);

    if (gameObject == nullptr) {
        Logger.info("Nullptr found!");
        ConditionalMaterialSwitcher_Awake(self);
        return;
    }

    auto name = *il2cpp_utils::GetPropertyValue<String*>(gameObject, "name").as_optional_result().value_or(nullptr);

    if (name == nullptr) {
        Logger.info("no name string found!");
        ConditionalMaterialSwitcher_Awake(self);
        return;
    }

    auto valueBool = *il2cpp_utils::GetFieldValue<BoolSO*>(self, "_value").value_or(nullptr);
    auto value = *il2cpp_utils::GetPropertyValue<SystemBool, false>(valueBool, "value").as_optional_result().value_or(nullptr);

    auto name2 = il2cpp_utils::detail::to_string(static_cast<StringW>(name));

    if (name2 == "NoteCube" || name2 == "NoteArrow" || name2 == "SaberGlowingEdges" || name2 == "ObstacleFrame" || name2 == "SaberTrailRendererHologram(Clone)")  {
        value.m_value = true;
        il2cpp_utils::SetPropertyValue<false>(valueBool, "value", value);
    }

    ConditionalMaterialSwitcher_Awake(self);
}

MAKE_HOOK_FIND_CLASS_UNSAFE_INSTANCE(ConditionalActivation_Awake, "", "ConditionalActivation", "Awake", void, Il2CppObject* self) {
    auto gameObject = *il2cpp_utils::GetPropertyValue<GameObject*>(self, "gameObject").as_optional_result().value_or(nullptr);
    auto name = *il2cpp_utils::GetPropertyValue<String*>(gameObject, "name").as_optional_result().value_or(nullptr);
    auto valueBool = *il2cpp_utils::GetFieldValue<BoolSO*>(self, "_value").value_or(nullptr);
    auto value = *il2cpp_utils::GetPropertyValue<SystemBool>(valueBool, "value").as_optional_result().value_or(nullptr);
    auto name2 = il2cpp_utils::detail::to_string(static_cast<StringW>(name));

    if ( name2 == "ObstacleFrame")  {
        value.m_value = true;
        il2cpp_utils::SetPropertyValue(valueBool, "value", value);
    }

    ConditionalActivation_Awake(self);
}

MAKE_HOOK(hGlslGpuProgramGLES_CompileProgramImpl, nullptr, void,
    unsigned int& unknown,
    core::basic_string<char,core::StringStorageDefault<char>> const& shaderName,
    core::basic_string<char, core::StringStorageDefault<char>> const& vertex,
    core::basic_string<char, core::StringStorageDefault<char>> const& fragment,
    core::basic_string<char, core::StringStorageDefault<char>> const& geometry,
    core::basic_string<char, core::StringStorageDefault<char>> const& hull,
    core::basic_string<char, core::StringStorageDefault<char>> const& domain,
    int& shader, int a, int * b, int *c, int* d) {
    Logger.info("hGlslGpuProgramGLES_CompileProgramImpl: {}", shaderName.c_str());
    hGlslGpuProgramGLES_CompileProgramImpl(unknown, shaderName, vertex, fragment, geometry, hull, domain, shader, a, b, c, d);
}

/// @brief Called at the early stages of game loading
/// @param info The mod info.  Update this with your mod's info.
/// @return
MOD_EXPORT_FUNC void setup(CModInfo& info) {
    // Convert the mod info to a C struct and set that as the modloader info.
    info = modInfo.to_c();

    Logger.info("Completed setup!");
}

/// @brief Called early on in the game loading
/// @return
MOD_EXPORT_FUNC void load() {
    // Initialize il2cpp functions
    Logger.info("libunity.so start: {}", modloader_unity_handle);
    if(modloader_unity_handle) {
        auto jniOnUnload = dlsym(modloader_unity_handle, "JNI_OnUnload");
        Logger.info("libunity.so yes: {}", (void*)jniOnUnload);
        auto GlslGpuProgramGLES_CompileProgramImpl =  (char*)jniOnUnload + 0x6E8EE0;
        Logger.info("GlslGpuProgramGLES_CompileProgramImpl {}", (void*)GlslGpuProgramGLES_CompileProgramImpl);
        if(GlslGpuProgramGLES_CompileProgramImpl)
            INSTALL_HOOK_DIRECT(Logger, hGlslGpuProgramGLES_CompileProgramImpl, reinterpret_cast<void*>(GlslGpuProgramGLES_CompileProgramImpl));
    }

    il2cpp_functions::Init();
}

/// @brief Called later on in the game loading - a good time to install function hooks
/// @return
MOD_EXPORT_FUNC void late_load() {
    INSTALL_HOOK(Logger, GraphicSettingsConditionalActivator_GetGraphicsActivatorType);
    INSTALL_HOOK(Logger, SettingValidations_AdjustQuest3);
    //INSTALL_HOOK(Logger, ConditionalMaterialSwitcher_Awake);
    //INSTALL_HOOK(Logger, ConditionalActivation_Awake);
    INSTALL_HOOK(Logger, SettingsApplicatorSO_ApplyGraphicSettings);
    INSTALL_HOOK(Logger, ObstacleController_InitGraphics);
    //INSTALL_HOOK(Logger, MainEffectController_OnPreRender);
    INSTALL_HOOK(Logger, MainEffectCore_SetGlobalShaderValues);
}
