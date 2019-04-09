#include <Atrc/Editor/Material/Material.h>

#include <Atrc/Editor/Material/DisneyReflection.h>
#include <Atrc/Editor/Material/IdealDiffuse.h>
#include <Atrc/Editor/Material/IdealMirror.h>

namespace Atrc::Editor
{

void RegisterBuiltinMaterialCreators(MaterialFactory &factory)
{
    static const DisneyReflectionCreator iDisneyReflectionCreator;
    static const IdealDiffuseCreator iIdealDiffuseCreator;
    static const IdealMirrorCreator iIdealMirrorCreator;
    factory.AddCreator(&iDisneyReflectionCreator);
    factory.AddCreator(&iIdealDiffuseCreator);
    factory.AddCreator(&iIdealMirrorCreator);
}

}; // namespace Atrc::Editor
