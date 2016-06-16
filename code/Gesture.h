#ifndef Gesture_H_
#define Gesture_H_



#include <QtWidgets/QMainWindow>
#include "ui_LeapUI.h"
#include "Detect.h"

class GestureUI: public QWidget
{
	Q_OBJECT
public:
	GestureUI(QWidget *parent = 0);
	~GestureUI();
	public slots:
	void getGesture();
	void cleanUI();
private:
	QGraphicsScene *Img;
	Detect *det;
	Ui::Form* ui;
};

#endif // HCI_H