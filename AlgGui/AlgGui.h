#pragma once

#include <QtWidgets/QDialog>
#include <QtCore>
#include <qfiledialog.h>
#include "ui_AlgGui.h"
#include <algWrap.h>
//#include "YoloDetector2.h"
#include <yolo_v2_class.hpp>

#include <opencv2/opencv.hpp>
//#include <opencv2/highgui.hpp>
using namespace cv;
using namespace algutil;


class AlgGui : public QDialog
{
	Q_OBJECT

public:
	
	AlgGui(QWidget *parent = Q_NULLPTR);

	


protected:
	VideoCapture capture;
	Mat frame_cv;
	QImage frame_qt;
	QImage frameToShow;
	std::string filePath_cv;
	std::string alarmPath_cv;// 报警图片保存路径

	Mat BG;
	Mat FGMask;
	Mat tsoImg;
	Mat traceImg;
	Mat alarmImg;
	QImage BGToShow;
	QImage FGMaskToShow;
	QImage tsoImgToShow;
	QImage traceImgToShow;
	QImage alarmImgToShow;

	Mat noDrawAlarmImg;

	int alarmCount = 0;// 报警计数，用于和nowYoloCount协同工作

	/*** param ***/
	int wayOfResize = cv::INTER_AREA;
	int isYolo;
	int yoloVerFlag;
	int alarmTime;
	enum yoloWay{
		NO_YOLO              = 0,
		YOLO_ALL_TIME        = 1,
		YOLO_ONLY_ALARM_TIME = 2
	};
	enum yoloVer {
		YOLO_V3       = 1,
		YOLO_V3_TINY  = 2
	};
	double yoloThresh;
	/*** param ***/


	/*** yolo使用 ***/
	std::shared_ptr<Detector> detector = nullptr;
	std::vector<std::string> obj_names;

	int nowYoloCount = 0;// 用于确认是否有报警图片需要进行yolo识别
	/*** yolo使用 ***/

	/***** algWrap使用 *****/
	BGCallBack bgcb;
	BBoxCallBack bboxcb;
	int width;
	int height;
	RGBData rgbdata;
	//Region region;
	RegionParam rp;

	Region getRegion(int width, int height)
	{
		algutil::Point point;
		Region region;

		point = algutil::Point(0, 0);
		region.emplace_back(point);

		point = algutil::Point(width - 1, 0);
		region.emplace_back(point);

		point = algutil::Point(width - 1, height - 1);
		region.emplace_back(point);

		point = algutil::Point(0, height - 1);
		region.emplace_back(point);

		return region;
	}


	// bg回调函数. static 解决类中回调函数的类指针问题。
	static void bgCallBack(RGBData backgroundImg, bool endFlag, void* data);

	// bbox回调函数. static 解决类中回调函数的类指针问题。
	static void bboxCallBack(std::vector<BBox> boxes, RGBData frame, void* data);

	void bgCallBack_intern(RGBData backgroundImg, bool endFlag, void* data) {
		if (endFlag)
		{
			Mat help(backgroundImg.height, backgroundImg.width, CV_8UC3, backgroundImg.data);
			help.copyTo(BG);
		}
	}

	// bbox回调函数
	void bboxCallBack_intern(std::vector<BBox> boxes, RGBData frame, void* data)
	{
		Mat help(frame.height, frame.width, CV_8UC3, frame.data);
		Mat help2 = help.clone();
		Mat drawFrame;

		if (!boxes.empty())
		{
			for (auto& box : boxes) {
				Rect rect(box.x, box.y, box.w, box.h);

				if (box.type == 0) {
					rectangle(help2, rect, Scalar(255, 0, 0), 2);
				}
				else
				{
					if (isYolo == NO_YOLO) 
					{
						help.copyTo(drawFrame);// 因为浅拷贝，故frame会实时改变
						rectangle(drawFrame, rect, Scalar(0, 0, 255), 2);
						//imshow("real alarm(over time)", drawFrame);
						drawFrame.copyTo(alarmImg);

						std::cout << "C:\\Users\\chen\\Desktop\\QtTest\\AlgGui\\alarmImg\\" + std::to_string(alarmCount) + ".jpg" << std::endl;
						imwrite("C:\\Users\\chen\\Desktop\\QtTest\\AlgGui\\alarmImg\\" + std::to_string(alarmCount) + ".jpg", alarmImg);
					}
					else
					{
						help.copyTo(noDrawAlarmImg);// 因为浅拷贝，故frame会实时改变
						noDrawAlarmImg.copyTo(alarmImg);
						rectangle(alarmImg, rect, Scalar(0, 0, 255), 2);
						//imshow("real alarm(over time)", drawFrame);

						std::cout << "C:\\Users\\chen\\Desktop\\QtTest\\AlgGui\\alarmImg\\" + std::to_string(alarmCount) + ".jpg" << std::endl;
						imwrite("C:\\Users\\chen\\Desktop\\QtTest\\AlgGui\\alarmImg\\" + std::to_string(alarmCount) + ".jpg", alarmImg);
					}


					alarmCount++;
				}
			}
		}
		help2.copyTo(traceImg);
		//imshow("trace from main", help2);
		//waitKey(1);
	}
	/***** algWrap使用 *****/


	bool isClickToClose = false;

	void videoWinAllClear();
	void clearAllImgCache();
	void disableAllParamSet();
	void enableAllParamSet();

private:
	Ui::AlgGuiClass ui;
	static AlgGui* p;

	void startShowVideo(std::string path);
	
private slots:
	void on_BtnExit_clicked();
	void on_BtnFilePath_clicked();
	void on_BtnCloseVideo_clicked();


	

};
