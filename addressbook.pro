
QT += widgets
requires(qtConfig(listview))

SOURCES   = adddialog.cpp \
            addresswidget.cpp \
            main.cpp \
            mainwindow.cpp \
            tablemodel.cpp \
            policywidget.cpp \
            policytablemodel.cpp \
            addpolicydialog.cpp \
            loginwindow.cpp

HEADERS   = adddialog.h \
            addresswidget.h \
            mainwindow.h \
            tablemodel.h \
            policywidget.h \
            policytablemodel.h \
            addpolicydialog.h \
            loginwindow.h

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/addressbook
INSTALLS += target

DISTFILES += \
    loginwindowUI.txt
