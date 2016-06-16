#pragma once
#include <QWidget>
#include "ui_ui_leapgui.h"

class ui_LeapGUI : public QWidget {
	Q_OBJECT

public:
	ui_LeapGUI(QWidget * parent = Q_NULLPTR);
	~ui_LeapGUI();

private:
	Ui::ui_LeapGUI ui;
};
