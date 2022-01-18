/**
 * @file mainwindow.h
 * @version 1.0
 * @date 10/09/2021
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QTreeWidgetItem>
#include <QList>
#include <QLabel>
#include "mysql.h"
#include "serialterminal.h"
#include "chosecamara.h"
#include "timer.h"
#include "camara.h"
#include "viewtemperatura.h"
#include "riel.h"
#include "ilumicacion.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MyVideoCapture;

/**
 * @brief Esta clase representa el formulario principal
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        /**
         * @brief Constructor
         * @param Padre
         */
        MainWindow(QWidget *parent = nullptr);

        /**
         * @brief Destructor
         */
        ~MainWindow();

        /**
         * @brief LoadLogs
         */
        void LoadLogs();

        /**
         * @brief Carga los usuarios en la lista del formulario
         */
        void LoadUsers();

        /**
         * @brief Carga los usuarios en la lista del formulario
         * @param user
         */
        void LoadUsers(User * user);

        /**
         * @brief Carga las habitaciones en la lista del formulario
         */
        void LoadRooms();

        /**
         * @brief Carga la lista de nodos de habitaciones y dispositivos
         */
        void LoadListRooms();

    private:
        SerialTerminal connectionSerial;
        Ui::MainWindow *ui;
        QStackedWidget *stackedWidgetIluminacion;
        QStackedWidget *stackedWidgetCamara;

        /**
         * @brief Representa la clase para el manejo de datos
         */
        mysql my_mysql;

        //QList<QLabel>* listCamara;

        MyVideoCapture* mOpenCV_videoCapture;

        //ChoseCamara choseCamara;
        timer timer;
        QList<Camara*> listaCamara;
        QList<ViewTemperatura*> listaTemperatura;
        QList<Riel*> listaRiel;
        QList<Ilumicacion*> listaIluminacion;

        QMap<QString, int> listaCamaraRoom;
        QMap<QString, int> listaTemperaturaRoom;
        QMap<QString, int> listaRielRoom;
        QMap<QString, int> listaIluminacionRoom;

        User *user;

    signals:
        void ChangeIndexStacked(int index);
        void SendIndexTreeWidgetIluminacion(int index);
        void SendIndexTreeWidgetCamara(int index);
        void sendIndexTabWidget(int index);
        void SendActiveSequence(bool tmp);
        void SendAutomatic(bool condition);

    public slots:
        void QtreeWidgetsConectionStackedWidget(QTreeWidgetItem * item);

    private slots:
        void on_actionComunicacionSerial_triggered();

        /**
         * @brief Guarda al usuario en la base de datos
         */
        void on_pushButton_GuardarUsuario_clicked();

        /**
         * @brief Elimina al usuario de la base de datos
         */
        void on_pushButton_EliminarUsuario_clicked();

        /**
         * @brief Guarda la habitacion de la base de datos
         */
        void on_pushButton_InsertarHabitacion_clicked();

        /**
         * @brief Elimina la habitacion de la base de datos
         */
        void on_pushButton_EliminarHabitacion_clicked();

//        void on_pushButton_ChoseCamara_clicked();
        void UpdateTemperature(int temperature);
        void on_actionSalit_triggered();

        void on_twMenu_tabBarClicked(int index);

        void on_spinBox_valueChanged(const QString &arg1);

        void on_checkBox_Alarma_clicked();
        void VerificarSitieneCamarasIluminacion(QString room);
        void VerificarSitieneTemperaturaActivado(QString room);
        bool VerificarSitieneCamaras(QString room);
        bool VerificarSitieneIluminacion(QString room);
        void VerificarSitieneRielActivado(QString room);

        void on_btnInput_clicked();

private:
        bool camaras[2];
        bool alarmas[2];

        QSqlQueryModel *mLogs;

};
#endif // MAINWINDOW_H

