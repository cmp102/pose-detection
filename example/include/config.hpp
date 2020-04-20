#pragma once 

#include <string>
#include <iostream>
#include <skeleton/skeleton.hpp>

struct Config{
	//Enums 
	enum Mode {streaming, image};

	explicit Config(std::string_view filename);

	void show();

	//Data
	std::string protoFile;
	std::string weightsFile;
	Skeleton::ModelType model {Skeleton::coco};
	Mode mode;
	std::string inFile;
	std::string outFile;
	double threshhold {0.1};
	int width {368};
};