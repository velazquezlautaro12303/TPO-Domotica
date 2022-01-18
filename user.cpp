#include "User.h"
#include "UserType.h"

User::User()
{

}

User::User(int id, QString login, QString passWord, UserType *userType)
{
    this->id = id;
    this->login = login;
    this->userType = userType;
    this->passWord = passWord;
}

int User::GetId()
{
    return this->id;
}

QString User::GetLogin()
{
    return this->login;
}

QString User::GetPassword()
{
    return this->passWord;
}

UserType * User::GetUserType()
{
    return this->userType;
}
