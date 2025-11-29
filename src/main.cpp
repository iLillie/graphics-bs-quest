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


struct Settings {
public:
    uint8_t room[0x10];
    uint8_t controller[0x24];
    uint8_t smoothCamera[0x2c];
    uint8_t audioSettings[0x10];
    uint8_t misc[0x10];
    float renderViewportScale;
    float vrResolutionScale;
    float menuVRResolutionScaleMultiplier;
    int antiAliasingLevel;
    int targetFramerate;
    int vSyncCount;
    int maxQueuedFrames;
    int mainEffect;
    int bloom;
    int mirror;
    int obstacles;
    bool screenDisplacementEffects;
    bool smokeGraphics;
    bool depthTexture;
    bool burnMarkTrails;
    int maxShockwaveParticles;
    int maxNumberOfCutSoundEffects;
};



enum ObstacleQuality {
    Low,
    Medium,
    High
};




DEFINE_IL2CPP_ARG_TYPE(Settings, "BeatSaber.Settings", "Settings");
DEFINE_IL2CPP_ARG_TYPE(ObstacleQuality, "BeatSaber.Settings", "QualitySettings/ObstacleQuality");

/*MAKE_HOOK_FIND_CLASS_UNSAFE_INSTANCE(SettingsApplicatorSO_ApplyGraphicSettings, "", "SettingsApplicatorSO", "ApplyGraphicSettings", void, Il2CppObject* self, Settings settings, int other) {
    settings.mainEffect = 1;
    settings.bloom = 1;
    settings.obstacles = 2;
    settings.smokeGraphics = true;
    settings.screenDisplacementEffects = true;
    settings.maxShockwaveParticles = 1;
    settings.burnMarkTrails = true;
    settings.depthTexture = true;
    settings.mirror = 3;
    Logger.info("Trying out to apply settigns!");
    SettingsApplicatorSO_ApplyGraphicSettings(self, settings, other);
}*/

MAKE_HOOK_FIND_CLASS_UNSAFE_STATIC(SettingValidations_AdjustQuest3, "BeatSaber.Settings", "SettingValidations", "AdjustQuest3", void, Settings* settings) {
    SettingValidations_AdjustQuest3(settings);
    settings->mainEffect = 1;
    settings->bloom = 1;
    settings->obstacles = 2;
    settings->smokeGraphics = true;
    settings->screenDisplacementEffects = true;
    settings->maxShockwaveParticles = 1;
    settings->burnMarkTrails = true;
    settings->depthTexture = true;
    settings->mirror = 3;
    Logger.info("Trying out to apply settigns!");
}

MAKE_HOOK_FIND_CLASS_UNSAFE_INSTANCE(GraphicSettingsConditionalActivator_GetGraphicsActivatorType, "", "GraphicSettingsConditionalActivator", "Start", bool, Il2CppObject* self) {
    Logger.info("Graphics Settings Conditional!");
    return true;
}

/*MAKE_HOOK_FIND_CLASS_UNSAFE_INSTANCE(GamePause_Pause, "", "GamePause", "Pause", void, Il2CppObject* self) {
    Logger.info("Calling paused!");
    GamePause_Pause(self);
    Logger.info("Has paused");
    Logger.info("Try getting Il2cppObject*");
    auto saberManager = il2cpp_utils::GetFieldValue<Il2CppObject*>(self, "_saberManager").value();
    Logger.info("Got object: {}", (void*)(saberManager));
    Logger.info("Try getting Bool");
    auto isPaused = il2cpp_utils::GetFieldValue<bool>(self, "_pause").value();
    Logger.info("Paused value: {}", isPaused);
}*/

MAKE_HOOK_FIND_CLASS_UNSAFE_INSTANCE(ConditionalMaterialSwitcher_Awake, "", "ConditionalMaterialSwitcher", "Awake", void, Il2CppObject* self) {
    Logger.info("ConditionalMaterialSwitcher!!");
    auto renderer = il2cpp_utils::GetFieldValue<Il2CppObject*>(self, "_renderer").value();
    auto material1 = il2cpp_utils::GetFieldValue<Il2CppObject*>(self, "_material1").value();
    il2cpp_utils::RunMethod(renderer, "set_sharedMaterial", material1);
}

MAKE_HOOK_FIND_CLASS_UNSAFE_INSTANCE(ConditionalActivation_Awake, "", "ConditionalActivation", "Awake", void, Il2CppObject* self) {
    Logger.info("ConditionalActivation!!");
    il2cpp_utils::SetFieldValue(self, "_activateOnFalse", true);
    ConditionalActivation_Awake(self);
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
    il2cpp_functions::Init();
}

/// @brief Called later on in the game loading - a good time to install function hooks
/// @return
MOD_EXPORT_FUNC void late_load() {
    INSTALL_HOOK(Logger, GraphicSettingsConditionalActivator_GetGraphicsActivatorType);
    INSTALL_HOOK(Logger, SettingValidations_AdjustQuest3);
    INSTALL_HOOK(Logger, ConditionalMaterialSwitcher_Awake);
    INSTALL_HOOK(Logger, ConditionalActivation_Awake);
}
