#include "TPPluginsManager.h"
#include "TPDirent.h"
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#ifdef WIN32
    #include <Windows.h>
#else
    #include <dlfcn.h>
#endif
TPPluginsManager::TPPluginsManager()
{

}

ITPPlugin *TPPluginsManager::getInstance(const std::string strType)
{
    ITPPlugin *pPlugin = nullptr;
    auto iter = TPSingleton::instance<plugin_map>().find(strType);
    if(iter != TPSingleton::instance<plugin_map>().end())
    {
        pPlugin = iter->second;
    }

    return pPlugin;
}

QObject *TPPluginsManager::getObject()
{
    return this;
}


bool TPPluginsManager::loadAllPlugins(const std::string strLibPath)
{

    return true;
}

void TPPluginsManager::listFiles(std::list<std::string>& list, const std::string& folder, const std::string& extension, bool recursive){
    DIR* dir;
    DIR* subDir;
    struct dirent *ent;
    // try to open top folder
    dir = opendir(folder.c_str());
    if (dir == NULL){
        // could not open directory
      fprintf(stderr, "Could not open \"%s\" directory.\n", folder.c_str());
      return;
    }else{
        // close, we'll process it next
        closedir(dir);
    }
    // enqueue top folder
    std::queue<std::string> folders;
    folders.push(folder);

    // run while has queued folders
    while (!folders.empty()){
        std::string currFolder = folders.front();
        folders.pop();
        dir = opendir(currFolder.c_str());
        if (dir == NULL) continue;
        // iterate through all the files and directories
        while ((ent = readdir (dir)) != NULL) {
            std::string name(ent->d_name);
            // ignore "." and ".." directories
            if ( name.compare(".") == 0 || name.compare("..") == 0) continue;
            // add path to the file name
            std::string path = currFolder;
            path.append("/");
            path.append(name);
            // check if it's a folder by trying to open it
            subDir = opendir(path.c_str());
            if (subDir != NULL){
                // it's a folder: close, we can process it later
                closedir(subDir);
                if (recursive) folders.push(path);
            }else{
                // it's a file
                if (extension.empty()){
                    list.push_back(path);
                }else{
                    // check file extension
                    size_t lastDot = name.find_last_of('.');
                    std::string ext = name.substr(lastDot+1);
                    if (ext.compare(extension) == 0){
                        // match
                        list.push_back(path);
                    }
                } // endif (extension test)
            } // endif (folder test)
        } // endwhile (nextFile)
        closedir(dir);
    } // endwhile (queued folders)

}


ITPPlugin* TPPluginsManager::load(const std::string& path){
    if ( path.empty() ){
        fprintf(stderr, "Failed to load library: Empty path\n");
        return NULL;
    }
    void* handle = NULL;

    // load library - OS dependent operation
    #ifdef WIN32
        handle = ::LoadLibraryA(path.c_str());
        if (!handle){
            fprintf(stderr, "Failed to load library \"%s\".\n", path.c_str());
            return NULL;
        }
    #else
        handle = ::dlopen(path.c_str(), RTLD_NOW);
        if (!handle){
            const char* errorString = ::dlerror();
            fprintf(stderr, "Failed to load library \"%s\".", path.c_str());
            if(errorString) fprintf(stderr, " OS returned error: \"%s\".", errorString);
            fprintf(stderr, "\n");
            return NULL;
        }
    #endif
    // return a DLibrary with the DLL handle
    return NULL;
}


////////////////////////////////////////////////////////////
void TPPluginsManager::unLoad(ITPPlugin *pPlugin){
    if (pPlugin->nLibHandle){
        #ifdef WIN32
            ::FreeLibrary( (HMODULE)pPlugin->nLibHandle );
        #else
            ::dlclose(handle);
        #endif
    }
}


////////////////////////////////////////////////////////////
void* TPPluginsManager::getSymbol(ITPPlugin *pPlugin, const std::string& symbol){
    if (!pPlugin->nLibHandle){
        fprintf(stderr, "Cannot inspect library symbols, library isn't loaded.\n");
        return NULL;
    }
    void* res;
    #ifdef WIN32
        res = (void*)(::GetProcAddress((HMODULE)pPlugin->nLibHandle, symbol.c_str()));
    #else
        res = (void*)(::dlsym(pPlugin->nLibHandle, symbol.c_str()));
    #endif
    if (!res){
        fprintf(stderr, "Library symbol \"%s\" not found.\n", symbol.c_str());
        return NULL;
    }
    return res;
}
