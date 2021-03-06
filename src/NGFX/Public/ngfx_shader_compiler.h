/**
 * MIT License
 *
 * Copyright (c) 2019 Zhou Qin
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __ngfx_shader_compiler_20180511__
#define __ngfx_shader_compiler_20180511__
#pragma once

#if _WIN32
#if defined(NGFX_SHADER_COMPILER_BUILD)
#if defined(NGFX_SHADER_COMPILER_BUILD_SHARED_LIB)
#define NGFX_SHADER_COMPILER_API __declspec(dllexport)
#else
#define NGFX_SHADER_COMPILER_API __declspec(dllimport)
#endif
#else
#define NGFX_SHADER_COMPILER_API
#endif
#else
#define NGFX_SHADER_COMPILER_API __attribute__((visibility("default")))
#endif

#include "ngfx_shader.h"

#if __cplusplus
extern "C" {
#endif

#if __cplusplus
}

namespace ngfx {

// Includer
// DeviceLimit
// DeviceAvailability
// Defines
// Optimize

enum class IncludeType : uint8_t {
    Local,
    System,
};

enum class CompileOutputType : uint8_t {
    SPRIV,
    MetalSL,
    DXIL,
    DXBC,
    GLSL
};

struct DeviceLimits {
};

struct IIncluder : public Rc {
    virtual ~IIncluder() {}
    virtual Result Open(IncludeType Type, const char *SrcFile, const char *RequestFile, void **ppData, uint64_t *pBytes,
                        void *pUserData) = 0;
    virtual void Close(void *pData) = 0;
};

struct IBlob : public Rc {
    virtual ~IBlob() {}

    virtual const void *GetData() = 0;
    virtual uint64_t GetSize() = 0;
};

struct ICompilerResult : public Rc {
    virtual ~ICompilerResult() {}
    virtual Result GetStatus() = 0;
    virtual Result GetResult(IBlob **pResult) = 0;
    virtual Result GetError(IBlob **pErr) = 0;
};

struct ShaderDefinition {
    const char *Name;
    const char *Definition;
};

struct CompileOptions
{
    const char *EntryPoint;
    ShaderProfile Profile;
    ShaderStage ShaderType;
    ShaderOptimizeFlag OptLevel;
};

struct IShaderCompiler : public Rc {
    virtual ~IShaderCompiler() {}

    virtual void SetDeviceLimits(DeviceLimits const &limits) {}
    virtual void SetOutputType(CompileOutputType const &oType) {}

    virtual Result Compile(const char *strSource, const char *strFile, CompileOptions const& options, IIncluder *pIncluder,
                           const ShaderDefinition *Definitions, ICompilerResult **pResult) = 0;
/*
    virtual Result PreProcess(const char *strSource, const char *strFile, const char *strEntryPoint,
                              ShaderProfile Profile, ShaderStageBit ShaderType, ShaderOptimizeLevel OptLevel,
                              IIncluder *pIncluder, const ShaderDefinition *Definitions, ICompilerResult **pResult) = 0;*/
};

} // namespace ngfx
extern "C" NGFX_SHADER_COMPILER_API ngfx::Result ngfxCreateShaderCompiler(ngfx::IShaderCompiler **ppCompiler);
extern "C" NGFX_SHADER_COMPILER_API ngfx::Result ngfxDestroyShaderCompiler(ngfx::IShaderCompiler *pCompiler);
#endif

#endif