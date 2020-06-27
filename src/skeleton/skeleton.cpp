#include <skeleton/skeleton.hpp>
#include <util/debug.hpp>
#include <skeleton/model/modelcoco.hpp>
#include <skeleton/model/modelmpii.hpp>
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

	for(unsigned int joint=0; joint < Skeleton::model->getMaxJoints(); ++joint){
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

	for(unsigned int joint=0; joint < Skeleton::model->getMaxJoints(); ++joint){
		double maxVal;
		cv::Point maxLoc;
		cv::minMaxLoc(netOutputParts[joint],0,&maxVal,0,&maxLoc);
		if(maxVal > threshhold){
			jointsVec[joint]=maxLoc;
		}

	}
}

Skeleton::Skeleton(
		std::string_view filename,
		double threshhold,
		int width,
		double orientation) :
	image { cv::imread(filename.data(), cv::IMREAD_COLOR)}
{
	if(orientation != 0){
		rotateMat(orientation, image);
	}
	this->jointsVec.resize(Skeleton::model->getMaxJoints());
	extractJoints2(threshhold,width);
	if(orientation != 0){
		rotate(-orientation);
	}
}

Skeleton::Skeleton(
		const cv::Mat& img,
		double threshhold,
		int width,
		double orientation) :
	image {img}
{
	if(orientation != 0){
		rotateMat(orientation, image);
	}
	this->jointsVec.resize(Skeleton::model->getMaxJoints());
	extractJoints2(threshhold,width);
	if(orientation != 0){
		rotate(-orientation);
	}
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
	for( auto& [j1, j2] : Skeleton::model->getPairs() ){
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


void Skeleton::rotateMat(double angle, cv::Mat& m){
	// get rotation matrix for rotating the image around its center in pixel
	// coordinates
	cv::Point2f center((m.cols-1)/2.0, (m.rows-1)/2.0);
	cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);

	// determine bounding rectangle, center not relevant
	cv::Rect2f bbox = cv::RotatedRect(
			cv::Point2f(),
			m.size(),
			angle).boundingRect2f();

	// adjust transformation matrix
	rot.at<double>(0,2) += bbox.width/2.0 - m.cols/2.0;
	rot.at<double>(1,2) += bbox.height/2.0 - m.rows/2.0;

	cv::Mat dst;
	cv::warpAffine(m, dst, rot, bbox.size());
	m=dst;
};

//Rotates entire skeleton
void Skeleton::rotate(double degrees){
	if(degrees == 0){
		return;
	}
	int rows {image.rows};
	int cols {image.cols};

	rotateMat(degrees, image);

	for(auto& jointOp : jointsVec){
		if(jointOp){
			cv::Mat mAux {cv::Size(cols, rows), CV_8U, cv::Scalar{0}};
			mAux.at<char>(jointOp.value()) = 1;
			rotateMat(degrees, mAux);
			cv::minMaxLoc(mAux,0,0,0,&jointOp.value());
		}
	}
}


void Skeleton::loadNetwork(std::string_view prototxt, std::string_view caffeModel, Skeleton::ModelType mtype){
	neuralNet = cv::dnn::readNetFromCaffe(prototxt.data(), caffeModel.data());
	if(mtype == Skeleton::mpii){
		Skeleton::model = std::make_unique<ModelMPII>();
	}else{
		Skeleton::model = std::make_unique<ModelCoco>();
	}
}

