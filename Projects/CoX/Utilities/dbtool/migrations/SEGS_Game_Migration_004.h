/*
 * SEGS - Super Entity Game Server - dbtool Migration
 * http://www.segs.io/
 * Copyright (c) 2006 - 2019 SEGS Team (see AUTHORS.md)
 * This software is licensed under the terms of the 3-clause BSD License. See LICENSE.md for details.
 */

#pragma once
#include "Utilities/dbtool/DBMigrationStep.h"

class SEGS_Game_Migration_004 : public DBMigrationStep
{
private:
    int m_target_version = 4;
    QString m_name = SEGS_GAME_DB_NAME;
    std::vector<TableSchema> m_table_schemas = {
        {"db_version", 4, "2018-03-05 00:55:01"},
        {"characters", 5, "2018-03-05 00:54:27"},
    };

public:
    int getTargetVersion() const override { return m_target_version; }
    QString getName() const override { return m_name; }
    std::vector<TableSchema> getTableVersions() const override { return m_table_schemas; }

    // execute the migration
    bool execute(DBConnection *db) override
    {
        // update database table schemas here
        // first: add columns to the characters table
        db->m_query->prepare("ALTER TABLE 'characters' ADD 'gui' BLOB, 'keybinds' BLOB");
        if(!db->m_query->exec())
            return false;

        // gui and keybinds are populated by the server. We're done.
        return true;
    }
};
