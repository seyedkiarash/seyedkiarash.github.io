#include "graphicsview.h"

void GraphicsView::startWireDrawing()
{
    if (!circuitModel) return;
    cancelPlacing();
    cancelWireDrawing();
    wireDrawingActive = true;
    wireBreakPoints.clear();
    setMouseTracking(true);
    setFocus();
    setCursor(Qt::CrossCursor);
}

void GraphicsView::cancelWireDrawing()
{
    wireDrawingActive = false;
    wireStartPoint = QPointF();
    wireBreakPoints.clear();
    if (previewWire) { scene->removeItem(previewWire); delete previewWire; previewWire = nullptr; }
    unsetCursor();
}

void GraphicsView::completeWire()
{
    if (!wireDrawingActive || wireStartPoint.isNull() || wireBreakPoints.isEmpty()) {
        cancelWireDrawing();
        return;
    }

    QList<QPointF> allPoints;
    allPoints.append(wireStartPoint);
    allPoints.append(wireBreakPoints);

    auto &proj = circuitModel->getProjectData();
    for (int i = 0; i < allPoints.size() - 1; ++i) {
        auto wire = std::make_shared<Wire>();
        wire->name = generateUniqueElementName("Wire").toStdString();

        auto node1 = std::make_shared<Node>(generateUniqueNodeName().toStdString(),
                                          allPoints[i].x(), allPoints[i].y());
        auto node2 = std::make_shared<Node>(generateUniqueNodeName().toStdString(),
                                          allPoints[i+1].x(), allPoints[i+1].y());

        wire->node1 = node1;
        wire->node2 = node2;

        proj.nodes.push_back(node1);
        proj.nodes.push_back(node2);
        proj.elements.push_back(wire);
    }

    cancelWireDrawing();
    updateView();
}

void GraphicsView::updateWirePreview(const QPointF& scenePos)
{
    if (!wireDrawingActive) return;

    QPointF snappedPos = snapEnabled ? snapToGrid(scenePos) : scenePos;

    if (previewWire) {
        scene->removeItem(previewWire);
        delete previewWire;
        previewWire = nullptr;
    }

    if (wireStartPoint.isNull()) {
        return;
    }

    QPointF lastFixed = wireBreakPoints.isEmpty() ? wireStartPoint : wireBreakPoints.last();

    QPointF orthPoint;
    qreal dx = qAbs(snappedPos.x() - lastFixed.x());
    qreal dy = qAbs(snappedPos.y() - lastFixed.y());
    if (dx >= dy) {
        orthPoint = QPointF(snappedPos.x(), lastFixed.y());
    } else {
        orthPoint = QPointF(lastFixed.x(), snappedPos.y());
    }

    previewWire = scene->addLine(lastFixed.x(), lastFixed.y(),
                                 orthPoint.x(), orthPoint.y(),
                                 QPen(Qt::yellow, 2, Qt::DashLine));
}

void GraphicsView::commitWireAt(const QPointF& scenePos)
{
    if (!wireDrawingActive) return;

    QPointF snappedPos = snapEnabled ? snapToGrid(scenePos) : scenePos;

    if (wireStartPoint.isNull()) {
        wireStartPoint = snappedPos;
        return;
    }

    QPointF lastFixed = wireBreakPoints.isEmpty() ? wireStartPoint : wireBreakPoints.last();
    QPointF orthPoint;
    qreal dx = qAbs(snappedPos.x() - lastFixed.x());
    qreal dy = qAbs(snappedPos.y() - lastFixed.y());
    if (dx >= dy) {
        orthPoint = QPointF(snappedPos.x(), lastFixed.y());
    } else {
        orthPoint = QPointF(lastFixed.x(), snappedPos.y());
    }

    wireBreakPoints.append(orthPoint);

    updateWirePreview(scenePos);
}
