#include "UserType.h"

UserType::UserType()
{

}

UserType::UserType(int id, QString description)
{
    this->id = id;
    this->description = description;
}

int UserType::GetId()
{
    return this->id;
}

QString UserType::GetDescription()
{
     return this->description;
}
