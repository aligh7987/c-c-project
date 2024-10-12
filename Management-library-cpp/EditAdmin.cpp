#include "EditAdmin.h"
#include "ui_EditAdmin.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "Admin.h"
EditAdmin::EditAdmin(QString id,QString name,QString mobilePhone,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditAdmin)
{
    this->id = id;
    ui->setupUi(this);
    ui->name->setText(name);
    ui->mobile->setText(mobilePhone);
}

EditAdmin::~EditAdmin()
{
    delete ui;
}

void EditAdmin::on_back_clicked()
{
    this->hide();
}


void EditAdmin::on_submit_clicked()
{
    QString name = ui->name->text();
    QString mobilePhone = ui->mobile->text();
    if(name.isEmpty() ||  mobilePhone.isEmpty()){
          QMessageBox::critical(this,"فیلد خالی","یکی از فیلد ها خالی است!");
    }
    else{
        unique_ptr<Admin> rA(new Admin());
        int counter=1 ;
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
                    if(rA->getAdminId() ==this->id){
                        rA->setName(name);
                        rA->setMobilePhone(mobilePhone.toLongLong());
                        out<<rA->getUserName() <<"\n" << rA->getPassword() <<"\n"<<rA->getName() <<"\n" << rA->getAdminId() <<"\n" <<rA->getMobilePhone() <<"\n";
                    }
                    else{
                        out<<rA->getUserName() <<"\n" << rA->getPassword() <<"\n"<<rA->getName() <<"\n" << rA->getAdminId() <<"\n" <<rA->getMobilePhone() <<"\n";
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
                      rA->setUserName(inp.readLine());
                       counter++;
                   }
                   else if(counter ==2){
                      rA->setPassword(inp.readLine());
                       counter++;
                   }
                   else if(counter ==3){
                     rA->setName(inp.readLine());
                       counter++;
                   }
                   else if(counter ==4){
                     rA->setAdminId(inp.readLine());
                       counter++;
                   }
                   else if(counter ==5){
                     rA->setMobilePhone(inp.readLine().toLongLong());
                      outText<<rA->getUserName() <<"\n" << rA->getPassword() <<"\n"<<rA->getName() <<"\n" << rA->getAdminId() <<"\n" <<rA->getMobilePhone() <<"\n";
                       counter=1;
                   }
               }
               fW.close();
               fR.close();
               if(QMessageBox::Ok ==QMessageBox::information(this,"عملیات موفق","ادمین مورد نظر با موفقیت ویرایش شد ")){
                   this->hide();
               }
        }

}

