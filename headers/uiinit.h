// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#ifndef UIINIT_H
#define UIINIT_H


#include "ui_mainwindow.h"
#include "coloricondrawer.h"
#include "constantsandstrings.h"
#include "ui_mainwindow.h"
#include "delegator.h"
#include "plotparameters.h"

//Функция-инициализации интерфейса и полей

void setupUiFields(Ui::MainWindow* ui);
void setUiButtonsGroups(Ui::MainWindow* ui);
void setUiColorLabels(Ui::MainWindow* ui, qreal devPixRat);
void imageInit(Ui::MainWindow* ui, qreal devPixRat);

#endif // UIINIT_H
