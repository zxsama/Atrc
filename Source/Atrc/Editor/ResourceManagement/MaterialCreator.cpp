#include <Atrc/Editor/ResourceManagement/MaterialCreator.h>

namespace
{
    class GGXDielectricInstance : public MaterialInstance
    {
        TextureSlot rc_;
        TextureSlot roughness_;
        FresnelSlot fresnel_;

    public:

        using MaterialInstance::MaterialInstance;

        void Display(ResourceManager &rscMgr) override
        {
            if(ImGui::TreeNode("rc"))
            {
                rc_.Display(rscMgr);
                ImGui::TreePop();
            }
            if(ImGui::TreeNode("roughness"))
            {
                roughness_.Display(rscMgr);
                ImGui::TreePop();
            }
            if(ImGui::TreeNode("fresnel"))
            {
                fresnel_.Display(rscMgr);
                ImGui::TreePop();
            }
        }

        void Export(const ResourceManager &rscMgr, LauncherScriptExportingContext &ctx) const override
        {
            ctx.AddLine("type = GGXDielectric;");
            ExportSubResource("rc", rscMgr, ctx, rc_);
            ExportSubResource("roughness", rscMgr, ctx, roughness_);
            ExportSubResource("fresnel", rscMgr, ctx, fresnel_);
        }
    };

    class GGXMetalInstance : public MaterialInstance
    {
        TextureSlot rc_;
        TextureSlot roughness_;
        FresnelSlot fresnel_;

    public:

        using MaterialInstance::MaterialInstance;

        void Display(ResourceManager &rscMgr) override
        {
            if(ImGui::TreeNode("rc"))
            {
                rc_.Display(rscMgr);
                ImGui::TreePop();
            }
            if(ImGui::TreeNode("roughness"))
            {
                roughness_.Display(rscMgr);
                ImGui::TreePop();
            }
            if(ImGui::TreeNode("fresnel"))
            {
                fresnel_.Display(rscMgr);
                ImGui::TreePop();
            }
        }

        void Export(const ResourceManager &rscMgr, LauncherScriptExportingContext &ctx) const override
        {
            ctx.AddLine("type = GGXMetal;");
            ExportSubResource("rc", rscMgr, ctx, rc_);
            ExportSubResource("roughness", rscMgr, ctx, roughness_);
            ExportSubResource("fresnel", rscMgr, ctx, fresnel_);
        }
    };

    class IdealBlackInstance : public MaterialInstance
    {
    public:

        using MaterialInstance::MaterialInstance;

        void Display(ResourceManager&) override { }

        void Export(const ResourceManager&, LauncherScriptExportingContext &ctx) const override
        {
            ctx.AddLine("type = IdealBlack;");
        }
    };

    class IdealDiffuseInstance : public MaterialInstance
    {
        TextureSlot albedo_;

    public:

        IdealDiffuseInstance(ResourceManager &rscMgr, std::string name)
            : MaterialInstance(std::move(name))
        {
            albedo_.SetInstance(rscMgr.Create<TextureInstance>("constant", ""));
        }

        void Display(ResourceManager &rscMgr) override
        {
            if(ImGui::TreeNodeEx("albedo", ImGuiTreeNodeFlags_DefaultOpen))
            {
                albedo_.Display(rscMgr);
                ImGui::TreePop();
            }
        }

        void Export(const ResourceManager &rscMgr, LauncherScriptExportingContext &ctx) const override
        {
            ctx.AddLine("type = IdealDiffuse;");
            ExportSubResource("albedo", rscMgr, ctx, albedo_);
        }
    };

    class IdealMirrorInstance : public MaterialInstance
    {
        TextureSlot rc_;
        FresnelSlot fresnel_;

    public:

        using MaterialInstance::MaterialInstance;

        void Display(ResourceManager &rscMgr) override
        {
            if(ImGui::TreeNode("rc"))
            {
                rc_.Display(rscMgr);
                ImGui::TreePop();
            }
            if(ImGui::TreeNode("fresnel"))
            {
                fresnel_.Display(rscMgr);
                ImGui::TreePop();
            }
        }

        void Export(const ResourceManager &rscMgr, LauncherScriptExportingContext &ctx) const override
        {
            ctx.AddLine("type = IdealMirror;");
            ExportSubResource("rc", rscMgr, ctx, rc_);
            ExportSubResource("fresnel", rscMgr, ctx, fresnel_);
        }
    };

    class IdealScalerInstance : public MaterialInstance
    {
        TextureSlot scale_;
        MaterialSlot internal_;

    public:

        using MaterialInstance::MaterialInstance;

        void Display(ResourceManager &rscMgr) override
        {
            if(ImGui::TreeNode("scale"))
            {
                scale_.Display(rscMgr);
                ImGui::TreePop();
            }
            if(ImGui::TreeNode("internal"))
            {
                internal_.Display(rscMgr);
                ImGui::TreePop();
            }
        }

        void Export(const ResourceManager &rscMgr, LauncherScriptExportingContext &ctx) const override
        {
            ctx.AddLine("type = IdealScaler;");
            ExportSubResource("scale", rscMgr, ctx, scale_);
            ExportSubResource("internal", rscMgr, ctx, internal_);
        }
    };

    class IdealSpecularInstance : public MaterialInstance
    {
        TextureSlot rc_;
        FresnelSlot dielectric_;

    public:

        using MaterialInstance::MaterialInstance;

        void Display(ResourceManager &rscMgr) override
        {
            if(ImGui::TreeNode("rc"))
            {
                rc_.Display(rscMgr);
                ImGui::TreePop();
            }
            if(ImGui::TreeNode("dielectric"))
            {
                dielectric_.Display(rscMgr);
                ImGui::TreePop();
            }
        }

        void Export(const ResourceManager &rscMgr, LauncherScriptExportingContext &ctx) const override
        {
            ctx.AddLine("type = IdealSpecular;");
            ExportSubResource("rc", rscMgr, ctx, rc_);
            ExportSubResource("fresnel", rscMgr, ctx, dielectric_);
        }
    };

    class InvisibleSurfaceInstance : public MaterialInstance
    {
    public:

        using MaterialInstance::MaterialInstance;

        void Display(ResourceManager&) override { }

        void Export(const ResourceManager &rscMgr, LauncherScriptExportingContext &ctx) const override
        {
            ctx.AddLine("type = Invisible;");
        }
    };

    class NormalizedDiffusionBSSRDFInstance : public MaterialInstance
    {
        MaterialSlot surface_;
        TextureSlot A_;
        TextureSlot dmfp_;
        float eta_ = 0;

    public:

        using MaterialInstance::MaterialInstance;

        void Display(ResourceManager &rscMgr) override
        {
            ImGui::InputFloat("eta", &eta_);
            if(ImGui::TreeNode("surface"))
            {
                surface_.Display(rscMgr);
                ImGui::TreePop();
            }
            if(ImGui::TreeNode("A"))
            {
                A_.Display(rscMgr);
                ImGui::TreePop();
            }
            if(ImGui::TreeNode("dmfp"))
            {
                dmfp_.Display(rscMgr);
                ImGui::TreePop();
            }
        }

        void Export(const ResourceManager &rscMgr, LauncherScriptExportingContext &ctx) const override
        {
            ctx.AddLine("type = BSSRDF;");
            ExportSubResource("surface", rscMgr, ctx, surface_);
            ExportSubResource("A", rscMgr, ctx, A_);
            ExportSubResource("dmfp", rscMgr, ctx, dmfp_);
            ctx.AddLine("eta = ", std::to_string(eta_), ";");
        }
    };

    class ONMatteInstance : public MaterialInstance
    {
        TextureSlot albedo_;
        TextureSlot sigma_;

    public:

        using MaterialInstance::MaterialInstance;

        void Display(ResourceManager &rscMgr) override
        {
            if(ImGui::TreeNode("albedo"))
            {
                albedo_.Display(rscMgr);
                ImGui::TreePop();
            }
            if(ImGui::TreeNode("sigma"))
            {
                sigma_.Display(rscMgr);
                ImGui::TreePop();
            }
        }

        void Export(const ResourceManager &rscMgr, LauncherScriptExportingContext &ctx) const override
        {
            ctx.AddLine("type = ONMatte;");
            ExportSubResource("albedo", rscMgr, ctx, albedo_);
            ExportSubResource("sigma", rscMgr, ctx, sigma_);
        }
    };

    class TSMetalInstance : public MaterialInstance
    {
        TextureSlot rc_;
        TextureSlot roughness_;
        FresnelSlot fresnel_;

    public:

        using MaterialInstance::MaterialInstance;

        void Display(ResourceManager &rscMgr) override
        {
            if(ImGui::TreeNode("rc"))
            {
                rc_.Display(rscMgr);
                ImGui::TreePop();
            }
            if(ImGui::TreeNode("roughness"))
            {
                roughness_.Display(rscMgr);
                ImGui::TreePop();
            }
            if(ImGui::TreeNode("fresnel"))
            {
                fresnel_.Display(rscMgr);
                ImGui::TreePop();
            }
        }

        void Export(const ResourceManager &rscMgr, LauncherScriptExportingContext &ctx) const override
        {
            ctx.AddLine("type = TSMetal;");
            ExportSubResource("rc", rscMgr, ctx, rc_);
            ExportSubResource("roughness", rscMgr, ctx, roughness_);
            ExportSubResource("fresnel", rscMgr, ctx, fresnel_);
        }
    };
}

void RegisterMaterialCreators(ResourceManager &rscMgr)
{
    static const GGXDielectricCreator iGGXDielectricCreator;
    static const GGXMetalCreator iGGXMetalCreator;
    static const IdealBlackCreator iIdealBlackCreator;
    static const IdealDiffuseCreator iIdealDiffuseCreator;
    static const IdealMirrorCreator iIdealMirrorCreator;
    static const IdealScalerCreator iIdealScalerCreator;
    static const IdealSpecularCreator iIdealSpecularCreator;
    static const InvisibleSurfaceCreator iInvisibleSurfaceCreator;
    static const NormalizedDiffusionBSSRDFCreator iNormalizedDiffusionBSSRDFCreator;
    static const ONMatteCreator iONMatteCreator;
    static const TSMetalCreator iTSMetalCreator;
    rscMgr.AddCreator(&iGGXDielectricCreator);
    rscMgr.AddCreator(&iGGXMetalCreator);
    rscMgr.AddCreator(&iIdealBlackCreator);
    rscMgr.AddCreator(&iIdealDiffuseCreator);
    rscMgr.AddCreator(&iIdealMirrorCreator);
    rscMgr.AddCreator(&iIdealScalerCreator);
    rscMgr.AddCreator(&iIdealSpecularCreator);
    rscMgr.AddCreator(&iInvisibleSurfaceCreator);
    rscMgr.AddCreator(&iNormalizedDiffusionBSSRDFCreator);
    rscMgr.AddCreator(&iONMatteCreator);
    rscMgr.AddCreator(&iTSMetalCreator);
}

std::shared_ptr<MaterialInstance> GGXDielectricCreator::Create(ResourceManager &rscMgr, std::string name) const
{
    return std::make_shared<GGXDielectricInstance>(std::move(name));
}

std::shared_ptr<MaterialInstance> GGXMetalCreator::Create(ResourceManager &rscMgr, std::string name) const
{
    return std::make_shared<GGXMetalInstance>(std::move(name));
}

std::shared_ptr<MaterialInstance> IdealBlackCreator::Create(ResourceManager &rscMgr, std::string name) const
{
    return std::make_shared<IdealBlackInstance>(std::move(name));
}

std::shared_ptr<MaterialInstance> IdealDiffuseCreator::Create(ResourceManager &rscMgr, std::string name) const
{
    return std::make_shared<IdealDiffuseInstance>(rscMgr, std::move(name));
}

std::shared_ptr<MaterialInstance> IdealMirrorCreator::Create(ResourceManager &rscMgr, std::string name) const
{
    return std::make_shared<IdealMirrorInstance>(std::move(name));
}

std::shared_ptr<MaterialInstance> IdealScalerCreator::Create(ResourceManager &rscMgr, std::string name) const
{
    return std::make_shared<IdealScalerInstance>(std::move(name));
}

std::shared_ptr<MaterialInstance> IdealSpecularCreator::Create(ResourceManager &rscMgr, std::string name) const
{
    return std::make_shared<IdealSpecularInstance>(std::move(name));
}

std::shared_ptr<MaterialInstance> InvisibleSurfaceCreator::Create(ResourceManager &rscMgr, std::string name) const
{
    return std::make_shared<InvisibleSurfaceInstance>(std::move(name));
}

std::shared_ptr<MaterialInstance> NormalizedDiffusionBSSRDFCreator::Create(ResourceManager &rscMgr, std::string name) const
{
    return std::make_shared<NormalizedDiffusionBSSRDFInstance>(std::move(name));
}

std::shared_ptr<MaterialInstance> ONMatteCreator::Create(ResourceManager &rscMgr, std::string name) const
{
    return std::make_shared<ONMatteInstance>(std::move(name));
}

std::shared_ptr<MaterialInstance> TSMetalCreator::Create(ResourceManager &rscMgr, std::string name) const
{
    return std::make_shared<TSMetalInstance>(std::move(name));
}
