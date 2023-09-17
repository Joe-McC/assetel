#include <QtQml>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include <misc/utilities.h>
#include <misc/mydocument.h>
#include <misc/treemodel.h>
#include <misc/treemanipulator.h>
#include <misc/parentsmodel.h>
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
    auto myDocument = &Misc::MyDocument::getInstance();

    auto treeModel = new TreeModel(&engine);
    auto treeManipulator = new TreeManipulator(*treeModel, &engine);


    auto america = std::make_shared<TreeItem>("America");
    auto asia = std::make_shared<TreeItem>("Asia");
    auto europe = std::make_shared<TreeItem>("Europe");
    auto brazil = std::make_shared<TreeItem>("Brazil");
    auto canada = std::make_shared<TreeItem>("Canada");
    auto italy = std::make_shared<TreeItem>("Italy");
    auto portugal = std::make_shared<TreeItem>("Portugal");

    treeModel->addTopLevelItem(america);
    treeModel->addTopLevelItem(asia);
    treeModel->addTopLevelItem(europe);
    treeModel->addItem(america, brazil);
    treeModel->addItem(america, canada);
    treeModel->addItem(europe, italy);
    treeModel->addItem(europe, portugal);

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


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
