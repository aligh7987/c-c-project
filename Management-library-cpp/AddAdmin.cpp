#include "AddAdmin.h"
#include "ui_AddAdmin.h"
#include "Admin.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
AddAdmin::AddAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAdmin)
{
    ui->setupUi(this);
}

AddAdmin::~AddAdmin()
{
    delete ui;
}

void AddAdmin::on_back_clicked()
{
    this->hide();
}


void AddAdmin::on_submit_clicked()
{
    QString name = ui->name->text();
    QString adminId = ui->adminId->text();
    QString mobilePhone = ui->numberPhone->text();
    if(name.isEmpty() || adminId.isEmpty() || mobilePhone.isEmpty()){
        QMessageBox::critical(this,"فیلد خالی","یکی از فیلد ها خالی است!");
    }
    else{
        int counter=1;
        unique_ptr<Admin> adm(new Admin());
        int duplicateId=0;
        QFile fread("admins.txt");
        if(fread.open(QFile::ReadOnly | QFile::Text)){
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
                  if(adm->getAdminId() == adminId){
                  QMessageBox::critical(this,"آیدی تکراری","آیدی وارد شده از قبل وجود دارد!");
                  duplicateId =1;
                  break;
                  }
                    counter++;
                }
                else if(counter ==5){
                  adm->setMobilePhone(in.readLine().toLongLong());
                    counter=1;
                }
        }

        }
                fread.close();
              if(!duplicateId){
                    adm->writeInAdminsFile(name,adminId,mobilePhone.toLongLong());
                    if(QMessageBox::Ok ==QMessageBox::information(this,"عملیات موفق","ادمین جدید با موفقیت ثبت شد") || QMessageBox::Close == QMessageBox::information(this,"عملیات موفق","ادمین جدید با موفقیت ثبت شد")){
                        this->hide();
                    }
              }
    }
}

