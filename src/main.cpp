#include "main.hpp"
#include "settings.hpp"
#include "basic-string.hpp"
#include "shader-patch.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "logger.hpp"
#include "modInfo.hpp"
#include "scotland2/shared/modloader.h"

MAKE_HOOK_FIND_CLASS_UNSAFE_STATIC(SettingValidations_AdjustQuest3, "BeatSaber.Settings", "SettingValidations", "AdjustQuest3", void, Settings* settings) {
    SettingValidations_AdjustQuest3(settings);
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
    if (strcmp(shaderName_c, "Custom/ParametricBoxFrameHD") == 0 && fragment.heap.size > 5400 && fragment.heap.size < 5500) {
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
    INSTALL_HOOK(Logger, SettingValidations_AdjustQuest3);
}
