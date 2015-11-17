/*
 * ZeroTier One - Network Virtualization Everywhere
 * Copyright (C) 2011-2015  ZeroTier, Inc.
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * --
 *
 * ZeroTier may be used and distributed under the terms of the GPLv3, which
 * are available at: http://www.gnu.org/licenses/gpl-3.0.html
 *
 * If you would like to embed ZeroTier into a commercial application or
 * redistribute it in a modified binary form, please contact ZeroTier Networks
 * LLC. Start here: http://www.zerotier.com/
 */

#include "Constants.hpp"
#include "Topology.hpp"
#include "RuntimeEnvironment.hpp"
#include "Node.hpp"
#include "Network.hpp"
#include "NetworkConfig.hpp"
#include "Buffer.hpp"

namespace ZeroTier {

#define ZT_DEFAULT_WORLD_LENGTH 494
static const unsigned char ZT_DEFAULT_WORLD[ZT_DEFAULT_WORLD_LENGTH] = {0x01,0x00,0x00,0x00,0x00,0x08,0xea,0xc9,0x0a,0x00,0x00,0x01,0x51,0x11,0x70,0xb2,0xfb,0xb8,0xb3,0x88,0xa4,0x69,0x22,0x14,0x91,0xaa,0x9a,0xcd,0x66,0xcc,0x76,0x4c,0xde,0xfd,0x56,0x03,0x9f,0x10,0x67,0xae,0x15,0xe6,0x9c,0x6f,0xb4,0x2d,0x7b,0x55,0x33,0x0e,0x3f,0xda,0xac,0x52,0x9c,0x07,0x92,0xfd,0x73,0x40,0xa6,0xaa,0x21,0xab,0xa8,0xa4,0x89,0xfd,0xae,0xa4,0x4a,0x39,0xbf,0x2d,0x00,0x65,0x9a,0xc9,0xc8,0x18,0xeb,0x80,0x31,0xa4,0x65,0x95,0x45,0x06,0x1c,0xfb,0xc2,0x4e,0x5d,0xe7,0x0a,0x40,0x7a,0x97,0xce,0x36,0xa2,0x3d,0x05,0xca,0x87,0xc7,0x59,0x27,0x5c,0x8b,0x0d,0x4c,0xb4,0xbb,0x26,0x2f,0x77,0x17,0x5e,0xb7,0x4d,0xb8,0xd3,0xb4,0xe9,0x23,0x5d,0xcc,0xa2,0x71,0xa8,0xdf,0xf1,0x23,0xa3,0xb2,0x66,0x74,0xea,0xe5,0xdc,0x8d,0xef,0xd3,0x0a,0xa9,0xac,0xcb,0xda,0x93,0xbd,0x6c,0xcd,0x43,0x1d,0xa7,0x98,0x6a,0xde,0x70,0xc0,0xc6,0x1c,0xaf,0xf0,0xfd,0x7f,0x8a,0xb9,0x76,0x13,0xe1,0xde,0x4f,0xf3,0xd6,0x13,0x04,0x7e,0x19,0x87,0x6a,0xba,0x00,0x2a,0x6e,0x2b,0x23,0x18,0x93,0x0f,0x60,0xeb,0x09,0x7f,0x70,0xd0,0xf4,0xb0,0x28,0xb2,0xcd,0x6d,0x3d,0x0c,0x63,0xc0,0x14,0xb9,0x03,0x9f,0xf3,0x53,0x90,0xe4,0x11,0x81,0xf2,0x16,0xfb,0x2e,0x6f,0xa8,0xd9,0x5c,0x1e,0xe9,0x66,0x71,0x56,0x41,0x19,0x05,0xc3,0xdc,0xcf,0xea,0x78,0xd8,0xc6,0xdf,0xaf,0xba,0x68,0x81,0x70,0xb3,0xfa,0x00,0x01,0x04,0xc6,0xc7,0x61,0xdc,0x27,0x09,0x88,0x41,0x40,0x8a,0x2e,0x00,0xbb,0x1d,0x31,0xf2,0xc3,0x23,0xe2,0x64,0xe9,0xe6,0x41,0x72,0xc1,0xa7,0x4f,0x77,0x89,0x95,0x55,0xed,0x10,0x75,0x1c,0xd5,0x6e,0x86,0x40,0x5c,0xde,0x11,0x8d,0x02,0xdf,0xfe,0x55,0x5d,0x46,0x2c,0xcf,0x6a,0x85,0xb5,0x63,0x1c,0x12,0x35,0x0c,0x8d,0x5d,0xc4,0x09,0xba,0x10,0xb9,0x02,0x5d,0x0f,0x44,0x5c,0xf4,0x49,0xd9,0x2b,0x1c,0x00,0x01,0x04,0x6b,0xbf,0x2e,0xd2,0x27,0x09,0x8a,0xcf,0x05,0x9f,0xe3,0x00,0x48,0x2f,0x6e,0xe5,0xdf,0xe9,0x02,0x31,0x9b,0x41,0x9d,0xe5,0xbd,0xc7,0x65,0x20,0x9c,0x0e,0xcd,0xa3,0x8c,0x4d,0x6e,0x4f,0xcf,0x0d,0x33,0x65,0x83,0x98,0xb4,0x52,0x7d,0xcd,0x22,0xf9,0x31,0x12,0xfb,0x9b,0xef,0xd0,0x2f,0xd7,0x8b,0xf7,0x26,0x1b,0x33,0x3f,0xc1,0x05,0xd1,0x92,0xa6,0x23,0xca,0x9e,0x50,0xfc,0x60,0xb3,0x74,0xa5,0x00,0x01,0x04,0xa2,0xf3,0x4d,0x6f,0x27,0x09,0x9d,0x21,0x90,0x39,0xf3,0x00,0x01,0xf0,0x92,0x2a,0x98,0xe3,0xb3,0x4e,0xbc,0xbf,0xf3,0x33,0x26,0x9d,0xc2,0x65,0xd7,0xa0,0x20,0xaa,0xb6,0x9d,0x72,0xbe,0x4d,0x4a,0xcc,0x9c,0x8c,0x92,0x94,0x78,0x57,0x71,0x25,0x6c,0xd1,0xd9,0x42,0xa9,0x0d,0x1b,0xd1,0xd2,0xdc,0xa3,0xea,0x84,0xef,0x7d,0x85,0xaf,0xe6,0x61,0x1f,0xb4,0x3f,0xf0,0xb7,0x41,0x26,0xd9,0x0a,0x6e,0x00,0x01,0x04,0x80,0xc7,0xc5,0xd9,0x27,0x09};

Topology::Topology(const RuntimeEnvironment *renv) :
	RR(renv),
	_amRoot(false)
{
	std::string alls(RR->node->dataStoreGet("peers.save"));
	const uint8_t *all = reinterpret_cast<const uint8_t *>(alls.data());
	RR->node->dataStoreDelete("peers.save");

	Buffer<ZT_PEER_SUGGESTED_SERIALIZATION_BUFFER_SIZE> *deserializeBuf = new Buffer<ZT_PEER_SUGGESTED_SERIALIZATION_BUFFER_SIZE>();
	unsigned int ptr = 0;
	while ((ptr + 4) < alls.size()) {
		try {
			const unsigned int reclen = ( // each Peer serialized record is prefixed by a record length
					((((unsigned int)all[ptr]) & 0xff) << 24) |
					((((unsigned int)all[ptr + 1]) & 0xff) << 16) |
					((((unsigned int)all[ptr + 2]) & 0xff) << 8) |
					(((unsigned int)all[ptr + 3]) & 0xff)
				);
			unsigned int pos = 0;
			deserializeBuf->copyFrom(all + ptr,reclen + 4);
			SharedPtr<Peer> p(Peer::deserializeNew(RR->identity,*deserializeBuf,pos));
			ptr += pos;
			if (!p)
				break; // stop if invalid records
			if (p->address() != RR->identity.address())
				_peers.set(p->address(),p);
		} catch ( ... ) {
			break; // stop if invalid records
		}
	}
	delete deserializeBuf;

	clean(RR->node->now());

	std::string dsWorld(RR->node->dataStoreGet("world"));
	World cachedWorld;
	if (dsWorld.length() > 0) {
		try {
			Buffer<ZT_WORLD_MAX_SERIALIZED_LENGTH> dswtmp(dsWorld.data(),(unsigned int)dsWorld.length());
			cachedWorld.deserialize(dswtmp,0);
		} catch ( ... ) {
			cachedWorld = World(); // clear if cached world is invalid
		}
	}
	World defaultWorld;
	{
		Buffer<ZT_DEFAULT_WORLD_LENGTH> wtmp(ZT_DEFAULT_WORLD,ZT_DEFAULT_WORLD_LENGTH);
		defaultWorld.deserialize(wtmp,0); // throws on error, which would indicate a bad static variable up top
	}
	if (cachedWorld.shouldBeReplacedBy(defaultWorld,false)) {
		_setWorld(defaultWorld);
		if (dsWorld.length() > 0)
			RR->node->dataStoreDelete("world");
	} else _setWorld(cachedWorld);
}

Topology::~Topology()
{
	Buffer<ZT_PEER_SUGGESTED_SERIALIZATION_BUFFER_SIZE> pbuf;
	std::string all;

	Address *a = (Address *)0;
	SharedPtr<Peer> *p = (SharedPtr<Peer> *)0;
	Hashtable< Address,SharedPtr<Peer> >::Iterator i(_peers);
	while (i.next(a,p)) {
		if (std::find(_rootAddresses.begin(),_rootAddresses.end(),*a) == _rootAddresses.end()) {
			pbuf.clear();
			try {
				(*p)->serialize(pbuf);
				try {
					all.append((const char *)pbuf.data(),pbuf.size());
				} catch ( ... ) {
					return; // out of memory? just skip
				}
			} catch ( ... ) {} // peer too big? shouldn't happen, but it so skip
		}
	}

	RR->node->dataStorePut("peers.save",all,true);
}

SharedPtr<Peer> Topology::addPeer(const SharedPtr<Peer> &peer)
{
#ifdef ZT_TRACE
	if ((!peer)||(peer->address() == RR->identity.address())) {
		if (!peer)
			fprintf(stderr,"FATAL BUG: addPeer() caught attempt to add NULL peer" ZT_EOL_S);
		else fprintf(stderr,"FATAL BUG: addPeer() caught attempt to add peer for self" ZT_EOL_S);
		abort();
	}
#endif

	SharedPtr<Peer> np;
	{
		Mutex::Lock _l(_lock);
		SharedPtr<Peer> &hp = _peers[peer->address()];
		if (!hp)
			hp = peer;
		np = hp;
	}

	np->use(RR->node->now());
	saveIdentity(np->identity());

	return np;
}

SharedPtr<Peer> Topology::getPeer(const Address &zta)
{
	if (zta == RR->identity.address()) {
		TRACE("BUG: ignored attempt to getPeer() for self, returned NULL");
		return SharedPtr<Peer>();
	}

	{
		Mutex::Lock _l(_lock);
		const SharedPtr<Peer> *const ap = _peers.get(zta);
		if (ap) {
			(*ap)->use(RR->node->now());
			return *ap;
		}
	}

	try {
		Identity id(_getIdentity(zta));
		if (id) {
			SharedPtr<Peer> np(new Peer(RR->identity,id));
			{
				Mutex::Lock _l(_lock);
				SharedPtr<Peer> &ap = _peers[zta];
				if (!ap)
					ap.swap(np);
				ap->use(RR->node->now());
				return ap;
			}
		}
	} catch ( ... ) {
		fprintf(stderr,"EXCEPTION in getPeer() part 2\n");
		abort();
	} // invalid identity on disk?

	return SharedPtr<Peer>();
}

Identity Topology::getIdentity(const Address &zta)
{
	{
		Mutex::Lock _l(_lock);
		const SharedPtr<Peer> *const ap = _peers.get(zta);
		if (ap)
			return (*ap)->identity();
	}
	return _getIdentity(zta);
}

void Topology::saveIdentity(const Identity &id)
{
	if (id) {
		char p[128];
		Utils::snprintf(p,sizeof(p),"iddb.d/%.10llx",(unsigned long long)id.address().toInt());
		RR->node->dataStorePut(p,id.toString(false),false);
	}
}

SharedPtr<Peer> Topology::getBestRoot(const Address *avoid,unsigned int avoidCount,bool strictAvoid)
{
	const uint64_t now = RR->node->now();
	Mutex::Lock _l(_lock);

	if (_amRoot) {
		/* If I am a root server, the "best" root server is the one whose address
		 * is numerically greater than mine (with wrap at top of list). This
		 * causes packets searching for a route to pretty much literally
		 * circumnavigate the globe rather than bouncing between just two. */

		for(unsigned long p=0;p<_rootAddresses.size();++p) {
			if (_rootAddresses[p] == RR->identity.address()) {
				for(unsigned long q=1;q<_rootAddresses.size();++q) {
					const SharedPtr<Peer> *const nextsn = _peers.get(_rootAddresses[(p + q) % _rootAddresses.size()]);
					if ((nextsn)&&((*nextsn)->hasActiveDirectPath(now))) {
						(*nextsn)->use(now);
						return *nextsn;
					}
				}
				break;
			}
		}

	} else {
		/* If I am not a root server, the best root server is the active one with
		 * the lowest quality score. (lower == better) */

		unsigned int bestQualityOverall = ~((unsigned int)0);
		unsigned int bestQualityNotAvoid = ~((unsigned int)0);
		const SharedPtr<Peer> *bestOverall = (const SharedPtr<Peer> *)0;
		const SharedPtr<Peer> *bestNotAvoid = (const SharedPtr<Peer> *)0;

		for(std::vector< SharedPtr<Peer> >::const_iterator r(_rootPeers.begin());r!=_rootPeers.end();++r) {
			bool avoiding = false;
			for(unsigned int i=0;i<avoidCount;++i) {
				if (avoid[i] == (*r)->address()) {
					avoiding = true;
					break;
				}
			}
			const unsigned int q = (*r)->relayQuality(now);
			if (q <= bestQualityOverall) {
				bestQualityOverall = q;
				bestOverall = &(*r);
			}
			if ((!avoiding)&&(q <= bestQualityNotAvoid)) {
				bestQualityNotAvoid = q;
				bestNotAvoid = &(*r);
			}
		}

		if (bestNotAvoid) {
			(*bestNotAvoid)->use(now);
			return *bestNotAvoid;
		} else if ((!strictAvoid)&&(bestOverall)) {
			(*bestOverall)->use(now);
			return *bestOverall;
		}

	}

	return SharedPtr<Peer>();
}

bool Topology::isUpstream(const Identity &id) const
{
	if (isRoot(id))
		return true;
	std::vector< SharedPtr<Network> > nws(RR->node->allNetworks());
	for(std::vector< SharedPtr<Network> >::const_iterator nw(nws.begin());nw!=nws.end();++nw) {
		SharedPtr<NetworkConfig> nc((*nw)->config2());
		if (nc) {
			for(std::vector< std::pair<Address,InetAddress> >::const_iterator r(nc->relays().begin());r!=nc->relays().end();++r) {
				if (r->first == id.address())
					return true;
			}
		}
	}
	return false;
}

bool Topology::worldUpdateIfValid(const World &newWorld)
{
	Mutex::Lock _l(_lock);
	if (_world.shouldBeReplacedBy(newWorld,true)) {
		_setWorld(newWorld);
		try {
			Buffer<ZT_WORLD_MAX_SERIALIZED_LENGTH> dswtmp;
			newWorld.serialize(dswtmp,false);
			RR->node->dataStorePut("world",dswtmp.data(),dswtmp.size(),false);
		} catch ( ... ) {
			RR->node->dataStoreDelete("world");
		}
		return true;
	}
	return false;
}

void Topology::clean(uint64_t now)
{
	Mutex::Lock _l(_lock);
	Hashtable< Address,SharedPtr<Peer> >::Iterator i(_peers);
	Address *a = (Address *)0;
	SharedPtr<Peer> *p = (SharedPtr<Peer> *)0;
	while (i.next(a,p)) {
		if (((now - (*p)->lastUsed()) >= ZT_PEER_IN_MEMORY_EXPIRATION)&&(std::find(_rootAddresses.begin(),_rootAddresses.end(),*a) == _rootAddresses.end())) {
			_peers.erase(*a);
		} else {
			(*p)->clean(RR,now);
		}
	}
}

Identity Topology::_getIdentity(const Address &zta)
{
	char p[128];
	Utils::snprintf(p,sizeof(p),"iddb.d/%.10llx",(unsigned long long)zta.toInt());
	std::string ids(RR->node->dataStoreGet(p));
	if (ids.length() > 0) {
		try {
			return Identity(ids);
		} catch ( ... ) {} // ignore invalid IDs
	}
	return Identity();
}

void Topology::_setWorld(const World &newWorld)
{
	// assumed _lock is locked (or in constructor)
	_world = newWorld;
	_amRoot = false;
	_rootAddresses.clear();
	_rootPeers.clear();
	for(std::vector<World::Root>::const_iterator r(_world.roots().begin());r!=_world.roots().end();++r) {
		_rootAddresses.push_back(r->identity.address());
		if (r->identity.address() == RR->identity.address()) {
			_amRoot = true;
		} else {
			SharedPtr<Peer> *rp = _peers.get(r->identity.address());
			if (rp) {
				_rootPeers.push_back(*rp);
			} else {
				SharedPtr<Peer> newrp(new Peer(RR->identity,r->identity));
				_peers.set(r->identity.address(),newrp);
				_rootPeers.push_back(newrp);
			}
		}
	}
}

} // namespace ZeroTier
