#include "libcharts_plugin.h"
#include "libcharts.h"

#include <qqml.h>

void LibchartsPlugin::registerTypes(const char *uri)
{
    // @uri com.develer.libcharts
    qmlRegisterType<LineSeries>(uri, 1, 0, "LineSeries");
    qmlRegisterType<LineChart>(uri, 1, 0, "LineChart");
}


