#include <skeleton/skeleton.hpp>
#include <util/debug.hpp>
#include <util/config.hpp>
#include <unistd.h>


/*
	program \
		--mode mode \
		--model model \
		--protofile protofile\
		--weightsfile weightfile\
		--threshhold 0.1\
		--width 368\
		-i infile.jpg\
		-o outfile.jpg
*/

int main(int argc, char** argv){
	// std::string protoFile = "../pose/mpi/pose_deploy_linevec_faster_4_stages.prototxt";
	// std::string weightsFile = "/home/prototano/Projects/UA/4/TFG/open-pose/pose/coco/pose_iter_440000.caffemodel";
	
	Config conf{argc, argv};
	conf.show();

	Skeleton::loadNetwork(conf.protoFile, conf.weightsFile);	

	if(conf.mode == Config::Mode::streaming){
		cv::VideoCapture capture{0};
		cv::Mat frame;
		if(capture.isOpened()){
			for(;;){
				debug_timer_start(jajaja)
				capture >> frame;
				Skeleton skltn(frame, conf.threshhold, conf.width);
				skltn.show("jajajaja");
				debug_timer_finish(jajaja)
			}
		}
	}else{
		Skeleton skltn(conf.inFile, conf.threshhold, conf.width);
		skltn.saveImage(conf.outFile);
	}


	return 0;
}
