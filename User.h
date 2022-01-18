#ifndef USER_H
#define USER_H

#include <QString>
#include <UserType.h>

class User
{
private:
    int id;
    QString login;
    QString passWord;
    UserType * userType;

public:
    User();
    User(int id, QString login, QString passWord, UserType *userType);

    int GetId();
    QString GetLogin();
    QString GetPassword();
    UserType * GetUserType();
};

#endif // USER_H
