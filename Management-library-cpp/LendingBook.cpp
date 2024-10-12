#include "LendingBook.h"
#include "ui_LendingBook.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDate>
#include "Member.h"
#include "Book.h"
LendingBook::LendingBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LendingBook)
{
    ui->setupUi(this);
    this->countOfBook = 0;
}

LendingBook::~LendingBook()
{
    delete ui;
}

void LendingBook::on_search_clicked()
{
    ui->tableMembers->clearContents();
    ui->tableMembers->setRowCount(0);
     QString ncode= ui->nCode->text();
    int counter=1;
    std::unique_ptr<Member> mmbr(new Member());
    Book book;
    if(!ncode.isEmpty()){
        QFile f("members.txt");
        QFile f2("books.txt");
        f2.open(QFile::ReadOnly);
        f.open(QFile::ReadOnly);
        QTextStream in(&f);
        QTextStream inp(&f2);
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
                if(mmbr->getNationalityCode() == ncode){
                    ui->tableMembers->insertRow(ui->tableMembers->rowCount());
                    ui->tableMembers->setItem(ui->tableMembers->rowCount()-1,0,new QTableWidgetItem(mmbr->getMembershipNumber()));
                    ui->tableMembers->setItem(ui->tableMembers->rowCount()-1,1,new QTableWidgetItem(mmbr->getName()));
                    ui->tableMembers->setItem(ui->tableMembers->rowCount()-1,2,new QTableWidgetItem(mmbr->getFatherName()));
                    ui->tableMembers->setItem(ui->tableMembers->rowCount()-1,3,new QTableWidgetItem(mmbr->getNationalityCode()));
                    ui->tableMembers->setItem(ui->tableMembers->rowCount()-1,4,new QTableWidgetItem(mmbr->getBirthday()));
                    ui->tableMembers->setItem(ui->tableMembers->rowCount()-1,5,new QTableWidgetItem(QString::number(mmbr->getMobilePhone())));
                    ui->tableMembers->setItem(ui->tableMembers->rowCount()-1,6,new QTableWidgetItem(mmbr->getEmail()));
                    ui->tableMembers->setItem(ui->tableMembers->rowCount()-1,7,new QTableWidgetItem(mmbr->getUserName()));
                    ui->tableMembers->setItem(ui->tableMembers->rowCount()-1,8,new QTableWidgetItem(mmbr->getPassword()));
                    ui->tableMembers->setItem(ui->tableMembers->rowCount()-1,9,new QTableWidgetItem(mmbr->getReturnDate()));
                    this->m.append(mmbr->getMembershipNumber());
                    this->m.append(mmbr->getName());
                    this->m.append(mmbr->getFatherName());
                    this->m.append(mmbr->getNationalityCode());
                    this->m.append(mmbr->getBirthday());
                    this->m.append(QString::number(mmbr->getMobilePhone()));
                    this->m.append(mmbr->getEmail());
                    this->m.append(mmbr->getUserName());
                    this->m.append(mmbr->getPassword());
                    //-------------------------------------------------------------------------
                    int count=1;
                    while(!inp.atEnd()){
                        if(count==1){
                            book.setBookId(inp.readLine());
                            count++;
                        }
                        else if(count==2){
                            book.setName(inp.readLine());
                            count++;
                        }
                        else if(count==3){
                            book.setWriter(inp.readLine());
                            count++;
                        }
                        else if(count==4){
                            book.setPublisher(inp.readLine());
                            count++;
                        }
                        else if(count==5){
                            book.setTranslater(inp.readLine());
                            count++;
                        }
                        else if(count==6){
                            book.setPrintYear(inp.readLine().toInt());
                            count++;
                        }
                        else if(count==7){
                            book.setBorrowStatus(inp.readLine().toInt());
                            count++;
                        }
                        else if(count==8){
                            book.setBorrowsMemberShipNumber(inp.readLine());
                            count++;
                        }
                        else if(count==9){
                            book.setGenre(inp.readLine());
                            count++;
                        }
                        else if(count==10){
                            book.setTheAgeRange(inp.readLine());
                            if(book.getBorrowsMemberShipNumber() == this->m[0]){
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
                            count=1;
                        }

                    }
                }
                counter=1;
            }
            }
        f.close();
        f2.close();
    }
    else{
        QMessageBox::critical(this,"فیلد خالی","کدملی را وارد کنید");
    }
}


void LendingBook::on_lendBook_clicked()
{
    QCalendar cal(QCalendar::System::Jalali);
    QDate today = QDate::currentDate();
    QDate returnday = today.addDays(14);
    QCalendar::YearMonthDay ret = cal.partsFromDate(returnday);
    QString retDate = QString("%1/%2/%3")
            .arg(ret.year, 4, 10, QChar('0'))
            .arg(ret.month, 2, 10, QChar('0'))
            .arg(ret.day, 2, 10, QChar('0'));
    QCalendar::YearMonthDay ymd = cal.partsFromDate(today);
     QString currentDate= QString("%1/%2/%3")
                .arg(ymd.year, 4, 10, QChar('0'))
                .arg(ymd.month, 2, 10, QChar('0'))
                .arg(ymd.day, 2, 10, QChar('0'));
    if(!ui->nCode->text().isEmpty()){
        std::unique_ptr<Member> mmbr(new Member());
        int counter=1 ;
        QFile f1("members.txt");
        QFile f2("membersTmp.txt");
        f1.open(QFile::ReadOnly|QFile::Text);
        QTextStream in(&f1);
        f2.open(QFile::WriteOnly|QFile::Text);
        QTextStream out(&f2);
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
                if(mmbr->getMembershipNumber() == this->m[0]){
                  out<<mmbr->getUserName() <<"\n" << mmbr->getPassword() <<"\n"<<mmbr->getName() <<"\n" <<mmbr->getMembershipNumber() <<"\n" <<mmbr->getFatherName() <<"\n"<<mmbr->getNationalityCode() <<"\n"<<mmbr->getBirthday() <<"\n" <<mmbr->getMobilePhone() <<"\n"<<mmbr->getEmail()<<"\n"<<currentDate<<"\n"<<retDate<<"\n";                }
                else{
                    out<<mmbr->getUserName() <<"\n" << mmbr->getPassword() <<"\n"<<mmbr->getName() <<"\n" <<mmbr->getMembershipNumber() <<"\n" <<mmbr->getFatherName() <<"\n"<<mmbr->getNationalityCode() <<"\n"<<mmbr->getBirthday() <<"\n" <<mmbr->getMobilePhone() <<"\n"<<mmbr->getEmail()<<"\n"<<mmbr->getBorrowingDate()<<"\n"<<mmbr->getReturnDate()<<"\n";
                }
                counter=1;
            }
            }
        f1.close();
        f2.close();
           QFile fR("membersTmp.txt");
           QFile fW("members.txt");
           fR.open(QFile::ReadOnly|QFile::Text);
           QTextStream inp(&fR);
           fW.open(QFile::WriteOnly|QFile::Text);
           QTextStream outText(&fW);
           while(!inp.atEnd() ){
               if(counter ==1){
                  mmbr->setUserName(inp.readLine());
                   counter++;
               }
               else if(counter ==2){
                  mmbr->setPassword(inp.readLine());
                   counter++;
               }
               else if(counter ==3){
                 mmbr->setName(inp.readLine());
                   counter++;
               }
               else if(counter ==4){
                 mmbr->setMembershipNumber(inp.readLine());
                   counter++;
               }
               else if(counter ==5){
                 mmbr->setFatherName(inp.readLine());
                 counter++;
                  }
               else if(counter ==6){
                 mmbr->setNationalityCode(inp.readLine());
                   counter++;
               }
               else if(counter ==7){
                 mmbr->setBirthday(inp.readLine());
               counter++;
               }

               else if(counter ==8){
                 mmbr->setMobilePhone(inp.readLine().toLongLong());
                 counter++;
                  }
               else if(counter ==9){
                   mmbr->setEmail(inp.readLine());
                   counter++;
               }
               else if(counter==10){
                   mmbr->setBorrowingDate(inp.readLine());
                   counter++;
               }
               else if(counter==11){
                   mmbr->setReturnDate(inp.readLine());
                   outText<<mmbr->getUserName() <<"\n" << mmbr->getPassword() <<"\n"<<mmbr->getName() <<"\n" <<mmbr->getMembershipNumber() <<"\n" <<mmbr->getFatherName() <<"\n"<<mmbr->getNationalityCode() <<"\n"<<mmbr->getBirthday() <<"\n" <<mmbr->getMobilePhone() <<"\n"<<mmbr->getEmail()<<"\n"<<mmbr->getBorrowingDate()<<"\n"<<mmbr->getReturnDate()<<"\n";;
                   counter=1;
               }
           }
           fW.close();
           fR.close();

            //-------------------------------------
           if(this->countOfBook <=4){
               if(countOfBook==0){
                   ui->tableBooks->clearContents();
                   ui->tableBooks->setRowCount(0);
               }
               QString bookId = ui->bookId->text();
               if(!bookId.isEmpty()){
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
                           if(book.getBookId() == bookId){
                                book.setBorrowStatus(true);
                                book.setBorrowsMemberShipNumber(this->m[0]);
                                this->countOfBook++;
                                out<< book.getBookId() <<"\n" << book.getName() <<"\n" << book.getWriter() <<"\n" << book.getPublisher() <<"\n" << book.getTranslater() <<"\n" << book.getPrintYear() <<"\n" << book.getBorrowStatus() <<"\n"<< book.getBorrowsMemberShipNumber() <<"\n"<< book.getGenre() <<"\n"<< book.getTheAgeRange() <<"\n";
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
                   counter=1;
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
               }else{
                   QMessageBox::critical(this,"فیلد خالی","آیدی کتاب وارد نشده است");
               }
           }else{
               QMessageBox::critical(this,"تعداد بیش از حد مجاز","تعداد کتاب ها باید حداکثر 4 عدد باشد");
           }
    }else{
         QMessageBox::critical(this,"فیلد خالی","کدملی را وارد کنید");
    }
}


void LendingBook::on_back_clicked()
{
    this->hide();
}

