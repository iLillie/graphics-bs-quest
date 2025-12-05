#include "main.hpp"
#include "settings.hpp"
#include "basic-string.hpp"
#include "shader-patch.hpp"
#include "type-defines.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "logger.hpp"
#include "modInfo.hpp"
#include "scotland2/shared/modloader.h"


MAKE_HOOK_FIND_CLASS_UNSAFE_STATIC(MainEffectCore_SetGlobalShaderValues, "", "MainEffectCore", "SetGlobalShaderValues", void, float baseColorBoost, float baseColorBoostThreshold) {
    //baseColorBoost = 0.15f;
    //baseColorBoostThreshold = 0.0f;
    MainEffectCore_SetGlobalShaderValues(baseColorBoost, baseColorBoostThreshold);
}



MAKE_HOOK_FIND_CLASS_UNSAFE_INSTANCE(MainEffectController_OnPreRender, "", "MainEffectController", "OnPreRender", void, Il2CppObject* self) {
   //auto shader = il2cpp_utils::GetClassFromName("UnityEngine", "Shader");
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

MAKE_HOOK(hCompileProgramImpl, nullptr, void,
    unsigned int& unknown,
    core::basic_string const& shaderName,
    core::basic_string const* vertex,
    core::basic_string& fragment,
    core::basic_string const& geometry,
    core::basic_string const& hull,
    core::basic_string const& domain,
    int& shader, int a, int * b, int *c, int* d) {
    auto shaderName_c = shaderName.c_str();


    // TODO: Figure out how to fix for mirror?
    if (strcmp(shaderName_c, "Custom/ParametricBoxFrameHD") == 0 && fragment.heap.size > 5390) {
        memcpy((void*)fragment.heap.data, (void*)&ParametricBoxFrameHD_fix_glsl, ParametricBoxFrameHD_fix_glsl_len);
        fragment.heap.size = ParametricBoxFrameHD_fix_glsl_len-1;
    }

    // Vertex and Fragment check to make sure it only changes for the player and not mirror
    if (strcmp(shaderName_c, "Custom/SaberBlade") == 0 && fragment.heap.size == 2188 && vertex->heap.size == 5265) {
        memcpy((void*)fragment.heap.data, (void*)&SaberBlade_fix_glsl, SaberBlade_fix_glsl_len);
        fragment.heap.size = SaberBlade_fix_glsl_len-1;
    }

    hCompileProgramImpl(unknown, shaderName, vertex, fragment, geometry, hull, domain, shader, a, b, c, d);
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


    if (!modloader_unity_handle) {
        il2cpp_functions::Init();
        return;
    }

    void* jniOnUnload = dlsym(modloader_unity_handle, "JNI_OnUnload");

    // GlslGpuProgramGLES::CompileProgramImpl
    if (auto const CompileProgramImpl = static_cast<char*>(jniOnUnload) + 0x6E8EE0)
        INSTALL_HOOK_DIRECT(Logger, hCompileProgramImpl, CompileProgramImpl);

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
