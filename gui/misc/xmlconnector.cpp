#include "xmlconnector.h"
#include <QPainter>
#include <iostream>


//issues:
//1. Add dragging
//2. Existing instances don't work when a new connector is created --think we need to add a Repeater in DrawingPane.qml, so first need to create a ConnectorModel.
//   Here, we would need to create a myDocument function which would add the connector instance to the model.
//3. Create Node Dialog disappears on first attempt when a connector has been created.



namespace Misc
{

XMLConnector::XMLConnector(QQuickItem* parent)
    : _isDragging(true), _isResizingEnd(false), _startPointLocal(false), _endPointLocal(false)
{
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);
    setEnabled(true);
    _init = true;
    std::cout << "XMLConnector::XMLConnector CONSTRUCTOR" << std::endl;
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

    std::cout << "XMLConnector::setStartPoint:  " << point.x() << ", " << point.y() << std::endl;
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
    std::cout << "XMLConnector::setEndPoint:  " << point.x() << ", " << point.y() << std::endl;
}

void XMLConnector::setConnectorUID(const QString &uid)
{
    _connectorUID = uid;
}

QString XMLConnector::getConnectorUID()
{
    return _connectorUID;
}

void XMLConnector::setConnectorXPositionStart(const QString &pos)
{
    _connectorStartPositionX = pos;
    _startPoint.setX(_connectorStartPositionX.toDouble());
    std::cout << "XMLConnector::setConnectorXPositionStart:  " << pos.toStdString() << std::endl;
    std::cout << "XMLConnector::setConnectorYPositionEnd _startPoint.x():  " << _startPoint.x() << std::endl;
    std::cout << "XMLConnector::setConnectorYPositionEnd _connectorStartPositionX:  " << _connectorStartPositionX.toStdString() << std::endl;
    //setStartPoint(QPoint(400,400));
    //setEndPoint(QPoint(410,410));
    emit connectorXPositionStartChanged();
}

QString XMLConnector::getConnectorXPositionStart()
{
    return _connectorStartPositionX;
}

void XMLConnector::setConnectorYPositionStart(const QString &pos)
{
    _connectorStartPositionY = pos;
    _startPoint.setY(_connectorStartPositionY.toDouble());

    std::cout << "XMLConnector::setConnectorYPositionStart:  " << pos.toStdString() << std::endl;
    std::cout << "XMLConnector::setConnectorYPositionEnd _startPoint.y():  " << _startPoint.y() << std::endl;
    std::cout << "XMLConnector::setConnectorYPositionEnd _connectorStartPositionY:  " << _connectorStartPositionY.toStdString() << std::endl;
    emit connectorYPositionStartChanged();
}

QString XMLConnector::getConnectorYPositionStart()
{
    return _connectorStartPositionY;
}

void XMLConnector::setConnectorXPositionEnd(const QString &pos)
{
    _connectorEndPositionX = pos;
    _endPoint.setX(_connectorEndPositionX.toDouble());
    std::cout << "XMLConnector::setConnectorXPositionEnd:  " << pos.toStdString() << std::endl;
    std::cout << "XMLConnector::setConnectorXPositionEnd _endPoint.x():  " << _endPoint.x() << std::endl;
    std::cout << "XMLConnector::setConnectorYPositionEnd _connectorEndPositionX:  " << _connectorEndPositionX.toStdString() << std::endl;
    emit connectorXPositionEndChanged();
}

QString XMLConnector::getConnectorXPositionEnd()
{
    std::cout << "XMLConnector::getConnectorXPositionEnd _connectorEndPositionX:  " << _connectorEndPositionX.toStdString() << std::endl;
    return _connectorEndPositionX;
}

void XMLConnector::setConnectorYPositionEnd(const QString &pos)
{
    _connectorEndPositionY = pos;
    _endPoint.setY(_connectorEndPositionY.toDouble());
    std::cout << "XMLConnector::setConnectorYPositionEnd:  " << pos.toStdString() << std::endl;
    std::cout << "XMLConnector::setConnectorYPositionEnd _endPoint.y():  " << _endPoint.y() << std::endl;
    std::cout << "XMLConnector::setConnectorYPositionEnd _connectorEndPositionY:  " << _connectorEndPositionY.toStdString() << std::endl;
    emit connectorYPositionEndChanged();
}

QString XMLConnector::getConnectorYPositionEnd()
{
    return _connectorEndPositionY;
}

void XMLConnector::setNodeStartID(const QString &startID)
{
    _nodeStartID = startID;
}

QString XMLConnector::getNodeStartID()
{
    return _nodeStartID;
}

void XMLConnector::setNodeEndID(const QString &endID)
{
    _nodeEndID = endID;
}

QString XMLConnector::getNodeEndID()
{
    return _nodeEndID;
}

void XMLConnector::paint(QPainter *painter)
{
    std::cout << "XMLConnector::_connectorStartPositionX:  " << _connectorStartPositionX.toStdString() << std::endl;
    std::cout << "XMLConnector::_connectorStartPositionY:  " << _connectorStartPositionY.toStdString() << std::endl;
    std::cout << "XMLConnector::_connectorEndPositionX:  " << _connectorEndPositionX.toStdString() << std::endl;
    std::cout << "XMLConnector::_connectorEndPositionY:  " << _connectorEndPositionY.toStdString() << std::endl;

    qDebug() << "XMLConnector::paint _startPoint.x(): " << _startPoint.x();
    qDebug() << "XMLConnector::paint _startPoint.y(): " << _startPoint.y();
    qDebug() << "XMLConnector::paint _endPoint.x(): " << _endPoint.x();
    qDebug() << "XMLConnector::paint _endPoint.x(): " << _endPoint.y();

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QPen(Qt::black, 2));

    painter->drawLine(_startPoint, _endPoint);

    qDebug() << "XMLConnector::paint _connectorUID(): " << _connectorUID;
    qDebug() << "XMLConnector::paint _startPoint.x(): " << _startPoint.x();
    qDebug() << "XMLConnector::paint _startPoint.y(): " << _startPoint.y();
    qDebug() << "XMLConnector::paint _endPoint.x(): " << _endPoint.x();
    qDebug() << "XMLConnector::paint _endPoint.x(): " << _endPoint.y();
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
            //qDebug() << "mouseMoveEvent _isResizingStart";
            _startPoint = event->pos();
        }
        if (_endPointLocal) {
            //qDebug() << "mouseMoveEvent _isResizingEnd";
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
            //qDebug() << "hoverMoveEvent _startPointLocal";
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

}
