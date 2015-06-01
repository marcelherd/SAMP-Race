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
	password[MAX_PASSWORD_LENGTH],
	money,
	experience,
	adminLevel,
	vehicleId,
	bool:banned
 }
 new Player[MAX_PLAYERS][PLAYER_MODEL];