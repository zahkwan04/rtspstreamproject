#ifndef RTSPSTREAMER_H
#define RTSPSTREAMER_H

#include <QObject>
#include <gst/gst.h>
#undef signals
#include <gstreamer-1.0/gst/rtsp-server/rtsp-server.h>
#define signals

class RtspStreamer : public QObject {
    Q_OBJECT

public:
    explicit RtspStreamer(QObject *parent = nullptr);
    void startStreaming(const QString &filePath);

private:
    GMainLoop *loop;
};

#endif // RTSPSTREAMER_H
