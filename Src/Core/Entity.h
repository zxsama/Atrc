#pragma once

#include "../Common.h"
#include "../Core/Material.h"
#include "../Math/Geometry.h"

AGZ_NS_BEG(Atrc)

ATRC_INTERFACE Entity;
ATRC_INTERFACE Light;

struct EntityIntersection
{
    GeometryIntersection geoInct;
    const Entity *entity;
    const Material *material;
    RC<BxDF> bxdf;
};

ATRC_INTERFACE Entity
{
public:

    virtual ~Entity() = default;

    virtual bool HasIntersection(const Ray &r) const
    {
        return EvalIntersection(r).has_value();
    }

    virtual Option<EntityIntersection> EvalIntersection(const Ray &r) const = 0;
};

AGZ_NS_END(Atrc)