#ifndef USERTYPE_H
#define USERTYPE_H

#include <QString>

class UserType
{
private:
    int id;
    QString description;

public:
    UserType();
    UserType(int id, QString description);

    int GetId();
    QString GetDescription();
};

#endif // USERTYPE_H
