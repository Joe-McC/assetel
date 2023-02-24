#ifndef ABSTRACTASSETELTEM_H
#define ABSTRACTASSETELTEM_H

#include <QWidget>

class AbstractAsseteltem : public QObject
{
public:
    //explicit AbstractAsseteltem(QObject *parent = nullptr);

    //virtual void insert(std::shared_ptr<AbstractAsseteltem> item, int index);
    //virtual void remove(std::unique_ptr<AbstractAsseteltem> item);

    // Do we need getParent()? Do we want child to know about parent, see discussion:
    // https://softwareengineering.stackexchange.com/questions/426442/how-can-composed-sub-objects-access-the-parent-object
    // We would need to create rule of 3 etc.
    //virtual std::unique_ptr<AbstractAsseteltem> getParent();
    //virtual std::shared_ptr<AbstractAsseteltem> getChild(int index);

    virtual std::pair<float, float> getPosition();
    virtual void setPosition(std::pair<float, float>);


signals:

};

#endif // ABSTRACTASSETELTEM_H
