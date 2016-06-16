#include "hci.h"

HCI::HCI(QWidget *parent)
	: QMainWindow(parent),
	ui(new Ui::HCIClass())
{
	ret = new std::string();
	ui->setupUi(this);
	ges = new GestureUI();
	voc = new Voice(ret);
	abo = new About();
	//background of mainwindow
	QPalette palette;
	palette.setBrush(QPalette::Background, QBrush(QPixmap("img/WelcomeBG.png")));
	this->setPalette(palette);
	//background of button_1
	QPalette palette_button_1;
	palette_button_1.setBrush(QPalette::Background, QBrush(QPixmap("img/WelcomeBar.png")));
	ui->pushButton->setPalette(palette_button_1);

	//background of button_2
	QPalette palette_button_2;
	palette_button_2.setBrush(QPalette::Background, QBrush(QPixmap("img/WelcomeBar.png")));
	ui->pushButton_2->setPalette(palette_button_2);

	//background of button_3
	QPalette palette_button_3;
	palette_button_3.setBrush(QPalette::Background, QBrush(QPixmap("img/WelcomeBar.png")));
	ui->pushButton_3->setPalette(palette_button_3);
	//background of button_4
	QPalette palette_button_4;
	palette_button_4.setBrush(QPalette::Background, QBrush(QPixmap("img/WelcomeBar.png")));
	ui->pushButton_4->setPalette(palette_button_4);
	//connect singals and slots
	connect(ui->pushButton_2,&QPushButton::clicked, this, &HCI::invokeGestureRec);
	connect(ui->pushButton, &QPushButton::clicked, this, &HCI::invokeVoiceRec);
	connect(ui->pushButton_3, &QPushButton::clicked, this, &HCI::invokeAbout);
}

void HCI::invokeGestureRec()
{
	ges->cleanUI();
	ges->show();
}

void HCI::invokeVoiceRec()
{
	voc->cleanUI();
	voc->show();
	voc->run();
}

void HCI::invokeAbout()
{
	abo->show();
}

HCI::~HCI()
{}
