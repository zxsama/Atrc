#pragma once

#include <Atrc/Core/Common.h>
#include <Atrc/Core/Integrator.h>
#include <Atrc/Core/Scene.h>

AGZ_NS_BEG(Atrc)

struct SubareaRect
{
    uint32_t xBegin, xEnd;
    uint32_t yBegin, yEnd;
};

class SubareaRenderer
{
public:

    virtual ~SubareaRenderer() = default;

    virtual void Render(const Scene &scene, const Integrator &integrator, RenderTarget &rt, const SubareaRect &area) const = 0;
};

class Renderer
{
public:

    virtual ~Renderer() = default;

    virtual void Render(const SubareaRenderer &subareaRenderer, const Scene &scene, const Integrator &integrator, RenderTarget &rt) const = 0;
};

AGZ_NS_END(Atrc)
