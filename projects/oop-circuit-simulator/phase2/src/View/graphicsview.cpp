//
// Created by Asus on 8/19/2025.
//
// =======================================================================
// =======================================================================
//
//   FILE: src/View/graphicsview.cpp (Core functions only)
//
// =======================================================================
// =======================================================================

#include "graphicsview.h"
#include "resistor.h"
#include "capacitor.h"
#include "inductor.h"
#include "voltagesource.h"
#include "currentsource.h"
#include "diode.h"
#include "zenerdiode.h"
#include "ground.h"
#include "wire.h"
#include "subcircuitview.h"
#include <QPainter>
#include <QGraphicsSimpleTextItem>
#include <QMouseEvent>
#include <QtMath>
#include <QCursor>
#include <QInputDialog>
#include <QApplication>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <set>

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::RubberBandDrag);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}

void GraphicsView::setCircuitModel(CircuitModel* model)
{
    qDebug() << "GraphicsView::setCircuitModel called with model:" << model;
    circuitModel = model;
}

void GraphicsView::updateView()
{
    populateScene();
}

void GraphicsView::populateScene()
{
    scene->clear();
    if (!circuitModel) {
        qDebug() << "populateScene: circuitModel is null!";
        return;
    }

    const auto& nodes = circuitModel->getProjectData().nodes;
    const auto& elements = circuitModel->getProjectData().elements;
    qDebug() << "populateScene: Found" << elements.size() << "elements and" << nodes.size() << "nodes";

    const bool isDark = qApp->palette().window().color().lightness() < 128;
    const QColor wireColor = isDark ? QColor(200,200,200) : QColor(0,0,0);
    const QColor nodeDotColor = isDark ? QColor(Qt::cyan) : QColor(0,0,0);
    const QColor nodeLabelColor = isDark ? QColor(Qt::yellow) : QColor(0,0,0);

    // ۱. رسم خطوط اتصال (سیم‌ها)
    for (const auto& element : elements) {
        if (element->node1 && element->node2 && element->getType() == std::string("Wire")) {
            QPen wirePen(wireColor, 2);
            scene->addLine(
                element->node1->getX(), element->node1->getY(),
                element->node2->getX(), element->node2->getY(),
                wirePen
            );
        }
    }

    // ۲. رسم المان‌ها
    for (const auto& element : elements) {
        CircuitComponent* graphicalItem = nullptr;
        std::string type = element->getType();
        qDebug() << "Creating graphical item for element type:" << QString::fromStdString(type);

        if (type == "Resistor") graphicalItem = new ResistorView(element);
        else if (type == "Capacitor") graphicalItem = new CapacitorView(element);
        else if (type == "Inductor") graphicalItem = new InductorView(element);
        else if (type == "VoltageSource" || type == "VoltageSourceDC" || type == "VoltageSourceSin" || type == "VoltageSourcePulse") graphicalItem = new VoltageSourceView(element);
        else if (type == "CurrentSource" || type == "CurrentSourceDC" || type == "CurrentSourceSin" || type == "CurrentSourcePulse") graphicalItem = new CurrentSourceView(element);
        else if (type == "Diode") graphicalItem = new DiodeView(element);
        else if (type == "ZenerDiode") graphicalItem = new ZenerDiodeView(element);
        else if (type == "Ground") graphicalItem = new GroundView(element);
        else if (type == "SubCircuit") graphicalItem = new SubCircuitView(element);

        if (graphicalItem) {
            scene->addItem(graphicalItem);
            graphicalItem->updateFromLogic();
        }
    }

    // ۳. رسم گره‌ها و برچسب آن‌ها با حذف تکراری‌ها روی مختصات یکسان
    std::set<std::pair<int,int>> drawnAt;
    for (const auto& node : nodes) {
        const int nx = qRound(node->getX());
        const int ny = qRound(node->getY());
        std::pair<int,int> key{nx, ny};
        if (drawnAt.count(key)) continue; // قبلاً در این مختصات برچسب/نقطه رسم شده
        drawnAt.insert(key);

        scene->addEllipse(nx - 3, ny - 3, 6, 6, QPen(nodeDotColor), QBrush(nodeDotColor));
        auto *label = new QGraphicsSimpleTextItem(QString::fromStdString(node->getName()));
        label->setBrush(nodeLabelColor);
        label->setPos(nx + 6, ny - 6);
        scene->addItem(label);
    }
}

void GraphicsView::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsView::drawBackground(painter, rect);
    QPen pen(QColor(0x4A, 0x4A, 0x4A), 1, Qt::DotLine);
    painter->setPen(pen);
    qreal left = rect.left() - fmod(rect.left(), gridSize);
    qreal top = rect.top() - fmod(rect.top(), gridSize);
    for (qreal x = left; x < rect.right(); x += gridSize)
        painter->drawLine(QPointF(x, rect.top()), QPointF(x, rect.bottom()));
    for (qreal y = top; y < rect.bottom(); y += gridSize)
        painter->drawLine(QPointF(rect.left(), y), QPointF(rect.right(), y));
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
    QPointF scenePos = mapToScene(event->pos());

    if (placingActive && previewGraphics) {
        updatePreviewAt(scenePos);
    } else if (wireDrawingActive) {
        updateWirePreview(scenePos);
    }
    
    // به‌روزرسانی پروب
    updateProbeDisplay(event->pos());
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    QPointF scenePos = mapToScene(event->pos());

    if (placingActive) {
        if (event->button() == Qt::LeftButton) {
            commitPlacementAt(scenePos);
            return; // consume
        } else if (event->button() == Qt::RightButton) {
            cancelPlacing();
            return;
        }
    } else if (wireDrawingActive) {
        if (event->button() == Qt::LeftButton) {
            commitWireAt(scenePos);
            return; // consume
        } else if (event->button() == Qt::RightButton) {
            completeWire();
            return;
        }
    } else if (event->button() == Qt::RightButton) {
        // حالت idle: تغییر نام نود یا ویرایش المان با راست کلیک
        auto node = findNodeNear(scenePos);
        if (node) {
            if (pinSelectionMode) {
                selectPin(node);
                return;
            } else {
                promptRenameNode(node);
                return;
            }
        }
        
        // Check if right-click is on a component
        auto component = findComponentNear(scenePos);
        if (component) {
            promptEditComponent(component);
            return;
        }
    }

    QGraphicsView::mousePressEvent(event);
}

QString GraphicsView::generateUniqueNodeName() const
{
    static int counter = 1;
    return QString("N%1").arg(counter++);
}

QString GraphicsView::generateUniqueElementName(const QString& logicalType) const
{
    static int rc = 1, cc = 1, lc = 1, vc = 1, ic = 1, dc = 1, zc = 1, gc = 1, wc = 1;
    if (logicalType == "Resistor") return QString("R%1").arg(rc++);
    if (logicalType == "Capacitor") return QString("C%1").arg(cc++);
    if (logicalType == "Inductor") return QString("L%1").arg(lc++);
    if (logicalType == "VoltageSource" || logicalType == "VoltageSourceDC") return QString("V%1").arg(vc++);
    if (logicalType == "CurrentSource" || logicalType == "CurrentSourceDC") return QString("I%1").arg(ic++);
    if (logicalType == "Diode") return QString("D%1").arg(dc++);
    if (logicalType == "ZenerDiode") return QString("Z%1").arg(zc++);
    if (logicalType == "Ground") return QString("G%1").arg(gc++);
    if (logicalType == "Wire") return QString("W%1").arg(wc++);
    return QString("X%1").arg(++vc);
}

QPointF GraphicsView::snapToGrid(const QPointF& pos) const
{
    qreal x = qRound(pos.x() / gridSize) * gridSize;
    qreal y = qRound(pos.y() / gridSize) * gridSize;
    return QPointF(x, y);
}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    if (placingActive) {
        if (event->key() == Qt::Key_R) {
            if (event->modifiers() & Qt::ShiftModifier) rotationAngleDeg -= 90.0;
            else rotationAngleDeg += 90.0;
            if (rotationAngleDeg >= 360.0) rotationAngleDeg -= 360.0;
            if (rotationAngleDeg < 0.0) rotationAngleDeg += 360.0;
            QPoint globalPos = QCursor::pos();
            QPoint viewPos = mapFromGlobal(globalPos);
            updatePreviewAt(mapToScene(viewPos));
            return;
        } else if (event->key() == Qt::Key_G) {
            snapEnabled = !snapEnabled;
            QPoint globalPos = QCursor::pos();
            QPoint viewPos = mapFromGlobal(globalPos);
            updatePreviewAt(mapToScene(viewPos));
            return;
        }
    }
    QGraphicsView::keyPressEvent(event);
}

void GraphicsView::onProjectLoaded()
{
    updateView();
}

// Subcircuit management methods
void GraphicsView::setSubcircuitCreationMode(bool enabled)
{
    subcircuitCreationMode = enabled;
    if (enabled) {
        clearSubcircuitData();
        setCursor(Qt::CrossCursor);
    } else {
        setCursor(Qt::ArrowCursor);
    }
}

void GraphicsView::setPinSelectionMode(bool enabled)
{
    pinSelectionMode = enabled;
    if (enabled) {
        selectedPins.clear();
        setCursor(Qt::PointingHandCursor);
    } else {
        setCursor(Qt::ArrowCursor);
    }
}

void GraphicsView::addElementToSubcircuit(const std::shared_ptr<Element>& element)
{
    if (subcircuitCreationMode && element) {
        subcircuitElements.push_back(element);
    }
}

void GraphicsView::selectPin(const std::shared_ptr<Node>& node)
{
    if (pinSelectionMode && node && selectedPins.size() < 2) {
        selectedPins.push_back(node);
        
        if (selectedPins.size() == 2) {
            // Both pins selected, show confirmation dialog
            QString pin1Name = QString::fromStdString(selectedPins[0]->getName());
            QString pin2Name = QString::fromStdString(selectedPins[1]->getName());
            
            QMessageBox::information(this, "پین‌های انتخاب شده", 
                QString("پین 1: %1\nپین 2: %2\n\nحالا می‌توانید تک‌قطبی را ذخیره کنید.").arg(pin1Name, pin2Name));
            
            setPinSelectionMode(false);
        }
    }
}

void GraphicsView::clearSubcircuitData()
{
    subcircuitElements.clear();
    selectedPins.clear();
}

// =======================================================================
// متدهای پروب
// =======================================================================

void GraphicsView::setProbeMode(int mode) {
    probeMode = mode;
    
    // حذف پروب قبلی
    if (probeItem) {
        scene->removeItem(probeItem);
        delete probeItem;
        probeItem = nullptr;
    }
    if (probeTextItem) {
        scene->removeItem(probeTextItem);
        delete probeTextItem;
        probeTextItem = nullptr;
    }
    
    if (probeMode == 0) {
        return;
    }
    
    // ایجاد پروب جدید
    QGraphicsEllipseItem* probe = new QGraphicsEllipseItem();
    probe->setRect(-8, -8, 16, 16);
    probe->setPen(QPen(Qt::black, 2));
    
    // تنظیم رنگ و شکل بر اساس نوع پروب
    switch (probeMode) {
        case 1: // ولتاژ - مثل اسیلوسکپ
            probe->setBrush(QBrush(Qt::red));
            probe->setRect(-10, -10, 20, 20);
            break;
        case 2: // جریان - ذره بین با فلش
            probe->setBrush(QBrush(Qt::blue));
            probe->setRect(-8, -8, 16, 16);
            break;
        case 3: // توان - ذره بین با علامت ⚡
            probe->setBrush(QBrush(Qt::green));
            probe->setRect(-8, -8, 16, 16);
            break;
    }
    
    probeItem = probe;
    scene->addItem(probeItem);
    probeItem->setVisible(false);
    
    // ایجاد متن نمایش مقدار
    probeTextItem = new QGraphicsTextItem();
    probeTextItem->setDefaultTextColor(Qt::white);
    probeTextItem->setFont(QFont("Arial", 10, QFont::Bold));
    scene->addItem(probeTextItem);
    probeTextItem->setVisible(false);
}

void GraphicsView::updateProbeDisplay(const QPoint& mousePos) {
    if (probeMode == 0 || !probeItem || !probeTextItem) return;
    
    // تبدیل مختصات ماوس به مختصات صحنه
    QPointF scenePos = mapToScene(mousePos);
    
    // نمایش پروب
    probeItem->setPos(scenePos);
    probeItem->setVisible(true);
    
    // نمایش متن پروب
    QString displayText;
    switch (probeMode) {
        case 1: // ولتاژ
            displayText = "پروب ولتاژ\n(اسیلوسکپ)";
            break;
        case 2: // جریان
            displayText = "پروب جریان\n(ذره بین + فلش)";
            break;
        case 3: // توان
            displayText = "پروب توان\n(ذره بین + ⚡)";
            break;
    }
    
    probeTextItem->setPlainText(displayText);
    probeTextItem->setPos(scenePos.x() + 20, scenePos.y() - 30);
    probeTextItem->setVisible(true);
}
