#pragma once

#include <QtWidgets/QDialog>
#include <QtCore>
#include <qfiledialog.h>
#include "ui_AlgGui.h"
#include "algwrap.h"

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
	static Mat _BG;
	Mat FGMask;
	Mat tsoImg;
	Mat traceImg;
	static Mat _traceImg;
	Mat alarmImg;
	static Mat _alarmImg;
	QImage BGToShow;
	QImage FGMaskToShow;
	QImage tsoImgToShow;
	QImage traceImgToShow;
	QImage alarmImgToShow;

	/*** param ***/
	int wayOfResize = cv::INTER_AREA;
	int isYolo;
	int alarmTime;
	enum {
		NO_YOLO              = 0,
		YOLO_ALL_TIME        = 1,
		YOLO_ONLY_ALARM_TIME = 2
	};
	/*** param ***/

	/***** algWrap使用 *****/
	BGCallBack bgcb;
	BBoxCallBack bboxcb;
	int width;
	int height;
	RGBData rgbdata;
	Region region;
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


	// bg回调函数
	static void bgCallBack(RGBData backgroundImg, bool endFlag, void* data);

	// bbox回调函数
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
					help.copyTo(drawFrame);// 因为浅拷贝，故frame会实时改变
					rectangle(drawFrame, rect, Scalar(0, 0, 255), 2);
					//imshow("real alarm(over time)", drawFrame);
					drawFrame.copyTo(alarmImg);
				}
			}
		}
		help2.copyTo(traceImg);
		//imshow("trace from main", help2);
		//waitKey(1);
	}
	
	/***** algWrap使用 *****/



	Mat bgImg;
	//Mat fgImg;
	//Mat tsoImg;
	QImage bgImg_qt;
	//QImage fgImg_qt;
	//QImage tsoImg_qt;

	//Mat alarmImg;
	//QImage alarmImg_qt;



	bool isClickToClose = false;

	void videoWinAllClear();
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
