#include "licensevalidationdialog.h"
#include "ui_licensevalidationdialog.h"

bool process_ok;
QStringList stream_data;

void LicenseValidationDialog::SetupScript()
{
	process = new QProcess(this);
	process->setWorkingDirectory(qApp->applicationDirPath());
	connect(process, SIGNAL(started()), this, SLOT(processStarted()));
	connect(process,SIGNAL(readyReadStandardOutput()),this,SLOT(readyReadStandardOutput()));
	connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
		[=](int exitCode, QProcess::ExitStatus exitStatus){ encodingFinished(); });
}

void LicenseValidationDialog::processStarted()
{
	stream_data.clear();
}

void LicenseValidationDialog::readyReadStandardOutput()
{
	QString data = process->readAllStandardOutput();
	stream_data << data;
}

void LicenseValidationDialog::encodingFinished()
{
	process_ok=true;
}

QStringList LicenseValidationDialog::RunCommand(QString command)
{
	QString cmd = "powershell.exe";
	QStringList parameters{command};
	process_ok=false;
	process->start(cmd, parameters);
	while(process_ok!=true) delay_MSec(100);
	process->close();
	return stream_data;
}

void LicenseValidationDialog::delay_MSec(unsigned int msec)
{
	QTime _Timer = QTime::currentTime().addMSecs(msec);
	while( QTime::currentTime() < _Timer )
	QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

QString LicenseValidationDialog::GetNTPDate()
{
	QString command = "w32tm /stripchart /computer:NTP_SERVER /samples:1 /dataonly";
	command.replace("NTP_SERVER", NTP_SERVER);
	QStringList returned_list = RunCommand(command);
	if(returned_list.length()>1)
	{
		QString returned;
		if(!returned_list.isEmpty())
		{
			foreach(QString line, returned_list) returned += line;
			QStringList new_returned = returned.split("\n");
			if(new_returned.length()>=2)
			{
				QStringList time_list = new_returned[2].split(' ');
				if(time_list.length()>=4)
				{
					QDate date = QDate::fromString(time_list[4], "dd.MM.yyyy");
					if(date.isValid())
					{
						return time_list[4];
					}
					else
					{
						qDebug() << "date_error";
						return "date_error";
					}
				}
				else
				{
					qDebug() << "date_error";
					return "date_error";
				}
			}
			else
			{
				qDebug() << "date_error";
				return "date_error";
			}
		}
		else
		{
			qDebug() << "date_error";
			return "date_error";
		}
	}
	else
	{
		qDebug() << "date_error";
		return "date_error";
	}
}
