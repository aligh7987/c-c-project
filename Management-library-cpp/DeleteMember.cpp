#include "DeleteMember.h"
#include "ui_DeleteMember.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "Member.h"
DeleteMember::DeleteMember(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteMember)
{
    ui->setupUi(this);
}

DeleteMember::~DeleteMember()
{
    delete ui;
}

void DeleteMember::on_back_clicked()
{
    this->hide();
}


void DeleteMember::on_delete_2_clicked()
{
    QString mmbrId = ui->mmbrShipId->text();
    std::unique_ptr<Member> mmbr(new Member());
    int counter=1, idflag=0;
    if(mmbrId.isEmpty()){
        QMessageBox::critical(this,"فیلد خالی","شماره عضویت وارد نشده است");
    }
    else{
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
                if(mmbr->getMembershipNumber() != mmbrId){
                   out<<mmbr->getUserName() <<"\n" << mmbr->getPassword() <<"\n"<<mmbr->getName() <<"\n" <<mmbr->getMembershipNumber() <<"\n" <<mmbr->getFatherName() <<"\n"<<mmbr->getNationalityCode() <<"\n"<<mmbr->getBirthday() <<"\n" <<mmbr->getMobilePhone() <<"\n"<<mmbr->getEmail()<<"\n" <<mmbr->getBorrowingDate()<<"\n"<<mmbr->getReturnDate()<<"\n";
                }
                else{
                    idflag =1;
                }
                counter=1;
            }
            }
        f1.close();
        f2.close();
    if(idflag){
           QFile fR("membersTmp.txt");
           QFile fW("members.txt");
           fR.open(QFile::ReadOnly|QFile::Text);
           QTextStream in(&fR);
           fW.open(QFile::WriteOnly|QFile::Text);
           QTextStream out(&fW);
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
                   out<<mmbr->getUserName() <<"\n" << mmbr->getPassword() <<"\n"<<mmbr->getName() <<"\n" <<mmbr->getMembershipNumber() <<"\n" <<mmbr->getFatherName() <<"\n"<<mmbr->getNationalityCode() <<"\n"<<mmbr->getBirthday() <<"\n" <<mmbr->getMobilePhone() <<"\n"<<mmbr->getEmail()<<"\n"<<mmbr->getBorrowingDate()<<"\n"<<mmbr->getReturnDate()<<"\n";;
                   counter=1;
               }
           }
           fW.close();
           fR.close();
           if(QMessageBox::Ok ==QMessageBox::information(this,"عملیات موفق","عضو مورد نظر با موفقیت حذف شد ")){
               this->hide();
           }

    }
    else{
        QMessageBox::critical(this,"آیدی نامعتبر","عضوی با این آیدی وجود ندارد");
    }

    }
    }




