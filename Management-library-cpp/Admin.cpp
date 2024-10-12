#include "Admin.h"
#include "ui_Admin.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QCloseEvent>
#include "ChangePassword.h"
#include "AddMember.h"
#include "AddBook.h"
#include "DeleteBook.h"
#include "ShowAllBooks.h"
#include "SearchBook.h"
#include "LendingBook.h"
#include "ShowAllMember.h"
#include "DeleteMember.h"
#include "PrintMemberCard.h"
#include "SearchMember.h"
#include "About.h"
#include "Login.h"
using namespace std;
Admin::Admin(QString name,QString adminId,long long mobilePhone,QWidget *parent ) :
    QMainWindow(parent),ui(new Ui::Admin)
{
    ui->setupUi(this);
    this->setUserName(this->adminId);
    this->setPassword(QString::number(mobilePhone));
    this->adminId = adminId ;
    this->name = name ;
    this->mobilePhone = mobilePhone;
}

Admin::Admin(const Admin& other,QWidget* parent):QMainWindow(parent){
    this->adminId = other.adminId ;
    this->name = other.name ;
    this->mobilePhone = other.mobilePhone;
    this->setUserName(other.getUserName());
    this->setPassword(other.getPassword());

}

Admin::Admin(const Admin &&other)
{
    this->adminId = other.adminId ;
    this->name = other.name ;
    this->mobilePhone = other.mobilePhone;
    this->setUserName(other.getUserName());
    this->setPassword(other.getPassword());
    other.~Admin();
}
void Admin::operator=(const Admin &other)
{
    this->adminId = other.adminId ;
    this->name = other.name ;
    this->mobilePhone = other.mobilePhone;
    this->setUserName(other.getUserName());
    this->setPassword(other.getPassword());

}

Admin::~Admin()
{
    delete ui;
}

const QString &Admin::getName() const
{
    return name;
}

void Admin::setName(const QString &newName)
{
    name = newName;
}

long long Admin::getMobilePhone() const
{
    return mobilePhone;
}

void Admin::setMobilePhone(long long newMobilePhone)
{
    mobilePhone = newMobilePhone;
}

QString Admin::getAdminId() const
{
    return adminId;
}

void Admin::setAdminId(QString newAdminId)
{
    adminId = newAdminId;
}

void Admin::writeInAdminsFile(QString name, QString adminId, long long mobNumber)
{
    this->setUserName(adminId);
    this->setPassword(QString::number(mobNumber));
    this->name = name;
    this->adminId = adminId;
    this->mobilePhone = mobNumber;
    QFile fi("admins.txt");
    fi.open(QFile::WriteOnly| QFile::Append);
    QTextStream out(&fi);
    out<<this->getUserName() <<"\n" << this->getPassword() <<"\n"<<this->name <<"\n" <<this->adminId <<"\n" <<this->mobilePhone <<"\n";
    fi.flush();
    fi.close();
}

void Admin::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButtons btn =QMessageBox::question(this,"خروج","آیا میخواهید برنامه را ببندید؟؟؟",QMessageBox::Yes | QMessageBox::No);
    if(QMessageBox::Yes == btn){
        event->accept();
    }
    else{
        event->ignore();
    }
}


void Admin::changePassword(QString userName, QString newPass)
{
    int counter=1 ;
        QFile f1("admins.txt");
        QFile f2("adminsTmp.txt");
        f1.open(QFile::ReadOnly|QFile::Text);
        QTextStream in(&f1);
        f2.open(QFile::WriteOnly|QFile::Text);
        QTextStream out(&f2);
        while(!in.atEnd() ){
            if(counter ==1){
               this->setUserName(in.readLine());
                counter++;
            }
            else if(counter ==2){
               this->setPassword(in.readLine());
                counter++;
            }
            else if(counter ==3){
              this->setName(in.readLine());
                counter++;
            }
            else if(counter ==4){
              this->setAdminId(in.readLine());
                counter++;
            }
            else if(counter ==5){
              this->setMobilePhone(in.readLine().toLongLong());
                if(this->getUserName() ==userName){
                    this->setPassword(newPass);
                    out<<this->getUserName() <<"\n" << this->getPassword() <<"\n"<<this->getName() <<"\n" << this->getAdminId() <<"\n" <<this->getMobilePhone() <<"\n";
                }
                else{
                    out<<this->getUserName() <<"\n" << this->getPassword() <<"\n"<<this->getName() <<"\n" << this->getAdminId() <<"\n" <<this->getMobilePhone() <<"\n";
                }
                counter=1;
            }
        }
        f1.close();
        f2.close();
           QFile fR("adminsTmp.txt");
           QFile fW("admins.txt");
           fR.open(QFile::ReadOnly|QFile::Text);
           QTextStream inp(&fR);
           fW.open(QFile::WriteOnly|QFile::Text);
           QTextStream outText(&fW);
           while(!inp.atEnd() ){
               if(counter ==1){
                  this->setUserName(inp.readLine());
                   counter++;
               }
               else if(counter ==2){
                  this->setPassword(inp.readLine());
                   counter++;
               }
               else if(counter ==3){
                 this->setName(inp.readLine());
                   counter++;
               }
               else if(counter ==4){
                 this->setAdminId(inp.readLine());
                   counter++;
               }
               else if(counter ==5){
                 this->setMobilePhone(inp.readLine().toLongLong());
                  outText<<this->getUserName() <<"\n" << this->getPassword() <<"\n"<<this->getName() <<"\n" << this->getAdminId() <<"\n" <<this->getMobilePhone() <<"\n";
                   counter=1;
               }
           }
           fW.close();
           fR.close();
}

void Admin::on_changePassword_clicked()
{
ChangePassword* ch = new ChangePassword(this->getUserName());
ch->exec();
}


void Admin::on_addMember_clicked()
{
    AddMember* aM = new AddMember();
    aM->exec();
}


void Admin::on_addBook_clicked()
{
AddBook * ab = new AddBook();
ab->exec();
}


void Admin::on_deleteBook_clicked()
{
    DeleteBook * db =new DeleteBook(this);
    db->exec();
}


void Admin::on_showAllBooks_clicked()
{
    ShowAllBooks* sab = new ShowAllBooks(this);
sab->showBooks();
    sab->show();

}


void Admin::on_searchBook_clicked()
{
    SearchBook *sb = new SearchBook(this);
    sb->exec();
}


void Admin::on_borrowingBook_clicked()
{
    LendingBook* lb= new LendingBook();
    lb->exec();
}


void Admin::on_showAllMembers_clicked()
{
    ShowAllMember* sh=new ShowAllMember(this);

    sh->showMember();
sh->show();
}


void Admin::on_deleteMember_clicked()
{
    DeleteMember* dm = new DeleteMember();
    dm->exec();
}


void Admin::on_printLibraryCard_clicked()
{
    PrintMemberCard* pmc = new PrintMemberCard(this);
    pmc->exec();
}


void Admin::on_searchMember_clicked()
{
    SearchMember* sm = new SearchMember(this);
    sm->exec();
}


void Admin::on_action_triggered()
{
    About* a = new About();
    a->exec();
}


void Admin::on_action_3_triggered()
{
    this->hide();
    Login * l =new Login();
    l->exec();
}




