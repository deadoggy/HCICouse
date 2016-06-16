#include"Voice.h"

Voice::Voice(std::string *ret_hci,QWidget *parent) :
	QWidget(parent), ui(new Ui::FormVoc()), ret(ret_hci)
{
	ui->setupUi(this);
	mutex.lock();
	waitCon = new QWaitCondition();
	RecThread = new VocThread(this,ret_hci);
	start = false;
	connect(ui->pushButton, &QPushButton::clicked, this, &Voice::clickStart);
	connect(this, &Voice::Start, &Voice::run);
	Det = new VoiceDet();
	//set coding 
	ui->textBrowser->setLocale(QLocale::Chinese);
	//background img of window
	QPalette winpal;
	winpal.setBrush(QPalette::Background, QBrush(QPixmap("img/LeapBG.png")));
	this->setPalette(winpal);
	//background img of button
	ui->pushButton->setStyleSheet("QPushButton{border-image: url(img/StartBe22496.png);}"
		"QPushButton:pressed{border-image: url(img/StartAf22496.png);}");
	//img of state 
	ui->pushButton_2->setIcon(QIcon("img/statusready65096.png"));
	ui->pushButton_2->setIconSize(QSize(650, 96));
	ui->pushButton_2->update();
	
}

Voice::~Voice() {}

void Voice::clickStart()
{
	ui->pushButton_2->setIcon(QIcon("img/statusrecording65096.png"));
	ui->pushButton_2->setIconSize(QSize(650, 96));
	ui->pushButton_2->update();
	start = true;
	waitCon->wakeAll();
}

void Voice::cleanUI() 
{
	ui->textBrowser->clear();
	ui->pushButton_2->setIcon(QIcon("img/statusready65096.png"));
	ui->pushButton_2->setIconSize(QSize(650, 96));
	ui->pushButton_2->update();
}

void Voice::run()
{
	RecThread->start();
}

void Voice::changeText()
{
	QByteArray Qba = ret->c_str();
	QTextCodec * codec = QTextCodec::codecForName("GB18030");
	QString qstr = codec->toUnicode(Qba);
	ui->textBrowser->setText(qstr);
}
//VoiceThread
VocThread::VocThread( Voice* p, std::string *ret_hci)
{
	ret = ret_hci;
	parent = p;
	connect(this,&VocThread::changeText, parent, &Voice::changeText);
}

void VocThread::run()
{
	forever
	{
		if (false == parent->start)
		{
			parent->waitCon->wait(&parent->mutex);
		}
	if (true == parent->Det->getVoiceStr(*ret))
	{
		changeText();
	}
	_sleep(1000);
	parent->ui->pushButton_2->setIcon(QIcon("img/statusready65096.png"));
	parent->ui->pushButton_2->setIconSize(QSize(650, 96));
	parent->ui->pushButton_2->update();
	parent->start = false;
	}

}