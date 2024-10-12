#include "LibraryManager.h"
#include "ui_LibraryManager.h"
#include <QMessageBox>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QCloseEvent>
#include "AddAdmin.h"
#include "DeleteAdmin.h"
#include "ShowAllAdmin.h"
#include "SearchAdmin.h"
#include "AddMember.h"
#include "DeleteMember.h"
#include "ShowAllMember.h"
#include "AddBook.h"
#include "DeleteBook.h"
#include "ShowAllBooks.h"
#include "SearchBook.h"
#include "LendingBook.h"
#include "PrintAdminCard.h"
#include "PrintMemberCard.h"
#include "SearchMember.h"
#include "Login.h"
#include "ChangePassword.h"
using namespace std;
LibraryManager::LibraryManager(QString name,QString adminId,long long mobilePhone,QWidget *parent ) :
    QMainWindow(parent),
    ui(new Ui::LibraryManager)
{
    this->manager = new Admin(name,adminId,mobilePhone,parent);
    ui->setupUi(this);
    manager->setPassword("manager");
    manager->setUserName("manager");
}

LibraryManager::LibraryManager(const LibraryManager &other,QWidget* parent):QMainWindow(parent),ui(new Ui::LibraryManager)
  ,manager(other.manager)
{
    ui->setupUi(this);
}

LibraryManager::LibraryManager(const LibraryManager &&other)
    :
      manager(other.manager)
{
other.~LibraryManager();
}

LibraryManager::~LibraryManager()
{
    delete ui;
}

void LibraryManager::operator=(LibraryManager &lm)
{
    this->manager = lm.manager;
    this->ui= lm.ui;
}

const Admin &LibraryManager::getManager() const
{
    return *manager;
}

void LibraryManager::setManager( Admin* &newManager,QString pass )
{
    this->manager = newManager;
    manager->setUserName("manager");
    manager->setPassword(pass);
}

 void LibraryManager::writeInManagerFile(QString name, QString adminId ,long long mobNumber, QString pass)
{

     Admin *ad = new Admin(name,adminId,mobNumber);
     this->setManager(ad,pass) ;
     QFile fi("manager.txt");
     fi.open(QFile::WriteOnly| QFile::Text);
     QTextStream out(&fi) ;
     out << this->manager->getUserName() << "\n" << this->manager->getPassword() << "\n" <<this->manager->getName() <<"\n"<<this->manager->getAdminId() <<"\n" << this->manager->getMobilePhone()<<"\n";
     fi.flush();
     fi.close();
     delete ad;
 }

 void LibraryManager::closeEvent(QCloseEvent *event)
 {
     QMessageBox::StandardButtons btn =QMessageBox::question(this,"خروج","آیا میخواهید برنامه را ببندید؟؟؟",QMessageBox::Yes | QMessageBox::No);
     if(QMessageBox::Yes == btn){
         event->accept();
     }
     else{
         event->ignore();
     }
 }


void LibraryManager::readInManagerFile()
{
    int counter =1 ;
    QFile f("manager.txt");
    f.open(QFile::ReadOnly | QFile::Text);
        QTextStream in(&f);
        while(!in.atEnd()){
            if(counter ==1){
                this->manager->setUserName(in.readLine());
                counter++;
            }
            else if(counter ==2){
                this->manager->setPassword(in.readLine());
                counter++;
            }
            else if(counter ==3){
                this->manager->setName(in.readLine());
                counter++;
            }
            else if(counter ==4){
                this->manager->setAdminId(in.readLine());
                counter++;
            }
            else if(counter ==5){
                this->manager->setMobilePhone(in.readLine().toLongLong());
            }
        }


    f.close();

}

void LibraryManager::on_addAdmin_clicked()
{
    AddAdmin*  newAdmin = new AddAdmin(this);
    newAdmin->exec();

}


void LibraryManager::on_deleteAdmin_clicked()
{
     DeleteAdmin *del = new DeleteAdmin(this);
    del->exec();

}


void LibraryManager::on_showAllAdmin_clicked()
{

    ShowAllAdmin* sh=new ShowAllAdmin(this);

    sh->showAdmin();
sh->show();
}


void LibraryManager::on_searchAdmin_clicked()
{
    SearchAdmin * sA = new SearchAdmin();
    sA->exec();
}


void LibraryManager::on_addMember_clicked()
{
    AddMember* aM = new AddMember();
    aM->show();
}


void LibraryManager::on_deleteMember_clicked()
{
    DeleteMember* dm = new DeleteMember();
    dm->exec();
}


void LibraryManager::on_showAllMember_clicked()
{
    ShowAllMember* sh=new ShowAllMember(this);

    sh->showMember();
sh->show();
}


void LibraryManager::on_addBook_clicked()
{
    AddBook* ab = new AddBook(this);
    ab->exec();
}


void LibraryManager::on_deleteBook_clicked()
{
    DeleteBook * db = new DeleteBook(this);
    db->exec();
}


void LibraryManager::on_showAllBook_clicked()
{
    ShowAllBooks * sab = new ShowAllBooks(this);
    sab->showBooks();
    sab->show();
}


void LibraryManager::on_searchBook_clicked()
{
    SearchBook* sb = new SearchBook(this);
    sb->exec();
}


void LibraryManager::on_borrowingBook_clicked()
{
    LendingBook* lb = new LendingBook(this);
    lb->exec();
}


void LibraryManager::on_printAdminCard_clicked()
{
PrintAdminCard* pad = new PrintAdminCard(this);
pad->exec();
}


void LibraryManager::on_printLibraryCard_clicked()
{
    PrintMemberCard* pmc = new PrintMemberCard(this);
    pmc->exec();
}


void LibraryManager::on_searchMember_clicked()
{
    SearchMember* sm = new SearchMember(this);
    sm->exec();
}




void LibraryManager::on_action_3_triggered()
{
    this->hide();
    Login * l =new Login();
    l->exec();
}




void LibraryManager::on_changePassword_clicked()
{
    ChangePassword * cp = new ChangePassword(this->getManager().getUserName());
    cp->exec();
}

