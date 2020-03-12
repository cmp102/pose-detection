#include "skeleton/skeleton.hpp"
#include "util/debug.hpp"
#include <string_view>
#include <unistd.h>

constexpr double threshhold = 0.1;
constexpr int WIDTH = 60;

int main(int argc, char** argv){
	// std::string protoFile = "../pose/mpi/pose_deploy_linevec_faster_4_stages.prototxt";
	std::string protoFile = "/home/prototano/Projects/UA/4/TFG/open-pose/pose/coco/pose_deploy_linevec.prototxt";
	std::string weightsFile = "../pose/mpi/pose_iter_160000.caffemodel";
	// std::string weightsFile = "/home/prototano/Projects/UA/4/TFG/open-pose/pose/coco/pose_iter_440000.caffemodel";
	Skeleton::loadNetwork(protoFile, weightsFile);	
	
	if(argc == 1){
		cv::VideoCapture capture{0};
		cv::Mat frame;
		if(capture.isOpened()){
			for(;;){
				debug_timer_start(jajaja)
				capture >> frame;
				Skeleton skltn(frame,threshhold, WIDTH);
				skltn.show("jajajaja");
				debug_timer_finish(jajaja)
			}
		}
	}
	std::string filename = argv[1];

	Skeleton skltn(filename, threshhold, WIDTH);

	if(argc >= 3){
		skltn.saveImage(argv[2]);
		return 0;
	}

	skltn.show("jajaja");

	for(;;){
		sleep(1);
	}

	return 0;
}
