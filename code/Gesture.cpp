#include"Gesture.h"

GestureUI::GestureUI(QWidget *parent)
	:QWidget(parent), ui(new Ui::Form())
{
	ui->setupUi(this);
	det = new Detect();

	//background img of window
	QPalette winpal;
	winpal.setBrush(QPalette::Background, QBrush(QPixmap("img/LeapBG.png")));
	this->setPalette(winpal);
	//background img of widget
	QPalette widgetpal;
	widgetpal.setBrush(backgroundRole(), QBrush(QPixmap("img/LeapRes65096.png")));
	ui->widget->setPalette(widgetpal);
	//background img of button
	//ui->pushButton->setIcon(QIcon("img/StartAf22496.png"));
	//ui->pushButton->setIconSize(QSize(224,96));
	ui->pushButton->setStyleSheet("QPushButton{border-image: url(img/StartBe22496.png);}"
		"QPushButton:pressed{border-image: url(img/StartAf22496.png);}");
	//setWindowFlags(Qt::Window);
	connect(ui->pushButton, &QPushButton::clicked,this,&GestureUI::getGesture);
}

void GestureUI::getGesture()
{
	int i = 100;
	bool suc = false;
	std::string  res;
	while (i--)
	{
		ui->progressBar->setValue(100-i);
		ui->graphicsView->setScene(nullptr);
		ui->textBrowser->clear();
		if (0 == i%10&& true == det->getGesture(res))
		{
			suc = true;
			QString path(res.c_str());
			Img = new QGraphicsScene();
			QPixmap *gesmap = new QPixmap("img/"+path +".jpg");
			Img->addPixmap(*gesmap);
			ui->textBrowser->setText(path);
			ui->graphicsView->setScene(Img);
			ui->progressBar->setValue(100);
			
			break;
		}
		_sleep(50);
	}
	if (false == suc)
	{
		ui->textBrowser->setText("Sorry! Try again!");
	}
	_sleep(1000);
	ui->progressBar->setValue(0);
}

void GestureUI::cleanUI()
{
	ui->textBrowser->clear();
	ui->graphicsView->setScene(nullptr);
}

GestureUI::~GestureUI() {}