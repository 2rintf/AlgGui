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

image_t make_empty_image(int w, int h, int c)
{
	image_t out;
	out.data = 0;
	out.h = h;
	out.w = w;
	out.c = c;
	return out;
}
//image_t make_image(int w, int h, int c)
//{
//	image_t out = make_empty_image(w, h, c);
//	out.data = (float*)calloc(h*w*c, sizeof(float)); //这边估计要保留下来，这块内存
//	return out;
//}

//void rgbgr_image(image_t im)
//{
//	int i;
//	for (i = 0; i < im.w*im.h; ++i) {
//		float swap = im.data[i];
//		im.data[i] = im.data[i + im.w*im.h * 2];
//		im.data[i + im.w*im.h * 2] = swap;
//	}
//}


image_t image_to_Mat(unsigned char * src, int width, int height)
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

//std::vector<std::string> objects_names_from_file(std::string const filename)
//{
//	std::ifstream file(filename);
//	std::vector<std::string> file_lines;
//	if (!file.is_open()) return file_lines;
//	for (std::string line; getline(file, line);) file_lines.push_back(line);
//	std::cout << "object names loaded \n";
//	return file_lines;
//}

void draw_boxes(cv::Mat& mat_img, std::vector<bbox_t> result_vec, std::vector<std::string> obj_names, int current_det_fps = -1, int current_cap_fps = -1)
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

	// alarmTime
	alarmTime = ui.BoxOfAlarmTime->value();
	std::cout << "alarm time:" << alarmTime << std::endl;


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
		

	if (isYolo!=NO_YOLO)
	{
		//std::string names_file = "coco.names";
		//std::string cfg_file = "yolov3-tiny.cfg";
		//std::string weights_file = "yolov3-tiny.weights";

		//std::cout << cfg_file << std::endl;
		//detector = createDarknetDetector(cfg_file, weights_file, 0);
		//obj_names = objects_names_from_file(names_file);

		detector = api->YOLOInitialize();
		obj_names = api->setNamesFile();
	}






	api->add(rp, true);

	for (;;) {
		if (isClickToClose) {
			videoWinAllClear();
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
		

		if (!BG.empty())
		{
			Mat transHelp;
			cvtColor(BG, transHelp, COLOR_BGR2RGB);
			cv::resize(transHelp, transHelp, cv::Size(ui.bgLabel->width(), ui.bgLabel->height()), wayOfResize);
			BGToShow = QImage((const unsigned char*)(transHelp.data), transHelp.cols, transHelp.rows, transHelp.step, QImage::Format_RGB888);
			ui.bgLabel->setPixmap(QPixmap::fromImage(BGToShow));
		}

		if (isYolo==NO_YOLO) {
			if (!traceImg.empty())
			{
				Mat transHelp;
				cvtColor(traceImg, transHelp, COLOR_BGR2RGB);
				cv::resize(transHelp, transHelp, cv::Size(ui.frameLabel->width(), ui.frameLabel->height()), wayOfResize);
				traceImgToShow = QImage((const unsigned char*)(transHelp.data), transHelp.cols, transHelp.rows, transHelp.step, QImage::Format_RGB888);
				ui.frameLabel->setPixmap(QPixmap::fromImage(traceImgToShow));
			}
		}
		else if (isYolo == YOLO_ALL_TIME) {
			// 将traceImg当作背景学习初始化的flag
			if (!traceImg.empty()) 
			{
				
				image_t imgFromFrame =api->image_to_Mat(frame_cv.data, frame_cv.cols, frame_cv.rows);

				std::vector<bbox_t> result_vec = detector->detect(imgFromFrame, 0.2);
				api->draw_boxes(frame_cv, result_vec, obj_names);

				free(imgFromFrame.data);// 释放内存！！

				// 开始正常UI交互
				Mat transHelp;
				cvtColor(frame_cv, transHelp, COLOR_BGR2RGB);
				cv::resize(transHelp, transHelp, cv::Size(ui.frameLabel->width(), ui.frameLabel->height()), wayOfResize);
				traceImgToShow = QImage((const unsigned char*)(transHelp.data), transHelp.cols, transHelp.rows, transHelp.step, QImage::Format_RGB888);
				ui.frameLabel->setPixmap(QPixmap::fromImage(traceImgToShow));
			}
		}
		else if (isYolo == YOLO_ONLY_ALARM_TIME)
		{
			// TO-DO
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
