#include "Member.h"
#include "ui_Member.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "PrintMemberCard.h"
#include "ListOfBorrowedBooks.h"
#include "About.h"
#include "Login.h"
#include "ChangePassword.h"
#include <QCloseEvent>
Member::Member(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Member)
{
    ui->setupUi(this);

}

Member::~Member()
{
    delete ui;
}

void Member::changePassword(QString userName, QString newPass)
{

    int counter=1 ;
    QFile f1("members.txt");
    QFile f2("membersTmp.txt");
    f1.open(QFile::ReadOnly|QFile::Text);
    QTextStream in(&f1);
    f2.open(QFile::WriteOnly|QFile::Text);
    QTextStream out(&f2);
    while(!in.atEnd() ){
        if(counter ==1){
           this->setUserName(in.readLine());
            counter++;
        }
        else if(counter ==2){
           this->setPassword(in.readLine());
            counter++;
        }
        else if(counter ==3){
          this->setName(in.readLine());
            counter++;
        }
        else if(counter ==4){
          this->setMembershipNumber(in.readLine());
            counter++;
        }
        else if(counter ==5){
          this->setFatherName(in.readLine());
          counter++;
           }
        else if(counter ==6){
          this->setNationalityCode(in.readLine());
            counter++;
        }
        else if(counter ==7){
          this->setBirthday(in.readLine());
        counter++;
        }

        else if(counter ==8){
          this->setMobilePhone(in.readLine().toLongLong());
          counter++;
           }
        else if(counter ==9){
            this->setEmail(in.readLine());
            counter++;
        }
        else if(counter==10){
            this->setBorrowingDate(in.readLine());
            counter++;
        }
        else if(counter==11){
            this->setReturnDate(in.readLine());
            if(this->getUserName() == userName){
                this->setPassword(newPass);
                out<<this->getUserName() <<"\n" << this->getPassword() <<"\n"<<this->getName() <<"\n" <<this->getMembershipNumber() <<"\n" <<this->getFatherName() <<"\n"<<this->getNationalityCode() <<"\n"<<this->getBirthday() <<"\n" <<this->getMobilePhone() <<"\n"<<this->getEmail()<<"\n"<<this->getBorrowingDate()<<"\n"<<this->getReturnDate()<<"\n";;
            }
            else{
                out<<this->getUserName() <<"\n" << this->getPassword() <<"\n"<<this->getName() <<"\n" <<this->getMembershipNumber() <<"\n" <<this->getFatherName() <<"\n"<<this->getNationalityCode() <<"\n"<<this->getBirthday() <<"\n" <<this->getMobilePhone() <<"\n"<<this->getEmail()<<"\n"<<this->getBorrowingDate()<<"\n"<<this->getReturnDate()<<"\n";;
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
              this->setUserName(inp.readLine());
               counter++;
           }
           else if(counter ==2){
              this->setPassword(inp.readLine());
               counter++;
           }
           else if(counter ==3){
             this->setName(inp.readLine());
               counter++;
           }
           else if(counter ==4){
             this->setMembershipNumber(inp.readLine());
               counter++;
           }
           else if(counter ==5){
             this->setFatherName(inp.readLine());
             counter++;
              }
           else if(counter ==6){
             this->setNationalityCode(inp.readLine());
               counter++;
           }
           else if(counter ==7){
             this->setBirthday(inp.readLine());
           counter++;
           }

           else if(counter ==8){
             this->setMobilePhone(inp.readLine().toLongLong());
             counter++;
              }
           else if(counter ==9){
               this->setEmail(inp.readLine());
               counter++;
           }
           else if(counter==10){
               this->setBorrowingDate(inp.readLine());
               counter++;
           }
           else if(counter==11){
               this->setReturnDate(inp.readLine());
               outText<<this->getUserName() <<"\n" << this->getPassword() <<"\n"<<this->getName() <<"\n" <<this->getMembershipNumber() <<"\n" <<this->getFatherName() <<"\n"<<this->getNationalityCode() <<"\n"<<this->getBirthday() <<"\n" <<this->getMobilePhone() <<"\n"<<this->getEmail()<<"\n"<<this->getBorrowingDate()<<"\n"<<this->getReturnDate()<<"\n";;
               counter=1;
           }
       }
       fW.close();
       fR.close();

}

void Member::writeinMemberFile(QString name, QString fatherName, QString nationalityCode, QString birthday, long long mobilePhone, QString email)
{
    this->setName(name);
    this->setFatherName(fatherName);
    this->setNationalityCode(nationalityCode);
    this->setBirthday(birthday);
    this->setMobilePhone(mobilePhone);
    this->setEmail(email);
    this->setBorrowingDate("");
    this->setReturnDate("");
    QString tmp = nationalityCode+"-" + this->mmbrSize();
    this->setMembershipNumber(tmp);
    this->setUserName(tmp);
    this->setPassword(nationalityCode);
    QFile f("members.txt");
    f.open(QFile::WriteOnly|QFile::Append);
    QTextStream out(&f);
    out << this->getUserName()<<"\n"<<this->getPassword()<<"\n"<<this->name <<"\n"<<this->membershipNumber <<"\n" <<this->fatherName<<"\n"<<this->nationalityCode<<"\n"<<this->birthday<<"\n"<<this->mobilePhone<<"\n"<<this->email <<"\n" <<this->borrowingDate<<"\n"<<this->returnDate<<"\n";
    f.close();
}

const QString &Member::getMembershipNumber() const
{
    return membershipNumber;
}

void Member::setMembershipNumber(const QString &newMembershipNumber)
{
    membershipNumber = newMembershipNumber;
}

QString Member::mmbrSize()
{
    int counter =1 , size=1;
       QFile f2("members.txt");
       f2.open(QFile::ReadOnly | QFile::Text);
           QTextStream in(&f2);
           while(!in.atEnd() ){
               if(counter ==1){
                  this->setUserName(in.readLine());
                   counter++;
               }
               else if(counter ==2){
                  this->setPassword(in.readLine());
                   counter++;
               }
               else if(counter ==3){
                 this->setName(in.readLine());
                   counter++;
               }
               else if(counter ==4){
                 this->setMembershipNumber(in.readLine());
                   counter++;
               }
               else if(counter ==5){
                 this->setFatherName(in.readLine());
                 counter++;
                  }
               else if(counter ==6){
                 this->setNationalityCode(in.readLine());
                   counter++;
               }
               else if(counter ==7){
                 this->setBirthday(in.readLine());
               counter++;
               }

               else if(counter ==8){
                 this->setMobilePhone(in.readLine().toLongLong());
                 counter++;
                  }
               else if(counter ==9){
                   this->setEmail(in.readLine());
                   counter++;
               }
               else if(counter==10){
                   this->setBorrowingDate(in.readLine());
                   counter++;
               }
               else if(counter==11){
                   this->setReturnDate(in.readLine());
                   size++;
                   counter=1;
               }
               }
           f2.close();
           return QString::number(size);
}

const QString &Member::getName() const
{
    return name;
}

void Member::setName(const QString &newName)
{
    name = newName;
}

const QString &Member::getFatherName() const
{
    return fatherName;
}

void Member::setFatherName(const QString &newFatherName)
{
    fatherName = newFatherName;
}

const QString &Member::getNationalityCode() const
{
    return nationalityCode;
}

void Member::setNationalityCode(const QString &newNationalityCode)
{
    nationalityCode = newNationalityCode;
}

const QString &Member::getBirthday() const
{
    return birthday;
}

void Member::setBirthday(const QString &newBirthday)
{
    birthday = newBirthday;
}

long long Member::getMobilePhone() const
{
    return mobilePhone;
}

void Member::setMobilePhone(long long newMobilePhone)
{
    mobilePhone = newMobilePhone;
}

const QString &Member::getEmail() const
{
    return email;
}

void Member::setEmail(const QString &newEmail)
{
    email = newEmail;
}

const QString &Member::getBorrowingDate() const
{
    return borrowingDate;
}

void Member::setBorrowingDate(const QString &newBorrowingDate)
{
    borrowingDate = newBorrowingDate;
}

const QString &Member::getReturnDate() const
{
    return returnDate;
}

void Member::setReturnDate(const QString &newReturnDate)
{
    returnDate = newReturnDate;
}

void Member::reject()
{
    if(QMessageBox::Yes == QMessageBox::question(this,"خروج","آیا میخواهید برنامه را ببندید؟؟؟",QMessageBox::Yes | QMessageBox::No)){
        this->close();
    }
}

void Member::on_printlibrarycard_clicked()
{
    PrintMemberCard* pmc = new PrintMemberCard(this);
    pmc->exec();
}


void Member::on_listBorrowedBooks_clicked()
{
    ListOfBorrowedBooks* l = new ListOfBorrowedBooks(this);
    l->exec();
}


void Member::on_action_triggered()
{
    About* a = new About();
    a->exec();
}


void Member::on_action_3_triggered()
{
    this->hide();
    Login * l =new Login();
    l->exec();
}


void Member::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButtons btn =QMessageBox::question(this,"خروج","آیا میخواهید برنامه را ببندید؟؟؟",QMessageBox::Yes | QMessageBox::No);
    if(QMessageBox::Yes == btn){
        event->accept();
    }
    else{
        event->ignore();
    }
}


void Member::on_changePassword_clicked()
{
    ChangePassword * cp = new ChangePassword(this->getUserName());
    cp->exec();
}

