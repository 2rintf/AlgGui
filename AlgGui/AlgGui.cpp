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
/**************** utils func end ****************/



AlgGui::AlgGui(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
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
		IndexOfYolo = false;
		break;
	case(1):
		IndexOfYolo = true;
		break;
	}
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
		std::cout <<"std::string = "<< filePath_cv << std::endl;
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

		Mat transHelp;
		cvtColor(frame_cv, transHelp, COLOR_BGR2RGB);

		double start3 = (double)cv::getTickCount();
		// Debug Mode : default(INTER_NEAREST -- bilinear interpolation) cost about 15ms. 
		//              INTER_NEAREST(-- nearest neighbor interpolation) cost about 5ms, but terrible effect.(!其速度是呈抛物线式，非单纯线性)
		//              INTER_AREA(-- resampling using pixel area relation) cost about 45ms, but nice effect.
		// Under Release Mode, they all cost LESS time.

		//cv::resize(transHelp,transHelp,cv::Size(),0.75,0.75,wayOfResize);
		cv::resize(transHelp, transHelp, cv::Size(ui.frameLabel->width(), ui.frameLabel->height()), wayOfResize);

		double time3 = ((double)(cv::getTickCount() - start3)) * 1000 / getTickFrequency();
		std::cout << "resize cost : " << time3 << "ms" << std::endl;


		// 注意step，对齐内存，防止一些奇葩格式的视频出错
		frame_qt = QImage((const unsigned char*)(transHelp.data), transHelp.cols, transHelp.rows, transHelp.step, QImage::Format_RGB888);
		//frameToShow = frame_qt.scaled(ui.videoLabel->width(), ui.videoLabel->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);


		ui.frameLabel->setPixmap(QPixmap::fromImage(frame_qt));


		waitKey(16);






	}
}
