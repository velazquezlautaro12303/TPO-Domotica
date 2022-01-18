/**
 * @file mysql.h
 * @version 1.0
 * @date 10/09/2021
 * @author Grupo04-Corporation
 * @title Capa de conexion a base de datos
 */

#ifndef MYSQL_H
#define MYSQL_H

#include <QWidget>
#include <QSqlDatabase>

#include <QList>
#include <QString>
#include <QTreeWidget>
#include <QStackedWidget>
#include <QListWidget>
#include <QTableView>
#include "serialterminal.h"
#include "timer.h"
#include "camara.h"
#include "viewtemperatura.h"
#include "ilumicacion.h"
#include <QtSql>
#include <qsqldatabase.h>
#include "riel.h"
#include "User.h"

/**
 * @brief Esta clase provee conexion a la base de datos, y distintos metodo
 * para que se puedan traer datos y hacer operaciones sobre la misma
 */
class mysql : public QWidget
{
    Q_OBJECT
    public:
        explicit mysql(QWidget *parent = nullptr);
        /**
         * @brief Metodo Conecta a la base de datos
         */
        void Connect();

        /**
         * @brief Metodo que cierra la conexion a la base de datos
         */
        void Close();
        /*-------------------------------*/
        /**
         * @brief Verifica la existencia del usuario en la base de datos
         * @param Login del usuario
         * @param Password del usuario
         * @return retorna verdadero o falso segun la existencia o no del usuario
         */
        /**
         * @brief Verifica la existencia del usuario en la base de datos
         * @param Login del usuario
         * @param Password del usuario
         * @return retorna verdadero o falso segun la existencia o no del usuario
         */
        User * VerifyUsers(QString login, QString password);

        /**
         * @brief mysql::LoadUsers
         * @param listWidget
         * @return
         */
        bool LoadUsers(QListWidget*& listWidget, QComboBox*& combo);

        /**
         * @brief Carga los usuario de la base de datos
         * @return Retorna el modelo con los usuarios
         */
        QSqlQueryModel * LoadUsers();

        /**
         * @brief Agrega un usuario a la base de datos
         * @param La consulta para agrear el usuario
         * @return
         */
        bool AddUser(QString queryAddUser);

        /**
         * @brief Elminina un usuario de la base de datos
         * @param La consulta para elimminar el usuario
         * @return
         */
        bool DeleteUser(QString queryDeletUser);

        /**
         * @brief LoadRooms
         * @param listWidget
         * @return
         */
        bool LoadRooms(QListWidget*& listWidget);

        /**
         * @brief Carga las habitaciones de la base de datos
         * @return Retorna las habitaciones
         */
        QSqlQueryModel * LoadRooms();

        /**
         * @brief Agrega una habitacion
         * @param La consulta para agregar la habitacion
         * @return
         */
        int AddRoom(QString queryRoom);

        /**
         * @brief DeleteRoom
         * @param stringDeleteRoom
         * @return
         */
        bool DeleteRoom(QString stringDeleteRoom);

        /**
         * @brief Carga el arbol con las habitaciones y los dispositivos
         * @param El arbol a cargar las habitaciones y los dispositivos
         * @param stackedWidget
         * @param connectionSerial
         * @return
         */
        void LoadTreeWidget(QTreeWidget*& treeWidget, QStackedWidget*& stackedWidget, QStackedWidget*& stackedWidgetCamara, SerialTerminal &connectionSerial, timer &_timer, QList<Camara*> &listaCamara, QStackedWidget *& stack_temperature, QStackedWidget *& stack_RELE, QList<ViewTemperatura*> &listaTemperatura, QList<Riel*> &listaRiel, QList<Ilumicacion*> &listaIluminacion, QMap<QString, int> &listaCamaraRoom, QMap<QString, int> &listaTemperaturaRoom, QMap<QString, int> &listaIluminacionRoom, QMap<QString, int> &listaRielRoom);

    private:
        /**
         * @brief La variable que representa la base de datos
         */
        QSqlDatabase db;
    signals:
};

#endif // MYSQL_H
