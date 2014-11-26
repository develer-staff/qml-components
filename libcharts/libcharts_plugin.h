#ifndef LIBCHARTS_PLUGIN_H
#define LIBCHARTS_PLUGIN_H

#include <QQmlExtensionPlugin>

class LibchartsPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif // LIBCHARTS_PLUGIN_H

