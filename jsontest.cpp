#include "jsontest.h"
#include "ui_jsontest.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QFile>
#include <QJsonArray>
#include <QDate>
jsontest::jsontest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::jsontest)
{
    ui->setupUi(this);

    //Запись
    QJsonObject o; //Объект записи
    o["name"] = "Flight Timetable"; //имя объекта
    QString curDate = QDate::currentDate().toString("dd.MM.yyyy"); // текущая дата
    o["date"] = curDate; //дата объекта
    QJsonArray table; //массив из 10 полетов для записи
    for(int i = 0; i < 10; i++)
    {
        QJsonObject t; // полет для записи в массив
        t["fl"] = i; // номер рейса
        t["duration"] = (i + 1) * 2; //продолжительность рейса
        table.append(t); //запись в массив
    }
    o["timetable"] = table; // запись в основной объект
    QJsonDocument d(o); //документ записи
    QFile file("D:/p/js.json");
    if(!file.open(QFile::WriteOnly | QFile::Text))
    { }
    file.write(d.toJson()); //запись
    file.close();
    //----------------------------------------------------------------------------------//
    //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>//
    //----------------------------------------------------------------------------------//
    //Чтение
    QFile newfile("D:/p/js.json"); // Открытие файла
    if(!newfile.open(QFile::ReadOnly | QFile::Text))
    { }
    QByteArray data = newfile.readAll(); //JSON данные
    QJsonDocument newd = QJsonDocument::fromJson(data);
    newfile.close();
    QJsonObject newo = newd.object(); // объект записи
    QString name = newo["name"].toString(); //имя объекта
    QString date = newo["date"].toString(); //дата создания
    ui->name->setText(name); // вывод данных
    ui->date->setText(date);
    QJsonArray newtable = newo["timetable"].toArray(); // массив из 10 полетов
    for(int i = 0; i < newtable.size(); i++) {
        QJsonObject t = newtable[i].toObject(); // объект полета
        int row = ui->table->rowCount();
        ui->table->insertRow(row); // подготовка таблицы
        int fl = t["fl"].toInt(); // номер полета
        int dur = t["duration"].toInt(); // длительность
        ui->table->setItem(row, 0, new QTableWidgetItem(QString::number(fl))); // вывод
        ui->table->setItem(row, 1, new QTableWidgetItem(QString::number(dur)));
    }
}

jsontest::~jsontest()
{
    delete ui;
}
