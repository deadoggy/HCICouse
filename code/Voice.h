#ifndef Voice_H_
#define Voice_H_

#include <QtWidgets/QMainWindow>
#include<QThread>
#include"ui_VoiceUI.h"
#include "iat_sample.h"
#include <QString>
#include <QTextCodec> 
#include<QByteArray>
#include<QMutex>
#include<QWaitCondition>


class Voice :public QWidget
{
	friend class VocThread;
	Q_OBJECT
public:
	Voice(std::string *ret_hci,QWidget *parent = 0);
	~Voice();
	void run();
	public slots: 
	void changeText();
	void clickStart();
	void cleanUI();
signals:
	void Start();

private :
	bool start;
	std::string *ret;
	QMutex mutex;
	VoiceDet * Det;
	Ui::FormVoc *ui;
	VocThread *RecThread;
	QWaitCondition *waitCon;
};

class VocThread : public QThread
{
	Q_OBJECT
public :
	VocThread(Voice *p, std::string *ret_hci);
	void run();
 signals:
	void changeText();
private:
	std::string *ret;
	Voice * parent;
	
};
#endif
