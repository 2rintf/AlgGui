#pragma once

#include <QtWidgets/QDialog>
#include <QtCore>
#include <qfiledialog.h>
#include "ui_AlgGui.h"

#include <opencv2/opencv.hpp>
//#include <opencv2/highgui.hpp>
using namespace cv;


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
	int wayOfResize = cv::INTER_AREA;
	bool isYolo = false;


	bool isClickToClose = false;

	void videoWinAllClear();
	void disableAllParamSet();
	void enableAllParamSet();

private:
	Ui::AlgGuiClass ui;

	void startShowVideo(std::string path);
	
private slots:
	void on_BtnExit_clicked();
	void on_BtnFilePath_clicked();
	void on_BtnCloseVideo_clicked();


	

};
