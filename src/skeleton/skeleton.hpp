#include <string>
#include <iostream>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <tuple>
#include <string_view>
#include <optional>

constexpr int nPoints = 18;


//using Skeleton =  std::map<std::string, cv::Point>;

struct Skeleton{
	enum Joint {
		NOSE, 
		NECK, 
		R_SHO,
		R_ELB,
		R_WR, 
		L_SHO,
		L_ELB,
		L_WR,
		R_HIP,
		R_KNEE,
		R_ANK, 
		L_HIP,
		L_KNEE,
		L_ANK,
		R_EYE,
		L_EYE,
		R_EAR,
		L_EAR,
		JOINTCOUNT};

	inline static constexpr std::tuple<Joint,Joint> pairs[] = {
		{NOSE, NECK},
		{NECK, R_SHO},
		{NECK, L_SHO},
		{R_SHO, R_ELB},
		{L_SHO, L_ELB},
		{R_ELB, R_WR},
		{L_ELB, L_WR},
		{R_SHO, R_HIP},
		{L_SHO, L_HIP},
		{R_HIP, L_HIP},
		{R_HIP, R_KNEE},
		{L_HIP, L_KNEE},
		{R_KNEE, R_ANK},
		{L_KNEE, L_ANK},
	};

	inline static constexpr const char* jointsStr[] = {
		"Nose", 
		"Neck",
		"R-Sho", 
		"R-Elb", 
		"R-Wr",
		"L-Sho", 
		"L-Elb", 
		"L-Wr",
		"R-Hip", 
		"R-Knee", 
		"R-Ank",
		"L-Hip", 
		"L-Knee", 
		"L-Ank",
		"R-Eye", 
		"L-Eye", 
		"R-Ear", 
		"L-Ear"};

	explicit Skeleton(std::string_view filename, double threshhold=0.1, int width=368);
	explicit Skeleton(const cv::Mat& img, double threshhold=0.1, int width=368);



	const std::optional<cv::Point>& getJointPos(Joint j) const;
	void show(std::string_view windowName) const;
	void saveImage(std::string_view filename) const;
	static void loadNetwork(std::string_view prototxt, std::string_view caffeModel);

	//
	//PRIVATE STUFF
	//
	private:
	std::vector<std::optional<cv::Point>> jointsVec {Joint::JOINTCOUNT};
	cv::Mat image {};
	void extractJoints(double threshhold, int width);
	void extractJoints2(double threshhold, int width);
	cv::Mat processImage(int width);
	void paint();
	inline static cv::dnn::Net neuralNet {};

};
