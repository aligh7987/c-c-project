#include "User.h"

User::User()
{

}

User::~User()
{

}

void User::changePassword(QString userName, QString newPass)
{
return;
}

const QString &User::getUserName() const
{
    return userName;
}

void User::setUserName(const QString &newUserName)
{
    userName = newUserName;
    return;
}

const QString &User::getPassword() const
{
    return password;
}

void User::setPassword(const QString &newPassword)
{
    password = newPassword;
    return;
}
