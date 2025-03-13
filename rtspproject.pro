QT += core gui widgets
CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    rtspstreamer.cpp

HEADERS += \
    mainwindow.h \
    rtspstreamer.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += /usr/include/gstreamer-1.0 \
                /usr/lib/x86_64-linux-gnu/gstreamer-1.0/include

LIBS += -lgstapp-1.0 -lgstbase-1.0 -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0

# GStreamer configuration for Windows
win32 {
    # Update these paths to match your GStreamer installation
    GSTREAMER_DIR = C:/gstreamer/1.0/msvc_x86_64

    # If the above path doesn't work, try these common installation paths
    !exists($${GSTREAMER_DIR}) {
        GSTREAMER_DIR = C:/gstreamer/1.0/mingw_x86_64
    }
    !exists($${GSTREAMER_DIR}) {
        GSTREAMER_DIR = C:/gstreamer/1.0/x86_64
    }

    INCLUDEPATH += \
        $${GSTREAMER_DIR}/include \
        $${GSTREAMER_DIR}/include/gstreamer-1.0 \
        $${GSTREAMER_DIR}/include/glib-2.0 \
        $${GSTREAMER_DIR}/lib/pkgconfig \
        $${GSTREAMER_DIR}/include/glib-2.0/include \
        $${GSTREAMER_DIR}/lib/glib-2.0/include


    LIBS += \
        -L$${GSTREAMER_DIR}/lib \
        -lgstreamer-1.0 \
        -lgobject-2.0 \
        -lglib-2.0 \
        -lgstrtsp-1.0 \
        -lgstrtp-1.0 \
        -lgstnet-1.0 \
        -lgstbase-1.0 \
        -lgstapp-1.0 \
        -lgstvideo-1.0 \
        -lgstrtspserver-1.0

    # Make sure GStreamer DLLs are in the PATH at runtime
    QMAKE_POST_LINK += $$quote(echo "Remember to add $${GSTREAMER_DIR}/bin to your PATH")
}
