#include "SearchBook.h"
#include "ui_SearchBook.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "Book.h"
#include "EditBook.h"
SearchBook::SearchBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchBook)
{
    ui->setupUi(this);
}

SearchBook::~SearchBook()
{
    delete ui;
}

void SearchBook::showBooks()
{
    Book book;
    int counter=1;
    QFile f("books.txt");
    f.open(QFile::ReadOnly);
    QTextStream in(&f);
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
             ui->tableBooks->insertRow(ui->tableBooks->rowCount());
             ui->tableBooks->setItem(ui->tableBooks->rowCount()-1,0,new QTableWidgetItem(book.getBookId()));
             ui->tableBooks->setItem(ui->tableBooks->rowCount()-1,1,new QTableWidgetItem(book.getName()));
             ui->tableBooks->setItem(ui->tableBooks->rowCount()-1,2,new QTableWidgetItem(book.getWriter()));
             ui->tableBooks->setItem(ui->tableBooks->rowCount()-1,3,new QTableWidgetItem(book.getPublisher()));
             ui->tableBooks->setItem(ui->tableBooks->rowCount()-1,4,new QTableWidgetItem(book.getTranslater()));
             ui->tableBooks->setItem(ui->tableBooks->rowCount()-1,5,new QTableWidgetItem(QString::number(book.getPrintYear())));
             ui->tableBooks->setItem(ui->tableBooks->rowCount()-1,6,new QTableWidgetItem(book.getGenre()));
             ui->tableBooks->setItem(ui->tableBooks->rowCount()-1,7,new QTableWidgetItem(book.getTheAgeRange()));
            counter=1;
        }
        }
    f.close();
}

void SearchBook::on_back_clicked()
{
    this->hide();
}


void SearchBook::on_delete_2_clicked()
{
    QList<QTableWidgetItem*>list = ui->tableBooks->selectedItems();
    if(!list.isEmpty()){
        QString id=list[0]->text();
        Book book;
        int counter=1 , idFlag=0;
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
                ui->tableBooks->clearContents();
                ui->tableBooks->setRowCount(0);
                ui->nameSearch->setText("");
            }
    }
    else{
         QMessageBox::critical(this,"عملیات نامعتبر","لطفا سطر مورد نظر برای حذف را انتخاب کنید");
    }
    }
}


void SearchBook::on_edit_clicked()
{
    QList<QTableWidgetItem*> list = ui->tableBooks->selectedItems();
    if(!list.isEmpty()){
        QString id=list[0]->text();
        QString name=list[1]->text();
        QString writer=list[2]->text();
        QString publisher=list[3]->text();
        QString translater=list[4]->text();
        QString year=list[5]->text();
        QString genre=list[6]->text();
        QString range=list[7]->text();
        EditBook* e = new EditBook(id,name,writer,publisher,translater,year,genre,range,this);
        e->exec();
        ui->tableBooks->clearContents();
        ui->tableBooks->setRowCount(0);
        this->showBooks();
        ui->nameSearch->setText("");
    }
    else{
        QMessageBox::critical(this,"عملیات نامعتبر","لطفا سطر مورد نظر برای ویرایش را انتخاب کنید");
    }
}


void SearchBook::on_search_clicked()
{
    ui->tableBooks->clearContents();
    ui->tableBooks->setRowCount(0);
    QString name = ui->nameSearch->text();
    if(!name.isEmpty()){
        int counter=1,flag=0;
        Book book;
        QFile fread("books.txt");
        fread.open(QFile::ReadOnly);
        QTextStream in(&fread);
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
               if(book.getName() ==name){
                   ui->tableBooks->insertRow(ui->tableBooks->rowCount());
                   ui->tableBooks->setItem(ui->tableBooks->rowCount()-1,0,new QTableWidgetItem(book.getBookId()));
                   ui->tableBooks->setItem(ui->tableBooks->rowCount()-1,1,new QTableWidgetItem(book.getName()));
                   ui->tableBooks->setItem(ui->tableBooks->rowCount()-1,2,new QTableWidgetItem(book.getWriter()));
                   ui->tableBooks->setItem(ui->tableBooks->rowCount()-1,3,new QTableWidgetItem(book.getPublisher()));
                   ui->tableBooks->setItem(ui->tableBooks->rowCount()-1,4,new QTableWidgetItem(book.getTranslater()));
                   ui->tableBooks->setItem(ui->tableBooks->rowCount()-1,5,new QTableWidgetItem(QString::number(book.getPrintYear())));
                   ui->tableBooks->setItem(ui->tableBooks->rowCount()-1,6,new QTableWidgetItem(book.getGenre()));
                   ui->tableBooks->setItem(ui->tableBooks->rowCount()-1,7,new QTableWidgetItem(book.getTheAgeRange()));
                        flag=1;
               }
                counter=1;
            }

        }
        fread.close();
        if(flag==0){
             QMessageBox::critical(this,"فرد نامعتبر","کتابی با این نام وجود ندارد");
        }

    }else{
        QMessageBox::critical(this,"فیلد خالی","لطفا نام کتاب را وارد کنید");
    }
}

