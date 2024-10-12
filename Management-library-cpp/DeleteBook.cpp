#include "DeleteBook.h"
#include "ui_DeleteBook.h"
#include "Book.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

DeleteBook::DeleteBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteBook)
{
    ui->setupUi(this);
}

DeleteBook::~DeleteBook()
{
    delete ui;
}

void DeleteBook::on_back_clicked()
{
    this->hide();
}


void DeleteBook::on_delete_2_clicked()
{
QString id = ui->bookid->text();
Book book;
int counter=1 , idFlag=0;
if(id.isEmpty()){
    QMessageBox::critical(this,"فیلد خالی","آیدی کتاب وارد نشده است");
}
else{
    QFile f1("books.txt");
    QFile f2("booksTmp.txt");
    f1.open(QFile::ReadOnly|QFile::Text);
    QTextStream in(&f1);
    f2.open(QFile::WriteOnly|QFile::Text);
    QTextStream out(&f2);
    while(!in.atEnd()){
        if(counter==1){
            book.setBookId(in.readLine());
            counter++;
        }
        else if(counter==2){
            book.setName(in.readLine());
            counter++;
        }
        else if(counter==3){
            book.setWriter(in.readLine());
            counter++;
        }
        else if(counter==4){
            book.setPublisher(in.readLine());
            counter++;
        }
        else if(counter==5){
            book.setTranslater(in.readLine());
            counter++;
        }
        else if(counter==6){
            book.setPrintYear(in.readLine().toInt());
            counter++;
        }
        else if(counter==7){
            book.setBorrowStatus(in.readLine().toInt());
            counter++;
        }
        else if(counter==8){
            book.setBorrowsMemberShipNumber(in.readLine());
            counter++;
        }
        else if(counter==9){
            book.setGenre(in.readLine());
            counter++;
        }
        else if(counter==10){
            book.setTheAgeRange(in.readLine());

            if(book.getBookId() != id){
                 out<< book.getBookId() <<"\n" << book.getName() <<"\n" << book.getWriter() <<"\n" << book.getPublisher() <<"\n" << book.getTranslater() <<"\n" << book.getPrintYear() <<"\n" << book.getBorrowStatus() <<"\n"<< book.getBorrowsMemberShipNumber() <<"\n"<< book.getGenre() <<"\n"<< book.getTheAgeRange() <<"\n";
            }
            else{
                idFlag=1;
            }
            counter=1;
        }

    }
    f1.close();
    f2.close();
    if(idFlag){
        QFile fR("booksTmp.txt");
        QFile fW("books.txt");
        fR.open(QFile::ReadOnly|QFile::Text);
        QTextStream in(&fR);
        fW.open(QFile::WriteOnly|QFile::Text);
        QTextStream out(&fW);
        while(!in.atEnd()){
            if(counter==1){
                book.setBookId(in.readLine());
                counter++;
            }
            else if(counter==2){
                book.setName(in.readLine());
                counter++;
            }
            else if(counter==3){
                book.setWriter(in.readLine());
                counter++;
            }
            else if(counter==4){
                book.setPublisher(in.readLine());
                counter++;
            }
            else if(counter==5){
                book.setTranslater(in.readLine());
                counter++;
            }
            else if(counter==6){
                book.setPrintYear(in.readLine().toInt());
                counter++;
            }
            else if(counter==7){
                book.setBorrowStatus(in.readLine().toInt());
                counter++;
            }
            else if(counter==8){
                book.setBorrowsMemberShipNumber(in.readLine());
                counter++;
            }
            else if(counter==9){
                book.setGenre(in.readLine());
                counter++;
            }
            else if(counter==10){
                book.setTheAgeRange(in.readLine());
                out<< book.getBookId() <<"\n" << book.getName() <<"\n" << book.getWriter() <<"\n" << book.getPublisher() <<"\n" << book.getTranslater() <<"\n" << book.getPrintYear() <<"\n" << book.getBorrowStatus() <<"\n"<< book.getBorrowsMemberShipNumber() <<"\n"<< book.getGenre() <<"\n"<< book.getTheAgeRange() <<"\n";
                counter=1;
            }

        }
        fW.close();
        fR.close();
        if(QMessageBox::Ok ==QMessageBox::information(this,"عملیات موفق","کتاب مورد نظر با موفقیت حذف شد ")){
            this->hide();
        }

    }
    else{
        QMessageBox::critical(this,"آیدی نامعتبر","کتابی با این آیدی وجود ندارد");
    }
}

}

