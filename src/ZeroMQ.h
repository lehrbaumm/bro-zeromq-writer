// See the file "COPYING" for copyright.
//
// Log writer for writing to ZeroMQ

#ifndef LOGGING_WRITER_ZEROMQ_H
#define LOGGING_WRITER_ZEROMQ_H

#include <string>

#include "logging/WriterBackend.h"
#include "threading/formatters/JSON.h"
#include "Desc.h"

namespace logging { namespace writer {

class ZeroMQ : public WriterBackend {

public:
    ZeroMQ(WriterFrontend* frontend);
    ~ZeroMQ();

    static WriterBackend* Instantiate(WriterFrontend* frontend)
    {
        return new ZeroMQ(frontend);
    }

protected:
    virtual bool DoInit(const WriterBackend::WriterInfo& info, int num_fields, const threading::Field* const* fields);
    virtual bool DoWrite(int num_fields, const threading::Field* const* fields, threading::Value** vals);
    virtual bool DoSetBuf(bool enabled);
    virtual bool DoRotate(const char* rotated_path, double open, double close, bool terminating);
    virtual bool DoFlush(double network_time);
    virtual bool DoFinish(double network_time);
    virtual bool DoHeartbeat(double network_time, double current_time);

private:
    std::string GetConfigValue(const WriterInfo& info, const std::string name) const;

    threading::formatter::JSON* formatter;

    void* zmq_context;
    void* zmq_publisher;
    const char* log_path;

    std::string endpoint;
    int zmq_hwm;
    int zmq_linger;
};

}}

#endif
