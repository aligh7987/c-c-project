#ifndef BOOK_H
#define BOOK_H
#include <QString>

class Book
{
public:
    Book();
    QString getBookId() const;
    void setBookId(QString newBookId);

    const QString &getName() const;
    void setName(const QString &newName);

    const QString &getWriter() const;
    void setWriter(const QString &newWriter);

    const QString &getPublisher() const;
    void setPublisher(const QString &newPublisher);

    const QString &getTranslater() const;
    void setTranslater(const QString &newTranslater);

    int getPrintYear() const;
    void setPrintYear(int newPrintYear);

    bool getBorrowStatus() const;
    void setBorrowStatus(bool newBorrowStatus);

    QString getBorrowsMemberShipNumber() const;
    void setBorrowsMemberShipNumber(QString newBorrowsMemberShipNumber);

    const QString &getGenre() const;
    void setGenre(const QString &newGenre);

    const QString &getTheAgeRange() const;
    void setTheAgeRange(const QString &newTheAgeRange);
    QString bookSize();
private:
    QString bookId;
    QString name;
    QString writer;
    QString publisher;
    QString translater ;
    int printYear;
    bool borrowStatus;
    QString borrowsMemberShipNumber;
    QString genre;
    QString theAgeRange;
};

#endif // BOOK_H
