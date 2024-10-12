#include "ShowAllMember.h"
#include "ui_ShowAllMember.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "Member.h"
#include "EditMember.h"
ShowAllMember::ShowAllMember(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowAllMember)
{
    ui->setupUi(this);
}

ShowAllMember::~ShowAllMember()
{
    delete ui;
}

void ShowAllMember::showMember()
{
    std::unique_ptr<Member> mmbr(new Member());


    int counter =1;
    QFile f2("members.txt");
    if(f2.open(QFile::ReadOnly | QFile::Text)){
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
            else if(counter==10){
                mmbr->setBorrowingDate(in.readLine());
                counter++;
            }
            else if(counter==11){
                mmbr->setReturnDate(in.readLine());
                ui->tableMembers->insertRow(ui->tableMembers->rowCount());
                ui->tableMembers->setItem(ui->tableMembers->rowCount()-1,0,new QTableWidgetItem(mmbr->getMembershipNumber()));
                ui->tableMembers->setItem(ui->tableMembers->rowCount()-1,1,new QTableWidgetItem(mmbr->getName()));
                ui->tableMembers->setItem(ui->tableMembers->rowCount()-1,2,new QTableWidgetItem(mmbr->getFatherName()));
                ui->tableMembers->setItem(ui->tableMembers->rowCount()-1,3,new QTableWidgetItem(mmbr->getNationalityCode()));
                ui->tableMembers->setItem(ui->tableMembers->rowCount()-1,4,new QTableWidgetItem(mmbr->getBirthday()));
                ui->tableMembers->setItem(ui->tableMembers->rowCount()-1,5,new QTableWidgetItem(QString::number(mmbr->getMobilePhone())));
                ui->tableMembers->setItem(ui->tableMembers->rowCount()-1,6,new QTableWidgetItem(mmbr->getEmail()));
                ui->tableMembers->setItem(ui->tableMembers->rowCount()-1,7,new QTableWidgetItem(mmbr->getUserName()));
                ui->tableMembers->setItem(ui->tableMembers->rowCount()-1,8,new QTableWidgetItem(mmbr->getPassword()));
                counter=1;
            }
            }
        }
    f2.close();

}

void ShowAllMember::on_back_clicked()
{
    this->hide();
}


void ShowAllMember::on_delete_2_clicked()
{
    QList<QTableWidgetItem*>list = ui->tableMembers->selectedItems();
    if(!list.isEmpty()){
        QString mmbrshipNum = list[0]->text();
        int counter=1, idFlag=0;
        std::unique_ptr<Member> mmbr(new Member());


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
                if(mmbr->getMembershipNumber() != mmbrshipNum){
                   out<<mmbr->getUserName() <<"\n" << mmbr->getPassword() <<"\n"<<mmbr->getName() <<"\n" <<mmbr->getMembershipNumber() <<"\n" <<mmbr->getFatherName() <<"\n"<<mmbr->getNationalityCode() <<"\n"<<mmbr->getBirthday() <<"\n" <<mmbr->getMobilePhone() <<"\n"<<mmbr->getEmail()<<"\n" <<mmbr->getBorrowingDate()<<"\n"<<mmbr->getReturnDate()<<"\n";
                }
                else{
                    idFlag =1;
                }
                counter=1;
            }
            }
        f1.close();
        f2.close();
        if(idFlag){
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
                  ui->tableMembers->clearContents();
                  ui->tableMembers->setRowCount(0);
                  this->showMember();
               }
        }

    }else{
         QMessageBox::critical(this,"عملیات نامعتبر","لطفا سطر مورد نظر برای حذف را انتخاب کنید");
    }
}


void ShowAllMember::on_edit_clicked()
{
    QList<QTableWidgetItem*> list = ui->tableMembers->selectedItems();
    if(!list.isEmpty()){
        QString mmbrshipNum = list[0]->text();
        QString name = list[1]->text();
        QString father = list[2]->text();
        QString nCode = list[3]->text();
        QString birthday = list[4]->text();
        QString mobile = list[5]->text();
        QString email = list[6]->text();


        EditMember * e = new EditMember(mmbrshipNum,name,father,nCode,birthday,mobile,email,this);
        e->exec();
        ui->tableMembers->clearContents();
        ui->tableMembers->setRowCount(0);
        this->showMember();
    }else{
        QMessageBox::critical(this,"عملیات نامعتبر","لطفا سطر مورد نظر برای حذف را انتخاب کنید");
    }
}

