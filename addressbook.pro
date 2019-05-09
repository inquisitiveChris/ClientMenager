
QT	+= widgets
requires(qtConfig(listview))

SOURCES   = \
    adddialog.cpp \
    addpolicydialog.cpp \
    addresswidget.cpp \
    cypher.cpp \
    main.cpp \
    mainwindow.cpp \
    newaddresstab.cpp \
    newpolicytab.cpp \
    oknologowania.cpp \
    policytablemodel.cpp \
    policywidget.cpp \
    simplecrypt.cpp \
    tablemodel.cpp


HEADERS   = \
    adddialog.h \
    addpolicydialog.h \
    addresswidget.h \
    cypher.h \
    mainwindow.h \
    newaddresstab.h \
    newpolicytab.h \
    oknologowania.h \
    policytablemodel.h \
    policywidget.h \
    simplecrypt.h \
    tablemodel.h

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/addressbook
INSTALLS += target

DISTFILES += \
    addressbook.pro.user \
    LICENSE \
    addressbook.pro.user \
    addressbook.pro.user.5f82d55 \
    LICENSE

SUBDIRS += \
    addressbook.pro \
    Krzysztof_qt_5_12_2.pro \

FORMS += \
    oknologowania.ui

RESOURCES += \
    resource.qrc
