#pragma once

#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"

struct GameObject : Il2CppObject {};
struct String : StringW {};
struct BoolSO : Il2CppObject {};
struct Renderer : Il2CppObject {};
struct Material : Il2CppObject {};
struct SystemBool {
    bool m_value;
};

struct Shader : Il2CppObject {};

struct Behaviour : Il2CppObject{};
struct MonoBehaviour : Behaviour{};
struct ImageEffectController : MonoBehaviour{};
struct MainEffectContainerSO : Il2CppObject{};
struct MainEffectSO : Il2CppObject{};
struct PyramidBloomMainEffectSO : MainEffectSO{};
struct MainEffectCore{};

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
