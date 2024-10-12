QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    About.cpp \
    AddAdmin.cpp \
    AddBook.cpp \
    AddMember.cpp \
    Admin.cpp \
    Book.cpp \
    ChangePassword.cpp \
    DeleteAdmin.cpp \
    DeleteBook.cpp \
    DeleteMember.cpp \
    EditAdmin.cpp \
    EditBook.cpp \
    EditMember.cpp \
    ForgetPassword.cpp \
    LendingBook.cpp \
    LibraryManager.cpp \
    ListOfBorrowedBooks.cpp \
    Member.cpp \
    PrintAdminCard.cpp \
    PrintMemberCard.cpp \
    SearchAdmin.cpp \
    SearchBook.cpp \
    SearchMember.cpp \
    ShowAllAdmin.cpp \
    ShowAllBooks.cpp \
    User.cpp \
    main.cpp \
    Login.cpp \
    showallmember.cpp

HEADERS += \
    About.h \
    AddAdmin.h \
    AddBook.h \
    AddMember.h \
    Admin.h \
    Book.h \
    ChangePassword.h \
    DeleteAdmin.h \
    DeleteBook.h \
    DeleteMember.h \
    EditAdmin.h \
    EditBook.h \
    EditMember.h \
    ForgetPassword.h \
    LendingBook.h \
    LibraryManager.h \
    ListOfBorrowedBooks.h \
    Login.h \
    Member.h \
    PrintAdminCard.h \
    PrintMemberCard.h \
    SearchAdmin.h \
    SearchBook.h \
    SearchMember.h \
    ShowAllAdmin.h \
    ShowAllBooks.h \
    ShowAllMember.h \
    User.h

FORMS += \
    About.ui \
    AddAdmin.ui \
    AddBook.ui \
    AddMember.ui \
    Admin.ui \
    ChangePassword.ui \
    DeleteAdmin.ui \
    DeleteBook.ui \
    DeleteMember.ui \
    EditAdmin.ui \
    EditBook.ui \
    EditMember.ui \
    ForgetPassword.ui \
    LendingBook.ui \
    LibraryManager.ui \
    ListOfBorrowedBooks.ui \
    Login.ui \
    Member.ui \
    PrintAdminCard.ui \
    PrintMemberCard.ui \
    SearchAdmin.ui \
    SearchBook.ui \
    SearchMember.ui \
    ShowAllAdmin.ui \
    ShowAllBooks.ui \
    ShowAllMember.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
