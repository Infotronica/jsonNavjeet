#ifndef WIDGETMAIN_H
#define WIDGETMAIN_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QComboBox>
#include <QTimer>

namespace Ui {
class WidgetMain;
}

class WidgetMain : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetMain(QWidget *parent = 0);
    ~WidgetMain();

    QString fileNameSettings;
    QJsonObject jsonObjectSettings; // keep configuration in JSON format

    void initialize();
    void createSettings();
    void loadSettings();
    void saveSettings();
    void jsonToWidgets();
    void widgetsToJSON();
    void msgOk(QString msg);
    int msgYesNo(QString msg);

private slots:
    void on_btnSave_clicked();

    void on_btnLoad_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::WidgetMain *ui;
};

#endif // WIDGETMAIN_H
