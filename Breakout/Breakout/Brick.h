#pragma once
#include <iostream>
#include "GameObject.h"
class Brick : public GameObject
{
public:
	Brick(std::string _name, std::string _ID, std::string _texturePath, int _hitPoints, std::string _hitSoundPath, 
		std::string _breakSoundPath, int _breakScore) : name(_name), ID(_ID), texturePath(_texturePath),
		hitPoints(_hitPoints), hitSoundPath(_hitSoundPath), breakSoundPath(_breakSoundPath), breakScore(_breakScore) {}
private:
	std::string name;
	std::string ID;
	std::string texturePath;
	int hitPoints;
	std::string hitSoundPath;
	std::string breakSoundPath;
	int breakScore;
};

