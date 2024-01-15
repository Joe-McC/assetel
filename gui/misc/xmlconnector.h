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
    Q_PROPERTY(QString connectorUID READ getConnectorUID WRITE setConnectorUID NOTIFY connectorUIDChanged)
    Q_PROPERTY(QString connectorXPosition READ getConnectorXPosition WRITE setConnectorXPosition NOTIFY connectorXPositionChanged)
    Q_PROPERTY(QString connectorYPosition READ getConnectorYPosition WRITE setConnectorYPosition NOTIFY connectorYPositionChanged)
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

    void setConnectorXPosition(const QString &xpos);
    QString getConnectorXPosition();

    void setConnectorYPosition(const QString &xpos);
    QString getConnectorYPosition();

    void setNodeStartID(const QString &startID);
    QString getNodeStartID();

    void setNodeEndID(const QString &endID);
    QString getNodeEndID();

    QString _connectorUID;
    QString _connectorXPosition;
    QString _connectorYPosition;
    QString _nodeStartID;
    QString _nodeEndID;

signals:
    void connectorUIDChanged();
    void connectorXPositionChanged();
    void connectorYPositionChanged();
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

#endif // XMLCONNECTOR_H
