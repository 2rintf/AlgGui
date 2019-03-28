#ifdef _WIN32
#define OPENCV
#define GPU
#endif


#include <yolo_v2_class.hpp>
#include <opencv2/opencv.hpp>



class YoloDetector2
{
public:
	/**构造器默认支持。可通过接口自定义yolo版本的cfg和weights。
	检测方式支持:   YoloWay::YOLO_ALL_TIME | YoloWay::YOLO_FOR_ALARM
	YOLO版本支持:  YoloVer::YOLO_V3 | YoloVer::YOLO_V3_TINY
	*/
	YoloDetector2(int yoloWay, int yoloVer);
	~YoloDetector2();


	// YOLO使用方式
	enum YoloWay
	{
		YOLO_FOR_ALARM = 1,     // 只对报警图片进行识别
		YOLO_ALL_TIME = 2      // 实时识别(GPU high consumption)
	};

	// 使用YOLO版本
	enum YoloVer
	{
		YOLO_V3 = 3,
		YOLO_V3_TINY = 4
	};


	// 创建检测器实例
	void initialize(int gpu_id = 0);
	// 创建检测器实例(自定义)
	void initialize(std::string cfg_filename, std::string weights_filename, std::string names_filename, int gpu_id = 0);

	void draw_boxes(cv::Mat& mat_img, std::vector<bbox_t> result_vec, int current_det_fps = -1, int current_cap_fps = -1);
	std::vector<std::string> objects_names_from_file(std::string const filename);
	std::vector<bbox_t> detect(cv::Mat frame, float thresh, bool use_mean = false);
	image_t image_to_Mat(unsigned char * src, int width, int height);

protected:
	std::shared_ptr<Detector> detectAPI = nullptr;
	std::string names_file;
	std::string cfg_file;
	std::string weights_file;
	std::vector<std::string> obj_names;


	int yoloWayFlag;
	int yoloVerFlag;

private:
	image_t make_empty_image(int w, int h, int c)
	{
		image_t out;
		out.data = 0;
		out.h = h;
		out.w = w;
		out.c = c;
		return out;
	}
	image_t make_image(int w, int h, int c)
	{
		image_t out = make_empty_image(w, h, c);
		out.data = (float*)calloc(h*w*c, sizeof(float)); //这边估计要保留下来，这块内存
		return out;
	}

	void rgbgr_image(image_t im)
	{
		int i;
		for (i = 0; i < im.w*im.h; ++i) {
			float swap = im.data[i];
			im.data[i] = im.data[i + im.w*im.h * 2];
			im.data[i + im.w*im.h * 2] = swap;
		}
	}

};




