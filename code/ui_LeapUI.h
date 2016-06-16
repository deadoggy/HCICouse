/********************************************************************************
** Form generated from reading UI file 'LeapUINl6848.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef LEAPUINL6848_H
#define LEAPUINL6848_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
	QPushButton *pushButton;
	QProgressBar *progressBar;
	QGraphicsView *graphicsView;
	QWidget *widget;
	QTextBrowser *textBrowser;

	void setupUi(QWidget *Form)
	{
		if (Form->objectName().isEmpty())
			Form->setObjectName(QStringLiteral("Form"));
		Form->setEnabled(true);
		Form->resize(721, 1024);
		Form->setMinimumSize(QSize(496, 516));
		Form->setMaximumSize(QSize(721, 1024));
		pushButton = new QPushButton(Form);
		pushButton->setObjectName(QStringLiteral("pushButton"));
		pushButton->setGeometry(QRect(240, 30, 224, 96));
		pushButton->setFocusPolicy(Qt::NoFocus);
		pushButton->setStyleSheet(QStringLiteral("background:transparent"));
		pushButton->setFlat(true);
		progressBar = new QProgressBar(Form);
		progressBar->setObjectName(QStringLiteral("progressBar"));
		progressBar->setGeometry(QRect(30, 160, 650, 51));
		progressBar->setValue(0);
		progressBar->setTextVisible(false);
		graphicsView = new QGraphicsView(Form);
		graphicsView->setObjectName(QStringLiteral("graphicsView"));
		graphicsView->setGeometry(QRect(30, 360, 650, 590));
		widget = new QWidget(Form);
		widget->setObjectName(QStringLiteral("widget"));
		widget->setGeometry(QRect(30, 230, 650, 96));
		textBrowser = new QTextBrowser(widget);
		textBrowser->setObjectName(QStringLiteral("textBrowser"));
		textBrowser->setGeometry(QRect(-1, 25, 651, 71));
		QFont font;
		font.setFamily(QStringLiteral("Microsoft YaHei UI Light"));
		font.setPointSize(25);
		font.setBold(true);
		font.setWeight(75);
		textBrowser->setFont(font);

		retranslateUi(Form);

		QMetaObject::connectSlotsByName(Form);
	} // setupUi

	void retranslateUi(QWidget *Form)
	{
		Form->setWindowTitle(QApplication::translate("Form", "Gesture", 0));
		pushButton->setText(QString());
	} // retranslateUi

};

namespace Ui {
	class Form : public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // LEAPUINL6848_H
