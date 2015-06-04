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
 *
 * Password hashing is done using Johnson_boy's Bcrypt for SA-MP plugin v2.2.3.
 * Plugin information: http://forum.sa-mp.com/showthread.php?t=453544
 * Visit the Wiki on information on how to use the plugin.
 */
 
forward HandlePlayerAuthentication(playerid);
forward ExistingUserCallback(playerid);
forward HandlePlayerRegistration(playerid);
forward PlayerRegistrationCallback(playerid);
forward HandlePlayerLogin(playerid, enteredPassword[]);
forward PlayerLoginCallback(playerid, enteredPassword[]);
forward PlayerLoginCheckCallback(playerid);

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
		new queryFailMessage[145];
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
		ShowPlayerDialog(playerid, DIALOG_REGISTRATION, DIALOG_STYLE_INPUT, "Welcome to our server", "{FFFFFF}Enter a password below to register:", "Register", "Quit");
	}
	else
	{
		// Existing user, login here
		ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_INPUT, "Welcome back", "{FFFFFF}Enter your password below:", "Login", "Quit");
	}
}

public HandlePlayerRegistration(playerid)
{
	new hashedPassword[BCRYPT_HASH_LENGTH];
	bcrypt_get_hash(hashedPassword);
	
	new query[140];
	mysql_format(sqlConnection, query, sizeof(query),
		"INSERT INTO player (name, password) VALUES ('%e', '%e')",
		Name[playerid], hashedPassword);
	Log(query, LOG_LEVEL:DEBUG);
	
	new success = mysql_tquery(sqlConnection, query, "PlayerRegistrationCallback", "d", playerid);
	
	if (!success)
	{
		new queryFailMessage[160];
		format(queryFailMessage, sizeof(queryFailMessage), "Query failed:\n%s", query);
		Log(queryFailMessage, LOG_LEVEL:ERROR);
	}
}

public PlayerRegistrationCallback(playerid)
{
	new registeredMessage[45];
	format(registeredMessage, sizeof(registeredMessage), "User %s has been registered.", Name[playerid]);
	Log(registeredMessage, LOG_LEVEL:INFO);
	SendClientMessage(playerid, COLOR_RED, "Your account has been registered successfully.");
}

public HandlePlayerLogin(playerid, enteredPassword[])
{
	new query[140];
	mysql_format(sqlConnection, query, sizeof(query),
		"SELECT password FROM player WHERE name='%e'",
		Name[playerid]);
	Log(query, LOG_LEVEL:DEBUG);
	
	new success = mysql_tquery(sqlConnection, query, "PlayerLoginCallback", "ds", playerid, enteredPassword);
	
	if (!success)
	{
		new queryFailMessage[160];
		format(queryFailMessage, sizeof(queryFailMessage), "Query failed:\n%s", query);
		Log(queryFailMessage, LOG_LEVEL:ERROR);
	}
}

public PlayerLoginCallback(playerid, enteredPassword[])
{
	new rows, fields;
	new storedPassword[BCRYPT_HASH_LENGTH];
	cache_get_data(rows, fields, sqlConnection);
	cache_get_field_content(0, "password", storedPassword, sqlConnection, sizeof(storedPassword));
	
	bcrypt_check(enteredPassword, storedPassword, "PlayerLoginCheckCallback", "d", playerid);
}

public PlayerLoginCheckCallback(playerid)
{
	if (bcrypt_is_equal())
	{
		SendClientMessage(playerid, COLOR_RED, "You have been logged in successfully.");
		
		new loggedInMessage[45];
		format(loggedInMessage, sizeof(loggedInMessage), "User %s has logged in.", Name[playerid]);
		Log(loggedInMessage, LOG_LEVEL:INFO);
	}
	else
	{
		ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_INPUT, "Welcome back", "{FF0000}ERROR: Invalid password\n{FFFFFF}Enter your password below:", "Login", "Quit");
	}
}