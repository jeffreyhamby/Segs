/*
 * Super Entity Game Server Project
 * http://segs.sf.net/
 * Copyright (c) 2006 Super Entity Game Server Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 *
 * $Id: Client.h 253 2006-08-31 22:00:14Z malign $
 */

// Inclusion guards
#pragma once
#ifndef CHARACTERCLIENT_H
#define CHARACTERCLIENT_H

#include <string>
#include <ace/OS_NS_time.h>
#include <ace/OS_NS_sys_time.h>
#include "ServerManager.h"
#include "Client.h"
#include "GameLink.h"
#include <vector>
// skeleton class used during authentication
class Character;
class GameServer;
//class CharacterHandler;
class CharacterClient : public IClient
{
    	friend class CharacterDatabase;
		std::vector<Character *>	m_characters;
		GameServer *			    m_server;
		u8							m_max_slots;
		u64							m_game_server_acc_id;
        ACE_Time_Value              m_last_activity;
		GameLink *					m_link; // convenience pointer
		void						setMaxSlots(u8 maxs) {m_max_slots=maxs;};
		void						setGameServerAccountId(u64 id){m_game_server_acc_id=id;}
public:
					CharacterClient(){}
virtual				~CharacterClient();
		void		setServer(GameServer * val) { m_server = val; }
		Character *	getCharacter(size_t idx);

        bool		serializeFromDb();
		bool		getCharsFromDb();
		size_t		getMaxSlots();
		void		reset();
        void        connection_update() {m_last_activity = ACE_OS::gettimeofday();}
		GameLink *	link() const { return m_link; }
		void		link(GameLink * val) { m_link = val; }
};

#endif // CHARACTERCLIENT_H
