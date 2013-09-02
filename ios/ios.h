#ifndef __sometuke__ios_component_factory__
#define __sometuke__ios_component_factory__

#include "sometuke/application_component.h"
#include "sometuke/ios/ios_configuration.h"
#include "sometuke/ios/ios_filt_utils.h"
#include "sometuke/ios/ios_image_loader.h"
#include "sometuke/ios/ios_system_font_renderer.h"

namespace sometuke {

class IOSComponent : public ApplicationComponent {
public:
    virtual ~IOSComponent() {}

    virtual Configuration *CreateConfiguration() {
        return new IOSConfiguration;
    }

    virtual FileUtils *CreateFileUtils() {
        return new IOSFileUtils;
    }
    
    virtual ImageLoader *CreateAssetsLoader() {
        return new IOSImageLoader;
    }
    
    virtual SystemFontRenderer *CreateSystemFontRenderer() {
        return new IOSSystemFontRenderer;
    }
};

}

#endif /* defined(__sometuke__ios_component_factory__) */
