#ifndef ADMIN_H
#define ADMIN_H
#include <vector>
using namespace std;
#include <QMainWindow>
#include "User.h"
namespace Ui {
class Admin;
}

class Admin : public QMainWindow , public User
{
    Q_OBJECT

public:
    explicit Admin(QString name="",QString adminId="",long long mobilePhone=0,QWidget *parent = nullptr );
    explicit Admin(const Admin& other,QWidget* parent=nullptr) ;
    explicit Admin(const Admin&& other);
    void operator=(const Admin& other);
    virtual void changePassword(QString userName , QString newPass);
    ~Admin();

    const QString &getName() const;
    void setName(const QString &newName);
    long long getMobilePhone() const;
    void setMobilePhone(long long newMobilePhone);
    QString getAdminId() const;
    void setAdminId(QString newAdminId);
    void writeInAdminsFile(QString name, QString adminId ,long long mobNumber);
    vector<Admin> readInAdminsFile();
    int sizeAdminsFile();
    void closeEvent(QCloseEvent *event);
signals:
    void succses(int flag);
private slots:


    void on_changePassword_clicked();

    void on_addMember_clicked();

    void on_addBook_clicked();

    void on_deleteBook_clicked();

    void on_showAllBooks_clicked();

    void on_searchBook_clicked();

    void on_borrowingBook_clicked();

    void on_showAllMembers_clicked();

    void on_deleteMember_clicked();

    void on_printLibraryCard_clicked();

    void on_searchMember_clicked();

    void on_action_triggered();

    void on_action_3_triggered();



private:
    Ui::Admin *ui;
    QString name;
    QString adminId;
    long long  mobilePhone ;
};

#endif // ADMIN_H
