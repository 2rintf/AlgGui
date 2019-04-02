#include "YoloDetector2.h"

/**构造器默认支持。可通过接口自定义yolo版本的cfg和weights。
检测方式支持:   YoloWay::YOLO_ALL_TIME | YoloWay::YOLO_FOR_ALARM
YOLO版本支持:  YoloVer::YOLO_V3 | YoloVer::YOLO_V3_TINY
*/
YoloDetector2::YoloDetector2(int yoloWay, int yoloVer)
{
	switch (yoloWay)
	{
	default:
		break;
	case(YoloWay::YOLO_ALL_TIME):
		yoloWayFlag = YoloWay::YOLO_ALL_TIME;
		break;
	case(YoloWay::YOLO_FOR_ALARM):
		yoloWayFlag = YoloWay::YOLO_FOR_ALARM;
		break;
	}

	switch (yoloVer)
	{
	default:
		break;
	case(YoloVer::YOLO_V3):
		cfg_file = "yolov3.cfg";
		weights_file = "yolov3.weights";
		break;
	case(YoloVer::YOLO_V3_TINY):
		cfg_file = "yolov3-tiny.cfg";
		weights_file = "yolov3-tiny.weights";
		break;
	}

	names_file = "coco.names";
}


YoloDetector2::~YoloDetector2()
{

}

// 创建检测器实例
void YoloDetector2::initialize(int gpu_id)
{
	detectAPI = createDarknetDetector(cfg_file, weights_file, gpu_id);
	obj_names = objects_names_from_file(names_file);
	//return detectAPI;
}
// 创建检测器实例(自定义)
void YoloDetector2::initialize(std::string cfg_filename, std::string weights_filename, std::string names_filename, int gpu_id)
{
	cfg_file = cfg_filename;
	weights_file = weights_filename;
	names_file = names_filename;

	detectAPI = createDarknetDetector(cfg_file, weights_file, gpu_id);
	obj_names = objects_names_from_file(names_file);
}

void YoloDetector2::draw_boxes(cv::Mat& mat_img, std::vector<bbox_t> result_vec, int current_det_fps, int current_cap_fps)
{
	if (obj_names.empty()) {
		std::cout << "names_file initialize failed!" << std::endl;
		return;
	}

	int const colors[6][3] = { { 1,0,1 },{ 0,0,1 },{ 0,1,1 },{ 0,1,0 },{ 1,1,0 },{ 1,0,0 } };
	for (auto &i : result_vec) {
		cv::Scalar color = obj_id_to_color(i.obj_id);
		cv::rectangle(mat_img, cv::Rect(i.x, i.y, i.w, i.h), color, 2);
		if (obj_names.size() > i.obj_id) {
			std::string obj_name = obj_names[i.obj_id];
			if (i.track_id > 0) obj_name += " - " + std::to_string(i.track_id);
			cv::Size const text_size = getTextSize(obj_name, cv::FONT_HERSHEY_COMPLEX_SMALL, 1, 2, 0);
			int const max_width = (text_size.width > i.w + 2) ? text_size.width : (i.w + 2);
			cv::rectangle(mat_img, cv::Point2f(std::max((int)i.x - 1, 0), std::max((int)i.y - 30, 0)),
				cv::Point2f(std::min((int)i.x + max_width, mat_img.cols - 1), std::min((int)i.y, mat_img.rows - 1)),
				color, CV_FILLED, 8, 0);
			putText(mat_img, obj_name, cv::Point2f(i.x, i.y - 10), cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0, 0, 0), 2);
		}
	}


}

std::vector<std::string> YoloDetector2::objects_names_from_file(std::string const filename)
{
	std::ifstream file(filename);
	std::vector<std::string> file_lines;
	if (!file.is_open()) return file_lines;
	for (std::string line; getline(file, line);) file_lines.push_back(line);
	std::cout << "object names loaded \n";
	return file_lines;
}

std::vector<bbox_t> YoloDetector2::detect(cv::Mat frame, float thresh, bool use_mean)
{
	image_t imgTFromFrame = image_to_Mat(frame.data, frame.cols, frame.rows);
	return detectAPI->detect(imgTFromFrame, thresh, use_mean);
}

image_t YoloDetector2::image_to_Mat(unsigned char * src, int width, int height)
{
	unsigned char *data = src;
	int h = height;
	int w = width;
	int c = 3;
	int step = width * c;
	//image_t out = make_image(w, h, c);
	image_t out = make_empty_image(w, h, c);

	int i, j, k, count = 0;;

	for (k = 0; k < c; ++k) {
		for (i = 0; i < h; ++i) {
			for (j = 0; j < w; ++j) {
				out.data[count++] = data[i*step + j * c + k] / 255.;
			}
		}
	}
	return out;
}


