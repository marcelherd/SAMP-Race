/*************************************************************
 * Copyright (c) 2015 Marcel Herd
 *
 * Distributed under the MIT License.
 *
 * The full license can be reviewed in the LICENSE file, 
 * distributed with this software.
 *************************************************************/
 
/**
 * This module provides an interface to our MySQL database and maintains 
 * the database connection.
 *
 * The MySQL connection is created using BlueG's MySQL plugin R39-3.
 * Plugin information: http://forum.sa-mp.com/showthread.php?t=56564
 * Visit the Wiki on information on how to use the plugin.
 */

#define SQL_HOST "127.0.0.1"
#define SQL_USER "root"
#define SQL_PASSWORD "123qwe1"
#define SQL_DATABASE "samp"

forward DatabaseInit();
forward DatabaseExit();

new sqlConnection;

#if DEBUG
	new E_LOGLEVEL:logLevel = LOG_ERROR | LOG_WARNING | LOG_DEBUG;
#else
	new E_LOGLEVEL:logLevel = LOG_ERROR | LOG_WARNING;
#endif

/**
 * <summary>
 *	This function is called once when the gamemode is initialized.
 *	It creates the connection to our MySQL database. 
 *	Server will exit if connection can not be established.
 * </summary>
 */
public DatabaseInit()
{
	mysql_log(logLevel);
	sqlConnection = mysql_connect(SQL_HOST, SQL_USER, SQL_DATABASE, SQL_PASSWORD);
	
	if (mysql_errno(sqlConnection))
	{
		Log("Could not establish database connection. Quitting.", LOG_LEVEL:ERROR);
		SendRconCommand("exit");
	}
}

/**
 * <summary>
 *	This function is called once when the gamemode is exited.
 *	It destroys the connection to our MySQL database.
 * </summary>
 */
public DatabaseExit()
{
	mysql_close(sqlConnection);
}