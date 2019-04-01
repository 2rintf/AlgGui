#pragma execution_character_set("utf-8")

#include "AlgGui.h"




/************** utils func *********************/

// [utils func]. 用于clear所有显示图片的label.
void AlgGui::videoWinAllClear()
{
	ui.frameLabel->clear();
	ui.bgLabel->clear();
	ui.fgLabel->clear();
	ui.tsoLabel->clear();
	ui.alarmImgLabel->clear();
}

// [utils func]. 用于clear所有显示图片变量的cache.
void AlgGui::clearAllImgCache()
{
	BG = Scalar::all(0);
	FGMask = Scalar::all(0);
	tsoImg = Scalar::all(0);
	traceImg = Scalar::all(0);
}

// [utils func]. 用于视频开始时，disable所有参数选项.
//               将所有参数选项栏都放在paramGroupBox中,就可以一次性操作。
void AlgGui::disableAllParamSet()
{
	//ui.BoxOfResizeWay->setDisabled(true);
	//ui.BoxOfIsYolo->setDisabled(true);

	ui.paramGroupBox->setDisabled(true);
}

// [utils func]. 用于视频结束后，enable所有参数选项.
void AlgGui::enableAllParamSet()
{
	//ui.BoxOfResizeWay->setEnabled(true);
	//ui.BoxOfIsYolo->setEnabled(true);

	ui.paramGroupBox->setEnabled(true);
}

// [utils func]. 编码转换，可以转为本机编码，防止乱码。
QString str2qstr(const std::string str)
{
	return QString::fromLocal8Bit(str.data());
}

// [utils func]. 编码转换，可以转为本机编码，防止乱码。
std::string qstr2str(const QString qstr)
{
	QByteArray cdata = qstr.toLocal8Bit();
	return std::string(cdata);
}
/**************** utils func end ****************/

AlgGui* AlgGui::p = NULL;
void AlgGui::bgCallBack(RGBData backgroundImg, bool endFlag, void* data)
{
	if (p == NULL)
		return;
	p->bgCallBack_intern(backgroundImg, endFlag, data);

}

void AlgGui::bboxCallBack(std::vector<BBox> boxes, RGBData frame, void* data)
{
	if (p == NULL)
	{
		return;
	}
	p->bboxCallBack_intern(boxes, frame, data);
}


AlgGui::AlgGui(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	p = this;
}


void AlgGui::on_BtnExit_clicked()
{
	exit(1);
}

void AlgGui::on_BtnCloseVideo_clicked()
{
	isClickToClose = true;
}

void AlgGui::on_BtnFilePath_clicked()
{

	// 重置报警计数Flag
	alarmCount = 0;
	nowYoloCount = 0;

	/*****************确认输入参数-START************************/
	std::cout << "===========param used==============" << std::endl;

	// 显示视频时的resize方式
	int IndexOfResizeWay = ui.BoxOfResizeWay->currentIndex();// default is INTER_AREA.
	switch (IndexOfResizeWay)
	{
	default:
		break;
	case(0):
		wayOfResize = cv::INTER_AREA;
		std::cout << "INTER_AREA" << std::endl;
		break;
	case(1):
		wayOfResize = cv::INTER_NEAREST;
		std::cout << "INTER_NEAREST" << std::endl;
		break;
	}

	// 是否选择YOLO
	int IndexOfYolo = ui.BoxOfIsYolo->currentIndex();// default is NO.
	switch (IndexOfYolo)
	{
	default:
		break;
	case(0):
		isYolo = NO_YOLO;
		std::cout << "NO YOLO" << std::endl;
		break;
	case(1):
		isYolo = YOLO_ALL_TIME;
		std::cout << "with YOLO all time" << std::endl;
		break;
	case(2):
		isYolo = YOLO_ONLY_ALARM_TIME;
		std::cout << "with YOLO only alarm time" << std::endl;
		break;
	}

	// YOLO版本选择
	int IndexOfYoloVer = ui.BoxOfYoloVer->currentIndex();
	switch (IndexOfYoloVer)
	{
	default:
		break;
	case(0):
		yoloVerFlag = YOLO_V3_TINY;
		std::cout << "YOLO ver: YOLO_V3_TINY" << std::endl;
		break;
	case(1):
		yoloVerFlag = YOLO_V3;
		std::cout << "YOLO ver: YOLO_V3" << std::endl;
	}

	// YOLO阈值
	yoloThresh = ui.BoxOfYoloThresh->value();
	std::cout << "YOLO thresh: " << yoloThresh << std::endl;


	// alarmTime
	alarmTime = ui.BoxOfAlarmTime->value();
	std::cout << "alarm time: " << alarmTime << std::endl;


	std::cout << "===========param used==============" << std::endl;
	/*****************确认输入参数-END************************/



	QString filePath = QFileDialog::getOpenFileName(this, "请选择视频...", "./", "*.mp4");//.toUtf8()
	if (filePath.isEmpty())
	{
		qDebug() << "file path NULL!" << endl;
		return;
	}
	else {
		qDebug() << filePath << endl;
		filePath_cv = qstr2str(filePath);
		//filePath_cv = filePath.toStdString();
		std::cout << "std::string = " << filePath_cv << std::endl;
	}

	// disable参数选项
	disableAllParamSet();

	// 开始视频处理
	startShowVideo(filePath_cv);

	// 视频结束，enable参数选项
	enableAllParamSet();


}


/*******具体操作函数*********/
void AlgGui::startShowVideo(std::string path)
{
	capture.open(path);
	capture >> frame_cv;
	width = frame_cv.cols;
	height = frame_cv.rows;
	Region region = getRegion(width, height);
	rgbdata = RGBData((char*)frame_cv.data, width, height);

	rp = RegionParam(region, 0.0011f, alarmTime, 120, { 0,0.3f,3.5f,9999 });


	PtrALGWrap api = createALGWrap(bgCallBack, bboxCallBack, nullptr, nullptr, width, height);


	if (isYolo != NO_YOLO)
	{
		//std::string names_file = "coco.names";
		//std::string cfg_file = "yolov3-tiny.cfg";
		//std::string weights_file = "yolov3-tiny.weights";

		//std::cout << cfg_file << std::endl;
		//detector = createDarknetDetector(cfg_file, weights_file, 0);
		//obj_names = objects_names_from_file(names_file);

		if (yoloVerFlag == YOLO_V3)
		{
			std::string cfg_file = "yolov3.cfg";
			std::string weights_file = "yolov3.weights";
			detector = api->YOLOInitializeSelf(cfg_file, weights_file, 0);
			obj_names = api->setNamesFile();
		}
		else
		{
			detector = api->YOLOInitialize();
			obj_names = api->setNamesFile();
		}

	}


	api->add(rp, true);

	for (;;) {
		if (isClickToClose) {
			videoWinAllClear();
			clearAllImgCache();
			isClickToClose = false;
			break;
		}
		capture >> frame_cv;
		// 如果视频结束，break
		if (frame_cv.empty())
		{
			//ui.frameLabel->setText("End.");
			videoWinAllClear();
			break;
		}

		rgbdata = RGBData((char*)frame_cv.data, width, height);

		double start3 = (double)cv::getTickCount();
		//update the background model
		api->work(rgbdata);



		//get fgmask
		api->getFgMask(FGMask);
		if (!FGMask.empty())
		{
			//imshow("fgmask from main", FGMask);
			Mat transHelp;
			cvtColor(FGMask, transHelp, COLOR_BGR2RGB);
			cv::resize(transHelp, transHelp, cv::Size(ui.fgLabel->width(), ui.fgLabel->height()), wayOfResize);
			FGMaskToShow = QImage((const unsigned char*)(transHelp.data), transHelp.cols, transHelp.rows, transHelp.step, QImage::Format_RGB888);
			ui.fgLabel->setPixmap(QPixmap::fromImage(FGMaskToShow));
		}


		//get tso
		api->getTsoEvidence(tsoImg);
		if (!tsoImg.empty()) {
			//imshow("tso from main", tsoImg);
			Mat transHelp;
			cvtColor(tsoImg, transHelp, COLOR_BGR2RGB);
			cv::resize(transHelp, transHelp, cv::Size(ui.tsoLabel->width(), ui.tsoLabel->height()), wayOfResize);
			tsoImgToShow = QImage((const unsigned char*)(transHelp.data), transHelp.cols, transHelp.rows, transHelp.step, QImage::Format_RGB888);
			ui.tsoLabel->setPixmap(QPixmap::fromImage(tsoImgToShow));
		}

		// get bg
		if (!BG.empty())
		{
			Mat transHelp;
			cvtColor(BG, transHelp, COLOR_BGR2RGB);
			cv::resize(transHelp, transHelp, cv::Size(ui.bgLabel->width(), ui.bgLabel->height()), wayOfResize);
			BGToShow = QImage((const unsigned char*)(transHelp.data), transHelp.cols, transHelp.rows, transHelp.step, QImage::Format_RGB888);
			ui.bgLabel->setPixmap(QPixmap::fromImage(BGToShow));
		}

		// 对于frameLabel的处理 (必须在BG初始学习完毕后，这样子就不会受到yolo速度慢的影响，导致背景学习帧数减少)
		if (api->isLearnedBG()) {
			if (isYolo == NO_YOLO)// 没有选择YOLO，则直接显示traceImg.
			{
				if (!traceImg.empty())
				{
					Mat transHelp;
					cvtColor(traceImg, transHelp, COLOR_BGR2RGB);
					cv::resize(transHelp, transHelp, cv::Size(ui.frameLabel->width(), ui.frameLabel->height()), wayOfResize);
					traceImgToShow = QImage((const unsigned char*)(transHelp.data), transHelp.cols, transHelp.rows, transHelp.step, QImage::Format_RGB888);
					ui.frameLabel->setPixmap(QPixmap::fromImage(traceImgToShow));
				}
			}
			else if (isYolo == YOLO_ALL_TIME)// 选择实时YOLO，则对frame进行yolo识别，然后显示.
			{
				// 将traceImg当作背景学习初始化的flag
				if (!traceImg.empty())
				{

					image_t imgFromFrame = api->image_to_Mat(frame_cv.data, frame_cv.cols, frame_cv.rows);

					std::vector<bbox_t> result_vec = detector->detect(imgFromFrame, yoloThresh);
					api->draw_boxes(frame_cv, result_vec, obj_names);

					free(imgFromFrame.data);// 释放内存！！


					Mat transHelp;
					cvtColor(frame_cv, transHelp, COLOR_BGR2RGB);
					cv::resize(transHelp, transHelp, cv::Size(ui.frameLabel->width(), ui.frameLabel->height()), wayOfResize);
					traceImgToShow = QImage((const unsigned char*)(transHelp.data), transHelp.cols, transHelp.rows, transHelp.step, QImage::Format_RGB888);
					ui.frameLabel->setPixmap(QPixmap::fromImage(traceImgToShow));
				}
			}
			else if (isYolo == YOLO_ONLY_ALARM_TIME)// 选择yolo只识别报警图片，则取noDrawAlarmImg进行yolo的detect，然后画框于alarmImg，并显示.
			{
				// TO-DO
				if (!traceImg.empty())
				{
					if (nowYoloCount != alarmCount)
					{
						image_t imgFromFrame = api->image_to_Mat(noDrawAlarmImg.data, noDrawAlarmImg.cols, noDrawAlarmImg.rows);

						std::vector<bbox_t> result_vec = detector->detect(imgFromFrame, yoloThresh);// 检测的时候使用无画框的图片进行detect
						api->draw_boxes(alarmImg, result_vec, obj_names);// 画yolo框时用有画框的图片

						free(imgFromFrame.data);// 释放内存！！

						imwrite("C:\\Users\\chen\\Desktop\\QtTest\\AlgGui\\alarmImg\\" + std::to_string(nowYoloCount) + "_yolo.jpg", alarmImg);
						nowYoloCount++;


						Mat transHelp;
						cvtColor(alarmImg, transHelp, COLOR_BGR2RGB);
						cv::resize(transHelp, transHelp, cv::Size(ui.alarmImgLabel->width(), ui.alarmImgLabel->height()), wayOfResize);
						alarmImgToShow = QImage((const unsigned char*)(transHelp.data), transHelp.cols, transHelp.rows, transHelp.step, QImage::Format_RGB888);
						ui.alarmImgLabel->setPixmap(QPixmap::fromImage(alarmImgToShow));
					}


					Mat transHelp;
					cvtColor(traceImg, transHelp, COLOR_BGR2RGB);
					cv::resize(transHelp, transHelp, cv::Size(ui.frameLabel->width(), ui.frameLabel->height()), wayOfResize);
					traceImgToShow = QImage((const unsigned char*)(transHelp.data), transHelp.cols, transHelp.rows, transHelp.step, QImage::Format_RGB888);
					ui.frameLabel->setPixmap(QPixmap::fromImage(traceImgToShow));

				}
			}
		}


		double time3 = ((double)(cv::getTickCount() - start3)) * 1000 / getTickFrequency();
		std::cout << "all cost : " << time3 << "ms" << std::endl;
		//Mat transHelp;
		//cvtColor(frame_cv, transHelp, COLOR_BGR2RGB);

		//double start3 = (double)cv::getTickCount();
		//// Debug Mode : default(INTER_NEAREST -- bilinear interpolation) cost about 15ms. 
		////              INTER_NEAREST(-- nearest neighbor interpolation) cost about 5ms, but terrible effect.(!其速度是呈抛物线式，非单纯线性)
		////              INTER_AREA(-- resampling using pixel area relation) cost about 45ms, but nice effect.
		//// Under Release Mode, they all cost LESS time.

		////cv::resize(transHelp,transHelp,cv::Size(),0.75,0.75,wayOfResize);
		//cv::resize(transHelp, transHelp, cv::Size(ui.frameLabel->width(), ui.frameLabel->height()), wayOfResize);

		//double time3 = ((double)(cv::getTickCount() - start3)) * 1000 / getTickFrequency();
		////std::cout << "resize cost : " << time3 << "ms" << std::endl;


		//// 注意step，对齐内存，防止一些奇葩格式的视频出错
		//frame_qt = QImage((const unsigned char*)(transHelp.data), transHelp.cols, transHelp.rows, transHelp.step, QImage::Format_RGB888);
		////frameToShow = frame_qt.scaled(ui.videoLabel->width(), ui.videoLabel->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);


		//ui.frameLabel->setPixmap(QPixmap::fromImage(frame_qt));


		waitKey(30);






	}
}
