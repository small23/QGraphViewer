#pragma once

#if !defined(CONSTANTSANDSTRINGS_H)
#define CONSTANTSANDSTRINGS_H 1

#include "QObject"
//Defines area
#define GRAPH_SCALE  600

//Strings area

const QString STR_ErrorTitle_ParsingError = QObject::tr("Ошибка парсинга");
const QString STR_ErrorTitle_SaveError = QObject::tr("Ошибка сохранения");
const QString STR_ErrorTitle_LoadingError = QObject::tr("Ошибка загрузки");
const QString STR_ErrorTitle_AddingError = QObject::tr("Ошибка добавления");
const QString STR_ErrorTitle_ProcessingError = QObject::tr("Ошибка обработки");

const QString STR_ErrorMessage_NoFilesToDraw = QObject::tr("Не указан ни один файл для построения!");
const QString STR_ErrorMessage_NoFileToDraw = QObject::tr("Не указан файл построения!");
const QString STR_ErrorMessage_NoDatafiles = QObject::tr("Не указаны файлы с данными для построения!");
const QString STR_ErrorMessage_NoOutpFileWithTransMatrix = QObject::tr("Не указан файл *.outp, Molgrath/Trajgrad/P2dcrynp не будут построены!");
const QString STR_ErrorMessage_CorruptDataOutp = QObject::tr("В файле .outp отсутствуют необходимые данные или файл поврежден!");
const QString STR_ErrorMessage_CorruptDataTrajgrad = QObject::tr("В файле Trajgrad.dat отсутствуют необходимые данные или файл поврежден!");
const QString STR_ErrorMessage_CorruptDataMolgraph = QObject::tr("В файле Molgrapf.dat отсутствуют необходимые данные или файл поврежден!");
const QString STR_ErrorMessage_CorruptDataMolgraph2 = QObject::tr("В файле Molgrapf.dat отсутствуют необходимые данные или файл поврежден!");
const QString STR_ErrorMessage_NoOutpFileWithTransMatrixStopDraw = QObject::tr("Не указан файл *.outp!");
const QString STR_ErrorMessage_CantOpenFileForWrite= QObject::tr("'%1' не удается открыть для записи!");
const QString STR_ErrorMessage_NoNecessaryDataInFile = QObject::tr("В предоставленном файле отсутствуют необходимые данные или файл поврежден!");
const QString STR_ErrorMessage_NonStandartNameMessage = QObject::tr("Файл '%1' имеет нестандартное имя и не будет добавлен.");
const QString STR_ErrorMessage_ImageSavingError = QObject::tr("Не удалось сохранить изображение!");
const QString STR_ErrorMessage_NoAtomsError = QObject::tr("Атомы не найдены! Проверьте правильность ввода информации.");
const QString STR_ErrorMessage_NoDataForSave = QObject::tr("Нет данных для сохранения!");

const QString STR_MessageBoxTitle_DataProcessed = QObject::tr("Данные обработаны");
const QString STR_MessageBoxMessage_DataProcessedAndSaved = QObject::tr("Данные обработаны и сохранены!");

const QString STR_Dialog_OpenFile= QObject::tr("Открыть файл...");
const QString STR_Dialog_SaveFile = QObject::tr("Сохранить файл как...");

const QString STR_Window_Changelog = QObject::tr("Список изменений");
const QString STR_Window_Settings = QObject::tr("Настройки");
const QString STR_Window_Help = QObject::tr("Help");

const QString STR_GraphTitle_ZoneStruct= QObject::tr("Зонная структура");
const QString STR_GraphTitle_PlotDefaultName= QObject::tr("График");
const QString STR_GraphTitle_PlotDefaultNameZoneStruct = QObject::tr("График");
const QString STR_GraphTitle_PlotRo = QObject::tr("Ro");
const QString STR_GraphTitle_PlotRoDef = QObject::tr("RoDef");
const QString STR_GraphTitle_PlotSpin = QObject::tr("Spin");
const QString STR_GraphTitle_PlotSpinDef = QObject::tr("SpinDef");

const QString STR_XLSX_AtomNumber = QObject::tr("№ атома");
const QString STR_XLSX_Atom = QObject::tr("Атом");
const QString STR_XLSX_Type= QObject::tr("Тип");
const QString STR_XLSX_FunctionNumber = QObject::tr("Число ф-й");
const QString STR_XLSX_BaseFunctionNumber = QObject::tr("Номера баз. ф-й");
const QString STR_XLSX_StartNumber = QObject::tr("N нач.");
const QString STR_XLSX_EndNumber = QObject::tr("N кон.");

const QString STR_XLSX_Short_SourceAtomNumber = QObject::tr("№ исх. ат.");
const QString STR_XLSX_Short_AtomNumber = QObject::tr("№ ат. в элм. яч.");

const QString STR_XLSX_Extended_SourceAtomNumber = QObject::tr("№ Исходного атома");
const QString STR_XLSX_Extended_AtomNumber = QObject::tr("№ Атома в эл. яч.");
const QString STR_XLSX_Extended_N1 = QObject::tr("n1");
const QString STR_XLSX_Extended_N2 = QObject::tr("n2");
const QString STR_XLSX_Extended_N3 = QObject::tr("n3");

const QString STR_UI_LineTypes_Solid = QObject::tr("Сплошная");
const QString STR_UI_LineTypes_Dash = QObject::tr("Тире");
const QString STR_UI_LineTypes_Pointed = QObject::tr("Точка");
const QString STR_UI_LineTypes_PointDash = QObject::tr("Точка-тире");

const QString STR_UI_PointTypes_Cirq = QObject::tr("Круг");
const QString STR_UI_PointTypes_Plus = QObject::tr("Плюс");
const QString STR_UI_PointTypes_Star = QObject::tr("Звездочка");
const QString STR_UI_PointTypes_Point = QObject::tr("Точка");
const QString STR_UI_PointTypes_X = QObject::tr("Перекрестие");
const QString STR_UI_PointTypes_Square = QObject::tr("Квадрат");
const QString STR_UI_PointTypes_Diamond = QObject::tr("Ромб");
const QString STR_UI_PointTypes_TriangUp = QObject::tr("Верхнеор. треугольник");
const QString STR_UI_PointTypes_TriangDown = QObject::tr("Нижнеор. треугольник");

const QString STR_UI_RotateTypes_None = QObject::tr("Нет");
const QString STR_UI_RotateTypes_Clockwise = QObject::tr("По часовой");
const QString STR_UI_RotateTypes_Counter_Clockwise = QObject::tr("Против часовой");

const QString STR_Graph_SaveGraph = QObject::tr("Сохранить график");
const QString STR_Graph_Settings= QObject::tr("Настройки");

const QString STR_LicenseTitle= QObject::tr("Лицензионное соглашение");
const QString STR_Licence = QObject::tr("Лицензия MIT\n\nCopyright © 2020 КемГУ\n\nДанная лицензия разрешает лицам, получившим копию данного программного"
		" обеспечения и сопутствующей документации (в дальнейшем именуемыми «Программное Обеспечение»), безвозмездно"
		" использовать Программное Обеспечение без ограничений, включая неограниченное право на использование, копирование,"
		" изменение, слияние, публикацию, распространение, сублицензирование и/или продажу копий Программного Обеспечения, "
		"а также лицам, которым предоставляется данное Программное Обеспечение, при соблюдении следующих условий:\n\n"
		"Указанное выше уведомление об авторском праве и данные условия должны быть включены во все копии или значимые "
		"части данного Программного Обеспечения.\n\nДАННОЕ ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ ПРЕДОСТАВЛЯЕТСЯ «КАК ЕСТЬ», БЕЗ КАКИХ-ЛИБО"
		" ГАРАНТИЙ, ЯВНО ВЫРАЖЕННЫХ ИЛИ ПОДРАЗУМЕВАЕМЫХ, ВКЛЮЧАЯ ГАРАНТИИ ТОВАРНОЙ ПРИГОДНОСТИ, СООТВЕТСТВИЯ ПО ЕГО КОНКРЕТНОМУ "
		"НАЗНАЧЕНИЮ И ОТСУТСТВИЯ НАРУШЕНИЙ, НО НЕ ОГРАНИЧИВАЯСЬ ИМИ. НИ В КАКОМ СЛУЧАЕ АВТОРЫ ИЛИ ПРАВООБЛАДАТЕЛИ НЕ НЕСУТ "
        "ОТВЕТСТВЕННОСТИ ПО КАКИМ-ЛИБО ИСКАМ, ЗА УЩЕРБ ИЛИ ПО ИНЫМ ТРЕБОВАНИЯМ, В ТОМ ЧИСЛЕ, ПРИ ДЕЙСТВИИ КОНТРАКТА, ДЕЛИКТЕ "
	"ИЛИ ИНОЙ СИТУАЦИИ, ВОЗНИКШИМ ИЗ-ЗА ИСПОЛЬЗОВАНИЯ ПРОГРАММНОГО ОБЕСПЕЧЕНИЯ ИЛИ ИНЫХ ДЕЙСТВИЙ С ПРОГРАММНЫМ ОБЕСПЕЧЕНИЕМ.");

const QString STR_BuildDate = QObject::tr("Дата сборки: %1, %2");

#endif // GRAPHBUILDER_H
