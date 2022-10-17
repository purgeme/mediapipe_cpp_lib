#pragma once

#include<vector>
#include<list>
#include<atomic>
#include<memory>
#include<thread>

#include "gmod_api.h"
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "mediapipe/framework/calculator_framework.h"

class Observer : public IObserver
{
    public:

        Observer(const char* in_stream_name) { _stream_name = in_stream_name;}

        absl::Status AddOutputStream(std::shared_ptr<mediapipe::CalculatorGraph> graph){
        // absl::Status ObserveOutputStream(mediapipe::CalculatorGraph* graph){
            std::string presence_name(_stream_name);
            presence_name.append("_presence");

            graph->ObserveOutputStream(presence_name, [this](const mediapipe::Packet& pk)
            {
                _presence = pk.Get<bool>();

                if( _presence_callback){
                    // _callback->OnPresence(this, _presence);
                    _presence_callback(this, _presence);
                }
                return absl::OkStatus();
            });

            RET_CHECK_OK(
                graph->ObserveOutputStream(_stream_name, [this](const mediapipe::Packet& pk)
                {

                    _raw_data = pk.GetRaw();
                    _message_type = pk.GetTypeId().name();
                    if( _packet_callback){
                        // _callback->OnPacket(this);
                        _packet_callback(this);
                    }
                    _raw_data = nullptr;
                    _message_type = "";
                    return absl::OkStatus();
                })
            );
            return absl::OkStatus();
        }

        virtual void SetPresenceCallback(std::function<void(class IObserver*, bool)> in_presence_callback) override { _presence_callback = in_presence_callback; LOG(INFO) << "Setting presence callback";}
        virtual void SetPacketCallback(std::function<void(class IObserver*)> in_packet_callback) override { _packet_callback = in_packet_callback; LOG(INFO) << "Setting packet callback";}
        virtual std::string GetMessageType() override { return _message_type; }
        virtual const void* const GetData() override { return _raw_data; }

    protected:
        std::string _stream_name;
        std::function<void(class IObserver*, bool)>  _presence_callback;
        std::function<void(class IObserver*)>  _packet_callback;
        const void* _raw_data = nullptr;
        std::string _message_type;
        bool _presence = false;
};

class GMOD : public IGMOD
{
public:
    virtual bool get_camera() override;
    virtual void set_camera(bool x) override;
    virtual bool get_overlay() override;
    virtual void set_overlay(bool x) override;

    virtual void set_camera_props(int cam_id, int cam_resx, int cam_resy, int cam_fps) override;

    virtual IObserver* create_observer(const char* stream_name) override;

    virtual bool is_loaded() override;

    virtual void start(const char* filename) override;
    virtual void stop() override;

private:
    void _workerThread();
    void _shutMPPGraph();
    absl::Status _runMPPGraph();

private:
    int _cam_id;
    int _cam_resx;
    int _cam_resy;
    int _cam_fps;
    bool _show_camera;
    bool _show_overlay;
    std::string _graph_filename;


    std::unique_ptr<std::thread> _worker;
    std::atomic<bool> _run_flag;
    std::atomic<bool> _load_flag;

    std::list<std::unique_ptr<Observer>> _observers;

public:
    std::shared_ptr<mediapipe::CalculatorGraph> _graph;

};

void hello();