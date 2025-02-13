#include <Geode/modify/MusicDownloadManager.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify (MyMusicDownloadManager, MusicDownloadManager) {
	static void onModify(auto& self) {
		(void) self.setHookPriority("MusicDownloadManager::pathForSFX", -1999);
	}
	gd::string pathForSFX(int p0) {
		const auto manager = Manager::getSharedInstance();
		const std::string& originalPath = MusicDownloadManager::pathForSFX(p0);
		if (!Utils::modEnabled() || !manager->filth) return originalPath;
		const std::string& desiredPath = manager->filthyPath.string();
		#ifdef GEODE_IS_ANDROID
		if (desiredPath == "file:///android_asset/sfx/s4451.ogg") return "sfx/s4451.ogg";
		#endif
		if (!Utils::isSupportedFMODExtension(desiredPath)) return originalPath;
		return desiredPath;
		// return "sfx/s4451.ogg";
	}
};