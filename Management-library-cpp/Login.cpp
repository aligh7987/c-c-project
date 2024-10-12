#include <QMessageBox>
#include <iostream>
#include <QFile>
#include <QTextStream>
using namespace std;
#include "Login.h"
#include <memory>
#include "ui_Login.h"
#include "Admin.h"

#include "LibraryManager.h"
#include "ForgetPassword.h"
#include "Member.h"
Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

}

Login::~Login()
{
    delete ui;
}


void Login::on_login_clicked()
{
    QString checkUserName = ui->username->text();
    QString checkPassword = ui->password->text();
    LibraryManager * mgr = new LibraryManager("","",0,this);
    Admin * adm = new Admin();
    Member * mmbr = new Member();
    int flagAdmin=0,flagMember=0 ;
    if(checkUserName.isEmpty() || checkPassword.isEmpty()){
        QMessageBox::critical(this,"ورودی نامعتبر","نام کاربری یا رمز عبور وارد نشده است!!!");
    }
    else{
        mgr->readInManagerFile();
        if(mgr->getManager().getUserName() == checkUserName && mgr->getManager().getPassword() == checkPassword){

            this->hide();
            mgr->show();

        }
        else{
          int counter=1;
          QFile f("admins.txt");
          f.open(QFile::ReadOnly | QFile::Text);
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
                     if(adm->getPassword() == checkPassword && adm->getUserName() == checkUserName){
                         flagAdmin =1;
                         this->hide();
                         adm->show();

                         break;
                     }
                      counter=1;
                  }
              }
              if(flagAdmin==0){
                counter =1;
                QFile f2("members.txt");
                f2.open(QFile::ReadOnly | QFile::Text);
                    QTextStream in(&f2);
                    while(!in.atEnd() ){
                        if(counter ==1){
                           mmbr->setUserName(in.readLine());
                            counter++;
                        }
                        else if(counter ==2){
                           mmbr->setPassword(in.readLine());
                            counter++;
                        }
                        else if(counter ==3){
                          mmbr->setName(in.readLine());
                            counter++;
                        }
                        else if(counter ==4){
                          mmbr->setMembershipNumber(in.readLine());
                            counter++;
                        }
                        else if(counter ==5){
                          mmbr->setFatherName(in.readLine());
                          counter++;
                           }
                        else if(counter ==6){
                          mmbr->setNationalityCode(in.readLine());
                            counter++;
                        }
                        else if(counter ==7){
                          mmbr->setBirthday(in.readLine());
                        counter++;
                        }

                        else if(counter ==8){
                          mmbr->setMobilePhone(in.readLine().toLongLong());
                          counter++;
                           }
                        else if(counter ==9){
                            mmbr->setEmail(in.readLine());
                            counter++;
                        }
                        else if(counter ==10){
                            mmbr->setBorrowingDate(in.readLine());
                            counter++;
                        }
                        else if( counter ==11){
                            mmbr->setReturnDate(in.readLine());
                            if(mmbr->getUserName()==checkUserName && mmbr->getPassword() == checkPassword){
                                this->hide();
                                flagMember =1;
                                mmbr->show();
                                break;
                            }
                            counter=1;
                        }
                        }
                    if(flagMember==0){
                        QMessageBox::critical(this,"ورودی نامعتبر","نام کاربری یا رمز عبور اشتباه است!!!");
                    }
                    }

              }
          }

}




void Login::on_forgotPas_clicked()
{
    ForgetPassword* fp = new ForgetPassword(this);
    fp->exec();
}
void Login::reject(){
    if(QMessageBox::Yes == QMessageBox::question(this,"خروج","آیا میخواهید برنامه را ببندید؟؟؟",QMessageBox::Yes | QMessageBox::No)){
        this->close();
    }
}
