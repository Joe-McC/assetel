#include <QtQml>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include <misc/utilities.h>
#include <misc/mydocument.h>
#include <misc/treemodel.h>
#include <misc/treemanipulator.h>
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

    auto america = new TreeItem("America");
    auto asia = new TreeItem("Asia");
    auto europe = new TreeItem("Europe");
    auto brazil = new TreeItem("Brazil");
    auto canada = new TreeItem("Canada");
    auto italy = new TreeItem("Italy");
    auto portugal = new TreeItem("Portugal");


    treeModel->addTopLevelItem(america);
    treeModel->addTopLevelItem(asia);
    treeModel->addTopLevelItem(europe);
    treeModel->addItem(america, brazil);
    treeModel->addItem(america, canada);
    treeModel->addItem(europe, italy);
    treeModel->addItem(europe, portugal);

    // Configure dark UI
    Misc::Utilities::configureDarkUi();

    // Automatically re-translate UI
    //QObject::connect(translator, &Misc::Translator::languageChanged, &engine,
    //                 &QQmlApplicationEngine::retranslate);


    //Misc::FolderView* folderView = new Misc::FolderView();
    //folderView->setSandBoxDetails(QDir::currentPath());   //show current path

    // Init QML interface
    auto c = engine.rootContext();
    QQuickStyle::setStyle("Fusion");
    c->setContextProperty("Cpp_Misc_Utilities", utilities);
    c->setContextProperty("Cpp_Misc_My_Document", myDocument);
    c->setContextProperty("treeManipulator", QVariant::fromValue(treeManipulator));

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
