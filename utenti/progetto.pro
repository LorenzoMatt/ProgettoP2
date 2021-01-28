######################################################################
# Automatically generated by qmake (3.1) Sun Dec 20 15:06:11 2020
######################################################################

TEMPLATE = app
TARGET = utenti
INCLUDEPATH += .
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
QT += xml
#DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += accesso.h \
    bottonevedicommento.h \
    database.h \
           commento.h \
           container.h \
    controller.h \
           deepptr.h \
           domanda.h \
    log.h \
           profilo.h \
           utente.h \
    basic.h \
    pagamento.h \
    gold.h \
    premium.h \
    account.h \
    widgetcampodati.h \
    creautente.h \
    vistacercautente.h \
    finestranuovadomanda.h \
    funzioniutili.h \
    finestravistadomande.h \
    finestraamiciseguaci.h \
    vistadomanda.h \
    amicononpresente.h \
    controlleradmin.h \
    nonautoredomanda.h \
    puntinonsufficienti.h \
    utentegiapresente.h \
    vistaamministratore.h \
    vistaprofilo.h \
    vistautente.h
FORMS +=
SOURCES += accesso.cpp \
    bottonevedicommento.cpp \
           commento.cpp \
    controller.cpp \
           domanda.cpp \
    log.cpp \
           main.cpp \
           profilo.cpp \
           utente.cpp \
    basic.cpp \
    pagamento.cpp \
    gold.cpp \
    premium.cpp \
    account.cpp \
    widgetcampodati.cpp \
    creautente.cpp \
    database.cpp \
    vistacercautente.cpp \
    finestranuovadomanda.cpp \
    finestravistadomande.cpp \
    funzioniutili.cpp \
    finestraamiciseguaci.cpp \
    amicononpresente.cpp \
    controlleradmin.cpp \
    nonautoredomanda.cpp \
    puntinonsufficienti.cpp \
    utentegiapresente.cpp \
    vistaamministratore.cpp \
    vistadomanda.cpp \
    vistaprofilo.cpp \
    vistautente.cpp

RESOURCES +=
