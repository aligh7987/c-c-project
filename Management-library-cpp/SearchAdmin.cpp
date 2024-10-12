#include "SearchAdmin.h"
#include "ui_SearchAdmin.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "Admin.h"
#include "EditAdmin.h"
#include "ShowAllAdmin.h"
SearchAdmin::SearchAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchAdmin)
{
    ui->setupUi(this);
}

void SearchAdmin::showAdmin()
{
    unique_ptr<Admin> adm(new Admin());
        int counter=1;
       QFile f("admins.txt");
       if(f.open(QFile::ReadOnly | QFile::Text)){
           QTextStream in(&f);
           while(!in.atEnd() ){
               if(counter ==1){
                  adm->setUserName(in.readLine());
                   counter++;
               }
               else if(counter ==2){
                  adm->setPassword(in.readLine());
                   counter++;
               }
               else if(counter ==3){
                 adm->setName(in.readLine());
                   counter++;
               }
               else if(counter ==4){
                 adm->setAdminId(in.readLine());
                   counter++;
               }
               else if(counter ==5){
                 adm->setMobilePhone(in.readLine().toLongLong());
                 ui->tableAdmin->insertRow(ui->tableAdmin->rowCount());
                 ui->tableAdmin->setItem(ui->tableAdmin->rowCount()-1,0,new QTableWidgetItem(adm->getAdminId()));
                 ui->tableAdmin->setItem(ui->tableAdmin->rowCount()-1,1,new QTableWidgetItem(adm->getName()));
                 ui->tableAdmin->setItem(ui->tableAdmin->rowCount()-1,2,new QTableWidgetItem(QString::number(adm->getMobilePhone())));
                   counter=1;
               }
           }
       }

}

SearchAdmin::~SearchAdmin()
{
    delete ui;
}

void SearchAdmin::on_search_clicked()
{
    ui->tableAdmin->clearContents();
    ui->tableAdmin->setRowCount(0);
    QString serachName  = ui->nameForSearch->text();
    if(!serachName.isEmpty()){
        int counter=1 , flag=0;

        unique_ptr<Admin> adm(new Admin());
        QFile fread("admins.txt");
       fread.open(QFile::ReadOnly | QFile::Text);
            QTextStream in(&fread);
            while(!in.atEnd() ){
                if(counter ==1){
                   adm->setUserName(in.readLine());
                    counter++;
                }
                else if(counter ==2){
                   adm->setPassword(in.readLine());
                    counter++;
                }
                else if(counter ==3){
                  adm->setName(in.readLine());
                    counter++;
                }
                else if(counter ==4){
                  adm->setAdminId(in.readLine());
                    counter++;
                }
                else if(counter ==5){
                  adm->setMobilePhone(in.readLine().toLongLong());
                  if(adm->getName() == serachName){
                      ui->tableAdmin->insertRow(ui->tableAdmin->rowCount());
                      ui->tableAdmin->setItem(ui->tableAdmin->rowCount()-1,0,new QTableWidgetItem(adm->getAdminId()));
                      ui->tableAdmin->setItem(ui->tableAdmin->rowCount()-1,1,new QTableWidgetItem(adm->getName()));
                      ui->tableAdmin->setItem(ui->tableAdmin->rowCount()-1,2,new QTableWidgetItem(QString::number(adm->getMobilePhone())));
                      flag=1;
                  }
                    counter=1;
                }
        }
               fread.close();
                if(flag==0){
                     QMessageBox::critical(this,"فرد نامعتبر","فردی با این نام وجود ندارد");
                }

    }
    else{
        QMessageBox::critical(this,"فیلد خالی","لطفا نام ونام خانوادگی کامل را وارد کنید");
    }
}


void SearchAdmin::on_back_clicked()
{
    this->hide();
}


void SearchAdmin::on_edit_clicked()
{
    QList<QTableWidgetItem*> list=ui->tableAdmin->selectedItems();
    if(!list.isEmpty()){
        QString id = list[0]->text();
        QString name = list[1]->text();
        QString mobile = list[2]->text();
        EditAdmin* e = new EditAdmin(id,name,mobile,this);
        e->exec();
        ui->tableAdmin->clearContents();
        ui->tableAdmin->setRowCount(0);
        this->showAdmin();
        ui->nameForSearch->setText("");
    }
    else{
          QMessageBox::critical(this,"عملیات نامعتبر","لطفا سطر مورد نظر برای ویرایش را انتخاب کنید");
    }
}


void SearchAdmin::on_delete_2_clicked()
{
    QList<QTableWidgetItem*> list=ui->tableAdmin->selectedItems();
    if(!list.isEmpty()){
        QString id = list[0]->text();
        QString name = list[1]->text();
        QString mobile = list[2]->text();
        unique_ptr<Admin> rA(new Admin());

        int counter=1 ,idFlag=0;

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
                   ui->tableAdmin->clearContents();
                   ui->tableAdmin->setRowCount(0);
                   ui->nameForSearch->setText("");
               }
        }

    }
    else{
        QMessageBox::critical(this,"عملیات نامعتبر","لطفا سطر مورد نظر برای حذف را انتخاب کنید");
    }
}

