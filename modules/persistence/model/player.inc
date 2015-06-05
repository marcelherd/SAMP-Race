/*************************************************************
 * Copyright (c) 2015 Marcel Herd
 *
 * Distributed under the MIT License.
 *
 * The full license can be reviewed in the LICENSE file, 
 * distributed with this software.
 *************************************************************/
 
/**
 * This module defines the player model.
 */
 
enum PLAYER_MODEL
{
	id,
	name[MAX_PLAYER_NAME],
	money,
	experience,
	ADMIN_MODEL:adminLevel,
	bool:banned
}
new Player[MAX_PLAYERS][PLAYER_MODEL];
new Name[MAX_PLAYERS][MAX_PLAYER_NAME];
new IP[MAX_PLAYERS][16];