#include <util/config.hpp>

Config::Config(int argc, char** argv){
	for(int i=1; i<argc; ++i){
		std::string option = argv[i];
		if(option == "--mode"){
			if(++i < argc){
				if(std::string("streaming") == argv[i]){
					mode=Mode::streaming;
				}else if(std::string("image") == argv[i]){
					mode=Mode::image;
				}
			}
		}else if(option == "-i"){
			if(++i < argc){
				inFile = argv[i];
			}
		}else if(option == "-o"){
			if(++i < argc){
				outFile = argv[i];
			}
		}else if(option == "--model"){
			if(++i < argc){
				if(std::string("mpi") == argv[i]){
					model=ModelType::mpi;
				}else if(std::string("coco") == argv[i]){
					model=ModelType::coco;
				}
			}
		}else if(option == "--protofile"){
			if(++i < argc){
				protoFile = argv[i];
			}
		}else if(option == "--weightsfile"){
			if(++i < argc){
				weightsFile = argv[i];
			}
		}else if(option == "--threshhold"){
			if(++i < argc){
				threshhold = atof(argv[i]);
			}
		}else if(option == "--width"){
			if(++i < argc){
				width = atoi(argv[i]);
			}
		}
	}
}

void Config::show(){
	std::cout << "Mode: " << mode << '\n';
	std::cout << "Model: " << model << '\n';
	std::cout << "ProtoFile: " << protoFile << '\n';
	std::cout << "WeightFile: " << weightsFile << '\n';
	std::cout << "Threshhold: " << threshhold << '\n';
	std::cout << "Width: " << width << '\n';
	std::cout << "Input file: " << inFile << '\n';
	std::cout << "Output file: " << outFile << '\n';		
}