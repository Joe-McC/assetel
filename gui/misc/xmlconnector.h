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
    //XMLConnector(QPointF initialStartPoint = QPointF(), QPointF initialEndPoint = QPointF(), QQuickItem* parent = nullptr);

    XMLConnector(QQuickItem* parent = nullptr);
    void paint(QPainter* painter) override;

    QPointF getStartPoint() const;
    void setStartPoint(const QPointF& point);

    QPointF getEndPoint() const;
    void setEndPoint(const QPointF& point);

signals:
    void startPointChanged();
    void endPointChanged();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void hoverMoveEvent(QHoverEvent* event) override;
    void hoverEnterEvent(QHoverEvent* event) override;
    void hoverLeaveEvent(QHoverEvent* event) override;

private:
    QPointF _startPoint;
    QPointF _endPoint;
    bool _isDragging;
    bool _isResizingEnd;
    bool _init;
    bool _startPointLocal;
    bool _endPointLocal;

    bool contains(const QPointF& point);
    bool isPointOnLine(const QPointF& point);
};

#endif // XMLCONNECTOR_H
