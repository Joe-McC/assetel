// ConnectorItem.cpp
#include "xmlconnector.h"
#include <QPainter>


XMLConnector::XMLConnector(QQuickItem* parent)
    : QQuickPaintedItem(parent), isDragging(true), isResizing(true)
{
    setAcceptHoverEvents(true);
    setStartPoint(QPoint(400,400));
    setEndPoint(QPoint(500,500));
    setEnabled(true);
}

void XMLConnector::paint(QPainter* painter)
{
    painter->drawLine(startPoint, endPoint);
}

QPointF XMLConnector::getStartPoint() const
{
    return startPoint;
}

void XMLConnector::setStartPoint(const QPointF& point)
{
    if (startPoint != point) {
        startPoint = point;
        emit startPointChanged();
        update();
    }
}

QPointF XMLConnector::getEndPoint() const
{
    return endPoint;
}

void XMLConnector::setEndPoint(const QPointF& point)
{
    if (endPoint != point) {
        endPoint = point;
        emit endPointChanged();
        update();
    }
}

void XMLConnector::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        isDragging = true;
        isResizing = false;
        startPoint = event->pos();
        endPoint = event->pos();
        update();
    }
}

void XMLConnector::mouseMoveEvent(QMouseEvent* event)
{
    if (isDragging)
    {
        endPoint = event->pos();
        update();
    }
    else if (isResizing)
    {
        endPoint = event->pos();
        update();
    }
}

void XMLConnector::mouseReleaseEvent(QMouseEvent* event)
{


    if (isDragging && event->button() == Qt::LeftButton)
    {
        endPoint = event->pos();
        isDragging = false;
        update();
    }
    else if (isResizing && event->button() == Qt::LeftButton)
    {
        endPoint = event->pos();
        isResizing = false;
        update();
    }

    qDebug() << "mouseReleaseEvent endPoint:" << endPoint;
}

bool XMLConnector::contains(const QPointF &point)
{
    const qreal epsilon = 10.0; // Set your own epsilon value
    qreal distance1 = QLineF(startPoint, endPoint).length();
    qreal distance2 = QLineF(startPoint, point).length() + QLineF(endPoint, point).length();

    return qAbs(distance1 - distance2) < epsilon;
}

void XMLConnector::hoverMoveEvent(QHoverEvent *event)
{
    if (isResizing)
    {
        endPoint = event->position();
        update();
    }
}

void XMLConnector::hoverEnterEvent(QHoverEvent *event)
{
    if (contains(event->position()))
    {
        setCursor(Qt::SizeHorCursor);
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
}

void XMLConnector::hoverLeaveEvent(QHoverEvent *event)
{
    setCursor(Qt::ArrowCursor);
}

bool XMLConnector::isPointOnLine(const QPointF &point)
{
    const qreal epsilon = 10.0; // Set your own epsilon value
    qreal distance = QLineF(startPoint, endPoint).length();
    qreal distanceToStart = QLineF(startPoint, point).length();
    qreal distanceToEnd = QLineF(endPoint, point).length();

    return qAbs(distance - (distanceToStart + distanceToEnd)) < epsilon;
}



