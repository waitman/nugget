/*
 * 
Disposera GUI
 nugget - calculator with touchscreen support
 
Copyright 2015 Waitman Gobble <ns@waitman.net>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

* 
*/
 
#include "mainwindow.h"
#include "ui_nugget.h"
#include <QStringList>
#include <QDate>
#include <QDebug>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QClipboard>
#include <QKeyEvent>
#include <QScreen>
#include <QDesktopWidget>
#include <QModelIndex>
#include <QModelIndexList>
#include <QAbstractItemModel>
#include <QItemSelectionModel>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

	ui->setupUi(this);
	
	const QRect screenGeometry = QApplication::desktop()->availableGeometry();
    QRect geometry(QPoint(0, 0), QSize(screenGeometry.width() * 9 / 10, screenGeometry.height() * 9 / 10));
    geometry.moveCenter(screenGeometry.center());
    setGeometry(geometry);

	curRow=0;
	newNext = false;
	clipboard = QApplication::clipboard();
	
	model = new QStandardItemModel(2,3,this); 
	model->setHorizontalHeaderItem(0, new QStandardItem(QString("Op")));
	model->setHorizontalHeaderItem(1, new QStandardItem(QString("Data")));
	model->setHorizontalHeaderItem(2, new QStandardItem(QString("Res")));
	
	ui->resTable->setModel(model);
	ui->resTable->horizontalHeader()->setStretchLastSection(true);
	ui->resTable->horizontalHeader()->resizeSection(0, 150);
	ui->resTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	
	connect(ui->b9,SIGNAL(clicked()),SLOT(press()));
	connect(ui->b8,SIGNAL(clicked()),SLOT(press()));
	connect(ui->b7,SIGNAL(clicked()),SLOT(press()));
	connect(ui->b6,SIGNAL(clicked()),SLOT(press()));
	connect(ui->b5,SIGNAL(clicked()),SLOT(press()));
	connect(ui->b4,SIGNAL(clicked()),SLOT(press()));
	connect(ui->b3,SIGNAL(clicked()),SLOT(press()));
	connect(ui->b2,SIGNAL(clicked()),SLOT(press()));
	connect(ui->b1,SIGNAL(clicked()),SLOT(press()));
	connect(ui->b0,SIGNAL(clicked()),SLOT(press()));
	connect(ui->bplus,SIGNAL(clicked()),SLOT(press()));
	connect(ui->bminus,SIGNAL(clicked()),SLOT(press()));
	connect(ui->bdivide,SIGNAL(clicked()),SLOT(press()));
	connect(ui->btimes,SIGNAL(clicked()),SLOT(press()));
	connect(ui->bl,SIGNAL(clicked()),SLOT(press()));
	connect(ui->bslash,SIGNAL(clicked()),SLOT(press()));
	connect(ui->bz,SIGNAL(clicked()),SLOT(press()));
	connect(ui->bcolon,SIGNAL(clicked()),SLOT(press()));
	connect(ui->bdot,SIGNAL(clicked()),SLOT(press()));
	connect(ui->bnew,SIGNAL(clicked()),SLOT(press()));
	connect(ui->bdel,SIGNAL(clicked()),SLOT(press()));
	connect(ui->brev,SIGNAL(clicked()),SLOT(press()));
	connect(ui->bback,SIGNAL(clicked()),SLOT(press()));
	
	installEventFilter(this);
	ui->resBox->setFocus();

}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::press(void)
{
	QPushButton* button = dynamic_cast<QPushButton*>(sender());
	QString bs = button->text();
	bs.replace('&',""); /* fix some weirdness */
	button->setText(bs);
	
	bool press_button = true;
	bool do_op = false;
	
	if (button->text() == "DEL") {
		press_button = false;
		ui->resBox->setText("");
		QStandardItem *valx = new QStandardItem("");
		model->setItem(curRow,1,valx);
		QStandardItem *valy = new QStandardItem("");
		model->setItem(curRow,2,valy);		
	}
	if (button->text() == "BACK") 
	{
		press_button = false;
		if (ui->resBox->text() != "")
		{
			ui->resBox->setText(ui->resBox->text().mid(0,ui->resBox->text().length()-1));
		}
	}
	if (button->text() == "REV") {
		press_button = false;
		QStandardItem *valx = new QStandardItem("");
		model->setItem(curRow,0,valx);
		QStandardItem *valy = new QStandardItem("");
		model->setItem(curRow,1,valy);		
		QStandardItem *valz = new QStandardItem("");
		model->setItem(curRow,2,valz);
		if (curRow>0)
		{
			curRow--;
			
			QStandardItem *dvaly = new QStandardItem("");
			model->setItem(curRow,1,dvaly);		
			QStandardItem *dvalz = new QStandardItem("");
			model->setItem(curRow,2,dvalz);
		}
		press_button = false;
	}
	if (button->text() == "NEW") {
			press_button = false;
			do_op = true;
	}
	if (button->text() == "L") press_button = false;
	if (button->text() == "A") press_button = false;
	if (button->text() == "Z") press_button = false;
	if (button->text() == "+") {
			press_button = false;
			do_op = true;
	}
	if (button->text() == "-") {
		press_button = false;
		do_op = true;
	}
	if (button->text() == "*") {
		press_button = false;
		do_op = true;
	}
	if (button->text() == "÷") {
		press_button = false;
		do_op = true;
	}

	if (press_button)
	{
		ui->resBox->setText(ui->resBox->text()+button->text());
		QStandardItem *valb = new QStandardItem(ui->resBox->text());
		model->setItem(curRow,1,valb);
		if (curRow>0)
		{
			QModelIndex sup = model->index(curRow-1,2);
			QString res = model->data(sup).toString();
			QModelIndex supa = model->index(curRow,0);
			QString op = model->data(supa).toString();
			docalc(ui->resBox->text(),op,res);
			
		} else {
			QStandardItem *valx = new QStandardItem(ui->resBox->text());
			model->setItem(curRow,2,valx);
		}
	}
	if (do_op)
	{	
		QStandardItem *vala = new QStandardItem(button->text());
		vala->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
		model->setItem(curRow+1,0,vala);
		QStandardItem *valb = new QStandardItem(ui->resBox->text());
		model->setItem(curRow,1,valb);
		curRow++;
		ui->resBox->setText("");
	}

	//qDebug() << button->text();
}

QString MainWindow::calc_age(QString cur)
{
	QStringList pcs = cur.split("/");
	QDate dNow(QDate::currentDate());
    QDate dBirthday(pcs[2].toInt(), pcs[0].toInt(), pcs[1].toInt());
	int days = dBirthday.daysTo(dNow);
	double age = (double)days/365;
	return QString::number(age);
}
void MainWindow::docalc(QString cur,QString op,QString res)
{
	if (res.count('/')==2)
	{
		res = calc_age(res);
	}
	if (cur.count('/')==2)
	{
		cur = calc_age(cur);
	}
	if (op == "+")
	{
		if (res.contains(":") || cur.contains(":"))
		{
			QStandardItem *vala = new QStandardItem(combineTimes(res,cur));
			model->setItem(curRow,2,vala);
		} else {
			if (res.contains(".") || cur.contains("."))
			{
				double v = res.toDouble() + cur.toDouble();
				QStandardItem *vala = new QStandardItem(QString::number(v));
				model->setItem(curRow,2,vala);
			} else {
				int v = res.toInt() + cur.toInt();
				QStandardItem *vala = new QStandardItem(QString::number(v));
				model->setItem(curRow,2,vala);
			}
		}
	}
	if (op == "-")
	{
		if (res.contains(":") || cur.contains(":"))
		{
			QStandardItem *vala = new QStandardItem(subtractTimes(res,cur));
			model->setItem(curRow,2,vala);
		} else {
			if (res.contains("/"))
			{
				res = calc_age(res);
			}
			if (res.contains(".") || cur.contains("."))
			{
				double v = res.toDouble() - cur.toDouble();
				QStandardItem *vala = new QStandardItem(QString::number(v));
				model->setItem(curRow,2,vala);
			} else {
				int v = res.toInt() - cur.toInt();
				QStandardItem *vala = new QStandardItem(QString::number(v));
				model->setItem(curRow,2,vala);
			}
		}
	}
	if (op == "*")
	{
		if (res.contains(".") || cur.contains("."))
		{
			double v = res.toDouble() * cur.toDouble();
			QStandardItem *vala = new QStandardItem(QString::number(v));
			model->setItem(curRow,2,vala);
		} else {
			int v = res.toInt() * cur.toInt();
			QStandardItem *vala = new QStandardItem(QString::number(v));
			model->setItem(curRow,2,vala);
		}
	}
	if (op == "÷")
	{
		if (res.contains(":") && !cur.contains(":"))
		{
			QString xres;
			xres = divideTimes(res,cur.toDouble());
			QStandardItem *vala = new QStandardItem(xres);
			model->setItem(curRow,2,vala);

		} else {

			double v = res.toDouble() / cur.toDouble();
			QStandardItem *vala = new QStandardItem(QString::number(v));
			model->setItem(curRow,2,vala);

		}

	}
	if (op == "NEW")
	{
		QStandardItem *vala = new QStandardItem(cur);
		model->setItem(curRow,2,vala);
	}
}

quint32 MainWindow::toMsecs(QString target)
{
	QStringList ls = target.split(":", QString::SkipEmptyParts);
	quint32 rs = 1;
	if (ls.count()==1)
	{
		rs = ls.at(0).toInt();
	}
	if (ls.count()==2)
	{
		rs = ls.at(0).toInt()*60 + ls.at(1).toInt();
	}
	if (ls.count()==3)
	{
		rs = ls.at(0).toInt()*60*60 + ls.at(1).toInt()*60 + ls.at(2).toInt();
	}
	return (rs*1000);
}

QString MainWindow::combineTimes(QString lega, QString legb)
{
	quint32 timea = toMsecs(lega);
	quint32 timeb = toMsecs(legb);
	QString combined = formatTime(timea+timeb);
	return combined;
}

QString MainWindow::subtractTimes(QString lega, QString legb)
{
	quint32 timea = toMsecs(lega);
	quint32 timeb = toMsecs(legb);
	QString combined = formatTime(timea-timeb);
	return combined;
}

QString MainWindow::divideTimes(QString lega,double valb)
{
	QString result = "0";
	quint32 timea = toMsecs(lega);
	if (valb>0)
	{
		result = formatTime(timea/valb);
	}
	return result;

}

QString MainWindow::formatTime(int elapsed)
{
	int secs = elapsed / 1000;
	int mins = (secs / 60) % 60;
	int hours = (secs / 3600);
	secs = secs % 60;

	QString str = QString("%1:%2:%3")
		.arg(hours, 2, 10, QLatin1Char('0'))
		.arg(mins, 2, 10, QLatin1Char('0'))
		.arg(secs, 2, 10, QLatin1Char('0'));
	
	return str;
}

bool MainWindow::eventFilter(QObject* object, QEvent* event)
{
	if (event->type()==QEvent::KeyPress)
	{
		bool press_button = true;
		bool do_op = false;
		QString keyp = "";
		
		QKeyEvent* pKeyEvent=static_cast<QKeyEvent*>(event);
		switch (pKeyEvent->key())
		{
				case Qt::Key_Delete:
				{
				
						press_button = false;
						ui->resBox->setText("");
						QStandardItem *valdx = new QStandardItem("");
						model->setItem(curRow,1,valdx);
						QStandardItem *valdy = new QStandardItem("");
						model->setItem(curRow,2,valdy);		
						break;
				}			
				case Qt::Key_Backspace:
				{
						press_button = false;
						if (ui->resBox->text() != "")
						{
							ui->resBox->setText(ui->resBox->text().mid(0,ui->resBox->text().length()-1));
						}
						break;
				}
				case Qt::Key_Q:
				{
						exit(0);
						break;
				}
				case Qt::Key_X:
				{
						press_button = false;
						QStandardItem *valx = new QStandardItem("");
						model->setItem(curRow+1,0,valx);
						QStandardItem *valy = new QStandardItem("");
						model->setItem(curRow,1,valy);		
						QStandardItem *valz = new QStandardItem("");
						model->setItem(curRow,2,valz);
						if (curRow>0)
						{
							curRow--;
						}
						press_button = false;
						break;
				}
				case Qt::Key_N:
				{
						press_button = false;
						do_op = true;
						break;
				}
				case Qt::Key_L:
				{
						press_button = false;
						break;
				}
				case Qt::Key_A:
				{
						press_button = false;
						break;
				}
				case Qt::Key_Z:
				{
						press_button = false;
						break;
				}		
				
				case Qt::Key_C:
				{
					press_button = false;
					QModelIndex sup = model->index(curRow,2);
					QString res = model->data(sup).toString();
					clipboard->setText(res, QClipboard::Clipboard);
					clipboard->setText(res, QClipboard::Selection);
					break;
				}

				case Qt::Key_V:
				{
						press_button = false;
						
						ui->resBox->setText(clipboard->text());
						QStandardItem *valb = new QStandardItem(ui->resBox->text());
						model->setItem(curRow,1,valb);
						break;
				}
				case Qt::Key_Plus:
				{
						press_button = false;
						do_op = true;
						keyp = "+";
						break;
				}		
				case Qt::Key_Minus:
				{
						press_button = false;
						do_op = true;
						keyp = "-";						
						break;
				}		
				case Qt::Key_Asterisk:
				{
						press_button = false;
						do_op = true;
						keyp = "*";						
						break;
				}			
				case Qt::Key_Slash:
				{
						if (pKeyEvent->modifiers() & Qt::ShiftModifier)
						{
							keyp = "/";						
						} else {
							press_button = false;
							do_op = true;
							keyp = "÷";						
						}
						break;
				}		
				case Qt::Key_Colon:
				{
						keyp = ":";
						break;
				}
				case Qt::Key_9:
				{
						keyp = "9";
						break;
				}
				case Qt::Key_8:
				{
						keyp = "8";
						break;
				}		
				case Qt::Key_7:
				{
						keyp = "7";
						break;
				}		
				case Qt::Key_6:
				{
						keyp = "6";
						break;
				}		
				case Qt::Key_5:
				{
						keyp = "5";
						break;
				}		
				case Qt::Key_4:
				{
						keyp = "4";
						break;
				}		
				case Qt::Key_3:
				{
						keyp = "3";
						break;
				}		
				case Qt::Key_2:
				{
						keyp = "2";
						break;
				}		
				case Qt::Key_1:
				{
						keyp = "1";
						break;
				}		
				case Qt::Key_0:
				{
						keyp = "0";
						break;
				}
				case Qt::Key_Period:
				{
						keyp = ".";
						break;
				}
		}
		
		if (press_button)
		{
			ui->resBox->setText(ui->resBox->text()+keyp);
			QStandardItem *valb = new QStandardItem(ui->resBox->text());
			model->setItem(curRow,1,valb);
			if (curRow>0)
			{
				QModelIndex sup = model->index(curRow-1,2);
				QString res = model->data(sup).toString();
				QModelIndex supa = model->index(curRow,0);
				QString op = model->data(supa).toString();
				docalc(ui->resBox->text(),op,res);
			
			} else {
				QStandardItem *valx = new QStandardItem(ui->resBox->text());
				model->setItem(curRow,2,valx);
			}
		}
		if (do_op)
		{	
			QStandardItem *vala = new QStandardItem(keyp);
			vala->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
			model->setItem(curRow+1,0,vala);
			QStandardItem *valb = new QStandardItem(ui->resBox->text());
			model->setItem(curRow,1,valb);
			curRow++;
			ui->resBox->setText("");
		}
		
		return true;
	}
	
	
	return QWidget::eventFilter(object, event);
}

QString MainWindow::getTabContent(void)
{
	QAbstractItemModel * model = ui->resTable->model();
	QItemSelectionModel * selection = ui->resTable->selectionModel();
	QModelIndexList indexes = selection->selectedIndexes();
	QString seltxt;

	QModelIndex previous = indexes.first();
	indexes.removeFirst();
	
	
	foreach( QModelIndex current, indexes )
	{
		QVariant data = model->data(current);
		QString text = data.toString();
		seltxt.append(text);
		if (current.row() != previous.row())
		{
			seltxt.append('\n');
		}
			else
		{
			seltxt.append('\t');
		}
		previous = current;
	}
	clipboard->setText(seltxt);
	return seltxt;
}
//EOF
