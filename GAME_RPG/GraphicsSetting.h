#pragma once
class GraphicsSetting {
private:


public:
	std::string title;
	sf::VideoMode resolution;
	bool fullScreen;
	bool verticalSync;
	unsigned frameRateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> vieoMode;
	GraphicsSetting();
	~GraphicsSetting();
	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);

};
