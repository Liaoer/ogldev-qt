#include "trianglewindow.h"



int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    //app.setApplicationName(" qt_ogldev");
    //app.setApplicationVersion("0.1");
    QSurfaceFormat format;
    format.setSamples(16);

    TriangleWindow window;
    window.setFormat(format);
    window.resize(1024,768);
    window.show();
    window.setAnimating(true);

    return app.exec();
}


