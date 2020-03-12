#include "skeleton.hpp"
#include "util/debug.hpp"
#include <opencv2/dnn.hpp>
#include <chrono>



std::vector<cv::Mat> splitNetOutput(cv::Mat& outBlob, const cv::Size targetSize){
	std::vector<cv::Mat> splitedBlob;

	int nParts = outBlob.size[1];
	int h = outBlob.size[2];
	int w = outBlob.size[3];

	for(int i=0; i < nParts; ++i){
		cv::Mat part(h, w, CV_32F, outBlob.ptr(0,i));
		auto& resizedPart = splitedBlob.emplace_back();
		cv::resize(part, resizedPart, targetSize);
	}

	return splitedBlob;
}

cv::Mat Skeleton::processImage(int width){

	//START CHRONO
	debug_timer_start(Process_Image)
	
	//Generate input blob from image
	auto inputBlob = cv::dnn::blobFromImage(
		image, 
		1.0/255.0, 
		cv::Size((int)((width*image.cols)/image.rows),width),
		cv::Scalar(0,0,0),
		false,
		false);

	//Process image
	neuralNet.setInput(inputBlob);
	auto netOutputBlob = neuralNet.forward();
	
	//END CHRONO
	debug_timer_finish(Process_Image)

	return netOutputBlob;
}

void Skeleton::extractJoints2(double threshhold=0.1, int width=368){
	// debug("HOLAAA")
	auto netOutputBlob = processImage(width);

	int h = netOutputBlob.size[2];
	int w = netOutputBlob.size[3];

	for(int joint=0; joint < Joint::JOINTCOUNT; ++joint){
		double maxVal;
		cv::Point maxLoc;
		cv::Mat part(h, w, CV_32F, netOutputBlob.ptr(0,joint));
		cv::minMaxLoc(part,0,&maxVal,0,&maxLoc);
		double x = (double)maxLoc.x/(double)w*(double)image.size().width;
		double y = (double)maxLoc.y/(double)h*(double)image.size().height;
		if(maxVal > threshhold){
			jointsVec[joint]=cv::Point(x,y);	
		}
	
	}
}

void Skeleton::extractJoints(double threshhold=0.1, int width=368){
	auto netOutputBlob = processImage(width);
	auto netOutputParts = splitNetOutput(netOutputBlob, cv::Size(image.cols,image.rows));

	for(int joint=0; joint < Joint::JOINTCOUNT; ++joint){
		double maxVal;
		cv::Point maxLoc;
		cv::minMaxLoc(netOutputParts[joint],0,&maxVal,0,&maxLoc);
		if(maxVal > threshhold){
			jointsVec[joint]=maxLoc;	
		}
	
	}
}

Skeleton::Skeleton(std::string_view filename, double threshhold, int width) : image { cv::imread(filename.data(), cv::IMREAD_COLOR)}{
	extractJoints2(threshhold,width);
	paint();
}

Skeleton::Skeleton(const cv::Mat& img, double threshhold, int width) : image {img}{
	extractJoints2(threshhold,width);
	paint();
}

void Skeleton::show(std::string_view windowName) const{
	cv::imshow(windowName.data(),image);
	cv::waitKey(1);
}

void Skeleton::saveImage(std::string_view filename) const{
	cv::imwrite( filename.data(), image );
}

void Skeleton::paint(){
	auto& outputFrame = image;
	for( auto& [j1, j2] : Skeleton::pairs ){
		if(jointsVec[j1] && jointsVec[j2]){
			cv::line(
				outputFrame, 
				jointsVec[j1].value(), 
				jointsVec[j2].value(), 
				cv::Scalar(255,0,0),
				5);
		}
	}
	for(auto& joint : jointsVec){
		if(joint){
			cv::circle(
				outputFrame, 
				joint.value(),
				10, 
				cv::Scalar(0,255,0),
				-1,
				cv::LINE_AA);
		}
	}
}

void Skeleton::loadNetwork(std::string_view prototxt, std::string_view caffeModel){
	neuralNet = cv::dnn::readNetFromCaffe(prototxt.data(), caffeModel.data());
}

