#include "rtspstreamer.h"
#include <QDebug>

RtspStreamer::RtspStreamer(QObject *parent) : QObject(parent), loop(nullptr), server(nullptr), isStreaming(false) {
    gst_init(nullptr, nullptr);
}

RtspStreamer::~RtspStreamer() {
    stopStreaming();
}

void RtspStreamer::startStreaming(const QString &filePath) {
    if (isStreaming) {
        qDebug() << "Streaming is already running!";
        return;
    }

    isStreaming = true;
    streamingThread = QThread::create([=]() {
        loop = g_main_loop_new(nullptr, FALSE);
        server = gst_rtsp_server_new();
        GstRTSPMountPoints *mounts = gst_rtsp_server_get_mount_points(server);
        GstRTSPMediaFactory *factory = gst_rtsp_media_factory_new();

        // Video + Audio Pipeline
        QString pipeline = QString(
                               "( filesrc location=%1 ! decodebin name=dec "
                               "dec. ! queue ! videoconvert ! x264enc ! rtph264pay name=pay0 pt=96 "
                               "dec. ! queue ! audioconvert ! audioresample ! avenc_aac ! rtpmp4gpay name=pay1 pt=97 )"
                               ).arg(filePath);

        gst_rtsp_media_factory_set_launch(factory, pipeline.toUtf8().constData());
        gst_rtsp_mount_points_add_factory(mounts, "/stream", factory);
        g_object_unref(mounts);
        gst_rtsp_server_attach(server, nullptr);

        qDebug() << "RTSP Stream started at rtsp://127.0.0.1:8554/stream";
        g_main_loop_run(loop);
    });

    streamingThread->start();
}

void RtspStreamer::stopStreaming() {
    if (!isStreaming) return;

    qDebug() << "Stopping RTSP Stream...";
    if (loop) g_main_loop_quit(loop);
    if (server) g_object_unref(server);

    streamingThread->quit();
    streamingThread->wait();

    isStreaming = false;
    qDebug() << "RTSP Stream stopped.";
}
