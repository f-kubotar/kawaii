#ifndef __sometuke__ios_component_factory__
#define __sometuke__ios_component_factory__

#include "sometuke/director.h"
#include "sometuke/ios/ios_assets_loader.h"
#include "sometuke/ios/ios_system_font_loader.h"

namespace sometuke {

class IOSComponentFactory : public ApplicationComponentFactory {
public:
    virtual ~IOSComponentFactory() {}

    virtual AssetsLoader *CreateAssetsLoader() {
        return new IOSAssetsLoader;
    }

    virtual SystemFontLoader *CreateSystemFontLoader() {
        return new IOSSystemFontLoader;
    }
};

}

#endif /* defined(__sometuke__ios_component_factory__) */