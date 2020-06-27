#pragma once

#include <string>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <string_view>
#include <optional>
#include <memory>
#include <skeleton/model/imodel.hpp>



struct Skeleton{

	enum ModelType {coco, mpii};

	explicit Skeleton(
			std::string_view filename,
			double threshhold=0.1,
			int width=368,
			double orientation=0.0);

	explicit Skeleton(
			const cv::Mat& img,
			double threshhold=0.1,
			int width=368,
			double orientation=0.0);


	const std::optional<cv::Point>& getJointPos(unsigned int j) const {return jointsVec.at(j);};
	void show(std::string_view windowName) const;
	void saveImage(std::string_view filename) const;
	static void loadNetwork(std::string_view prototxt, std::string_view caffeModel, ModelType mtype);
	void paint();
	constexpr const cv::Mat& getImage() const {return image;};
	inline static std::unique_ptr<IModel> model {nullptr};


	//
	//PRIVATE STUFF
	//
	private:
	std::vector<std::optional<cv::Point>> jointsVec {};
	cv::Mat image {};
	void extractJoints(double threshhold, int width);
	void extractJoints2(double threshhold, int width);
	cv::Mat processImage(int width);
	void rotate(double degrees);
	static void rotateMat(double angle, cv::Mat& m);
	inline static cv::dnn::Net neuralNet {};
};

