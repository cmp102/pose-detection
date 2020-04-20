#include <config.hpp>
#include <confparser.hpp>
#include <sstream>

std::stringstream& operator>> (std::stringstream& ss, Skeleton::ModelType& model){
	if(ss.str() == "coco"){
		model = Skeleton::ModelType::coco;
	}else if(ss.str() == "mpii"){
		model = Skeleton::ModelType::mpii;
	}
	return ss;
} 

std::stringstream& operator>> (std::stringstream& ss, Config::Mode& mode){
	if(ss.str() == "image"){
		mode = Config::Mode::image;
	}else if(ss.str() == "streaming"){
		mode = Config::Mode::streaming;
	}
	return ss;
} 

Config::Config(std::string_view filename){
	confparser::Config cnf;
	
	cnf.bindParam("mode"				,mode);
	cnf.bindParam("input"			,inFile);
	cnf.bindParam("output"			,outFile);
	cnf.bindParam("model"			,model);
	cnf.bindParam("protofile"		,protoFile);
	cnf.bindParam("weightsfile"	,weightsFile);
	cnf.bindParam("threshhold"		,threshhold);
	cnf.bindParam("width"			,width);

	cnf.loadFile(filename);
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