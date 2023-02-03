#ifndef ABSTRACTASSETELTEM_H
#define ABSTRACTASSETELTEM_H

#include <QWidget>

class AbstractAsseteltem : public QObject
{
public:
    explicit AbstractAsseteltem(QObject *parent = nullptr);

    virtual void insert(std::unique_ptr<AbstractAsseteltem> item, int index);
    virtual void remove(std::unique_ptr<AbstractAsseteltem> item );

    virtual std::unique_ptr<AbstractAsseteltem> getParent();
    virtual std::unique_ptr<AbstractAsseteltem> getChild(int index);

    virtual std::pair<float, float> getPosition();
    virtual void setPosition();


signals:

};

#endif // ABSTRACTASSETELTEM_H
