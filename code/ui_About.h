/********************************************************************************
** Form generated from reading UI file 'Aboutp10080.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef ABOUTP10080_H
#define ABOUTP10080_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormAbo
{
public:
	QTextBrowser *textBrowser;

	void setupUi(QWidget *Form)
	{
		if (Form->objectName().isEmpty())
			Form->setObjectName(QStringLiteral("Form"));
		Form->resize(400, 300);
		textBrowser = new QTextBrowser(Form);
		textBrowser->setObjectName(QStringLiteral("textBrowser"));
		textBrowser->setEnabled(false);
		textBrowser->setGeometry(QRect(70, 50, 256, 192));

		retranslateUi(Form);

		QMetaObject::connectSlotsByName(Form);
	} // setupUi

	void retranslateUi(QWidget *Form)
	{
		Form->setWindowTitle(QApplication::translate("Form", "Form", 0));
		textBrowser->setHtml(QApplication::translate("Form", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
			"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
			"p, li { white-space: pre-wrap; }\n"
			"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
			"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\345\260\217\347\273\204\346\210\220\345\221\230\357\274\210\346\214\211\345\255\246\345\217\267\346\216\222\345\272\217\357\274\211\357\274\232</p>\n"
			"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">1452686 \350\265\265\346\255\243</p>\n"
			"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">1452699 \345\274\240\350\213\261\346\265\251</p>\n"
			"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; "
			"-qt-block-indent:0; text-indent:0px;\">1452716 \345\274\240\345\260\271\345\230\211</p>\n"
			"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">1452713 \345\274\240\345\277\227\345\274\272</p>\n"
			"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
			"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
	} // retranslateUi

};

namespace Ui {
	class FormAbo : public Ui_FormAbo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // ABOUTP10080_H
