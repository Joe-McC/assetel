#include "xmlconnector.h"
#include <QPainter>


//issues:
//1. Add dragging
//2. Existing instances don't work when a new connector is created

XMLConnector::XMLConnector(QQuickItem* parent)
    : QQuickPaintedItem(parent), _isDragging(true), _isResizingEnd(false), _startPointLocal(false), _endPointLocal(false)
{
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);
    setStartPoint(QPoint(400,400));
    setEndPoint(QPoint(410,410));
    setEnabled(true);
    _init = true;
}

QPointF XMLConnector::getStartPoint() const
{
    return _startPoint;
}

void XMLConnector::setStartPoint(const QPointF& point)
{
    if (_startPoint != point) {
        _startPoint = point;
        emit startPointChanged();
        update();
    }
}

QPointF XMLConnector::getEndPoint() const
{
    return _endPoint;
}

void XMLConnector::setEndPoint(const QPointF& point)
{
    if (_endPoint != point) {
        _endPoint = point;
        emit endPointChanged();
        update();
    }
}

void XMLConnector::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QPen(Qt::black, 2));

    painter->drawLine(_startPoint, _endPoint);
}

void XMLConnector::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (_init) {
            if (!_isResizingEnd)
            {
                _endPoint = event->pos();
                _isResizingEnd = true;
                qDebug() << "_init mousePressEvent _isResizingStart";
                qDebug() << "_init mousePressEvent _isResizingStart startPoint:" << _startPoint;
                qDebug() << "_init mousePressEvent _isResizingStart endPoint:" << _endPoint;
            }
            else if (_isResizingEnd)
            {
                _endPoint = event->pos();
                _isResizingEnd = false;
                _init = false;
                qDebug() << "_init mousePressEvent _isResizingEnd";
                qDebug() << "_init mousePressEvent _isResizingEnd startPoint:" << _startPoint;
                qDebug() << "_init mousePressEvent _isResizingEnd endPoint:" << _endPoint;
            }
        }
        else {

            if (!_isResizingEnd) {
                qreal newX = event->pos().rx();
                qreal newY = event->pos().ry();

                qreal origStartX = _startPoint.rx();
                qreal origStartY = _startPoint.ry();

                qreal origEndX = _endPoint.rx();
                qreal origEndY = _endPoint.ry();

                _startPointLocal = (qAbs(newX - origStartX) < 20) && (qAbs(newY - origStartY) < 20);
                _endPointLocal = (qAbs(newX - origEndX) < 20) && (qAbs(newY - origEndY) < 20);


                qDebug() << "newX:" << newX;
                qDebug() << "newY:" << newY;
                qDebug() << "origStartX:" << origStartX;
                qDebug() << "origStartY:" << origStartY;
                qDebug() << "origEndX:" << origEndX;
                qDebug() << "origEndY:" << origEndY;
                qDebug() << "_startPointLocal:" << _startPointLocal;
                qDebug() << "_endPointLocal:" << _endPointLocal;

                if (_startPointLocal)
                {
                    _isResizingEnd = true;
                    _startPoint = event->pos();
                    qDebug() << "mousePressEvent first click startPointLocal";
                    qDebug() << "mousePressEvent first click startPointLocal startPoint:" << _startPoint;
                    qDebug() << "mousePressEvent first click startPointLocal endPoint:" << _endPoint;
                }
                else if (_endPointLocal)
                {
                    _isResizingEnd = true;
                    _endPoint = event->pos();
                    qDebug() << "mousePressEvent first click endPointLocal";
                    qDebug() << "mousePressEvent first click endPointLocal startPoint:" << _startPoint;
                    qDebug() << "mousePressEvent first click endPointLocal endPoint:" << _endPoint;
                }
            }
            else if (_isResizingEnd) {
                _isResizingEnd = false;


                if (_startPointLocal)
                {
                    _startPointLocal = false;
                    //_isResizingStart = true;

                    //_isResizingEnd = false;
                    _startPoint = event->pos();
                    qDebug() << "mousePressEvent last click startPointLocal";
                    qDebug() << "mousePressEvent last click startPointLocal startPoint:" << _startPoint;
                    qDebug() << "mousePressEvent last click startPointLocal endPoint:" << _endPoint;
                }
                else if (_endPointLocal)
                {
                    _endPointLocal = false;
                    _endPoint = event->pos();
                    qDebug() << "mousePressEvent last click endPointLocal";
                    qDebug() << "mousePressEvent last click endPointLocal startPoint:" << _startPoint;
                    qDebug() << "mousePressEvent last click endPointLocal endPoint:" << _endPoint;
                }
            }
        }
    }

    update();
}

void XMLConnector::mouseMoveEvent(QMouseEvent *event)
{
    if (_isResizingEnd) {
        if (_startPointLocal) {
            qDebug() << "mouseMoveEvent _isResizingStart";
            _startPoint = event->pos();
        }
        if (_endPointLocal) {
            qDebug() << "mouseMoveEvent _isResizingEnd";
            _endPoint = event->pos();
        }
    }

    update();
}

void XMLConnector::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    // Additional logic for resizing or moving the line can be added here
}

bool XMLConnector::contains(const QPointF &point)
{
    const qreal epsilon = 10.0; // Set your own epsilon value
    qreal distance1 = QLineF(_startPoint, _endPoint).length();
    qreal distance2 = QLineF(_startPoint, point).length() + QLineF(_endPoint, point).length();

    return qAbs(distance1 - distance2) < epsilon;
}

void XMLConnector::hoverMoveEvent(QHoverEvent *event)
{
    if (_isResizingEnd) {
        if (_startPointLocal) {
            qDebug() << "hoverMoveEvent _startPointLocal";
            _startPoint = event->pos();
             update();
        }
        if (_endPointLocal) {
            qDebug() << "hoverMoveEvent _endPointLocal";
            _endPoint = event->pos();
             update();
        }

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
    qreal distance = QLineF(_startPoint, _endPoint).length();
    qreal distanceToStart = QLineF(_startPoint, point).length();
    qreal distanceToEnd = QLineF(_endPoint, point).length();

    return qAbs(distance - (distanceToStart + distanceToEnd)) < epsilon;
}

