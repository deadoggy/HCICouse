#ifndef HCI_H
#define HCI_H



#include <QtWidgets/QMainWindow>
#include "ui_hci.h"
#include "About.h"
#include "Gesture.h"
#include "Voice.h"

class HCI : public QMainWindow
{
	Q_OBJECT

public:
	HCI(QWidget *parent = 0);
	~HCI();
	Ui::HCIClass* getUI()
	{
		return ui;
	}
	public	slots:
    void invokeGestureRec();
	void invokeVoiceRec();
	void invokeAbout();
private:
	std::string *ret;
	GestureUI *ges;
	Voice *voc;
	VocThread * RecThread;
	Ui::HCIClass* ui;
	About *abo;
};

#endif // HCI_H
