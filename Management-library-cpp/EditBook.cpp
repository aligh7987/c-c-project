#include "EditBook.h"
#include "ui_EditBook.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "Book.h"
EditBook::EditBook(QString id,QString name,QString writer,QString publisher,QString translater,QString year,QString genre,QString range,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditBook)
{
    ui->setupUi(this);
    this->id=id;
    ui->name->setText(name);
    ui->writer->setText(writer);
    ui->publisher->setText(publisher);
    ui->translater->setText(translater);
    ui->year->setText(year);
    ui->genre->setText(genre);
    if(range=="child"){
        ui->child->setChecked(true);
    }
    else if(range == "teen"){
        ui->teen->setChecked(true);
    }
    else{
        ui->young->setChecked(true);
    }
}

EditBook::~EditBook()
{
    delete ui;
}

void EditBook::on_back_clicked()
{
    this->hide();
}


void EditBook::on_submit_clicked()
{
    QString name = ui->name->text();
    QString writer = ui->writer->text();
    QString publish = ui->publisher->text();
    QString translater = ui->translater->text();
    QString year = ui->year->text();
    QString genre = ui->genre->text();
    bool child = ui->child->isChecked();
    bool teen = ui->teen->isChecked();
    bool young = ui->young->isChecked();
    if(name.isEmpty() || writer.isEmpty() || publish.isEmpty() ||  year.isEmpty() || genre.isEmpty() || (!child && !teen && !young)){
          QMessageBox::critical(this,"فیلد خالی","یکی از فیلد ها خالی است!");
    }
    else{
        Book book;
        int counter=1;
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

                if(book.getBookId() == this->id){
                    book.setBookId(name+"-"+book.bookSize());
                    book.setName(name);
                    book.setWriter(writer);
                    book.setPublisher(publish);
                    book.setTranslater(translater);
                    book.setPrintYear(year.toInt());
                    book.setGenre(genre);
                    if(child){
                        book.setTheAgeRange("child");
                     }
                    else if(teen){
                        book.setTheAgeRange("teen");
                    }
                    else{
                        book.setTheAgeRange("young");
                    }
                     out<< book.getBookId() <<"\n" << book.getName() <<"\n" << book.getWriter() <<"\n" << book.getPublisher() <<"\n" << book.getTranslater() <<"\n" << book.getPrintYear() <<"\n" << book.getBorrowStatus() <<"\n"<< book.getBorrowsMemberShipNumber() <<"\n"<< book.getGenre() <<"\n"<< book.getTheAgeRange() <<"\n";
                }
                else{
                    out<< book.getBookId() <<"\n" << book.getName() <<"\n" << book.getWriter() <<"\n" << book.getPublisher() <<"\n" << book.getTranslater() <<"\n" << book.getPrintYear() <<"\n" << book.getBorrowStatus() <<"\n"<< book.getBorrowsMemberShipNumber() <<"\n"<< book.getGenre() <<"\n"<< book.getTheAgeRange() <<"\n";
                }
                counter=1;
            }

        }
        f1.close();
        f2.close();
        QFile fR("booksTmp.txt");
        QFile fW("books.txt");
        fR.open(QFile::ReadOnly|QFile::Text);
        QTextStream inp(&fR);
        fW.open(QFile::WriteOnly|QFile::Text);
        QTextStream outText(&fW);
        while(!inp.atEnd()){
            if(counter==1){
                book.setBookId(inp.readLine());
                counter++;
            }
            else if(counter==2){
                book.setName(inp.readLine());
                counter++;
            }
            else if(counter==3){
                book.setWriter(inp.readLine());
                counter++;
            }
            else if(counter==4){
                book.setPublisher(inp.readLine());
                counter++;
            }
            else if(counter==5){
                book.setTranslater(inp.readLine());
                counter++;
            }
            else if(counter==6){
                book.setPrintYear(inp.readLine().toInt());
                counter++;
            }
            else if(counter==7){
                book.setBorrowStatus(inp.readLine().toInt());
                counter++;
            }
            else if(counter==8){
                book.setBorrowsMemberShipNumber(inp.readLine());
                counter++;
            }
            else if(counter==9){
                book.setGenre(inp.readLine());
                counter++;
            }
            else if(counter==10){
                book.setTheAgeRange(inp.readLine());
                outText<< book.getBookId() <<"\n" << book.getName() <<"\n" << book.getWriter() <<"\n" << book.getPublisher() <<"\n" << book.getTranslater() <<"\n" << book.getPrintYear() <<"\n" << book.getBorrowStatus() <<"\n"<< book.getBorrowsMemberShipNumber() <<"\n"<< book.getGenre() <<"\n"<< book.getTheAgeRange() <<"\n";
                counter=1;
            }

        }
        fW.close();
        fR.close();
        if(QMessageBox::Ok ==QMessageBox::information(this,"عملیات موفق","کتاب مورد نظر با موفقیت ویرایش شد ")){
            this->hide();
        }
    }
}

