/**
 * Zillians MMO
 * Copyright (C) 2007-2009 Zillians.com, Inc.
 * For more information see http://www.zillians.com
 *
 * Zillians MMO is the library and runtime for massive multiplayer online game
 * development in utility computing model, which runs as a service for every
 * developer to build their virtual world running on our GPU-assisted machines.
 *
 * This is a close source library intended to be used solely within Zillians.com
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef TCPNETENGINE_H_
#define TCPNETENGINE_H_

#include "net-api/sys/NetEngineTemplate.h"
#include "net-api/sys/tcp/TcpConnection.h"
#include "net-api/sys/tcp/TcpConnector.h"
#include "net-api/sys/tcp/TcpAcceptor.h"
#include "net-api/sys/tcp/TcpDispatcher.h"

namespace zillians { namespace net {

class TcpNetEngine : public NetEngineTemplate<TcpConnection, TcpConnector, TcpAcceptor, TcpDispatcher>
{ };

} }

#endif /* TCPNETENGINE_H_ */
