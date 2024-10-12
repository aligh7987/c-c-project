#include "ChangePassword.h"
#include "ui_ChangePassword.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "User.h"
#include "Admin.h"
#include "LibraryManager.h"
#include "Member.h"
ChangePassword::ChangePassword(QString userName,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePassword)
{
    ui->setupUi(this);
    this->username = userName;

}

ChangePassword::~ChangePassword()
{
    delete ui;
}

void ChangePassword::on_back_clicked()
{
    this->hide();
}


void ChangePassword::on_submit_clicked()
{
    QString newPass = ui->newPass->text();
    QString reNewPass = ui->repeatNewPass->text();
    shared_ptr<LibraryManager> lm(new LibraryManager());
    shared_ptr<Admin> a(new Admin());
    shared_ptr<Member> m (new Member());
    shared_ptr<User> user;
    int flagAdmin=0 , flagMember=0 , flagManager=0;
    if( newPass.isEmpty() || reNewPass.isEmpty()){
         QMessageBox::critical(this,"ورودی نامعتبر","یکی از فیلدها وارد نشده است!!!!");
    }
    else if(newPass != reNewPass){
           QMessageBox::critical(this,"ورودی نامعتبر","رمز جدید با تکرارش تطابق ندارد!!!");
    }
    else{
        lm->readInManagerFile();
        if(lm->getManager().getUserName() == this->username){
            if(lm->getManager().getPassword() != newPass){
                lm->writeInManagerFile(lm->getManager().getName(),lm->getManager().getAdminId(),lm->getManager().getMobilePhone(),newPass);
                flagManager=1;
            }else{
                QMessageBox::critical(this,"ورودی نامعتبر","رمز جدید با رمز قبلی یکی است!!!");
            }
         }
        else{
            int counter=1 ;
            QFile f("admins.txt");
            f.open(QFile::ReadOnly|QFile::Text);
            QTextStream in(&f);
            while(!in.atEnd() ){
                if(counter ==1){
                   a->setUserName(in.readLine());

                    counter++;
                }
                else if(counter ==2){
                   a->setPassword(in.readLine());
                    counter++;
                }
                else if(counter ==3){
                  a->setName(in.readLine());
                    counter++;
                }
                else if(counter ==4){
                  a->setAdminId(in.readLine());
                    counter++;
                }
                else if(counter ==5){
                  a->setMobilePhone(in.readLine().toLongLong());
                  if(a->getUserName() == this->username){
                      if(a->getPassword()!=newPass){
                          flagAdmin=1;
                           break;
                      }else{
                          QMessageBox::critical(this,"ورودی نامعتبر","رمز جدید با رمز قبلی یکی است!!!");
                      }

                  }
                    counter=1;
                }
            }
            f.close();
            if(flagAdmin){
                user=a;
                user->changePassword(this->username,newPass);
            }
            else {
                    int counter2=1 ;
                    QFile f2("members.txt");
                    f2.open(QFile::ReadOnly|QFile::Text);
                    QTextStream in(&f2);
                    while(!in.atEnd() ){
                        if(counter2 ==1){
                           m->setUserName(in.readLine());
                            counter2 ++;
                        }
                        else if(counter2 ==2){
                           m->setPassword(in.readLine());
                            counter2 ++;
                        }
                        else if(counter2 ==3){
                          m->setName(in.readLine());
                            counter2 ++;
                        }
                        else if(counter2 ==4){
                          m->setMembershipNumber(in.readLine());
                            counter2 ++;
                        }
                        else if(counter2 ==5){
                          m->setFatherName(in.readLine());
                          counter2 ++;
                           }
                        else if(counter2 ==6){
                          m->setNationalityCode(in.readLine());
                            counter2 ++;
                        }
                        else if(counter2 ==7){
                          m->setBirthday(in.readLine());
                        counter2 ++;
                        }

                        else if(counter2 ==8){
                          m->setMobilePhone(in.readLine().toLongLong());
                          counter2 ++;
                           }
                        else if(counter2 ==9){
                            m->setEmail(in.readLine());

                            counter2 ++;
                        }
                        else if(counter2==10){
                            m->setBorrowingDate(in.readLine());
                            counter2 ++;
                        }
                        else if(counter2==11){
                            m->setReturnDate(in.readLine());
                            if(m->getUserName() == this->username){
                                if(m->getPassword() != newPass){
                                    flagMember=1;
                                    break;
                                }else{
                                    QMessageBox::critical(this,"ورودی نامعتبر","رمز جدید با رمز قبلی یکی است!!!");

                                }
                            }
                            counter2 =1;
                        }
                    }
                    f2.close();
                 if(flagMember){
                     user= m;
                     user->changePassword(this->username,newPass);
                 }
             }
        }
    }
    if(flagAdmin || flagMember || flagManager){
        if(QMessageBox::information(this,"عملیات موفق","رمز شما با موفقیت تغییر کرد") == QMessageBox::Ok || QMessageBox::information(this,"عملیات موفق","رمز شما با موفقیت تغییر کرد") == QMessageBox::Close){
            this->hide();
        }
    }

}

