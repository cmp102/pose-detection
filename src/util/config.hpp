#pragma once 

#include <string>
#include <iostream>

struct Config{
	//Enums 
	enum ModelType {coco, mpi};
	enum Mode {streaming, image};

	explicit Config(int argc, char** argv);

	void show();

	//Data
	std::string protoFile;
	std::string weightsFile;
	ModelType model {coco};
	Mode mode;
	std::string inFile;
	std::string outFile;
	double threshhold {0.1};
	int width {368};
};