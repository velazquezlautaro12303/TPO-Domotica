#include "mysql.h"
#include <QMessageBox>

#include <QDebug>
#include <QSqlQuery>

#include <QAbstractItemModel>
#include <qstandarditemmodel.h>
#include <qapplication.h>

#include "camara.h"

mysql::mysql(QWidget *parent) : QWidget(parent)
{

}

void mysql::Connect(/*QString nameConnection*/)
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Driver={MySQL ODBC 8.0 Unicode Driver};Database=smarthouse");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("murcielago456");

    bool connection = db.open();
    if(connection == false)
    {
        QMessageBox::critical(this,"Error","No se pudo conectar a la Base de Datos");
    }
}

void mysql::Close()
{
    db.close();
}

/*----------------------------------------------------------------*/

User * mysql::VerifyUsers(QString login, QString password)
{
    User * userLogin = NULL;

    QSqlQueryModel * user = new QSqlQueryModel();

    QString queryVerifyUsers= QString("call VerifyUser('%1', '%2');").arg(login).arg(password);

    user->setQuery(queryVerifyUsers);

    if (user->rowCount() != 0)
    {
        QString id = user->record(0).value("Id").toString();
        QString login = user->record(0).value("Login").toString();
        QString password = user->record(0).value("PassWord").toString();
        int idUserType = user->record(0).value("IdUserType").toInt();
        QString userDescription = user->record(0).value("Description").toString();

        UserType * userType = new UserType(idUserType, userDescription);


        userLogin = new User(id.toInt(), login, password, userType);

    }

    return userLogin;
}

QSqlQueryModel * mysql::LoadUsers()
{
    QSqlQueryModel * users = new QSqlQueryModel();
    users->setQuery("call GetUsers();");

    return users;
}

bool mysql::LoadUsers(QListWidget*& listWidget, QComboBox*& combo)
{
    bool ok = false;

    combo->clear();
    listWidget->clear();
    QSqlQuery query;
    if (query.exec("call GetUsers();"))
    {
        int id;
        QVariant login;
        int active;
        while (query.next())
        {
            id = query.value("Id").toInt();
            login = query.value("Login").toString();
            active = query.value("Active").toInt();

            QString stringLogin = login.toString();

            combo->insertItem(id, stringLogin, login);
            combo->itemData(id);

            if (active == 1)
            {
                listWidget->addItem(stringLogin);
            }
        }
    }

    return ok;
}

bool mysql::AddUser(QString stringAddUser)
{
    int result = 1;

    QSqlQuery queryAddUser = QSqlQuery(db);

    if (queryAddUser.exec(stringAddUser))
    {
        while (queryAddUser.next())
        {
            result = queryAddUser.value("result").toInt();
        }
    }

    return result;
}

bool mysql::DeleteUser(QString stringDeleteUser)
{
      bool ok = false;

      QSqlQuery queryDeleteUser = QSqlQuery(db);

      if (queryDeleteUser.exec(stringDeleteUser))
      {
          ok = true;
      }

      return ok;
 }

bool mysql::LoadRooms(QListWidget*& listWidget)
{
    bool ok = false;

    listWidget->clear();
    QSqlQuery query;
    if (query.exec("call GetRooms();"))
    {
        QVariant login;
        while (query.next())
        {
            login = query.value("Description").toString();
            QString stringLogin = login.toString();
            listWidget->addItem(stringLogin);


        }
    }

    return ok;
}

QSqlQueryModel * mysql::LoadRooms()
{
    QSqlQueryModel * rooms = new QSqlQueryModel();
    rooms->setQuery("call GetRooms();");

    return rooms;
}

int mysql::AddRoom(QString stringAddRoom)
{
    int result = 1;

    QSqlQuery queryAddUser = QSqlQuery(db);

    if (queryAddUser.exec(stringAddRoom))
    {
        while (queryAddUser.next())
        {
            result = queryAddUser.value("result").toInt();
        }
    }

    return result;
}

bool mysql::DeleteRoom(QString stringDeleteRoom)
{
    bool ok = false;

    QSqlQuery queryDeleteUser = QSqlQuery(db);

    if (queryDeleteUser.exec(stringDeleteRoom))
    {
        ok = true;
    }

    return ok;
}

void mysql::LoadTreeWidget(QTreeWidget*& treeWidget, QStackedWidget*& stackedWidget, QStackedWidget*& stackedWidgetCamara, SerialTerminal &connectionSerial, timer &_timer, QList<Camara*> &listaCamara, QStackedWidget *& stack_temperature, QStackedWidget *& stack_RELE, QList<ViewTemperatura*> &listaTemperatura, QList<Riel*> &listaRiel, QList<Ilumicacion*> &listaIluminacion, QMap<QString, int> &listaCamaraRoom, QMap<QString, int> &listaTemperaturaRoom, QMap<QString, int> &listaIluminacionRoom, QMap<QString, int> &listaRielRoom)
{
    treeWidget->clear();
    listaCamara.clear();
    listaRiel.clear();
    listaTemperatura.clear();

    int indiceStackCamara = 0;
    int indiceStackIluminacion = 0;
    int indiceStackRiel = 0;
    int indiceStackTemperatura = 0;

    QSqlQuery query;
    if (query.exec("call GetDevicesRooms();"))
    {
        bool condition = query.next();
        while (condition)
        {
            QVariant idRoom = query.value("IdRoom").toString();
            QTreeWidgetItem* itemParent = new QTreeWidgetItem();
            while (condition && idRoom == query.value("IdRoom"))
            {
                QString descriptionRoom = query.value("DescriptionRoom").toString();

                itemParent->setText(0, descriptionRoom);
                itemParent->setData(1, 0, idRoom);
                itemParent->setData(2, 0, 0);

                QVariant idDevice = query.value("IdDevice").toString();
                QString descriptionDevice = query.value("DescriptionDevice").toString();
                QString idTypeDevice = query.value("idTypeDevice").toString();

                QTreeWidgetItem* itemChild = new QTreeWidgetItem();
                itemChild->setText(0, descriptionDevice);
                itemChild->setData(1, 0, idDevice);
                itemChild->setData(2, 0, idTypeDevice);

                QVariant IdTypeDevice = query.value("IdTypeDevice").toString();

                if (IdTypeDevice == 1)
                {
                    itemChild->setIcon(0,QIcon(":/Imagenes/Camara.png"));

                    QVariant HasAlarm = query.value("HasAlarm").toString();
                    if (HasAlarm == "1")
                    {
                        QTreeWidgetItem* itemChildAlarma = new QTreeWidgetItem();
                        itemChildAlarma->setText(0, "Alarma");
                        itemChildAlarma->setCheckState(0,Qt::Unchecked);
                        itemChild->addChild(itemChildAlarma);
                        itemChildAlarma->setDisabled(false);
                    }

                    QVariant idCamara = query.value("Orden").toInt();

                    qDebug() << idCamara.toInt();

                    Camara* _camara = new Camara(itemChild, connectionSerial, _timer, idCamara.toInt());   //Reemplazar el uno por num de camara obtener de sql
                    stackedWidgetCamara->addWidget(_camara);

                    listaCamara.append(_camara);
                    listaCamaraRoom.insert(descriptionRoom, indiceStackCamara++);
                }
                else if(IdTypeDevice == 2)//Sensor de Temperatura
                {
                    itemChild->setCheckState(0,Qt::Unchecked);

                    ViewTemperatura *temp = new ViewTemperatura();
                    stack_temperature->addWidget(temp);
                    listaTemperatura.append(temp);

                    listaTemperaturaRoom.insert(descriptionRoom, indiceStackTemperatura++);
                }
                else if(IdTypeDevice == 3)
                {
                    itemChild->setIcon(0,QIcon(":/Imagenes/Foco.png"));

                    Ilumicacion *luz = new Ilumicacion(connectionSerial,this->parentWidget());

                    stackedWidget->addWidget(luz);
                    listaIluminacion.append(luz);

                    listaIluminacionRoom.insert(descriptionRoom, indiceStackIluminacion++);
                }
                else if(IdTypeDevice == 4)  //Riel
                {
                    itemChild->setCheckState(0,Qt::Unchecked);

                    Riel *riel = new Riel(connectionSerial);

                    stack_RELE->addWidget(riel);

                    listaRiel.append(riel);

                    listaRielRoom.insert(descriptionRoom, indiceStackRiel++);
                }
                else if(IdTypeDevice == 5)  //Sensor de puerta
                {
                    itemChild->setCheckState(0,Qt::Unchecked);
                }

                itemParent->addChild(itemChild);

                condition = query.next();
            }
            treeWidget->addTopLevelItem(itemParent);
        }
    }
}
