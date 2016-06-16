#pragma once
#include"ui_About.h"

class About :public QWidget
{
public:
	About(QWidget *parent = 0) :
		QWidget(parent)
	{
		ui = new Ui::FormAbo();
		ui->setupUi(this);
	}
private:
	Ui::FormAbo *ui;
};
