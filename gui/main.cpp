#include <QtQml>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include <misc/utilities.h>
#include <misc/mydocument.h>
#include <misc/treemodel.h>
#include <misc/treemanipulator.h>
#include <misc/parentsmodel.h>
#include <misc/nodelistmodel.h>
//#include <misc/xmlwriter.h>
//#include <misc/folderview.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    engine.addImportPath("qrc:/modules");

    auto utilities = &Misc::Utilities::getInstance();
    //auto myDocument = &Misc::MyDocument::getInstance();

// create XMLProcessor instance here and pass to mydocument and nodemodellist? OR add connections between myDocument and NodeListModel
    //auto xmlProcessor = &Misc::XMLProcessor::getInstance();

    auto myDocument = new Misc::MyDocument(engine);
    auto nodeListModel = new Misc::NodeListModel(&engine, myDocument);

    auto treeModel = new TreeModel(&engine, myDocument);
    auto treeManipulator = new TreeManipulator(*treeModel, &engine);

    //QList<QObject*> nodes = myDocument->getNodes();

    Misc::ParentsModel parentsModel;

    // Configure dark UI
    Misc::Utilities::configureDarkUi();

    // Init QML interface
    auto c = engine.rootContext();
    QQuickStyle::setStyle("Fusion");
    c->setContextProperty("Cpp_Misc_Utilities", utilities);
    c->setContextProperty("Cpp_Misc_My_Document", myDocument);
    c->setContextProperty("treeManipulator", QVariant::fromValue(treeManipulator));
    c->setContextProperty("availableParentsModel", &parentsModel);
    c->setContextProperty("nodeListModel", nodeListModel);
    //qmlRegisterType<Misc::XMLNode>("xmlNode", 1, 0, "XMLNode");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
