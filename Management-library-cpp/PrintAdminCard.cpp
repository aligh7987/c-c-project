#include "PrintAdminCard.h"
#include "ui_PrintAdminCard.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include "Admin.h"
PrintAdminCard::PrintAdminCard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrintAdminCard)
{
    ui->setupUi(this);
}

PrintAdminCard::~PrintAdminCard()
{
    delete ui;
}

void PrintAdminCard::on_showCard_clicked()
{
    QString id = ui->id->text();
    if(!id.isEmpty()){
        int counter=1,idFlag=0;
        unique_ptr<Admin> adm(new Admin());
        QString text , name ;
        QFile f1("admins.txt");
        f1.open(QFile::ReadOnly|QFile::Text);
        QTextStream in(&f1);
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
                if(adm->getAdminId() == id){
                    name = adm->getName();
                    text = "آیدی:  " + id + "\n\n\n" + "نام و نام خانوادگی : " + name + "\n\n\n" + "\t\t\t\t" + "محل امضا مدیر";
                    ui->adminCard->setText(text);
                    idFlag=1;
                }
                counter=1;
            }
        }
        f1.close();
        if(idFlag==0){
             QMessageBox::critical(this,"آیدی نامعتبر","ادمینی با این آیدی وجود ندارد");
        }
    }else{
        QMessageBox::critical(this,"فیلد خالی","لطفا آیدی را وارد کنید");
    }
}


void PrintAdminCard::on_back_clicked()
{
    this->hide();
}


void PrintAdminCard::on_print_2_clicked()
{
    if(!ui->id->text().isEmpty()){
        QPrinter printer;
        printer.setPrinterName("desierd printer name");
        QPrintDialog dialog(&printer,this);
        if(dialog.exec() == QDialog::Rejected)return
         ui->adminCard->print(&printer);
    }
    else{
        QMessageBox::critical(this,"فیلد خالی","لطفا آیدی را وارد کنید");
    }

}

