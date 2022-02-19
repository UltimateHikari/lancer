#include <filesystem>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <linux/limits.h>
#endif

    // https://stackoverflow.com/a/70052837
namespace pathing{

    std::filesystem::path get_exe_dir(){
    #ifdef _WIN32
        // Windows specific
        wchar_t szPath[MAX_PATH];
        GetModuleFileNameW( NULL, szPath, MAX_PATH );
    #else
        // Linux specific
        char szPath[PATH_MAX];
        ssize_t count = readlink( "/proc/self/exe", szPath, PATH_MAX );
        if( count < 0 || count >= PATH_MAX )
            return {}; // some error
        szPath[count] = '\0';
    #endif
        return std::filesystem::path{ szPath }.parent_path() / ""; // to finish the folder path with (back)slash
    }

}