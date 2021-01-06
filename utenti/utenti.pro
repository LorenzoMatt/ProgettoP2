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
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += accesso.h \
           amico_non_presente.h \
    bottonevedicommento.h \
    database.h \
           commento.h \
           container.h \
    controller.h \
           deepptr.h \
           domanda.h \
    log.h \
           non_autore_domanda.h \
           profilo.h \
           togliere_te_stesso_dagli_amici.h \
           utente.h \
    utente_gia_presente.h \
    basic.h \
    pagamento.h \
    gold.h \
    punti_non_sufficienti.h \
    premium.h \
    account.h \
    vista_domanda.h \
    vista_utente.h \
    widgetcampodati.h \
    creautente.h \
    vista_amministratore.h \
    controller_admin.h \
    funzioni_globali.h \
    vistacercautente.h \
    vista_profilo.h \
    finestranuovadomanda.h \
    funzioniutili.h \
    finestravistadomande.h
FORMS += \
    finestravistadomande.ui
SOURCES += accesso.cpp \
           amico_non_presente.cpp \
    bottonevedicommento.cpp \
           commento.cpp \
    controller.cpp \
           domanda.cpp \
    log.cpp \
           main.cpp \
           non_autore_domanda.cpp \
           profilo.cpp \
           utente.cpp \
    utente_gia_presente.cpp \
    basic.cpp \
    pagamento.cpp \
    gold.cpp \
    punti_non_sufficienti.cpp \
    premium.cpp \
    account.cpp \
    vista_domanda.cpp \
    widgetcampodati.cpp \
    vista_utente.cpp \
    creautente.cpp \
    database.cpp \
    vista_amministratore.cpp \
    controller_admin.cpp \
    vistacercautente.cpp \
    vista_profilo.cpp \
    finestranuovadomanda.cpp \
    finestravistadomande.cpp

RESOURCES +=
