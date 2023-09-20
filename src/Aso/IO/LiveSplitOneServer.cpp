/*
 * Copyright (C) 2022-2023  Tyler O'Brien <hello@tylerobrien.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

/*
|--------------------------------------------------------------------------
| Includes
|--------------------------------------------------------------------------
*/

#include <Aso/IO/LiveSplitOneServer.hpp>
#include <Aso/LiveSplit.hpp>

#include <thread>
#include <ws.h>

/*
|--------------------------------------------------------------------------
| Locals
|--------------------------------------------------------------------------
*/

bool _aso_server_alive = false;

uint16_t _aso_server_port = 8080;
uint32_t _aso_server_timeoutMs = 1000;

std::thread _aso_server_main;
aso::LiveSplitOneServer::ConnectFunction _aso_server_connect = NULL;
aso::LiveSplitOneServer::DisconnectFunction _aso_server_disconnect = NULL;
aso::LiveSplitOneServer::UpdateFunction _aso_server_update = NULL;

/*
|--------------------------------------------------------------------------
| Functions
|--------------------------------------------------------------------------
*/

namespace aso {

/**
 *
 */
void _ws_write(ws_cli_conn_t *client, const char *message)
{
    ws_sendframe_txt(client, message);
}

/**
 *
 */
void _ws_on_open(ws_cli_conn_t *client)
{
    LiveSplit::connect(
        std::bind(&_ws_write, client, std::placeholders::_1)
    );

    _aso_server_connect();
    _aso_server_alive = true;

    while (_aso_server_alive)
    {
        _aso_server_update();
    }
}

/**
 *
 */
void _ws_on_close(ws_cli_conn_t *client)
{
    LiveSplit::disconnect();

    _aso_server_disconnect();
    _aso_server_alive = false;
}

/**
 *
 */
void _ws_on_recv(ws_cli_conn_t *client, const unsigned char *msg, uint64_t size, int type)
{
    //
}

/**
 *
 */
void _ws_run()
{
    ws_events evs;

    evs.onopen = &_ws_on_open;
    evs.onclose = &_ws_on_close;
    evs.onmessage = &_ws_on_recv;

    ws_socket(&evs, _aso_server_port, 0, _aso_server_timeoutMs);
}

/**
 *
 */
void LiveSplitOneServer::run(ConnectFunction connect, DisconnectFunction disconnect, UpdateFunction update)
{
    run(connect, disconnect, update, 8080, 1000);
}

/**
 *
 */
void LiveSplitOneServer::run(ConnectFunction connect, DisconnectFunction disconnect, UpdateFunction update, uint16_t port)
{
    run(connect, disconnect, update, port, 1000);
}

/**
 *
 */
void LiveSplitOneServer::run(ConnectFunction connect, DisconnectFunction disconnect, UpdateFunction update, uint16_t port, uint32_t timeoutMs)
{
    _aso_server_connect    = connect;
    _aso_server_disconnect = disconnect;
    _aso_server_update     = update;
    _aso_server_port       = port;
    _aso_server_timeoutMs  = timeoutMs;
    _aso_server_main       = std::thread(&_ws_run);
}

}
