QT += widgets
requires(qtConfig(listview))

SOURCES   = adddialog.cpp \
            addresswidget.cpp \
            main.cpp \
            mainwindow.cpp \
            newaddresstab.cpp \
            tablemodel.cpp \
            policywidget.cpp \
    loginwindow.cpp
HEADERS   = adddialog.h \
            addresswidget.h \
            mainwindow.h \
            newaddresstab.h \
            tablemodel.h \
            policywidget.h \
    loginwindow.h

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/addressbook
INSTALLS += target

DISTFILES += \
    loginwindowUI.txt
