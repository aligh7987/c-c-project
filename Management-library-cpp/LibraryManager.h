#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include <QMainWindow>
#include <iostream>
#include "Admin.h"
#include"DeleteAdmin.h"
using namespace std;
namespace Ui {
class LibraryManager;
}

class LibraryManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit LibraryManager(QString name="",QString adminId="",long long mobilePhone=0,QWidget *parent = nullptr);
    explicit LibraryManager(const LibraryManager& other,QWidget* parent=nullptr);
    explicit LibraryManager(const LibraryManager&& other);
    ~LibraryManager();
    void operator=( LibraryManager& lm);
    const Admin &getManager() const;
    void setManager( Admin* &newManager,QString pass );
    void readInManagerFile();
    void  writeInManagerFile(QString name, QString adminId ,long long mobNumber, QString pass = "manager");

private slots:
    void on_addAdmin_clicked();
    void closeEvent(QCloseEvent *event);
    void on_deleteAdmin_clicked();

    void on_showAllAdmin_clicked();

    void on_searchAdmin_clicked();

    void on_addMember_clicked();

    void on_deleteMember_clicked();

    void on_showAllMember_clicked();

    void on_addBook_clicked();

    void on_deleteBook_clicked();

    void on_showAllBook_clicked();

    void on_searchBook_clicked();

    void on_borrowingBook_clicked();

    void on_printAdminCard_clicked();

    void on_printLibraryCard_clicked();

    void on_searchMember_clicked();


    void on_action_3_triggered();



    void on_changePassword_clicked();

private:
    Ui::LibraryManager *ui;
    Admin* manager;

};

#endif // LIBRARYMANAGER_H
