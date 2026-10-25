// =======================================================================
// =======================================================================
//
//   FILE: src/View/graphicsview.h (New File, replaces schematicview.h)
//
// =======================================================================
// =======================================================================

#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QInputDialog>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <memory>
#include <QGraphicsLineItem>
#include "circuitcomponent.h"
#include "circuitmodel.h"

class GraphicsView : public QGraphicsView {
    Q_OBJECT

public:
    explicit GraphicsView(QWidget *parent = nullptr);
    void setCircuitModel(CircuitModel* model);
    void startPlacing(const QString& logicalType);
    void startWireDrawing();
    void updateView();
    
    // Subcircuit management
    void setSubcircuitCreationMode(bool enabled);
    void setPinSelectionMode(bool enabled);
    bool isSubcircuitCreationMode() const { return subcircuitCreationMode; }
    bool isPinSelectionMode() const { return pinSelectionMode; }
    const std::vector<std::shared_ptr<Node>>& getSelectedPins() const { return selectedPins; }
    
    // پروب
    void setProbeMode(int mode); // 0=غیرفعال, 1=ولتاژ, 2=جریان, 3=توان
    void updateProbeDisplay(const QPoint& mousePos);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void onProjectLoaded();

private:
    QGraphicsScene* scene;
    CircuitModel* circuitModel;
    
    // Component placement
    bool placingActive = false;
    QString placingType;
    std::shared_ptr<Element> previewElementLogic;
    CircuitComponent* previewGraphics;
    double rotationAngleDeg = 0.0;
    bool snapEnabled = true;
    const qreal gridSize = 20.0;
    
    // Wire drawing
    bool wireDrawingActive = false;
    QPointF wireStartPoint;
    QList<QPointF> wireBreakPoints;
    QGraphicsLineItem* previewWire;
    
    // Subcircuit creation
    bool subcircuitCreationMode = false;
    bool pinSelectionMode = false;
    std::vector<std::shared_ptr<Node>> selectedPins;
    std::vector<std::shared_ptr<Element>> subcircuitElements;
    
    // پروب
    int probeMode = 0; // 0=غیرفعال, 1=ولتاژ, 2=جریان, 3=توان
    QGraphicsItem* probeItem = nullptr;
    QGraphicsTextItem* probeTextItem = nullptr;
    
    // Methods
    void updatePreviewAt(const QPointF& scenePos);
    void commitPlacementAt(const QPointF& scenePos);
    void cancelPlacing();
    void updateWirePreview(const QPointF& scenePos);
    void commitWireAt(const QPointF& scenePos);
    void completeWire();
    void cancelWireDrawing();
    QString generateUniqueNodeName() const;
    QString generateUniqueElementName(const QString& logicalType) const;
    QPointF snapToGrid(const QPointF& pos) const;
    
    // Node and component interaction
    std::shared_ptr<Node> findNodeNear(const QPointF& pos, qreal radiusPx = 20.0) const;
    void promptRenameNode(const std::shared_ptr<Node>& node);
    std::shared_ptr<Element> findComponentNear(const QPointF& pos, qreal radiusPx = 30.0) const;
    void promptEditComponent(const std::shared_ptr<Element>& component);
    void updateComponentValue(const std::shared_ptr<Element>& component, const QString& newValue);
    QString getComponentValueString(const std::shared_ptr<Element>& component) const;
    
    // Subcircuit methods
    void addElementToSubcircuit(const std::shared_ptr<Element>& element);
    void selectPin(const std::shared_ptr<Node>& node);
    void clearSubcircuitData();
    
    void populateScene();
    void findNodeAt(const QPointF& scenePos);
};

#endif // GRAPHICSVIEW_H

