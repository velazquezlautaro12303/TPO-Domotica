#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QTreeWidget>
#include <QCheckBox>

#include "ilumicacion.h"
#include "camara.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , my_mysql(this)
{
    ui->setupUi(this);

    stackedWidgetIluminacion = new QStackedWidget;
    stackedWidgetCamara = new QStackedWidget;

    ui->stackedWidget_INFO->addWidget(stackedWidgetCamara);
    ui->stackedWidget_INFO->addWidget(stackedWidgetIluminacion);
    ui->stackedWidget_INFO->addWidget(new QWidget());

    ui->lblRoom->setText("");

    connect(ui->twRooms, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(QtreeWidgetsConectionStackedWidget(QTreeWidgetItem *)));
    connect(this, SIGNAL(SendIndexTreeWidgetIluminacion(int)), stackedWidgetIluminacion, SLOT(setCurrentIndex(int)));
    connect(this, SIGNAL(SendIndexTreeWidgetCamara(int)), stackedWidgetCamara, SLOT(setCurrentIndex(int)));
    connect(this, SIGNAL(ChangeIndexStacked(int)), ui->stackedWidget_INFO, SLOT(setCurrentIndex(int)));
    connect(this, SIGNAL(sendIndexTabWidget(int)), ui->twMenu, SLOT(setCurrentIndex(int)));
    connect(this, SIGNAL(SendActiveSequence(bool)), &connectionSerial, SLOT(Active_Sensor_Puerta(bool)));
    connect(this, SIGNAL(SendAutomatic(bool)), &connectionSerial, SLOT(SendPersianaAutomatic(bool)));
    connect(&connectionSerial, SIGNAL(SendTemperature(int)), this, SLOT(UpdateTemperature(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LoadLogs()
{
    this->mLogs = new QSqlQueryModel();
    this->mLogs->setQuery("call GetLogs('', '2021-01-01 00:00:00', '2021-12-14 00:00:00')");
    ui->tvLogs->setModel(this->mLogs);
}

void MainWindow::LoadUsers()
{
    my_mysql.LoadUsers(ui->lwUsers, ui->cmbUsers);
}

void MainWindow::LoadUsers(User * user)
{
    this->user = user;

    ui->lblUser->setText("Usuario : " + user->GetLogin());

    if (user->GetUserType()->GetId() != 1)
    {
        ui->twMenu->removeTab(1);
    }

    this->LoadUsers();
}

void MainWindow::LoadRooms()
{
    my_mysql.LoadRooms(ui->lwRooms);
}

void MainWindow::LoadListRooms()
{
    foreach (QWidget* var, listaCamara) {
        stackedWidgetCamara->removeWidget(var);
    }
    foreach (QWidget* var, listaTemperatura) {
        ui->stackedWidget_Temperature->removeWidget(var);
    }
    foreach (QWidget* var, listaRiel) {
        ui->stackedWidget_RELE->removeWidget(var);
    }
    foreach (QWidget* var, listaIluminacion) {
        stackedWidgetIluminacion->removeWidget(var);
    }

    listaCamara.clear();
    listaRiel.clear();
    listaIluminacion.clear();
    listaTemperatura.clear();

    listaCamaraRoom.clear();
    listaRielRoom.clear();
    listaIluminacionRoom.clear();
    listaTemperaturaRoom.clear();

    my_mysql.LoadTreeWidget(ui->twRooms,stackedWidgetIluminacion, stackedWidgetCamara, connectionSerial, timer, listaCamara, ui->stackedWidget_Temperature, ui->stackedWidget_RELE, listaTemperatura, listaRiel, listaIluminacion, listaCamaraRoom, listaTemperaturaRoom, listaIluminacionRoom, listaRielRoom);
}

bool MainWindow::VerificarSitieneCamaras(QString room)
{
    bool tmp = false;
    if(listaCamaraRoom.contains(room))
    {
        emit ChangeIndexStacked(0);
        emit SendIndexTreeWidgetCamara(listaCamaraRoom.value(room));
        tmp = true;
    }
    return tmp;
}

bool MainWindow::VerificarSitieneIluminacion(QString room)
{
    bool tmp = false;
    if(listaIluminacionRoom.contains(room))
    {
        emit ChangeIndexStacked(1);
        emit SendIndexTreeWidgetIluminacion(listaCamaraRoom.value(room));
        tmp = true;
    }
    return tmp;
}

void MainWindow::VerificarSitieneCamarasIluminacion(QString room)
{
    if(VerificarSitieneCamaras(room) == false)
    {
        if(VerificarSitieneIluminacion(room) == false)
        {
            emit ChangeIndexStacked(2);
        }
    }
}

void MainWindow::VerificarSitieneRielActivado(QString room)
{
    if(listaRielRoom.contains(room))
    {
        foreach (QTreeWidgetItem* var, ui->twRooms->findItems(room, Qt::MatchContains))
        {
            for(int i = 0; i < var->childCount(); i++)
            {
                if(var->child(i)->text(0) == "Riel")
                {
                    if(var->child(i)->checkState(0) == Qt::Checked)
                    {
                        ui->stackedWidget_RELE->setCurrentIndex(0);
                        emit SendAutomatic(true);
                    }
                    else
                    {
                        ui->stackedWidget_RELE->setCurrentIndex(listaRielRoom.value(room) + 1);
                        emit SendAutomatic(false);
                    }
                }
            }
        }
    }
    else
    {
        ui->stackedWidget_RELE->setCurrentIndex(0);
    }
}

void MainWindow::VerificarSitieneTemperaturaActivado(QString room)
{
    if(listaTemperaturaRoom.contains(room))
    {
        foreach (QTreeWidgetItem* var, ui->twRooms->findItems(room, Qt::MatchContains))
        {
            for(int i = 0; i < var->childCount(); i++)
            {
                if(var->child(i)->text(0) == "Sensor Temperatura")
                {
                    if(var->child(i)->checkState(0) == Qt::Checked)
                    {
                        ui->stackedWidget_Temperature->setCurrentIndex(listaTemperaturaRoom.value(room) + 1);
                    }
                    else
                    {
                        ui->stackedWidget_Temperature->setCurrentIndex(0);
                    }
                }
            }
        }
    }
}

void MainWindow::QtreeWidgetsConectionStackedWidget(QTreeWidgetItem * item)
{
    QString room = "";

    emit sendIndexTabWidget(0);

    ui->twRooms->clearSelection();
    item->setSelected(true);

    ui->stackedWidget_RELE->setCurrentIndex(0);

    if (item->data(2,0) == 0) // Es habitacion
    {
        room = item->data(0,0).toString();
        item->setExpanded(true);
        VerificarSitieneCamarasIluminacion(room);
    }
    else if(item->data(2,0) == 1)
    {
        room = item->parent()->text(0);
        VerificarSitieneCamaras(room);
    }
    else if(item->data(2,0) == 3)
    {
        room = item->parent()->text(0);
        VerificarSitieneCamarasIluminacion(room);
    }
    else if(item->data(2,0) == 2 || item->data(2,0) == 4)
    {
        room = item->parent()->text(0);
        VerificarSitieneCamarasIluminacion(room);
    }
    else if(item->text(0) == "Alarma")
    {
        room = item->parent()->parent()->text(0);

        if(item->checkState(0) == Qt::Checked)
        {
            listaCamara.at(listaCamaraRoom.value(room))->mOpenCV_videoCapture->alarmaActive = true;
        }
        else
        {
            listaCamara.at(listaCamaraRoom.value(room))->mOpenCV_videoCapture->alarmaActive = false;
            listaCamara.at(listaCamaraRoom.value(room))->mOpenCV_videoCapture->stateAlarma = false;
            listaCamara.at(listaCamaraRoom.value(room))->mOpenCV_videoCapture->SendOnAlarma(0);
            timer.removeItem(item->parent());
        }

        VerificarSitieneCamaras(room);
    }
    else if(item->data(2,0) == 5)
    {
        room = item->parent()->text(0);

        if(item->checkState(0) == Qt::Checked)
        {
            emit SendActiveSequence(true);
        }
        else
        {
            emit SendActiveSequence(false);
        }

        VerificarSitieneCamarasIluminacion(room);
    }

    VerificarSitieneRielActivado(room);
    VerificarSitieneTemperaturaActivado(room);

    ui->lblRoom->setText("Habitacion : " + room);
}

void MainWindow::on_actionComunicacionSerial_triggered()
{
    connectionSerial.show();
}

void MainWindow::on_pushButton_GuardarUsuario_clicked()
{
    if (ui->lineEdit_Usuario->text() != "")
    {
        if(ui->lineEdit_Contrasenia->text() == ui->lineEdit_RepitaContrasenia->text() && ui->lineEdit_RepitaContrasenia->text() != "" && ui->lineEdit_Usuario->text() != "")
        {
            QString user = ui->lineEdit_Usuario->text();
            QString password = ui->lineEdit_Contrasenia->text();

            int idCurrentUser = this->user->GetId();

            QString queryAddUser = QString("call AddUser(%1, '%2', '%3');").arg(idCurrentUser).arg(user).arg(password);

            if (my_mysql.AddUser(queryAddUser) == 1)
            {
                QMessageBox::about(this, "Informacion", "El usuario fue guardado con exito");

                ui->lineEdit_Usuario->clear();
                ui->lineEdit_Contrasenia->clear();
                ui->lineEdit_RepitaContrasenia->clear();

                this->LoadUsers();
            }
            else if (my_mysql.AddUser(queryAddUser) == 0)
            {
                 QMessageBox::critical(this, "Error", "Ya existe el usuario");
            }
        }
        else
        {
            QMessageBox::critical(this, "Error", "Las contraseñas son distintas");
        }
    }
    else
    {
         QMessageBox::critical(this, "Error", "Debe ingresar el usuario");
    }
}

void MainWindow::on_pushButton_EliminarUsuario_clicked()
{
    QListWidgetItem* item = ui->lwUsers->currentItem();
    QString login = item->text();

    if (login == "Javier" || login == "lautaro")
    {
         QMessageBox::about(this, "Informacion", "No se puede borrar el usuario porque es administrador");
         return;
    }

    int idCurrentUser = this->user->GetId();

    QString queryDeleteUser = QString("call DeleteUser(%1, '%2');").arg(idCurrentUser).arg(login);

    if (my_mysql.AddUser(queryDeleteUser))
    {
        QMessageBox::about(this, "Informacion", "El usuario fue eliminado con exito");

        ui->lineEdit_Usuario->clear();
        ui->lineEdit_Contrasenia->clear();
        ui->lineEdit_RepitaContrasenia->clear();

        this->LoadUsers();
    }
    else
    {
         QMessageBox::critical(this, "Error", "Hubo un error al guardar al usuario");
    }
}

void MainWindow::on_pushButton_InsertarHabitacion_clicked()
{
    if (ui->lineEdit_NombreHabitacion->text() != "")
    {
        QString room = ui->lineEdit_NombreHabitacion->text();

        bool hasDimer = ui->checkBox_Dimerizado->isChecked();
        bool hasTemperatureControl = ui->checkBox_Temperatura->isChecked();
        bool hasRiel = ui->checkBox_Riel->isChecked();
        bool hasSensor = ui->checkBox_Sensor->isChecked();
        int countCameras = ui->spinBox->text().toInt();

        QString valueHasDimmer = "false";
        if (hasDimer)
        {
            valueHasDimmer = "true";
        }
        QString valueHasTemperatureControl = "false";
        if (hasTemperatureControl)
        {
            valueHasTemperatureControl = "true";
        }
        QString valueHasRiel = "false";
        if (hasRiel)
        {
            valueHasRiel = "true";
        }
        QString valueHasSensor = "false";
        if (hasSensor)
        {
            valueHasSensor = "true";
        }

        QString stringAlarms = "";
        for (int i  = 0 ; i < 2; i++)
        {
            if (alarmas[i])
            {
                stringAlarms = stringAlarms + "1,";
            }
            else
            {
                stringAlarms = stringAlarms + "0,";
            }
        }

        int idCamara = ui->spinBox->text().toInt();

        bool hasAlarm = ui->checkBox_Alarma->isChecked();

         QString valueHasAlarm = "false";
         if (hasAlarm)
         {
             valueHasAlarm = "true";
         }

         int idCurrentUser = this->user->GetId();

         QString queryAddRoom = QString("call AddRoomDevice(%1, '%2', %3, %4, %5, %6, %7, %8, %9);").arg(idCurrentUser).arg(room).arg(valueHasDimmer).arg(valueHasTemperatureControl).arg(countCameras).arg(valueHasRiel).arg(valueHasSensor).arg(idCamara).arg(valueHasAlarm);

        if (my_mysql.AddRoom(queryAddRoom) == 1)
        {
            QMessageBox::about(this, "Informacion", "La habitacion fue guardada con exito");

            ui->spinBox->setValue(0);
            ui->checkBox_Dimerizado->setCheckState(Qt::CheckState::Unchecked);
            ui->checkBox_Temperatura->setCheckState(Qt::CheckState::Unchecked);
            ui->checkBox_Riel->setCheckState(Qt::CheckState::Unchecked);
            ui->checkBox_Sensor->setCheckState(Qt::CheckState::Unchecked);
            ui->lineEdit_NombreHabitacion->clear();

            this->LoadRooms();
            this->LoadListRooms();

            camaras[0] = false;
            camaras[1] = false;

            alarmas[0] = false;
            alarmas[1] = false;
        }
        else  if (my_mysql.AddRoom(queryAddRoom) == 0)
        {
             QMessageBox::critical(this, "Error", "Ya existe la habitacion");
        }
    }
    else
    {
         QMessageBox::critical(this, "Error", "Debe ingresar la descripcion de la habitacion");
    }
}

void MainWindow::on_pushButton_EliminarHabitacion_clicked()
{
    QListWidgetItem* item = ui->lwRooms->currentItem();
    QString descripcion = item->text();

    int idCurrentUser = this->user->GetId();

    QString queryDeleteRoom = QString("call DeleteRoom(%1, '%2');").arg(idCurrentUser).arg(descripcion);

    if (my_mysql.DeleteUser(queryDeleteRoom))
    {
        QMessageBox::about(this, "Informacion", "La habitacion fue eliminada con exito");

        ui->lineEdit_NombreHabitacion->clear();
        ui->lineEdit_Contrasenia->clear();
        ui->lineEdit_RepitaContrasenia->clear();

        this->LoadRooms();
        this->LoadListRooms();
    }
    else
    {
         QMessageBox::critical(this, "Error", "Hubo un error al eliminar la habitacion");
    }
}

//void MainWindow::on_pushButton_ChoseCamara_clicked()
//{
//    choseCamara.show();
//}

void MainWindow::UpdateTemperature(int temperature)
{
    listaTemperatura.at(0)->setTemp("Temp: " + QString::number(temperature) + "º");
}

void MainWindow::on_actionSalit_triggered()
{
    this->close();
}


void MainWindow::on_twMenu_tabBarClicked(int index)
{
    ui->lblRoom->setText("");
}


void MainWindow::on_spinBox_valueChanged(const QString &arg1)
{
    int idCamara = ui->spinBox->text().toInt();

    if (idCamara != 0)
    {
       ui->checkBox_Alarma->setChecked(alarmas[idCamara - 1]);
    }
    else
    {
        ui->checkBox_Alarma->setChecked(false);
    }
}


void MainWindow::on_checkBox_Alarma_clicked()
{
    int idCamara = ui->spinBox->text().toInt();
    if (idCamara != 0)
    {
        bool checkAlarma = ui->checkBox_Alarma->isChecked();

        alarmas[idCamara - 1] = checkAlarma;
    }
    else
    {
         ui->checkBox_Alarma->setChecked(false);
    }
}

static QString returnDate(QDate date)
{
    int yearfrom = date.year();
    int monthfrom = date.month();
    int dayfrom = date.day();

    QString dateFromString = QString::number(yearfrom);

    dateFromString.append("-");

    if(monthfrom < 10)
    {
        dateFromString.append("0");
    }

    dateFromString.append(QString::number(monthfrom));

    dateFromString.append("-");

    if(dayfrom < 10)
    {
        dateFromString.append("0");
    }

    dateFromString.append(QString::number(dayfrom));

    return dateFromString;
}

void MainWindow::on_btnInput_clicked()
{
    int index = ui->cmbUsers->currentIndex();
    QString login = ui->cmbUsers->itemText(index);
    QVariant idUser = ui->cmbUsers->itemData(index);

    QDate dateFrom = ui->deDateFrom->date();
    QDate dateTo = ui->deDateTo->date();

    QString dateFromString = returnDate(dateFrom);
    QString dateToString = returnDate(dateTo);

    if(dateFromString < dateToString)
    {
        qDebug() << "call GetLogs('" + login + "', " + dateFromString +" 00:00:00', '" + dateToString + " 00:00:00')";
        this->mLogs->setQuery("call GetLogs('" + login + "', '" + dateFromString +" 00:00:00', '" + dateToString + " 00:00:00')");
    }
    else
    {
        QMessageBox::critical(this, "Error", "Error en ingreso de fechas");
    }

}
