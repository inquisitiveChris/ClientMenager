
QT	+= widgets
requires(qtConfig(listview))

SOURCES   =
    adddialog.cpp \
    addresswidget.cpp \
    cypher.cpp \
    main.cpp \
    mainwindow.cpp \
    newaddresstab.cpp \
    oknologowania.cpp \
    policywidget.cpp \
    simplecrypt.cpp \
    tablemodel.cpp

HEADERS   =
    adddialog.h \
    addresswidget.h \
    cypher.h \
    mainwindow.h \
    newaddresstab.h \
    oknologowania.h \
    policywidget.h \
    simplecrypt.h \
    tablemodel.h

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/addressbook
INSTALLS += target

DISTFILES += \
    loginwindowUI.txt \
    addressbook.pro.user \
    .gitattributes \
    .gitignore \
    LICENSE

SUBDIRS += \
    addressbook.pro \
    Krzysztof_qt_5_12_2.pro

FORMS += \
    oknologowania.ui
