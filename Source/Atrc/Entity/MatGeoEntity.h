#pragma once

#include <Atrc/Common.h>
#include <Atrc/Entity/Entity.h>
#include <Atrc/Material/Material.h>

AGZ_NS_BEG(Atrc)

template<typename GeoTpl,
         std::enable_if_t<std::is_base_of_v<Entity, GeoTpl>, int> = 0>
class MatGeoEntity
    : ATRC_PROPERTY AGZ::Uncopiable,
      public GeoTpl
{
    RC<Material> mat_;

public:

    template<typename...Args>
    explicit MatGeoEntity(RC<Material> mat, Args&&...args)
        : GeoTpl(std::forward<Args>(args)...), mat_(mat)
    {
        
    }

    RC<BxDF> GetBxDF(const Intersection &inct) const override
    {
        return mat_->GetBxDF(inct, inct.uv);
    }
};

AGZ_NS_END(Atrc)
