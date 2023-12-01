// ConnectorItem.cpp
#include "xmlconnector.h"
#include <QPainter>


XMLConnector::XMLConnector(QQuickItem* parent)
    : QQuickPaintedItem(parent), isDragging(true), isResizing(true)
{
    setAcceptHoverEvents(true);
    setEnabled(true);
}

void XMLConnector::paint(QPainter* painter)
{
    painter->drawLine(startPoint, endPoint);
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
}

bool XMLConnector::contains(const QPointF &point)
{
    const qreal epsilon = 5.0; // Set your own epsilon value
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
    const qreal epsilon = 5.0; // Set your own epsilon value
    qreal distance = QLineF(startPoint, endPoint).length();
    qreal distanceToStart = QLineF(startPoint, point).length();
    qreal distanceToEnd = QLineF(endPoint, point).length();

    return qAbs(distance - (distanceToStart + distanceToEnd)) < epsilon;
}



