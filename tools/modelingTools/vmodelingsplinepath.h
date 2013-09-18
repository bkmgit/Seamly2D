/****************************************************************************
 **
 **  Copyright (C) 2013 Valentina project All Rights Reserved.
 **
 **  This file is part of Valentina.
 **
 **  Tox is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  Tox is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with Valentina.  If not, see <http://www.gnu.org/licenses/>.
 **
 ****************************************************************************/

#ifndef VMODELINGSPLINEPATH_H
#define VMODELINGSPLINEPATH_H

#include "vmodelingtool.h"
#include "xml/vdomdocument.h"
#include <QGraphicsPathItem>
#include "dialogs/dialogsplinepath.h"
#include "widgets/vcontrolpointspline.h"
#include "container/vcontainer.h"

class VModelingSplinePath:public VModelingTool, public QGraphicsPathItem
{
    Q_OBJECT
public:
                                     VModelingSplinePath(VDomDocument *doc, VContainer *data, qint64 id,
                                                     Tool::Enum typeCreation,
                                                     QGraphicsItem * parent = 0);
     virtual void setDialog();
     static VModelingSplinePath* Create(QSharedPointer<DialogSplinePath> &dialog,
                                        VDomDocument *doc, VContainer *data);
     static VModelingSplinePath* Create(const qint64 _id, const VSplinePath &path, VDomDocument *doc,
                                        VContainer *data, Document::Enum parse, Tool::Enum typeCreation);
signals:
    void                             RefreshLine(const qint32 &indexSpline, SplinePoint::Position pos,
                                                 const QPointF &controlPoint, const QPointF &splinePoint);
    void                             setEnabledPoint(bool enable);
public slots:
    virtual void                     FullUpdateFromFile();
    virtual void                     FullUpdateFromGui(int result);
    void                             ControlPointChangePosition(const qint32 &indexSpline,
                                                                SplinePoint::Position position,
                                                                const QPointF pos);
protected:
    virtual void                     contextMenuEvent ( QGraphicsSceneContextMenuEvent * event );
    virtual void                     AddToFile();
    virtual void                     mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );
    virtual void                     hoverMoveEvent ( QGraphicsSceneHoverEvent * event );
    virtual void                     hoverLeaveEvent ( QGraphicsSceneHoverEvent * event );
private:
    QSharedPointer<DialogSplinePath> dialogSplinePath;
    QVector<VControlPointSpline *>   controlPoints;
    void                             RefreshGeometry();
    void                             AddPathPoint(QDomElement &domElement, const VSplinePoint &splPoint);
    void                             UpdatePathPoint(QDomNode& node, VSplinePath &path);
    void                             CorectControlPoints(const VSpline &spl, VSplinePath &splPath,
                                                         const qint32 &indexSpline);
};

#endif // VMODELINGSPLINEPATH_H