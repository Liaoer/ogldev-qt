#include "backend.h"
#include <QApplication>
#include <QLabel>

#ifndef QT_NO_OPENGL
#include "openglwindow.h"
#endif

int backend::start(RenderDelegate *delegate, int argc, char *argv[])
{
    QApplication app(argc, argv);
#ifndef QT_NO_OPENGL
    QSurfaceFormat format;
    format.setSamples(16);

    TriangleWindow window;
    window.setFormat(format);
    window.resize(1024,768);
    window.show();
    window.setAnimating(true);
#else
    QLabel note("OpenGL Support requireed");
    note.show();
#endif
    return app.exec();  
}
