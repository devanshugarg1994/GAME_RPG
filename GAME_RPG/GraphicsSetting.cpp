#include "stdafx.h"
#include "GraphicsSetting.h"

GraphicsSetting::GraphicsSetting()
{
	this->title = "DEFAULT";
	this->resolution = sf::VideoMode::getDesktopMode();
	this->fullScreen = false;
	this->verticalSync = false;
	this->frameRateLimit = 120;
	this->contextSettings.antialiasingLevel = 0;
	this->vieoMode = sf::VideoMode::getFullscreenModes();
}

GraphicsSetting::~GraphicsSetting()
{
}

void GraphicsSetting::saveToFile(const std::string path) {
	std::ofstream ofs(path);

	if (ofs.is_open()) {
		ofs << this->resolution.width << " " << this->resolution.height;
		ofs << this->fullScreen;
		ofs << this->frameRateLimit;
		ofs << this->verticalSync;
		ofs << this->contextSettings.antialiasingLevel;
	}
	ofs.close();
}
void GraphicsSetting::loadFromFile(const std::string path) {
	std::ifstream ifs(path);

	if (ifs.is_open()) {
		std::getline(ifs, this->title);
		ifs >> this->resolution.width >> this->resolution.height;
		ifs >> this->fullScreen;
		ifs >> this->frameRateLimit;
		ifs >> this->verticalSync;
		ifs >> this->contextSettings.antialiasingLevel;
	}
	ifs.close();
}
