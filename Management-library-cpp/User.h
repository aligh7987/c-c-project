#ifndef USER_H
#define USER_H
#include <QString>

class User
{
public:
    User();
    virtual ~User();
    virtual void changePassword(QString userName , QString newPass);
    const QString &getUserName() const;
    void setUserName(const QString &newUserName);
    const QString &getPassword() const;
    void setPassword(const QString &newPassword);

protected:

private:
QString userName;
QString password;
};

#endif // USER_H
