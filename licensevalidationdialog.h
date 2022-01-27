#ifndef LICENSEVALIDATIONDIALOG_H
#define LICENSEVALIDATIONDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QPixmap>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QSettings>
#include <QFile>
#include <QDate>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class LicenseValidationDialog; }
QT_END_NAMESPACE

class LicenseValidationDialog : public QDialog
{
	Q_OBJECT

public:
	LicenseValidationDialog(QWidget *parent = nullptr);
	~LicenseValidationDialog();

	bool CheckBasicValid();
	bool valid = false;

private slots:
	void processStarted();
	void readyReadStandardOutput();
	void encodingFinished();
	void on_pushButton_OK_clicked();
	void on_pushButton_cancel_clicked();

private:
	Ui::LicenseValidationDialog *ui;

	//DO NOT TOUCH
	QProcess* process;
	QStringList RunCommand(QString command);
	void delay_MSec(unsigned int msec);
	void SetupScript();
	QString GetNTPDate();
	void PrepareWindow();
	void SetLanguage();
	bool silent = false;
	QStringList language_pack;
	QString error1, error2, error3, error4;
	bool CheckLicense(QString license_key, QString license_hash, QString user_name, QString expiration_time);
	void SaveLicenseFile(QString license_key, QString license_hash, QString user_name, QString expiration_time);

	//DEVELOPER SETTINGS
	QString API_KEY = "";
	QString NTP_SERVER = "";
	bool save_license = true;
	bool set_custom_language = false;
	QString custom_language_file_path = "";

};
#endif // LICENSEVALIDATIONDIALOG_H
