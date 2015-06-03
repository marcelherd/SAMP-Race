/*************************************************************
 * Copyright (c) 2015 Marcel Herd
 *
 * Distributed under the MIT License.
 *
 * The full license can be reviewed in the LICENSE file, 
 * distributed with this software.
 *************************************************************/
 
/**
 * This module implements player registration and login.
 */
 
forward HandlePlayerAuthentication(playerid);
forward ExistingUserCallback(playerid);

/**
 * <summary>
 *	Checks whether a user is registered.
 *	If the user is registered, he will be prompted to login,
 *	otherwise he will be able to create an account.
 * </summary>
 *
 * <param name="playerid">
 *	ID of the player that is to be checked.
 * </param>
 */
public HandlePlayerAuthentication(playerid)
{
	new query[128];
	mysql_format(sqlConnection, query, sizeof(query), 
		"SELECT id FROM player WHERE name='%e'", 
		Name[playerid]);
	Log(query, LOG_LEVEL:DEBUG);
	
	new success = mysql_tquery(sqlConnection, query, "ExistingUserCallback", "d", playerid);
	
	if (!success)
	{
		new queryFailMessage[45];
		format(queryFailMessage, sizeof(queryFailMessage), "Query failed:\n%s", query);
		Log(queryFailMessage, LOG_LEVEL:ERROR);
	}
}

public ExistingUserCallback(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields, sqlConnection);
	
	if (!rows)
	{
		// New user, register here
	}
	else
	{
		// Existing user, login here
	}
}