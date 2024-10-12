#include "ListOfBorrowedBooks.h"
#include "ui_ListOfBorrowedBooks.h"
#include "Member.h"
#include "Book.h"
#include <QFile>
#include <QTextStream>
ListOfBorrowedBooks::ListOfBorrowedBooks(Member* m,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListOfBorrowedBooks)
{
    ui->setupUi(this);
    this->tmp = new Member();
    this->tmp = m ;
    ui->borrowingDate->setText(this->tmp->getBorrowingDate());
    ui->returnDate->setText(this->tmp->getReturnDate());
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
            if(book.getBorrowsMemberShipNumber() == this->tmp->getMembershipNumber()){
                ui->tableBooks->insertRow(ui->tableBooks->rowCount());
                ui->tableBooks->setItem(ui->tableBooks->rowCount()-1,0,new QTableWidgetItem(book.getBookId()));
                ui->tableBooks->setItem(ui->tableBooks->rowCount()-1,1,new QTableWidgetItem(book.getName()));
                ui->tableBooks->setItem(ui->tableBooks->rowCount()-1,2,new QTableWidgetItem(book.getWriter()));
                ui->tableBooks->setItem(ui->tableBooks->rowCount()-1,3,new QTableWidgetItem(book.getPublisher()));
                ui->tableBooks->setItem(ui->tableBooks->rowCount()-1,4,new QTableWidgetItem(book.getTranslater()));
                ui->tableBooks->setItem(ui->tableBooks->rowCount()-1,5,new QTableWidgetItem(QString::number(book.getPrintYear())));
                ui->tableBooks->setItem(ui->tableBooks->rowCount()-1,6,new QTableWidgetItem(book.getGenre()));
                ui->tableBooks->setItem(ui->tableBooks->rowCount()-1,7,new QTableWidgetItem(book.getTheAgeRange()));

            }
          counter=1;
        }
        }
    f.close();
}

ListOfBorrowedBooks::~ListOfBorrowedBooks()
{
    delete ui;
}

void ListOfBorrowedBooks::on_back_clicked()
{
    this->hide();
}

