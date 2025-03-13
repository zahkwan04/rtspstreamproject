#ifndef RTSPSTREAMER_H
#define RTSPSTREAMER_H

#include <QObject>
#include <gst/gst.h>
#undef signals
#include <gstreamer-1.0/gst/rtsp-server/rtsp-server.h>
#define signals
#include <QThread>

class RtspStreamer : public QObject {
    Q_OBJECT

public:
    explicit RtspStreamer(QObject *parent = nullptr);
    ~RtspStreamer();

public slots:
    void startStreaming(const QString &filePath);
    void stopStreaming();

private:
    GMainLoop *loop;
    GstRTSPServer *server;
    QThread *streamingThread;
    bool isStreaming;
};

#endif // RTSPSTREAMER_H
