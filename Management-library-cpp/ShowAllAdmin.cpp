#include "ShowAllAdmin.h"
#include "ui_ShowAllAdmin.h"
#include "Admin.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "LibraryManager.h"
#include "EditAdmin.h"
ShowAllAdmin::ShowAllAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowAllAdmin)
{
    ui->setupUi(this);
}
ShowAllAdmin::~ShowAllAdmin()
{
    delete ui;
}

void ShowAllAdmin::showAdmin()
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
             ui->tableAdmins->insertRow(ui->tableAdmins->rowCount());
             ui->tableAdmins->setItem(ui->tableAdmins->rowCount()-1,0,new QTableWidgetItem(adm->getAdminId()));
             ui->tableAdmins->setItem(ui->tableAdmins->rowCount()-1,1,new QTableWidgetItem(adm->getName()));
             ui->tableAdmins->setItem(ui->tableAdmins->rowCount()-1,2,new QTableWidgetItem(QString::number(adm->getMobilePhone())));
               counter=1;
           }
       }
   }

}
void ShowAllAdmin::on_back_clicked()
{
    this->hide();
}


void ShowAllAdmin::on_delete_2_clicked()
{
    QList<QTableWidgetItem*> list=ui->tableAdmins->selectedItems();
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
                   ui->tableAdmins->clearContents();
                   ui->tableAdmins->setRowCount(0);
                   this->showAdmin();
               }
        }

    }
    else{
        QMessageBox::critical(this,"عملیات نامعتبر","لطفا سطر مورد نظر برای حذف را انتخاب کنید");
    }

}


void ShowAllAdmin::on_edit_clicked()
{
    QList<QTableWidgetItem*> list=ui->tableAdmins->selectedItems();
    if(!list.isEmpty()){
        QString id = list[0]->text();
        QString name = list[1]->text();
        QString mobile = list[2]->text();
        EditAdmin* e = new EditAdmin(id,name,mobile,this);
        e->exec();
        ui->tableAdmins->clearContents();
        ui->tableAdmins->setRowCount(0);
        this->showAdmin();
    }
    else{
          QMessageBox::critical(this,"عملیات نامعتبر","لطفا سطر مورد نظر برای ویرایش را انتخاب کنید");
    }
}

