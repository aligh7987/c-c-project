#include "ForgetPassword.h"
#include "ui_ForgetPassword.h"
#include "Login.h"
#include <QMessageBox>
#include <vector>
#include "Member.h"
#include "LibraryManager.h"
#include <QFile>
#include <QTextStream>
#include <deque>
using namespace std;
ForgetPassword::ForgetPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ForgetPassword)
{
    ui->setupUi(this);
}

ForgetPassword::~ForgetPassword()
{
    delete ui;
}

void ForgetPassword::on_back_clicked()
{
    this->hide();
    Login *l = new Login() ;
    l->exec();
}
void ForgetPassword::reject(){
    this->close();
    Login *l = new Login() ;
    l->exec();

}
void ForgetPassword::on_submit_clicked()
{
QString userName = ui->username->text();
QString newPassword = ui->newpassword->text();
QString repeatPassword = ui->repeatpassword->text();
int  flagAdmin =0 , flagMember=0;

unique_ptr<LibraryManager> rM(new LibraryManager());
unique_ptr<Admin> rA(new Admin());
unique_ptr<Member> mmbr(new Member());
if(userName.isEmpty() || newPassword.isEmpty() || repeatPassword.isEmpty()){
    QMessageBox::critical(this,"ورودی نامعتبر","یکی از فیلدها وارد نشده است!!!!");
    }
else if(newPassword != repeatPassword){
       QMessageBox::critical(this,"ورودی نامعتبر","رمز جدید با تکرارش تطابق ندارد!!!");
}
else{
    rM->readInManagerFile();
    if(rM->getManager().getUserName() == userName){
        if(rM->getManager().getPassword() != newPassword){
            rM->writeInManagerFile(rM->getManager().getName(),rM->getManager().getAdminId(),rM->getManager().getMobilePhone(),newPassword);

            QMessageBox::information(this,"عملیات موفق","رمز شما با موفقیت تغییر یافت");

        }else{
           QMessageBox::critical(this,"ورودی نامعتبر","رمز جدید با رمز قبلی یکی است!!!");
        }
        }
    else{
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
            if(rA->getUserName() ==userName){
                if(rA->getPassword() != newPassword){
                    rA->setPassword(newPassword);
                     flagAdmin=1;
                    out<<rA->getUserName() <<"\n" << rA->getPassword() <<"\n"<<rA->getName() <<"\n" << rA->getAdminId() <<"\n" <<rA->getMobilePhone() <<"\n";

                }else{
                    QMessageBox::critical(this,"ورودی نامعتبر","رمز جدید با رمز قبلی یکی است!!!");
                }
                   }
            else{
                out<<rA->getUserName() <<"\n" << rA->getPassword() <<"\n"<<rA->getName() <<"\n" << rA->getAdminId() <<"\n" <<rA->getMobilePhone() <<"\n";
            }
            counter=1;
        }
    }
    f1.close();
    f2.close();
      if(flagAdmin){
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
           QMessageBox::information(this,"عملیات موفق","رمز شما با موفقیت تغییر یافت");
    }
           else{
        int counter=1 ;
    QFile f1("members.txt");
    QFile f2("membersTmp.txt");
    f1.open(QFile::ReadOnly|QFile::Text);
    QTextStream in(&f1);
    f2.open(QFile::WriteOnly|QFile::Text);
    QTextStream out(&f2);
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
        else if(counter==10){
            mmbr->setBorrowingDate(in.readLine());
            counter++;
        }
        else if(counter==11){
            mmbr->setReturnDate(in.readLine());
            if(mmbr->getUserName() == userName){
                if(mmbr->getPassword()!=newPassword){
                    mmbr->setPassword(newPassword);
                    out<<mmbr->getUserName() <<"\n" << mmbr->getPassword() <<"\n"<<mmbr->getName() <<"\n" <<mmbr->getMembershipNumber() <<"\n" <<mmbr->getFatherName() <<"\n"<<mmbr->getNationalityCode() <<"\n"<<mmbr->getBirthday() <<"\n" <<mmbr->getMobilePhone() <<"\n"<<mmbr->getEmail()<<"\n"<<mmbr->getBorrowingDate()<<"\n"<<mmbr->getReturnDate()<<"\n";;
                     flagMember=1;
                }else{
                    QMessageBox::critical(this,"ورودی نامعتبر","رمز جدید با رمز قبلی یکی است!!!");
                }
             }
            else{
                out<<mmbr->getUserName() <<"\n" << mmbr->getPassword() <<"\n"<<mmbr->getName() <<"\n" <<mmbr->getMembershipNumber() <<"\n" <<mmbr->getFatherName() <<"\n"<<mmbr->getNationalityCode() <<"\n"<<mmbr->getBirthday() <<"\n" <<mmbr->getMobilePhone() <<"\n"<<mmbr->getEmail()<<"\n"<<mmbr->getBorrowingDate()<<"\n"<<mmbr->getReturnDate()<<"\n";;
            }
            counter=1;
        }
        }
    f1.close();
    f2.close();
           if(flagMember){
           QFile fR("membersTmp.txt");
           QFile fW("members.txt");
           fR.open(QFile::ReadOnly|QFile::Text);
           QTextStream inp(&fR);
           fW.open(QFile::WriteOnly|QFile::Text);
           QTextStream outText(&fW);
           while(!inp.atEnd() ){
               if(counter ==1){
                  mmbr->setUserName(inp.readLine());
                   counter++;
               }
               else if(counter ==2){
                  mmbr->setPassword(inp.readLine());
                   counter++;
               }
               else if(counter ==3){
                 mmbr->setName(inp.readLine());
                   counter++;
               }
               else if(counter ==4){
                 mmbr->setMembershipNumber(inp.readLine());
                   counter++;
               }
               else if(counter ==5){
                 mmbr->setFatherName(inp.readLine());
                 counter++;
                  }
               else if(counter ==6){
                 mmbr->setNationalityCode(inp.readLine());
                   counter++;
               }
               else if(counter ==7){
                 mmbr->setBirthday(inp.readLine());
               counter++;
               }

               else if(counter ==8){
                 mmbr->setMobilePhone(inp.readLine().toLongLong());
                 counter++;
                  }
               else if(counter ==9){
                   mmbr->setEmail(inp.readLine());
                   counter++;
               }
               else if(counter==10){
                   mmbr->setBorrowingDate(inp.readLine());
                   counter++;
               }
               else if(counter==11){
                   mmbr->setReturnDate(inp.readLine());
                   outText<<mmbr->getUserName() <<"\n" << mmbr->getPassword() <<"\n"<<mmbr->getName() <<"\n" <<mmbr->getMembershipNumber() <<"\n" <<mmbr->getFatherName() <<"\n"<<mmbr->getNationalityCode() <<"\n"<<mmbr->getBirthday() <<"\n" <<mmbr->getMobilePhone() <<"\n"<<mmbr->getEmail()<<"\n"<<mmbr->getBorrowingDate()<<"\n"<<mmbr->getReturnDate()<<"\n";;
                   counter=1;
               }
           }
           fW.close();
           fR.close();
            QMessageBox::information(this,"عملیات موفق","رمز شما با موفقیت تغییر یافت");
               }
        else{
                QMessageBox::critical(this,"ورودی نامعتبر","نام کاربری وارد شده وجود ندارد!!!");
              }
           }
    }
    }

this->hide();

}

