#include "bits/stdc++.h"
#include "raylib.h"
int main(){
    const std::string asset = std::string(GetApplicationDirectory()) + "assets/mapped2.png";
    std::cout << asset;
    #if defined(_MSVC_LANG)
        std::cout << _MSVC_LANG << '\n'; // Used by Visual Studio (MSVC)
    #else
        std::cout << __cplusplus << '\n'; // Used by GCC, Clang, and others
    #endif
    return 0;
}
