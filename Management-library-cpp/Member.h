#ifndef MEMBER_H
#define MEMBER_H

#include <QMainWindow>
#include "User.h"
namespace Ui {
class Member;
}

class Member : public QMainWindow , public User
{
    Q_OBJECT

public:
    explicit Member(QWidget *parent = nullptr);
    ~Member();
     virtual void changePassword(QString userName , QString newPass);
    void writeinMemberFile(QString name, QString fatherName, QString nationalityCode, QString birthday, long long mobilePhone, QString email);
    const QString &getMembershipNumber() const;
    void setMembershipNumber(const QString &newMembershipNumber);
    QString mmbrSize();
    const QString &getName() const;
    void setName(const QString &newName);

    const QString &getFatherName() const;
    void setFatherName(const QString &newFatherName);

    const QString &getNationalityCode() const;
    void setNationalityCode(const QString &newNationalityCode);

    const QString &getBirthday() const;
    void setBirthday(const QString &newBirthday);

    long long getMobilePhone() const;
    void setMobilePhone(long long newMobilePhone);

    const QString &getEmail() const;
    void setEmail(const QString &newEmail);

    const QString &getBorrowingDate() const;
    void setBorrowingDate(const QString &newBorrowingDate);

    const QString &getReturnDate() const;
    void setReturnDate(const QString &newReturnDate);
    void reject();
private slots:
    void on_printlibrarycard_clicked();

    void on_listBorrowedBooks_clicked();

    void on_action_triggered();

    void on_action_3_triggered();

void closeEvent(QCloseEvent *event);
void on_changePassword_clicked();

private:
    Ui::Member *ui;
      QString membershipNumber ;
      QString name;
      QString fatherName;
      QString nationalityCode;
      QString birthday ;
      long long mobilePhone ;
      QString email ;
      QString borrowingDate;
      QString returnDate;

};

#endif // MEMBER_H
