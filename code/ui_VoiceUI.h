/********************************************************************************
** Form generated from reading UI file 'VoiceUIfX6848.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef VOICEUIFX6848_H
#define VOICEUIFX6848_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormVoc
{
public:
	QPushButton *pushButton;
	QPushButton *pushButton_2;
	QTextBrowser *textBrowser;

	void setupUi(QWidget *Form)
	{
		if (Form->objectName().isEmpty())
			Form->setObjectName(QStringLiteral("Form"));
		Form->setEnabled(true);
		Form->resize(721, 982);
		Form->setMinimumSize(QSize(496, 516));
		Form->setMaximumSize(QSize(16777215, 16777215));
		QFont font;
		font.setFamily(QStringLiteral("Microsoft YaHei UI Light"));
		font.setPointSize(11);
		font.setBold(true);
		font.setWeight(75);
		Form->setFont(font);
		pushButton = new QPushButton(Form);
		pushButton->setObjectName(QStringLiteral("pushButton"));
		pushButton->setGeometry(QRect(240, 30, 224, 96));
		pushButton->setStyleSheet(QStringLiteral("background:transparent"));
		pushButton->setFlat(true);
		pushButton_2 = new QPushButton(Form);
		pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
		pushButton_2->setEnabled(false);
		pushButton_2->setGeometry(QRect(40, 180, 650, 96));
		pushButton_2->setStyleSheet(QStringLiteral("background:transparent"));
		pushButton_2->setFlat(true);
		textBrowser = new QTextBrowser(Form);
		textBrowser->setObjectName(QStringLiteral("textBrowser"));
		textBrowser->setGeometry(QRect(40, 300, 650, 591));

		retranslateUi(Form);

		QMetaObject::connectSlotsByName(Form);
	} // setupUi

	void retranslateUi(QWidget *Form)
	{
		Form->setWindowTitle(QApplication::translate("Form", "Voice", 0));
		pushButton->setText(QString());
		pushButton_2->setText(QString());
	} // retranslateUi

};

namespace Ui {
	class FormVoc : public Ui_FormVoc {};
} // namespace Ui

QT_END_NAMESPACE

#endif // VOICEUIFX6848_H
