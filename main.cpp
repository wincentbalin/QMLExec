#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDir>

#ifdef STATIC_LIBRARY
#include <QtPlugin>
Q_IMPORT_PLUGIN(QtLabsAnimationPlugin)
Q_IMPORT_PLUGIN(QtLabsCalendarPlugin)
Q_IMPORT_PLUGIN(QmlFolderListModelPlugin)
Q_IMPORT_PLUGIN(BodymovinPlugin)
Q_IMPORT_PLUGIN(QtLabsPlatformPlugin)
Q_IMPORT_PLUGIN(QtQmlLabsModelsPlugin)
Q_IMPORT_PLUGIN(QmlSettingsPlugin)
Q_IMPORT_PLUGIN(QtQuickSharedImagePlugin)
Q_IMPORT_PLUGIN(QmlWavefrontMeshPlugin)
#ifdef Q_OS_WIN
Q_IMPORT_PLUGIN(QWinExtrasQmlPlugin)
#endif
#endif


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QString appDir = QGuiApplication::applicationDirPath();
    const QString mainFile = QDir(appDir).filePath(QStringLiteral("main.qml"));
    const QUrl url = QUrl::fromLocalFile(mainFile);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
