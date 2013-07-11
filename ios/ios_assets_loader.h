#ifndef __skidarake__ios_assets_loader__
#define __skidarake__ios_assets_loader__

#include "skidarake/assets_loader.h"
#include "skidarake/ios/devices.h"

namespace skidarake {

using namespace std;

class IOSAssetsLoader : public AssetsLoader {
public:
    IOSAssetsLoader() {
        suffixes_[kiPhone]              = "";
        suffixes_[kiPhoneRetinaDisplay] = "@x2";
        suffixes_[kiPad]                = "-ipad";
        suffixes_[kiPadRetinaDisplay]   = "-ipad@x2";
    }

    vector<char> ReadBytes(const string& relative_path);
    shared_ptr<Texture2D> ReadTexture(const string &relative_path);
    string ReadString(const string& relative_path);
    const string FullPathFromRelativePath(const string& relative_path);

private:
    bool EndsWith(const string& str, const string& suffix) {
        if (str.length() >= suffix.length()) {
            return (0 == str.compare(str.length() - suffix.length(), suffix.length(), suffix));
        } else {
            return false;
        }
    }

    string suffixes_[kDevice_MAX];
};

} 

#endif /* defined(__skidarake__ios_assets_loader__) */
