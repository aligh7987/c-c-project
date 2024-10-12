#include "AddBook.h"
#include "ui_AddBook.h"
#include <QMessageBox>
#include "Book.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
AddBook::AddBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBook)
{
    ui->setupUi(this);
}

AddBook::~AddBook()
{
    delete ui;
}

void AddBook::on_back_clicked()
{
    this->hide();
}


void AddBook::on_submit_clicked()
{
    int flag=0;
    QString name = ui->name->text();
    QString writer = ui->writer->text();
    QString publish = ui->publisher->text();
    QString translater = ui->translater->text();
    QString year = ui->printYear->text();
    QString ganre = ui->ganre->text();
    bool child = ui->chidRange->isChecked();
    bool teen = ui->teenRange->isChecked();
    bool young = ui->adultGanre->isChecked();
    if(name.isEmpty() || writer.isEmpty() || publish.isEmpty() ||  year.isEmpty() || ganre.isEmpty() || (!child && !teen && !young)){
          QMessageBox::critical(this,"فیلد خالی","یکی از فیلد ها خالی است!");
    }
    else{
        Book book;
        book.setBorrowStatus(false);
        book.setBorrowsMemberShipNumber("");
        book.setGenre(ganre);
        book.setName(name);
        book.setBookId(name+"-"+book.bookSize());
        book.setPrintYear(year.toInt());
        book.setPublisher(publish);
        book.setWriter(writer);
        book.setTranslater(translater);
        if(child){
                book.setTheAgeRange("child");
        }
        else if(teen){
            book.setTheAgeRange("teen");
        }
        else{
            book.setTheAgeRange("young");
        }
        QFile f ("books.txt");
        f.open(QFile::WriteOnly|QFile::Append);
        QTextStream out(&f);
        out<< book.getBookId() <<"\n" << book.getName() <<"\n" << book.getWriter() <<"\n" << book.getPublisher() <<"\n" << book.getTranslater() <<"\n" << book.getPrintYear() <<"\n" << book.getBorrowStatus() <<"\n"<< book.getBorrowsMemberShipNumber() <<"\n"<< book.getGenre() <<"\n"<< book.getTheAgeRange() <<"\n";
        f.close();
        flag=1;
    }
    if(flag){
        if(QMessageBox::Ok ==QMessageBox::information(this,"عملیات موفق","کتاب جدید ثبت شد") || QMessageBox::Close == QMessageBox::information(this,"عملیات موفق","کتاب جدید ثبت شد")){
            this->hide();
        }
    }
}

