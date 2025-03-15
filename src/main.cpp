#include <Geode/Geode.hpp>
#include <Geode/modify/MusicDownloadManager.hpp>
#include <Geode/binding/MusicDownloadManager.hpp>
#include "blacklistMan.hpp"
#include "songListMan.hpp"
#include <Geode/modify/AppDelegate.hpp>

// Namespaces
namespace fs = std::filesystem;
using namespace geode::prelude;

// Vars
auto p = MusicDownloadManager::sharedState();                                                     // Music Download Manager Singleton

std::string getFilenameWithoutExtension(const std::string &fullPath)
{
    // Use std::filesystem to get the filename and remove the extension
    std::filesystem::path p(fullPath);
    return p.stem().string(); // Get the filename without the extension
}

class $modify(MusicDownloadManager)
{
    void downloadCustomSong(int p0) {
        log::info("{}",p0);
        this->getSongInfo(p0,false);
        MusicDownloadManager::downloadCustomSong(p0);
    }
};

$on_mod(DataSaved)
{
        log::info("Saving...");
        std::vector<songItem> SongList = songListMan::compileIntoVector(p->getDownloadedSongs());
        songListMan::Save(SongList);
        blacklistMan::saveBlacklist();
};