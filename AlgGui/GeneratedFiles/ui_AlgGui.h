/********************************************************************************
** Form generated from reading UI file 'AlgGui.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALGGUI_H
#define UI_ALGGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AlgGuiClass
{
public:
    QGroupBox *groupBox_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *frameLabel;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *bgLabel;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_3;
    QLabel *fgLabel;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_4;
    QLabel *tsoLabel;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *BtnFilePath;
    QPushButton *BtnCloseVideo;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *BtnExit;
    QGroupBox *paramGroupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label;
    QComboBox *BoxOfResizeWay;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *BoxOfIsYolo;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QComboBox *BoxOfYoloVer;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QDoubleSpinBox *BoxOfYoloThresh;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QSpinBox *BoxOfAlarmTime;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_5;
    QLabel *alarmImgLabel;

    void setupUi(QDialog *AlgGuiClass)
    {
        if (AlgGuiClass->objectName().isEmpty())
            AlgGuiClass->setObjectName(QStringLiteral("AlgGuiClass"));
        AlgGuiClass->resize(1353, 616);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AlgGuiClass->sizePolicy().hasHeightForWidth());
        AlgGuiClass->setSizePolicy(sizePolicy);
        AlgGuiClass->setMaximumSize(QSize(1920, 1080));
        groupBox_3 = new QGroupBox(AlgGuiClass);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(350, 10, 961, 581));
        groupBox = new QGroupBox(groupBox_3);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 451, 281));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        frameLabel = new QLabel(groupBox);
        frameLabel->setObjectName(QStringLiteral("frameLabel"));

        gridLayout->addWidget(frameLabel, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(groupBox_3);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(470, 10, 451, 281));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        bgLabel = new QLabel(groupBox_2);
        bgLabel->setObjectName(QStringLiteral("bgLabel"));

        gridLayout_2->addWidget(bgLabel, 0, 0, 1, 1);

        groupBox_5 = new QGroupBox(groupBox_3);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 290, 451, 281));
        gridLayout_3 = new QGridLayout(groupBox_5);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        fgLabel = new QLabel(groupBox_5);
        fgLabel->setObjectName(QStringLiteral("fgLabel"));

        gridLayout_3->addWidget(fgLabel, 0, 0, 1, 1);

        groupBox_6 = new QGroupBox(groupBox_3);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(470, 290, 451, 281));
        gridLayout_4 = new QGridLayout(groupBox_6);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        tsoLabel = new QLabel(groupBox_6);
        tsoLabel->setObjectName(QStringLiteral("tsoLabel"));

        gridLayout_4->addWidget(tsoLabel, 0, 0, 1, 1);

        horizontalLayoutWidget_2 = new QWidget(AlgGuiClass);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(20, 30, 321, 61));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        BtnFilePath = new QPushButton(horizontalLayoutWidget_2);
        BtnFilePath->setObjectName(QStringLiteral("BtnFilePath"));

        horizontalLayout_4->addWidget(BtnFilePath);

        BtnCloseVideo = new QPushButton(horizontalLayoutWidget_2);
        BtnCloseVideo->setObjectName(QStringLiteral("BtnCloseVideo"));

        horizontalLayout_4->addWidget(BtnCloseVideo);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        BtnExit = new QPushButton(horizontalLayoutWidget_2);
        BtnExit->setObjectName(QStringLiteral("BtnExit"));

        horizontalLayout_4->addWidget(BtnExit);

        paramGroupBox = new QGroupBox(AlgGuiClass);
        paramGroupBox->setObjectName(QStringLiteral("paramGroupBox"));
        paramGroupBox->setGeometry(QRect(20, 90, 321, 211));
        verticalLayout = new QVBoxLayout(paramGroupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label = new QLabel(paramGroupBox);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(11);
        label->setFont(font);

        horizontalLayout_6->addWidget(label);

        BoxOfResizeWay = new QComboBox(paramGroupBox);
        BoxOfResizeWay->addItem(QString());
        BoxOfResizeWay->addItem(QStringLiteral("INTER_NEAREST"));
        BoxOfResizeWay->setObjectName(QStringLiteral("BoxOfResizeWay"));
        BoxOfResizeWay->setEnabled(true);

        horizontalLayout_6->addWidget(BoxOfResizeWay);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(paramGroupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font1;
        font1.setPointSize(11);
        label_2->setFont(font1);

        horizontalLayout->addWidget(label_2);

        BoxOfIsYolo = new QComboBox(paramGroupBox);
        BoxOfIsYolo->setObjectName(QStringLiteral("BoxOfIsYolo"));

        horizontalLayout->addWidget(BoxOfIsYolo);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_4 = new QLabel(paramGroupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font1);

        horizontalLayout_3->addWidget(label_4);

        BoxOfYoloVer = new QComboBox(paramGroupBox);
        BoxOfYoloVer->setObjectName(QStringLiteral("BoxOfYoloVer"));

        horizontalLayout_3->addWidget(BoxOfYoloVer);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(paramGroupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);

        horizontalLayout_5->addWidget(label_5);

        BoxOfYoloThresh = new QDoubleSpinBox(paramGroupBox);
        BoxOfYoloThresh->setObjectName(QStringLiteral("BoxOfYoloThresh"));
        BoxOfYoloThresh->setMaximum(0.99);
        BoxOfYoloThresh->setSingleStep(0.1);
        BoxOfYoloThresh->setValue(0.5);

        horizontalLayout_5->addWidget(BoxOfYoloThresh);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(paramGroupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        horizontalLayout_2->addWidget(label_3);

        BoxOfAlarmTime = new QSpinBox(paramGroupBox);
        BoxOfAlarmTime->setObjectName(QStringLiteral("BoxOfAlarmTime"));
        BoxOfAlarmTime->setMinimum(1);
        BoxOfAlarmTime->setMaximum(999);
        BoxOfAlarmTime->setValue(120);
        BoxOfAlarmTime->setDisplayIntegerBase(10);

        horizontalLayout_2->addWidget(BoxOfAlarmTime);


        verticalLayout->addLayout(horizontalLayout_2);

        groupBox_4 = new QGroupBox(AlgGuiClass);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(20, 300, 321, 201));
        gridLayout_5 = new QGridLayout(groupBox_4);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        alarmImgLabel = new QLabel(groupBox_4);
        alarmImgLabel->setObjectName(QStringLiteral("alarmImgLabel"));

        gridLayout_5->addWidget(alarmImgLabel, 0, 0, 1, 1);


        retranslateUi(AlgGuiClass);

        BoxOfResizeWay->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AlgGuiClass);
    } // setupUi

    void retranslateUi(QDialog *AlgGuiClass)
    {
        AlgGuiClass->setWindowTitle(QApplication::translate("AlgGuiClass", "AlgGui", Q_NULLPTR));
        groupBox_3->setTitle(QString());
        groupBox->setTitle(QApplication::translate("AlgGuiClass", "Frame", Q_NULLPTR));
        frameLabel->setText(QString());
        groupBox_2->setTitle(QApplication::translate("AlgGuiClass", "Background", Q_NULLPTR));
        bgLabel->setText(QString());
        groupBox_5->setTitle(QApplication::translate("AlgGuiClass", "FGMask", Q_NULLPTR));
        fgLabel->setText(QString());
        groupBox_6->setTitle(QApplication::translate("AlgGuiClass", "TSOEvidence", Q_NULLPTR));
        tsoLabel->setText(QString());
        BtnFilePath->setText(QApplication::translate("AlgGuiClass", "Open File..", Q_NULLPTR));
        BtnCloseVideo->setText(QApplication::translate("AlgGuiClass", "Close", Q_NULLPTR));
        BtnExit->setText(QApplication::translate("AlgGuiClass", "Exit", Q_NULLPTR));
        paramGroupBox->setTitle(QApplication::translate("AlgGuiClass", "Param", Q_NULLPTR));
        label->setText(QApplication::translate("AlgGuiClass", "Resize\346\226\271\345\274\217:", Q_NULLPTR));
        BoxOfResizeWay->setItemText(0, QApplication::translate("AlgGuiClass", "INTER_AREA", Q_NULLPTR));

        BoxOfResizeWay->setCurrentText(QApplication::translate("AlgGuiClass", "INTER_AREA", Q_NULLPTR));
        label_2->setText(QApplication::translate("AlgGuiClass", "\345\220\257\345\212\250YOLO:", Q_NULLPTR));
        BoxOfIsYolo->clear();
        BoxOfIsYolo->insertItems(0, QStringList()
         << QApplication::translate("AlgGuiClass", "\345\220\246", Q_NULLPTR)
         << QApplication::translate("AlgGuiClass", "\346\230\257\357\274\214\345\271\266\345\256\236\346\227\266", Q_NULLPTR)
         << QApplication::translate("AlgGuiClass", "\346\230\257\357\274\214\344\275\206\344\273\205\346\212\245\350\255\246\345\233\276\347\211\207", Q_NULLPTR)
        );
        label_4->setText(QApplication::translate("AlgGuiClass", "YOLO\347\211\210\346\234\254:", Q_NULLPTR));
        BoxOfYoloVer->clear();
        BoxOfYoloVer->insertItems(0, QStringList()
         << QApplication::translate("AlgGuiClass", "YOLOV3-tiny", Q_NULLPTR)
         << QApplication::translate("AlgGuiClass", "YOLOV3", Q_NULLPTR)
        );
        label_5->setText(QApplication::translate("AlgGuiClass", "YOLO\351\230\210\345\200\274\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("AlgGuiClass", "Alarm\346\227\266\351\227\264\357\274\232", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("AlgGuiClass", "AlArmImg", Q_NULLPTR));
        alarmImgLabel->setText(QApplication::translate("AlgGuiClass", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AlgGuiClass: public Ui_AlgGuiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALGGUI_H
