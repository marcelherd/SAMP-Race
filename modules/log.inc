/*************************************************************
 * Copyright (c) 2015 Marcel Herd
 *
 * Distributed under the MIT License.
 *
 * The full license can be reviewed in the LICENSE file, 
 * distributed with this software.
 *************************************************************/
 
/**
 * This module defines a common logging interface.
 */
 
enum LOG_LEVEL
{
	DEBUG_ = 0,
	INFO = 1,
	WARNING = 2,
	ERROR = 3
}

forward Log(const message[], LOG_LEVEL:logLevel_);
forward Debug_(const message[], const timestamp[]);
forward Info(const message[], const timestamp[]);
forward Warning(const message[], const timestamp[]);
forward Error(const message[], const timestamp[]);
forward CreateTimestamp();

/**
 * <summary>
 *	Prints the desired message to stdout with a log level dependant prefix.
 *	The resulting message is displayed as: "[Log Level] (hh:mm:ss) message".
 * </summary>
 */
stock Log(const message[], LOG_LEVEL:logLevel_)
{
	switch (logLevel_)
	{
		case DEBUG_: Debug_(message, CreateTimestamp());
		case INFO: Info(message, CreateTimestamp());
		case WARNING: Warning(message, CreateTimestamp());
		case ERROR: Error(message, CreateTimestamp());
	}
}

/**
 * <summary>
 *	Prints desired mesage with debug prefix and current timestamp as hh:mm:ss.
 * </summary>
 */
stock Debug_(const message[], const timestamp[])
{
	printf("[DEBUG] (%s) %s", timestamp, message);
}

/**
 * <summary>
 *	Prints desired mesage with info prefix and current timestamp as hh:mm:ss.
 * </summary>
 */
stock Info(const message[], const timestamp[])
{
	printf("[INFO] (%s) %s", timestamp, message);
}

/**
 * <summary>
 *	Prints desired mesage with warning prefix and current timestamp as hh:mm:ss.
 * </summary>
 */
stock Warning(const message[], const timestamp[])
{
	printf("[WARNING] (%s) %s", timestamp, message);
}

/**
 * <summary>
 *	Prints desired mesage with error prefix and current timestamp as hh:mm:ss.
 * </summary>
 */
stock Error(const message[], const timestamp[])
{
	printf("[ERROR] (%s) %s", timestamp, message);
}

/**
 * <summary>
 *	This function creates a 24H timestamp formatted as hh:mm:ss.
 * </summary>
 *
 * <returns>
 *	Timestamp string formatted as hh:mm:ss.
 * </returns>
 */
stock CreateTimestamp()
{
	new hours, minutes, seconds;
	gettime(hours, minutes, seconds);
	
	new timestamp[10];
	format(timestamp, sizeof(timestamp), "%02d:%02d:%02d", hours, minutes, seconds);
	
	return timestamp;
}
 