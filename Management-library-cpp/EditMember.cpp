#include "EditMember.h"
#include "ui_EditMember.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "Member.h"
EditMember::EditMember(QString mmbrshipNum,QString name,QString father,QString ncode,QString birthday,QString mobile,QString email,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditMember)
{
    ui->setupUi(this);
    this->id = mmbrshipNum;
    ui->name->setText(name);
    ui->fatherName->setText(father);
    ui->nationalityCod->setText(ncode);
    ui->birthday->setText(birthday);
    ui->mobile->setText(mobile);
    ui->email->setText(email);
}

EditMember::~EditMember()
{
    delete ui;
}

void EditMember::on_back_clicked()
{
    this->hide();
}


void EditMember::on_submit_clicked()
{
    QString name =ui->name->text();
    QString father = ui->fatherName->text();
    QString nCode = ui->nationalityCod->text();
    QString birthday = ui->birthday->text();
    QString mobile = ui->mobile->text();
    QString email = ui->email->text();
    std::unique_ptr<Member> mmbr(new Member());
    if(!name.isEmpty() || !father.isEmpty() || !nCode.isEmpty() || !birthday.isEmpty() || !mobile.isEmpty() ){
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
                if(mmbr->getMembershipNumber() == this->id){
                    out<< nCode+"-"+mmbr->mmbrSize() <<"\n" << nCode <<"\n" << name << "\n"<<nCode+"-"+mmbr->mmbrSize() <<"\n" << father <<"\n"<<nCode <<"\n"<<birthday <<"\n" << mobile.toLongLong()<<"\n"<<email <<"\n"<< mmbr->getBorrowingDate()<<"\n"<<mmbr->getReturnDate()<<"\n";
                }
                else{
                    out<<mmbr->getUserName() <<"\n" << mmbr->getPassword() <<"\n"<<mmbr->getName() <<"\n" <<mmbr->getMembershipNumber() <<"\n" <<mmbr->getFatherName() <<"\n"<<mmbr->getNationalityCode() <<"\n"<<mmbr->getBirthday() <<"\n" <<mmbr->getMobilePhone() <<"\n"<<mmbr->getEmail()<<"\n"<<mmbr->getBorrowingDate()<<"\n"<<mmbr->getReturnDate()<<"\n";;
                }
                counter=1;
            }
            }
        f1.close();
        f2.close();
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
           if(QMessageBox::Ok ==QMessageBox::information(this,"عملیات موفق","عضو مورد نظر با موفقیت ویرایش شد ")){
               this->hide();
           }
    }
}

