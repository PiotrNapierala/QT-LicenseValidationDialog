#include "licensevalidationdialog.h"
#include "ui_licensevalidationdialog.h"

void LicenseValidationDialog::PrepareWindow()
{
	if(set_custom_language==true) SetLanguage();
	else
	{
		error1 = "Activation error!";
		error2 = "There was an error during activation: The given data is correct, but the license has expired!";
		error3 = "There was an error during activation: No connection to the time server!";
		error4 = "There was an error during activation: The given data is incorrect!";
	}

	QPixmap hashtag_icon(":/icons/IMG/hashtag.png");
	QPixmap key_icon(":/icons/IMG/key.png");
	QPixmap time_icon(":/icons/IMG/time.png");
	QPixmap user_icon(":/icons/IMG/user.png");

	ui->label_hash_icon->setPixmap(hashtag_icon.scaled(22,22));
	ui->label_key_icon->setPixmap(key_icon.scaled(22,22));
	ui->label_time_icon->setPixmap(time_icon.scaled(22,22));
	ui->label_user_icon->setPixmap(user_icon.scaled(22,22));

	ui->lineEdit_license_key->setFocus();

	QDate current_date = QDate::currentDate();
	ui->dateEdit->setDate(current_date);

	QFile license_file(qApp->applicationDirPath()+"/license.ini");
	if(license_file.exists())
	{
		QSettings license(qApp->applicationDirPath()+"/license.ini", QSettings::IniFormat);
		ui->lineEdit_license_key->setText(license.value("license_key").toString());
		ui->lineEdit_user_name->setText(license.value("user_name").toString());
		ui->lineEdit_license_hash->setText(license.value("license_hash").toString());
		ui->dateEdit->setDate(QDate::fromString(license.value("expiration_time").toString(), "dd.MM.yyyy"));
	}
}

void LicenseValidationDialog::SetLanguage()
{
	QString path;
	if(custom_language_file_path.isEmpty()) path = qApp->applicationDirPath()+"/language.txt";
	else path = custom_language_file_path;
	QFile language_file(path);
	if(language_file.open(QIODevice::ReadOnly))
	{
	   QTextStream in(&language_file);
	   while (!in.atEnd())
	   {
		   language_pack << in.readLine();
	   }
	   language_file.close();
	}

	this->setWindowTitle(language_pack[0]);
	ui->label_license_key->setText(language_pack[1]);
	ui->label_license_hash->setText(language_pack[2]);
	ui->label_user_name->setText(language_pack[3]);
	ui->label_expiration->setText(language_pack[4]);
	ui->pushButton_cancel->setText(language_pack[5]);
	ui->pushButton_OK->setText(language_pack[6]);
	error1 = language_pack[7];
	error2 = language_pack[8];
	error3 = language_pack[9];
	error4 = language_pack[10];
}
