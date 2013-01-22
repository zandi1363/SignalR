#pragma once

class IConnectionHandler;
class IClientTransport;

#include <string>
#include "IHttpClient.h"
#include "NegotiateResponse.h"
#include "IClientTransport.h"

using namespace std;

class Connection
{
public:
    enum State
    {
        Connecting,
        Connected,
        Reconnecting,
        Disconnecting,
        Disconnected,
    };

    Connection(string url, IConnectionHandler* handler);
    ~Connection(void);

    void Start();
    void Start(IClientTransport* tranport);
    void Start(IHttpClient* client);
    void Stop();
    void Send(string data);
    
    State GetState();
    string GetConnectionId();
    string GetConnectionToken();
    string GetGroupsToken();
    IClientTransport* GetTransport();
    string GetUrl();
    string GetMessageId();

    // Transport API
    bool ChangeState(State oldState, State newState);
    bool EnsureReconnecting();
    void OnError(exception error);
    void OnReceived(string data);

    void SetConnectionState(NegotiateResponse negotiateResponse);

private:
    string mUrl;
    string mConnectionId;
    string mConnectionToken;
    string mGroupsToken;
    string mMessageId;
    State mState;
    IClientTransport* mTransport;
    IConnectionHandler* mHandler;

    static void OnTransportStartCompleted(exception* error, void* state);
    static void OnNegotiateCompleted(NegotiateResponse* negotiateResponse, exception* error, void* state);
};

