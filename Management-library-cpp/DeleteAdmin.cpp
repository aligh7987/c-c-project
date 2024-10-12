#include "DeleteAdmin.h"
#include "ui_DeleteAdmin.h"
#include <QMessageBox>
#include "Admin.h"
#include <QFile>
#include <QTextStream>

DeleteAdmin::DeleteAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteAdmin)
{
    ui->setupUi(this);
}


DeleteAdmin::~DeleteAdmin()
{
    delete ui;
}

void DeleteAdmin::on_back_clicked()
{
    this->hide();
}


void DeleteAdmin::on_delete_2_clicked()
{
    QString id = ui->lineEdit->text();
    unique_ptr<Admin> rA(new Admin());

    int counter=1 , idFlag=0 ;
    if(id.isEmpty()){
        QMessageBox::critical(this,"فیلد خالی","آیدی وارد نشده است");
    }
    else{

        QFile f1("admins.txt");
        QFile f2("adminsTmp.txt");
        f1.open(QFile::ReadOnly|QFile::Text);
        QTextStream in(&f1);
        f2.open(QFile::WriteOnly|QFile::Text);
        QTextStream out(&f2);
        while(!in.atEnd() ){
            if(counter ==1){
               rA->setUserName(in.readLine());
                counter++;
            }
            else if(counter ==2){
               rA->setPassword(in.readLine());
                counter++;
            }
            else if(counter ==3){
              rA->setName(in.readLine());
                counter++;
            }
            else if(counter ==4){
              rA->setAdminId(in.readLine());
                counter++;
            }
            else if(counter ==5){
              rA->setMobilePhone(in.readLine().toLongLong());
                if(rA->getAdminId() != id){
                    out<<rA->getUserName() <<"\n" << rA->getPassword() <<"\n"<<rA->getName() <<"\n" << rA->getAdminId() <<"\n" <<rA->getMobilePhone() <<"\n";
                }
                else{
                    idFlag=1;
                }
                counter=1;
            }
        }
        f1.close();
        f2.close();
    if(idFlag){
           QFile fR("adminsTmp.txt");
           QFile fW("admins.txt");
           fR.open(QFile::ReadOnly|QFile::Text);
           QTextStream in(&fR);
           fW.open(QFile::WriteOnly|QFile::Text);
           QTextStream out(&fW);
           while(!in.atEnd() ){
               if(counter ==1){
                  rA->setUserName(in.readLine());
                   counter++;
               }
               else if(counter ==2){
                  rA->setPassword(in.readLine());
                   counter++;
               }
               else if(counter ==3){
                 rA->setName(in.readLine());
                   counter++;
               }
               else if(counter ==4){
                 rA->setAdminId(in.readLine());
                   counter++;
               }
               else if(counter ==5){
                 rA->setMobilePhone(in.readLine().toLongLong());
                  out<<rA->getUserName() <<"\n" << rA->getPassword() <<"\n"<<rA->getName() <<"\n" << rA->getAdminId() <<"\n" <<rA->getMobilePhone() <<"\n";
                   counter=1;
               }
           }
           fW.close();
           fR.close();
           if(QMessageBox::Ok ==QMessageBox::information(this,"عملیات موفق","ادمین مورد نظر با موفقیت حذف شد ")){
               this->hide();
           }

    }
    else{
        QMessageBox::critical(this,"آیدی نامعتبر","ادمینی با این آیدی وجود ندارد");
    }

    }

}

