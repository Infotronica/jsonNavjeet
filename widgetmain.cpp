#include "widgetmain.h"
#include "ui_widgetmain.h"

WidgetMain::WidgetMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetMain)
{
    ui->setupUi(this);
}

WidgetMain::~WidgetMain()
{
    delete ui;
}

void WidgetMain::initialize()
{
    QStringList stringList;

    fileNameSettings="jsonSettings.txt"; // configuration file in JSON format

    stringList << "One" << "Tow" << "Three" << "Four" << "Five";
    ui->comboBox->clear();
    ui->comboBox->addItems(stringList);
    ui->comboBox->setCurrentIndex(-1);

    createSettings();
}

void WidgetMain::createSettings()
{
    bool existe;

    existe=QFile(fileNameSettings).exists();
    if (!existe) // if JSON file does not exists create it
    {
        // create configuration in JSON format
        jsonObjectSettings.insert("lineEdit", "");
        jsonObjectSettings.insert("comboBox", "");
        jsonObjectSettings.insert("checkBox", "0");
        jsonObjectSettings.insert("dial", "0");
        jsonObjectSettings.insert("horizontalSlider", "0");
        saveSettings();
    }

    loadSettings();
}

void WidgetMain::loadSettings()
{
    QJsonDocument jsonDocument;
    QByteArray byteArray;
    QFile qFile;

    qFile.setFileName(fileNameSettings);
    qFile.open(QFile::ReadOnly); // open in read mode
    byteArray=qFile.readAll(); // read all the file content
    qFile.close(); // close the file
    jsonDocument = QJsonDocument::fromJson(byteArray); // parse to JSON document
    jsonObjectSettings = jsonDocument.object(); // parse to JSON object

    jsonToWidgets();
}

void WidgetMain::saveSettings()
{
    QJsonDocument jsonDocument;
    QByteArray byteArray;
    QFile qFile;

    widgetsToJSON();

    jsonDocument = QJsonDocument(jsonObjectSettings);  // parse to JSON object from JSON document
    byteArray=jsonDocument.toJson(QJsonDocument::Indented); // parse to byte array in indented way

    qFile.setFileName(fileNameSettings);
    qFile.open(QFile::WriteOnly); // open in write mode
    qFile.write(byteArray); // transfet all the byte array into the file buffer
    qFile.flush(); // empty the buffer to disk
    qFile.close(); // close the file
}

void WidgetMain::jsonToWidgets()
{
    QString lineEdit,comboBox;
    int checkBox,dial,horizontalSlider;

    // take the JSON configuration and put in the widgets properties
    lineEdit=jsonObjectSettings.value("lineEdit").toString();
    comboBox=jsonObjectSettings.value("comboBox").toString();
    checkBox=jsonObjectSettings.value("checkBox").toString().toInt();
    dial=jsonObjectSettings.value("dial").toString().toInt();
    horizontalSlider=jsonObjectSettings.value("horizontalSlider").toString().toInt();

    ui->lineEdit->setText(lineEdit);
    ui->comboBox->setCurrentText(comboBox);
    ui->checkBox->setChecked(checkBox);
    ui->dial->setValue(dial);
    ui->horizontalSlider->setValue(horizontalSlider);
}

void WidgetMain::widgetsToJSON()
{
    QString lineEdit,comboBox;
    int checkBox,dial,horizontalSlider;

    // take value of widget propeties and put in JSON configuration
    lineEdit=ui->lineEdit->text();
    comboBox=ui->comboBox->currentText();

    if (ui->checkBox->isChecked())
    {
        checkBox=1;
    }
    else
    {
        checkBox=0;
    }

    dial=ui->dial->value();
    horizontalSlider=ui->horizontalSlider->value();

    jsonObjectSettings["lineEdit"]=lineEdit;
    jsonObjectSettings["comboBox"]=comboBox;
    jsonObjectSettings["checkBox"]=QString::number(checkBox);
    jsonObjectSettings["dial"]=QString::number(dial);
    jsonObjectSettings["horizontalSlider"]=QString::number(horizontalSlider);
}

void WidgetMain::msgOk(QString msg) // mostrar un mensaje de aviso
{
    QMessageBox msgBox;

    msgBox.setText(msg);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.addButton("Ok",QMessageBox::YesRole);
    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.exec();
}

int WidgetMain::msgYesNo(QString msg) // mostrar un mensaje con petición de SI o NO
{
    QMessageBox msgBox;
    int mb;

    msgBox.setText(msg);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.addButton("No",QMessageBox::NoRole); // return 0
    msgBox.addButton("Si",QMessageBox::YesRole); // return 1
    msgBox.setDefaultButton(QMessageBox::Yes);
    mb=msgBox.exec();
    return mb;
}

void WidgetMain::on_btnSave_clicked()
{
    saveSettings();
}

void WidgetMain::on_btnLoad_clicked()
{
    loadSettings();
}

void WidgetMain::on_pushButton_clicked()
{
    msgOk("Hello Navjeet");
}

void WidgetMain::on_pushButton_2_clicked()
{
    int mb;

    mb=msgYesNo("Are you cute?");

    if (mb)
    {
        msgOk("You chose yes");
    }
    else
    {
        msgOk("Wrong answer");
    }
}
