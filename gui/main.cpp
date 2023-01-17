#include <QtQml>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include <misc/utilities.h>
#include <misc/mydocument.h>
#include <misc/xmlwriter.h>
//#include <misc/folderview.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    auto utilities = &Misc::Utilities::getInstance();
    auto my_document = &Misc::MyDocument::getInstance();
    auto xml_doc = &Misc::XMLWriter::getInstance();
    //MyDocument::
    //auto folderView = &Misc::FolderView::getInstance();

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
    c->setContextProperty("Cpp_Misc_My_Document", my_document);
    //c->setContextProperty("folderView", folderView);


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
