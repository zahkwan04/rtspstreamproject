#include "rtspstreamer.h"
#include <QDebug>
#include <QThread>

RtspStreamer::RtspStreamer(QObject *parent) : QObject(parent), loop(nullptr), server(nullptr), isStreaming(false) {
    gst_init(nullptr, nullptr);
}

RtspStreamer::~RtspStreamer() {
    stopStreaming();
}

void RtspStreamer::startStreaming(const QString &filePath) {
    if (isStreaming) {
        qDebug() << "Streaming is already running.";
        return;
    }

    isStreaming = true;

    QThread *thread = QThread::create([this, filePath]() {
        runStreamingLoop(filePath);
    });

    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    thread->start();
}

void RtspStreamer::runStreamingLoop(const QString &filePath) {
    loop = g_main_loop_new(nullptr, FALSE);
    server = gst_rtsp_server_new();
    GstRTSPMountPoints *mounts = gst_rtsp_server_get_mount_points(server);
    GstRTSPMediaFactory *factory = gst_rtsp_media_factory_new();

    QString pipeline = QString("( filesrc location=%1 ! decodebin ! videoconvert ! x264enc ! rtph264pay name=pay0 pt=96 )").arg(filePath);
    gst_rtsp_media_factory_set_launch(factory, pipeline.toUtf8().constData());
    gst_rtsp_mount_points_add_factory(mounts, "/stream", factory);
    g_object_unref(mounts);
    gst_rtsp_server_attach(server, nullptr);

    qDebug() << "RTSP Stream started at rtsp://127.0.0.1:8554/stream";

    g_main_loop_run(loop);

    // Cleanup after loop exits
    g_main_loop_unref(loop);
    loop = nullptr;
    g_object_unref(server);
    server = nullptr;
}

void RtspStreamer::stopStreaming() {
    if (!isStreaming) return;

    qDebug() << "Stopping RTSP Stream...";
    isStreaming = false;

    if (loop) {
        g_main_loop_quit(loop);
    }
}
