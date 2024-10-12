#include "AddMember.h"
#include "ui_AddMember.h"
#include "Member.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
AddMember::AddMember(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMember)
{
    ui->setupUi(this);
}

AddMember::~AddMember()
{
    delete ui;
}

void AddMember::on_back_clicked()
{
    this->hide();
}


void AddMember::on_submit_clicked()
{
    QString name =ui->name->text();
    QString father = ui->fatherName->text();
    QString nCode = ui->nationalityCod->text();
    QString birthday = ui->birthday->text();
    QString mobile = ui->mobile->text();
    QString email = ui->email->text();
    std::unique_ptr<Member> m (new Member());
    if(!name.isEmpty() || !father.isEmpty() || !nCode.isEmpty() || !birthday.isEmpty() || !mobile.isEmpty() ){
        QFile f("members.txt");
        f.open(QFile::WriteOnly|QFile::Append);

       QTextStream out(&f);
        out<< nCode+"-"+m->mmbrSize() <<"\n" << nCode <<"\n" << name << "\n"<<nCode+"-"+m->mmbrSize() <<"\n" << father <<"\n"<<nCode <<"\n"<<birthday <<"\n" << mobile.toLongLong()<<"\n"<<email <<"\n"<< ""<<"\n"<<""<<"\n";
        f.close();
        if(QMessageBox::Ok ==QMessageBox::information(this,"عملیات موفق","عضو جدید با موفقیت ثبت شد") || QMessageBox::Close == QMessageBox::information(this,"عملیات موفق","عضو جدید با موفقیت ثبت شد")){
            this->hide();
        }
    }else{
        QMessageBox::critical(this,"فیلد خالی","یکی از فیلد ها خالی است!");
    }
}

