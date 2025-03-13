#ifndef RTSPSTREAMER_H
#define RTSPSTREAMER_H

#include <QObject>
#include <QThread>
#include <gst/gst.h>
#undef signals
#include <gstreamer-1.0/gst/rtsp-server/rtsp-server.h>
#define signals

class RtspStreamer : public QObject {
    Q_OBJECT

public:
    explicit RtspStreamer(QObject *parent = nullptr);
    ~RtspStreamer();

    void startStreaming(const QString &filePath);
    void stopStreaming();

private:
    QThread streamingThread;
    GMainLoop *loop;
    GstRTSPServer *server;
    bool isStreaming;

    void runStreamingLoop(const QString &filePath);
};

#endif // RTSPSTREAMER_H
