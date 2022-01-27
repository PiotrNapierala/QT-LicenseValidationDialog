#include "licensevalidationdialog.h"
#include "ui_licensevalidationdialog.h"

LicenseValidationDialog::LicenseValidationDialog(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::LicenseValidationDialog)
{
	ui->setupUi(this);
	SetupScript();
	PrepareWindow();
}

LicenseValidationDialog::~LicenseValidationDialog()
{
	delete ui;
}

bool LicenseValidationDialog::CheckBasicValid()
{
	QFile license_file(qApp->applicationDirPath()+"/license.ini");
	if(license_file.exists())
	{
		if(GetNTPDate()!="date_error")
		{
			QSettings license(qApp->applicationDirPath()+"/license.ini", QSettings::IniFormat);
			QString license_key = license.value("license_key").toString();
			QString user_name = license.value("user_name").toString();
			QString expiration_time = license.value("expiration_time").toString();
			QString license_hash = license.value("license_hash").toString();
			silent = true;
			valid = CheckLicense(license_key, license_hash, user_name, expiration_time);
			silent = false;
			return valid;
		}
		else
		{
			QMessageBox::critical(this, error1, error3, QMessageBox::Ok);
			return false;
		}
	}
	else return false;
}

void LicenseValidationDialog::SaveLicenseFile(QString license_key, QString license_hash, QString user_name, QString expiration_time)
{
	QSettings license(qApp->applicationDirPath()+"/license.ini", QSettings::IniFormat);
	license.setValue("license_key", license_key);
	license.setValue("user_name", user_name);
	license.setValue("expiration_time", expiration_time);
	license.setValue("license_hash", license_hash);
}

bool LicenseValidationDialog::CheckLicense(QString license_key, QString license_hash, QString user_name, QString expiration_time)
{
	QString user_key = license_key + user_name + expiration_time + API_KEY;

	QCryptographicHash hash(QCryptographicHash::Sha256);
	hash.addData(user_key.toUtf8());
	QString user_hash = hash.result().toHex();
	hash.reset();

	if(license_hash==user_hash)
	{
		QDate license_date = QDate::fromString(expiration_time, "dd.MM.yyyy");
		if(GetNTPDate()!="date_error")
		{
			QDate current_date = QDate::fromString(GetNTPDate(), "dd.MM.yyyy");
			if(current_date<=license_date) return true;
			else
			{
				if(silent==false) QMessageBox::warning(this, error1, error2, QMessageBox::Ok);
				return false;
			}
		}
		else
		{
			if(silent==false) QMessageBox::critical(this, error1, error3, QMessageBox::Ok);
			return false;
		}
	}
	else
	{
		if(silent==false) QMessageBox::critical(this, error1, error4, QMessageBox::Ok);
		return false;
	}
}

void LicenseValidationDialog::on_pushButton_OK_clicked()
{
	QString license_key = ui->lineEdit_license_key->text();
	QString user_name = ui->lineEdit_user_name->text();
	QString expiration_time = ui->dateEdit->date().toString("dd.MM.yyyy");
	QString license_hash = ui->lineEdit_license_hash->text();

	bool license_ok = CheckLicense(license_key, license_hash, user_name, expiration_time);

	if(license_ok==true)
	{
		valid = true;
		if(save_license==true) SaveLicenseFile(license_key, license_hash, user_name, expiration_time);
		this->close();
	}
	else
	{
		valid = false;
	}
}


void LicenseValidationDialog::on_pushButton_cancel_clicked()
{
	valid = false;
	this->close();
}

