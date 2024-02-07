// ConnectorItem.h
#ifndef XMLCONNECTOR_H
#define XMLCONNECTOR_H

#include <QQuickPaintedItem>
#include <QPointF>
#include <QHoverEvent>
#include <QCursor>


namespace Misc
{

class XMLConnector : public QQuickPaintedItem
{

    Q_OBJECT
    Q_PROPERTY(QString connectorUID READ getConnectorUID WRITE setConnectorUID NOTIFY connectorUIDChanged)
    Q_PROPERTY(QString connectorXPositionStart READ getConnectorXPositionStart WRITE setConnectorXPositionStart NOTIFY connectorXPositionStartChanged)
    Q_PROPERTY(QString connectorYPositionStart READ getConnectorYPositionStart WRITE setConnectorYPositionStart NOTIFY connectorYPositionStartChanged)
    Q_PROPERTY(QString connectorXPositionEnd READ getConnectorXPositionEnd WRITE setConnectorXPositionEnd NOTIFY connectorXPositionEndChanged)
    Q_PROPERTY(QString connectorYPositionEnd READ getConnectorYPositionEnd WRITE setConnectorYPositionEnd NOTIFY connectorYPositionEndChanged)
    //Q_PROPERTY(QPointF connectorPositionStart READ getConnectorPositionStart WRITE setConnectorPositionStart NOTIFY connectorStartPosChanged)
    //Q_PROPERTY(QPointF connectorPositionEnd READ getConnectorPositionEnd WRITE setConnectorPositionEnd NOTIFY connectorEndPosChanged)
    Q_PROPERTY(QString nodeStartID READ getNodeStartID WRITE setNodeStartID NOTIFY nodeStartIDChanged)
    Q_PROPERTY(QString nodeEndID READ getNodeEndID WRITE setNodeEndID NOTIFY nodeEndIDChanged)


public:
    //XMLConnector(QPointF initialStartPoint = QPointF(), QPointF initialEndPoint = QPointF(), QQuickItem* parent = nullptr);

    XMLConnector(QQuickItem* parent = nullptr);
    void paint(QPainter* painter) override;

    QPointF getStartPoint() const;
    void setStartPoint(const QPointF& point);

    QPointF getEndPoint() const;
    void setEndPoint(const QPointF& point);

    void setConnectorUID(const QString &uid);
    QString getConnectorUID();

    void setConnectorXPositionStart(const qreal &pos);
    qreal getConnectorXPositionStart();

    void setConnectorYPositionStart(const qreal &pos);
    qreal getConnectorYPositionStart();

    void setConnectorXPositionEnd(const qreal &pos);
    qreal getConnectorXPositionEnd();

    void setConnectorYPositionEnd(const qreal &pos);
    qreal getConnectorYPositionEnd();

    void setNodeStartID(const QString &startID);
    QString getNodeStartID();

    void setNodeEndID(const QString &endID);
    QString getNodeEndID();

    QString _connectorUID;
    //QPointF _connectorStartPosition;
    //QPointF _connectorEndPosition;

    qreal _connectorStartPositionX;
    qreal _connectorStartPositionY;
    qreal _connectorEndPositionX;
    qreal _connectorEndPositionY;

    QString _nodeStartID;
    QString _nodeEndID;

signals:
    void connectorUIDChanged();
    void connectorStartPosChanged();
    void connectorEndPosChanged();
    void nodeStartIDChanged();
    void nodeEndIDChanged();

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

}

#endif // XMLCONNECTOR_H
