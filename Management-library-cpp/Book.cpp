#include "Book.h"
#include <QFile>
#include <QTextStream>
Book::Book()
{

}

QString Book::getBookId() const
{
    return bookId;
}

void Book::setBookId(QString newBookId)
{
    bookId = newBookId;
}

const QString &Book::getName() const
{
    return name;
}

void Book::setName(const QString &newName)
{
    name = newName;
}

const QString &Book::getWriter() const
{
    return writer;
}

void Book::setWriter(const QString &newWriter)
{
    writer = newWriter;
}

const QString &Book::getPublisher() const
{
    return publisher;
}

void Book::setPublisher(const QString &newPublisher)
{
    publisher = newPublisher;
}

const QString &Book::getTranslater() const
{
    return translater;
}

void Book::setTranslater(const QString &newTranslater)
{
    translater = newTranslater;
}

int Book::getPrintYear() const
{
    return printYear;
}

void Book::setPrintYear(int newPrintYear)
{
    printYear = newPrintYear;
}

bool Book::getBorrowStatus() const
{
    return borrowStatus;
}

void Book::setBorrowStatus(bool newBorrowStatus)
{
    borrowStatus = newBorrowStatus;
}

QString Book::getBorrowsMemberShipNumber() const
{
    return borrowsMemberShipNumber;
}

void Book::setBorrowsMemberShipNumber(QString newBorrowsMemberShipNumber)
{
    borrowsMemberShipNumber = newBorrowsMemberShipNumber;
}

const QString &Book::getGenre() const
{
    return genre;
}

void Book::setGenre(const QString &newGenre)
{
    genre = newGenre;
}

const QString &Book::getTheAgeRange() const
{
    return theAgeRange;
}

void Book::setTheAgeRange(const QString &newTheAgeRange)
{
    theAgeRange = newTheAgeRange;
}

QString Book::bookSize()
{
int counter=1,size=1;
QFile f("books.txt");
f.open(QFile::ReadOnly);
QTextStream in(&f);
while(!in.atEnd()){
    if(counter==1){
        this->setBookId(in.readLine());
        counter++;
    }
    else if(counter==2){
        this->setName(in.readLine());
        counter++;
    }
    else if(counter==3){
        this->setWriter(in.readLine());
        counter++;
    }
    else if(counter==4){
        this->setPublisher(in.readLine());
        counter++;
    }
    else if(counter==5){
        this->setTranslater(in.readLine());
        counter++;
    }
    else if(counter==6){
        this->setPrintYear(in.readLine().toInt());
        counter++;
    }
    else if(counter==7){
        this->setBorrowStatus(in.readLine().toInt());
        counter++;
    }
    else if(counter==8){
        this->setBorrowsMemberShipNumber(in.readLine());
        counter++;
    }
    else if(counter==9){
        this->setGenre(in.readLine());
        counter++;
    }
    else if(counter==10){
        this->setTheAgeRange(in.readLine());
        counter=1;
        size++;
    }
f.close();

}
return QString::number(size);
}
