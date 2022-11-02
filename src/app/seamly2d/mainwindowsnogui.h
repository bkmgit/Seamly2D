/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2017  Seamly, LLC                                       *
 *                                                                         *
 *   https://github.com/fashionfreedom/seamly2d                            *
 *                                                                         *
 ***************************************************************************
 **
 **  Seamly2D is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  Seamly2D is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with Seamly2D.  If not, see <http://www.gnu.org/licenses/>.
 **
 **************************************************************************

 ************************************************************************
 **
 **  @file   mainwindowsnogui.h
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   12 5, 2015
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Valentine project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2015 Seamly2D project
 **  <https://github.com/fashionfreedom/seamly2d> All Rights Reserved.
 **
 **  Seamly2D is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  Seamly2D is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with Seamly2D.  If not, see <http://www.gnu.org/licenses/>.
 **
 *************************************************************************/

#ifndef MAINWINDOWSNOGUI_H
#define MAINWINDOWSNOGUI_H

#include <QMainWindow>
#include <QPrinter>
#include <QToolButton>

#include "../vlayout/vlayoutpiece.h"
#include "xml/vpattern.h"
#include "dialogs/export_layout_dialog.h"
#include "../vlayout/vlayoutgenerator.h"
#include "../vwidgets/vabstractmainwindow.h"

class QGraphicsScene;
struct PosterData;
class QGraphicsRectItem;

class MainWindowsNoGUI : public VAbstractMainWindow
{
    Q_OBJECT
public:
    explicit MainWindowsNoGUI(QWidget *parent = nullptr);
    virtual ~MainWindowsNoGUI() Q_DECL_OVERRIDE;

public slots:
    void toolLayoutSettings(QToolButton *tButton, bool checked);
    void PrintPreviewOrigin();
    void PrintPreviewTiled();
    void PrintOrigin();
    void PrintTiled();
    void RefreshDetailsLabel();
    void refreshGrainLines();
    void refreshSeamAllowances();    
    void exportSVG(const QString &name, QGraphicsRectItem *paper, QGraphicsScene *scene)const;
    void exportPNG(const QString &name, QGraphicsScene *scene)const;
    void exportTIF(const QString &name, QGraphicsScene *scene)const;
    void exportJPG(const QString &name, QGraphicsScene *scene)const;
    void exportBMP(const QString &name, QGraphicsScene *scene)const;
    void exportPPM(const QString &name, QGraphicsScene *scene)const;
    void exportPDF(const QString &name, QGraphicsRectItem *paper, QGraphicsScene *scene, bool ignoreMargins,
                 const QMarginsF &margins)const;
    void exportEPS(const QString &name, QGraphicsRectItem *paper, QGraphicsScene *scene, bool ignoreMargins,
                 const QMarginsF &margins)const;
    void exportPS(const QString &name, QGraphicsRectItem *paper, QGraphicsScene *scene, bool ignoreMargins,
                const QMarginsF &margins)const;

protected:
    QVector<VLayoutPiece> listDetails;

    /** @brief currentScene pointer to current scene. */
    QGraphicsScene *currentScene;

    QGraphicsScene *tempSceneLayout;

    /** @brief pattern container with data (points, arcs, splines, spline paths, variables) */
    VContainer         *pattern;

    /** @brief doc dom document container */
    VPattern           *doc;

    QList<QGraphicsItem *> papers;
    QList<QGraphicsItem *> shadows;
    QList<QGraphicsScene *> scenes;
    QList<QList<QGraphicsItem *> > details;

    QVector<QVector<VLayoutPiece> > detailsOnLayout;

    QAction *undoAction;
    QAction *redoAction;
    QAction *actionDockWidgetToolOptions;
    QAction *actionDockWidgetGroups;
    QAction *actionDockWidgetLayouts;
    QAction *actionDockWidgetToolbox;

    bool isNoScaling;
    bool isLayoutStale;
    bool ignoreMargins;
    QMarginsF margins;
    QSizeF paperSize;

    static QVector<VLayoutPiece> PrepareDetailsForLayout(const QHash<quint32, VPiece> &details);

    void ExportData(const QVector<VLayoutPiece> &listDetails, const ExportLayoutDialog &dialog);

    void InitTempLayoutScene();
    virtual void CleanLayout()=0;
    virtual void PrepareSceneList()=0;
    QIcon ScenePreview(int i) const;
    bool LayoutSettings(VLayoutGenerator& lGenerator);
    int ContinueIfLayoutStale();
    QString FileName() const;
    void SetSizeHeightForIndividualM() const;
private slots:
    void PrintPages (QPrinter *printer);
    void ErrorConsoleMode(const LayoutErrors &state);
private:
    Q_DISABLE_COPY(MainWindowsNoGUI)

    bool isTiled;
    bool isAutoCrop;
    bool isUnitePages;

    QString layoutPrinterName;

    static QList<QGraphicsItem *> CreateShadows(const QList<QGraphicsItem *> &papers);
    static QList<QGraphicsScene *> CreateScenes(const QList<QGraphicsItem *> &papers,
                                                const QList<QGraphicsItem *> &shadows,
                                                const QList<QList<QGraphicsItem *> > &details);



    void PdfTiledFile(const QString &name);

    void convertPdfToPs(const QStringList &params)const;
    void ObjFile(const QString &name, QGraphicsRectItem *paper, QGraphicsScene *scene)const;
    void FlatDxfFile(const QString &name, int version, bool binary, QGraphicsRectItem *paper, QGraphicsScene *scene,
                 const QList<QList<QGraphicsItem *> > &details)const;
    void AAMADxfFile(const QString &name, int version, bool binary, const QSize &size,
                     const QVector<VLayoutPiece> &details) const;

    void PreparePaper(int index) const;
    void RestorePaper(int index) const;

    void PrepareTextForDXF(const QString &placeholder, const QList<QList<QGraphicsItem *> > &details) const;
    void RestoreTextAfterDXF(const QString &placeholder, const QList<QList<QGraphicsItem *> > &details) const;

    void PrintPreview();
    void LayoutPrint();

    enum class PrintType : char {PrintPDF, PrintPreview, PrintNative};

    void SetPrinterSettings(QPrinter *printer, const PrintType &printType);
    bool IsLayoutGrayscale() const;
    QPageSize FindQPrinterPageSize(const QSizeF &size) const;

    bool isPagesUniform() const;
    bool IsPagesFit(const QSizeF &printPaper) const;

    void ExportScene(const ExportLayoutDialog &dialog,
                     const QList<QGraphicsScene *> &scenes,
                     const QList<QGraphicsItem *> &papers,
                     const QList<QGraphicsItem *> &shadows,
                     const QList<QList<QGraphicsItem *> > &details,
                     bool ignoreMargins, const QMarginsF &margins) const;

    void ExportApparelLayout(const ExportLayoutDialog &dialog, const QVector<VLayoutPiece> &details, const QString &name,
                             const QSize &size) const;

    void ExportDetailsAsApparelLayout(const ExportLayoutDialog &dialog, QVector<VLayoutPiece> listDetails);

    void ExportFlatLayout(const ExportLayoutDialog &dialog,
                          const QList<QGraphicsScene *> &scenes,
                          const QList<QGraphicsItem *> &papers,
                          const QList<QGraphicsItem *> &shadows,
                          const QList<QList<QGraphicsItem *> > &details,
                          bool ignoreMargins, const QMarginsF &margins);

    void ExportDetailsAsFlatLayout(const ExportLayoutDialog &dialog, const QVector<VLayoutPiece> &listDetails);
};

#endif // MAINWINDOWSNOGUI_H
