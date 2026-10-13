#include "IPasswordRetriever.hpp"

#include <cstring>
#ifdef __WIN32__
#include <windows.h>
#elif __APPLE__
#include <cstdio>
#include <cstdlib>
#include <string>
#endif

class ClipboardRetriever final : public IPasswordRetriever {
public:
    void retrievePassword(const std::string& password) const override {
        const char* passC = password.c_str();

        #ifdef __WIN32__
            const size_t len = strlen(passC)+1;
    
            HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
            memcpy(GlobalLock(hMem), passC, len);
            GlobalUnlock(hMem);

            OpenClipboard(0);
            EmptyClipboard();
            SetClipboardData(CF_TEXT, hMem);
            CloseClipboard();

        #elif __APPLE__
            FILE* pipe = popen("pbcopy", "w");
            if(!pipe) std::abort();
            fwrite(passC, sizeof(char), password.size(), pipe);
            pclose(pipe);
        #endif 
    }
};
