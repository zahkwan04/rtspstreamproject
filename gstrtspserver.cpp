#include "mainwindow.h"
#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>
#include <QDebug>

void media_configure(GstRTSPMediaFactory *factory, GstRTSPMedia *media, gpointer user_data) {
    GstElement *pipeline = gst_rtsp_media_get_element(media);
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
}

GstRtspServerThread::GstRtspServerThread(QObject *parent) : QThread(parent) {}

void GstRtspServerThread::run() {
    start_rtsp_server();
}

void GstRtspServerThread::start_rtsp_server() {
    gst_init(nullptr, nullptr);

    GstRTSPServer *server = gst_rtsp_server_new();
    GstRTSPMountPoints *mounts = gst_rtsp_server_get_mount_points(server);
    GstRTSPMediaFactory *factory = gst_rtsp_media_factory_new();

    gst_rtsp_media_factory_set_launch(factory,
                                      "( appsrc name=mysource is-live=true format=3 ! videoconvert ! x264enc ! rtph264pay name=pay0 pt=96 )");

    g_signal_connect(factory, "media-configure", G_CALLBACK(media_configure), nullptr);
    gst_rtsp_mount_points_add_factory(mounts, "/stream", factory);

    gst_rtsp_server_attach(server, nullptr);

    qDebug() << "RTSP Stream available at rtsp://127.0.0.1:8554/stream";

    GMainLoop *loop = g_main_loop_new(nullptr, FALSE);
    g_main_loop_run(loop);
}
