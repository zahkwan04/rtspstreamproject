#include "rtspstreamer.h"
#include <QDebug>

RtspStreamer::RtspStreamer(QObject *parent) : QObject(parent) {
    gst_init(nullptr, nullptr);
}

void RtspStreamer::startStreaming(const QString &filePath) {
    GstRTSPServer *server;
    GstRTSPMountPoints *mounts;
    GstRTSPMediaFactory *factory;
    loop = g_main_loop_new(nullptr, FALSE);

    server = gst_rtsp_server_new();
    mounts = gst_rtsp_server_get_mount_points(server);

    factory = gst_rtsp_media_factory_new();
    QString pipeline = QString("( filesrc location=%1 ! decodebin ! videoconvert ! x264enc ! rtph264pay name=pay0 pt=96 )").arg(filePath);
    gst_rtsp_media_factory_set_launch(factory, pipeline.toUtf8().constData());
    gst_rtsp_mount_points_add_factory(mounts, "/stream", factory);
    g_object_unref(mounts);
    gst_rtsp_server_attach(server, nullptr);

    qDebug() << "RTSP Stream started at rtsp://127.0.0.1:8554/stream";
    g_main_loop_run(loop);
}
