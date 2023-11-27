// ConnectorItem.h
#ifndef XMLCONNECTOR_H
#define XMLCONNECTOR_H

#include <QQuickPaintedItem>
#include <QPointF>
#include <QHoverEvent>
#include <QCursor>

class XMLConnector : public QQuickPaintedItem
{
    Q_OBJECT
public:
    XMLConnector(QQuickItem* parent = nullptr);

    void paint(QPainter* painter) override;

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void hoverMoveEvent(QHoverEvent* event) override;
    void hoverEnterEvent(QHoverEvent* event) override;
    void hoverLeaveEvent(QHoverEvent* event) override;

private:
    QPointF startPoint;
    QPointF endPoint;
    bool isDragging;
    bool isResizing;

    bool contains(const QPointF& point);
    bool isPointOnLine(const QPointF& point);
};

#endif // XMLCONNECTOR_H
