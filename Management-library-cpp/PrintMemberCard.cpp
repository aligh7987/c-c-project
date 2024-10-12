#include "PrintMemberCard.h"
#include "ui_PrintMemberCard.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>
#include "Member.h"
PrintMemberCard::PrintMemberCard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrintMemberCard)
{
    ui->setupUi(this);
}

PrintMemberCard::~PrintMemberCard()
{
    delete ui;
}

void PrintMemberCard::on_showCard_clicked()
{
    QString id = ui->membershipNum->text();
    if(!id.isEmpty()){
        int counter=1,idFlag=0;
        std::unique_ptr<Member> mmbr(new Member());
         QString text , name ;
        QFile f1("members.txt");
        f1.open(QFile::ReadOnly|QFile::Text);
        QTextStream in(&f1);
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
                if(mmbr->getMembershipNumber() == id){
                    name = mmbr->getName();
                    text = "شماره عضویت :  " + id + "\n\n\n" + "نام و نام خانوادگی : " + name + "\n\n\n" + "\t\t\t\t" + "محل امضا مدیر";
                    ui->memberCard->setText(text);
                    idFlag=1;
                }
                counter=1;
            }
        }
        f1.close();
        if(idFlag==0){
             QMessageBox::critical(this,"شماره عضویت نامعتبر","عضوی با این شماره عضویت وجود ندارد");
        }
    }else{
        QMessageBox::critical(this,"فیلد خالی","لطفا شماره عضویت را وارد کنید");

    }
}


void PrintMemberCard::on_back_clicked()
{
    this->hide();
}


void PrintMemberCard::on_print_clicked()
{
    if(!ui->membershipNum->text().isEmpty()){
        QPrinter printer;
        printer.setPrinterName("desierd printer name");
        QPrintDialog dialog(&printer,this);
        if(dialog.exec() == QDialog::Rejected)return
         ui->memberCard->print(&printer);
    }
    else{
        QMessageBox::critical(this,"فیلد خالی","لطفا شماره عضویت را وارد کنید");
    }
}

